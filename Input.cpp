#include "Input.h"

Engine::Input::Input()
{
}

Engine::Input::~Input()
{
}

void Engine::Input::OpenGameController()
{
	if (SDL_NumJoysticks() > 0) {
		if (SDL_IsGameController(0))
		{
			controller = SDL_GameControllerOpen(0);
			if (controller != nullptr)cout << "Game Controller is Detected" << endl;
		}
	}
}

void Engine::Input::CloseGameController()
{
	if (controller != nullptr) {
		SDL_GameControllerClose(0);
		cout << "Game Controller is Removed" << endl;
	}
}

// -------------- Input Handling --------------------

void Engine::Input::PollInput()
{
	SDL_Event evt;

	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evt)) {
		switch (evt.type) {
		case SDL_QUIT:
			state = State::EXIT;
			break;
		case SDL_MOUSEMOTION:
			SetMouseCoords((float)evt.motion.x, (float)evt.motion.y);
			break;
		case SDL_KEYDOWN:
			PressKey(evt.key.keysym.sym);
			break;
		case SDL_KEYUP:
			ReleaseKey(evt.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			PressKey(evt.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			ReleaseKey(evt.button.button);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			OpenGameController();
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			CloseGameController();
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			PressKey(evt.cbutton.button);
			break;
		case SDL_CONTROLLERBUTTONUP:
			ReleaseKey(evt.cbutton.button);
			break;
		}
	}
}

void Engine::Input::PressKey(unsigned int keyID) {
	// Here we are treating _keyMap as an associative array.
	// if keyID doesn't already exist in _keyMap, it will get added
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = true;
	}

}

void Engine::Input::ReleaseKey(unsigned int keyID) {
	auto it = _mapNames.find(keyID);
	if (it != _mapNames.end()) {
		string mapName = it->second;
		_keyMap[mapName] = false;
	}
}

void Engine::Input::SetMouseCoords(float x, float y) {
	_mouseCoords.x = x;
	_mouseCoords.y = y;
}

bool Engine::Input::IsKeyDown(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _keyMap.find(name);
	if (it != _keyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

bool Engine::Input::IsKeyUp(string name) {
	// Check if it is pressed this frame, and wasn't pressed last frame
	if (IsKeyDown(name) == true && WasKeyDown(name) == false) {
		return true;
	}
	return false;
}

bool Engine::Input::WasKeyDown(string name) {
	// We dont want to use the associative array approach here
	// because we don't want to create a key if it doesnt exist.
	// So we do it manually
	auto it = _previousKeyMap.find(name);
	if (it != _previousKeyMap.end()) {
		// Found the key
		return it->second;
	}
	else {
		// Didn't find the key
		return false;
	}
}

void Engine::Input::InputMapping(string mappingName, unsigned int keyId)
{
	_mapNames.insert(pair<unsigned int, string>(keyId, mappingName));
}
