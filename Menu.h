#ifndef MENU_H
#define MENU_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>
#include <SDL/SDL_thread.h>

#include <ft2build.h>
#include <freetype/freetype.h>
#include <map>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

#define FONTSIZE 40
#define FONTNAME "ChocolateCoveredRaindrops.ttf"
#define NUM_BUTTON 3

struct Character {
	GLuint TextureID; // ID handle of the glyph texture
	ivec2 Size; // Size of glyph
	ivec2 Bearing; // Offset from baseline to left/top of glyph
	GLuint Advance; // Offset to advance to next glyph
};

class Menu :
	public Engine::Game
{
public:
	Menu(float sw, float sh);
	~Menu();
	float button_width[NUM_BUTTON], button_height[NUM_BUTTON], hover_button_width[NUM_BUTTON], hover_button_height[NUM_BUTTON];
	float sw = 0, sh = 0;
	int activeButtonIndex = -2;
	void RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vec3 color);
	void InitText();
	void InitButton();
	void RenderButton();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	GLuint program;

private:
	map<GLchar, Character> Characters;
	GLuint texture[NUM_BUTTON], hover_texture[NUM_BUTTON], VBO, VBO2, VAO, VAO2;
};
#endif

