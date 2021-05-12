#ifndef TRAP_H
#define TRAP_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Trap :
	public Engine::Game
{
public:
	Trap(float swtile, float shtile, float xtile, float ytile);
	~Trap();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	float xposarray[2] = { 400, 840 };
	float yposarray[2] = { 800, 340 };
	float heightarray[2] = { 50, 50};
	float widtharray[2] = { 50, 50 };
	void BuildTrapSprite();
	void DrawTrapSprite(float width, float height, float x, float y);

private:
	float swtile = 0, shtile = 0, xtile = 0, ytile = 0, frame_dur = 0, frame_width2 = 0, frame_height2 = 0, oldxpos = 0, oldypos = 0, xpos2 = 0, ypos2 = 0, gravity = 0;
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2;
};
#endif
