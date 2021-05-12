#ifndef TILE_H
#define TILE_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Tile :
	public Engine::Game
{
public:
	Tile(float swtile, float shtile, float xtile, float ytile);
	~Tile();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	float xposarray[5] = { 0, 960, 720, 300, 1200};
	float yposarray[5] = { 860, 300, 400, 250, 600};
	float heightarray[5] = { 100, 100, 100, 100, 100};
	float widtharray[5] = { 960, 200, 200, 200, 300};
	void BuildCrateSprite();
	void DrawCrateSprite(float width, float height, float x, float y);

private:
	float swtile = 0, shtile = 0, xtile = 0, ytile = 0, frame_dur = 0, frame_width2 = 0, frame_height2 = 0, oldxpos = 0, oldypos = 0, xpos2 = 0, ypos2 = 0, gravity = 0;
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2;
};
#endif