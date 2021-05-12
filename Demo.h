#ifndef DEMO_H
#define DEMO_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"
#include "Input.h"
#include "Player.h"
#include "Tile.h"
#include "Menu.h"
#include "Audio.h"
#include "Trap.h"
#include "Door.h"


#define NUM_FRAMES 3
#define FRAME_DUR 80

using namespace glm;

class Demo :
	public Engine::Game
{
public:
	Demo();
	~Demo();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void RenderPlay();
	Player* player;
	Tile* tile;
	Menu* menu;
	Audio* audio;
	Trap* trap;
	Door* door;

private:
	float  xpos2 = 0, ypos2 = 0, gravity = 0;
	bool play = true;
	bool gameover = false;
	bool finish = false;
	int timeleft = 20;
	int millisecond = 500;
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2;
	void ControlPlayerSprite(float deltaTime);
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
};
#endif
