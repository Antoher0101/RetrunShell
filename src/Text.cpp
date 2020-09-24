#include "Text.h"

#include "VertexBuffer.h"
#include "Shader.h"

gltext::Text::Text(VertexBuffer& buffer)
{
    this->vao = &buffer;

    this->scale_ = 1.f;
    color_ = {0.f,0.f,0.f};
	outline_color_ = { 0.f,0.f,0.f };
    position_ = {0.f,0.f};
    TextWidth = 0;
    TextHeight = 0;

    outlineThickness = 2;
}

void gltext::Text::init(const std::string& font_name, unsigned int height)
{
    std::string font = "resource/fonts/" + font_name;
    if (FT_Init_FreeType(&lib))
    {
        std::cout << "Could not init FreeType Library" << std::endl;
    }
    if (FT_New_Face(lib, font.c_str(), 0, &face))
    {
        std::cout << "Failed to load font" << std::endl;
        throw std::runtime_error("Failed to load font");
    }
    FT_Set_Pixel_Sizes(face, 0, height);
    genGlyphList();
}

void gltext::Text::genOutline()
{
    for (GLubyte ch = 0; ch < 128; ch++)
    {
        FT_Stroker_New(lib, &stroker);
        //  2 * 64 result in 2px outline
        FT_Stroker_Set(stroker, outlineThickness * 64, FT_STROKER_LINECAP_ROUND, FT_STROKER_LINEJOIN_ROUND, 0);
       
        if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_NO_BITMAP))
            throw std::runtime_error("FT_Load_Glyph failed");
    	
        if (FT_Get_Glyph(face->glyph, &glyph))
            throw std::runtime_error("FT_Get_Glyph failed");

        FT_Glyph_StrokeBorder(&glyph, stroker, false, true);
        
        FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, nullptr, true);
        FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(glyph);

        Glyph ch_glyph{
            texture = vao->addGlyphTexture(bitmap_glyph),
            glm::ivec2(bitmap_glyph->bitmap.width, bitmap_glyph->bitmap.rows),
            glm::ivec2(bitmap_glyph->left, bitmap_glyph->top),
            face->glyph->advance.x
        };
        outlines.insert(std::pair<GLchar, Glyph>(ch, ch_glyph));
    }
    FT_Stroker_Done(stroker);
}

void gltext::Text::genGlyphList()
{
    for (GLubyte ch = 0; ch < 128; ch++)
    {
        if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
            throw std::runtime_error("FT_Load_Glyph failed");
    	
        if (FT_Get_Glyph(face->glyph, &glyph))
            throw std::runtime_error("FT_Get_Glyph failed");

        FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, nullptr, true);
        FT_BitmapGlyph bitmap_glyph = reinterpret_cast<FT_BitmapGlyph>(glyph);
        
        Glyph ch_glyph{
            texture = vao->addGlyphTexture(bitmap_glyph),
            glm::ivec2(bitmap_glyph->bitmap.width, bitmap_glyph->bitmap.rows),
            glm::ivec2(bitmap_glyph->left, bitmap_glyph->top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Glyph>(ch, ch_glyph));
    }
    genOutline();
    clean();
}

void gltext::Text::setPos(GLint x, GLint y)
{
    position_ = { x,y };
}

void gltext::Text::setPos(int alignment) // Bug: Positioning error related to calculating 'TextWidth'
{
	switch (alignment)
	{
    case 0x2B: position_ = { 0,screenH_-TextHeight }; break;                                   // LEFT/TOP
    case 0x20: position_ = { (screenW_ - TextWidth) / 2,screenH_ - TextHeight }; break;        // TOP
    case 0x2F: position_ = { (screenW_ - TextWidth) / 2,screenH_ - TextHeight }; break;        // TOP
    case 0x2C: position_ = { screenW_-TextWidth,screenH_ - TextHeight }; break;                // RIGHT/TOP
    case 0x0B: position_ = { 0,screenH_ / 2 }; break;                                          // LEFT
    case 0x0F: position_ = { (screenW_ - TextWidth) / 2,(screenH_ - TextHeight) / 2 }; break;  // CENTER
    case 0x38: position_ = { (screenW_ - TextWidth) / 2,(screenH_ - TextHeight) / 2 }; break;  // CENTER
    case 0x0C: position_ = { screenW_ - TextWidth,screenH_/2 }; break;                         // RIGHT
    case 0x1B: position_ = { 0, MaxBearingY }; break;                                            // LEFT/BOTTOM
    case 0x18: position_ = { (screenW_ - TextWidth) / 2,MaxBearingY }; break;                    // BOTTOM
    case 0x1F: position_ = { (screenW_ - TextWidth) / 2,MaxBearingY }; break;                    // BOTTOM
    case 0x1C: position_ = { screenW_ - TextWidth,MaxBearingY }; break;                          // RIGHT/BOTTOM
    default: position_ = { 0,0 }; break;
	}
}

