#ifndef PLAYER_H
#define PLAYER_H


#include <SOIL/SOIL.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

#define NUM_FRAMES 3
#define FRAME_DUR 80

using namespace glm;

class Player :
	public Engine::Game
{
public:
	Player(float sw, float sh, float x, float y);
	~Player();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	float frame_width = 0, frame_height = 0, frame_width2 = 0, frame_height2 = 0;
	void DrawPlayerSprite();
	void BuildPlayerSprite();
	void UpdatePlayerSpriteAnim(float deltaTime);
	bool IsCollided(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
	bool walk_anim = false, onGround = true;
	unsigned int frame_idx = 0, flip = 0;
	float xstart = 0, ystart = 0, sw = 0, sh = 0, frame_dur = 0, oldxpos = 0, oldypos = 0, xpos = 0, ypos = 0, yground = 0, xpos2 = 0, ypos2 = 0, gravity = 0, xVelocity = 0, yVelocity = 0, yposGround = 0;

private:
	GLuint VBO, VAO, EBO, texture, program, VBO2, VAO2, EBO2, texture2, program2;
	
};
#endif
