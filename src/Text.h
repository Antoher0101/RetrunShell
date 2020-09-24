#pragma once
#include  <map>
#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"

#include "mx/Projection.h"

#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#include FT_STROKER_H

// Alignment types
#define AT_LEFT 0x00B
#define AT_RIGHT 0x00C
#define AT_CENTER 0x00F
#define AT_TOP 0x020
#define AT_BOTTOM 0x018

class Shader;
class VertexBuffer;

using std::string;

namespace gltext
{
	struct Glyph {
		GLuint     TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing; // Offset from baseline to left/top of glyph
		GLuint     Advance; // Offset to advance to next glyph
	};
	/*
	 * After creating a class object with a buffer(and create an empty textbuffer), you need to initialize the freetype using
	 * void init(font_name, height)
	 *
	 * Then, generate list of the symbols using void genGlyphList()
	 *
	 * After that create a shader with no attributes and link it
	 */
	class Text
	{
		FT_Library lib;
		FT_Face face;
		FT_Stroker stroker;
		FT_Glyph glyph;
		
		GLuint texture;
		VertexBuffer* vao;
		
		GLfloat scale_;
		glm::vec3 color_;
		glm::vec3 outline_color_;
		glm::ivec2 position_;

		GLint MaxBearingY; // Max glyph offset along the y-axis
		GLint TextWidth; 
		GLint TextHeight;
		GLint outlineThickness;
		
		string text_;
		Shader* shader_;
		
		mx::Projection projection;
		
		FT_Bool outlineEnabled = false;

		static FT_UInt screenW_;
		static FT_UInt screenH_;
		std::map<GLchar, Glyph> characters;
		std::map<GLchar, Glyph> outlines;
		
		void genGlyphList();
		void genOutline();
		void displayText();
		void displayOutline();
		
		void clean();
	public:
		Text(VertexBuffer& buffer);
		void init(const string& font_name, unsigned int height);
		
		
		void RenderText(Shader* shader, const string& text, const string& param = "");
		
		void setPos(GLint x, GLint y);
		void setPos(int alignment);
		
		void setScale(GLfloat scale);
		void setColor(GLfloat r, GLfloat g, GLfloat b);

		void setOutline(bool setoutline = 1);
		void setOutlineThickness(GLint thickness) { outlineThickness = thickness; }
		void setOutlineColor(GLfloat r, GLfloat g, GLfloat b) { outline_color_ = { r,g,b }; }
		
		static void updateScreenSize(FT_UInt w, FT_UInt h) { screenW_ = w; screenH_ = h; }
	};

}