void gltext::Text::setScale(GLfloat scale)
{
    scale_ = scale;
}

void gltext::Text::setColor(GLfloat r, GLfloat g, GLfloat b)
{
    color_ = { r,g,b };
}

inline void gltext::Text::setOutline(bool setoutline)
{
	outlineEnabled = setoutline;
}

void gltext::Text::RenderText(Shader* shader, const string& text, const string& param)
{
    projection.setOrtho(screenW_, screenH_);
    text_ = text+param;
    shader_ = shader;
    glDisable(GL_DEPTH_TEST);
    if(outlineEnabled)displayOutline();
    displayText();
    glEnable(GL_DEPTH_TEST);
}

void gltext::Text::displayText()
{
    shader_->setShader();
    shader_->setUniform("projection", projection.getMatrix());
    shader_->setUniform("textColor", { color_.r, color_.g, color_.b });
	
    int by = 0, max_y = 0;
    float x = position_.x;
    float y = position_.y;
    vao->staticDraw();
    for (std::string::const_iterator c = text_.begin(); c != text_.end(); ++c)
    {
        Glyph ch = characters[*c];

        GLfloat xpos = x + ch.Bearing.x * scale_;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale_;

        GLfloat w = ch.Size.x * scale_;
        GLfloat h = ch.Size.y * scale_;

        if (*c == '\n')
        { // Set position of the new line
            y -= (ch.Size.y + ch.Bearing.y) * 1.1f * scale_;
            x -= x - position_.x;
            continue;
        }
        // Update VBO for each character
        std::vector<glm::vec4> vertices = {
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos, ypos, 0.0, 1.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos + w, ypos + h, 1.0, 0.0 }
        };
        x += (ch.Advance >> 6) * scale_;
        vao->updateBuffer(ch, vertices);

        if (by < ch.Size.y - ch.Bearing.y)
            MaxBearingY = by = ch.Size.y - ch.Bearing.y;
        if (max_y < ch.Size.y)
            TextHeight = max_y = ch.Size.y;
    }
    TextWidth = x - position_.x;
    vao->unbindBuffer();
}

void gltext::Text::displayOutline()
{
    shader_->setShader();
    shader_->setUniform("projection", projection.getMatrix());
    shader_->setUniform("textColor", { outline_color_.r, outline_color_.g, outline_color_.b });
	
    int by = 0, max_y = 0;
    float x = position_.x;
    float y = position_.y;
    vao->staticDraw();
    for (std::string::const_iterator c = text_.begin(); c != text_.end(); ++c)
    {
        Glyph ch = outlines[*c];

        if (*c == '\n')
        { // Set position of the new line
            y -= (ch.Size.y + ch.Bearing.y) * 1.1f * scale_;
            x -= x - position_.x;
            continue;
        }
        GLfloat xpos = x + ch.Bearing.x * scale_;
        GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale_;

        GLfloat w = ch.Size.x * scale_;
        GLfloat h = ch.Size.y * scale_;
        // Update VBO for each character
        std::vector<glm::vec4> vertices = {
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos, ypos, 0.0, 1.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos, ypos + h, 0.0, 0.0 },
            { xpos + w, ypos, 1.0, 1.0 },
            { xpos + w, ypos + h, 1.0, 0.0 }
        };
        x += (ch.Advance >> 6) * scale_;
        vao->updateBuffer(ch, vertices);

        if (by < ch.Size.y - ch.Bearing.y)
            MaxBearingY = by = ch.Size.y - ch.Bearing.y;
        if (max_y < ch.Size.y)
            TextHeight = max_y = ch.Size.y;
    }
    TextWidth = x - position_.x;
    vao->unbindBuffer();
}

void gltext::Text::clean()
{
    FT_Done_Glyph(glyph);
    FT_Done_Face(face);
    FT_Done_FreeType(lib);
}

FT_UInt gltext::Text::screenW_ = 0;
FT_UInt gltext::Text::screenH_ = 0;