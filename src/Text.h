#pragma once
#include  <map>
#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H

class VertexBuffer;
namespace gltext
{
	struct Glyph {
		GLuint     TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint     Advance;
	};
	
	class Text
	{
		FT_Library lib;
		FT_Face face;
		
		std::map<GLchar, Glyph> characters;
	public:
		GLuint texture;
		
		Text();
		
		void init(const char* font_name, unsigned int height);
		void make_flist(VertexBuffer* vao);
		void clean();
	};

}