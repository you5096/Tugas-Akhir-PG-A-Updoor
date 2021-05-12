#ifndef AUDIO_H
#define AUDIO_H


#include <SOIL/SOIL.h>

#include <SDL/SDL_mixer.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Game.h"

using namespace glm;

class Audio :
	public Engine::Game
{
public:
	Audio();
	~Audio();
	virtual void Init();
	virtual void Update(float deltaTime);
	virtual void Render();
	void InitAudio();
	void AddInputs();
private:
	Mix_Chunk* sound = NULL;
	Mix_Music* music = NULL;
	int sfx_channel = -1;
};
#endif

