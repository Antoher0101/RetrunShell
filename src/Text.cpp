#include "Text.h"
#include "VertexBuffer.h"

gltext::Text::Text()
{
}

void gltext::Text::init(const char* font_name, unsigned int height)
{
    if (FT_Init_FreeType(&lib))
    {
        std::cout << "Could not init FreeType Library" << std::endl;
    }
    if (FT_New_Face(lib, "resource/fonts/arial.ttf", 0, &face))
    {
        //std::cout << "Failed to load font" << std::endl;
        throw std::runtime_error("Failed to load font");
    }
    FT_Set_Pixel_Sizes(face, 0, height);
}

void gltext::Text::make_flist(VertexBuffer* vao)
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

void gltext::Text::clean()
{
    FT_Done_Face(face);
    FT_Done_FreeType(lib);
}
