#ifndef GAME_H
#define GAME_H

#include <SDL/SDL.h>
#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <unordered_map>

#include "Input.h"

using namespace std;
using namespace glm;

enum class WindowFlag { WINDOWED, FULLSCREEN, EXCLUSIVE_FULLSCREEN, BORDERLESS };

namespace Engine {
	class Game :
		public Engine::Input
	{
	public:
		Game();
		~Game();
		void Start(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
		void Err(string errorString);

	protected:
		virtual void Init() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		GLuint BuildShader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void UseShader(GLuint program);
		unsigned int GetScreenHeight();
		unsigned int GetScreenWidth();

	private:
		unordered_map<unsigned int, string> _mapNames;
		unordered_map<string, bool> _keyMap;
		unordered_map<string, bool> _previousKeyMap;
		vec2 _mouseCoords;
		SDL_GameController* controller;
		unsigned int screenWidth, screenHeight, lastFrame = 0, last = 0, _fps = 0, fps = 0;
		float targetFrameTime = 0, timeScale;
		float GetDeltaTime();
		void GetFPS();
		void LimitFPS();
		void CheckShaderErrors(GLuint shader, string type);
		void PrintFPS();
	};
}
#endif