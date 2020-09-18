#include "Text.h"
#include "VertexBuffer.h"
#include "Shader.h"

gltext::Text::Text(VertexBuffer& buffer)
{
    this->vao = &buffer;

    this->scale_ = 1.f;
    color_ = {0.f,0.f,0.f};
    position_ = {0.f,0.f};
    TextWidth = 0;
    TextHeight = 0;
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
        //std::cout << "Failed to load font" << std::endl;
        throw std::runtime_error("Failed to load font");
    }
    FT_Set_Pixel_Sizes(face, 0, height);
}

void gltext::Text::genGlyphList()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

    for (GLubyte c = 0; c < 128; c++)
    {
        // Load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "Failed to load Glyph" << std::endl;
            continue;
        }
        Glyph character = {
            texture = vao->addGlyphTexture(face),
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        characters.insert(std::pair<GLchar, Glyph>(c, character));
    }
    clean();
}

void gltext::Text::RenderText(string text, Shader* shader)
{
    projection.setOrtho(screenW_, screenH_);
    shader->setShader();
    shader->setUniform("projection", projection.getMatrix());
    shader->setUniform("textColor", { color_.r, color_.g, color_.b });
    int by = 0, max_y = 0;
    float x = position_.x;
    float y = position_.y;
    vao->staticDraw();
    for (std::string::const_iterator c = text.begin(); c != text.end(); ++c)
    {
        Glyph ch = characters[*c];
    	
        if (*c == '\n') 
        { // Set position of the new line
	        y -= (ch.Size.y + ch.Bearing.y)*1.1f*scale_; 
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
    TextWidth = x-position_.x;
    vao->unbindBuffer();
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

void gltext::Text::clean()
{
    FT_Done_Face(face);
    FT_Done_FreeType(lib);
}

FT_UInt gltext::Text::screenW_ = 0;
FT_UInt gltext::Text::screenH_ = 0;