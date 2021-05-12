#include "Demo.h"


Demo::Demo()
{
}


Demo::~Demo()
{
}

void Demo::Init()
{
	player = new Player(GetScreenWidth(),GetScreenHeight(),0,700);
	menu = new Menu(GetScreenWidth(), GetScreenHeight());
	audio = new Audio();


	menu->program = BuildShader("shader.vert", "shader.frag");
	menu->InitText();
	menu->InitButton();
	
	InputMapping("SelectButton", SDLK_RETURN);
	InputMapping("NextButton", SDLK_DOWN);
	InputMapping("PrevButton", SDLK_UP);

	audio->InitAudio();

	player -> BuildPlayerSprite();
	// Add input mapping
	// to offer input change flexibility you can save the input mapping configuration in a configuration file (non-hard code) !
	InputMapping("Move Right", SDLK_RIGHT);
	InputMapping("Move Left", SDLK_LEFT);
	InputMapping("Move Right", SDLK_d);
	InputMapping("Move Left", SDLK_a);
	InputMapping("Move Right", SDL_BUTTON_RIGHT);
	InputMapping("Move Left", SDL_BUTTON_LEFT);
	InputMapping("Move Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	InputMapping("Move Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	InputMapping("Jump", SDLK_w);
	InputMapping("Quit", SDLK_ESCAPE);
	InputMapping("Menu", SDLK_m);

	tile = new Tile(GetScreenWidth(), GetScreenHeight(), 100, 100);
	tile ->BuildCrateSprite();
	trap = new Trap(GetScreenWidth(), GetScreenHeight(), 100, 100);
	trap ->BuildTrapSprite();
	door = new Door(GetScreenWidth(), GetScreenHeight(), 100, 100);
	door->BuildDoorSprite();
}

void Demo::Update(float deltaTime)
{
	if (IsKeyDown("SelectButton")) {
		if (menu->activeButtonIndex == 2) {
			SDL_Quit();
			exit(0);
		}
		else if (menu->activeButtonIndex == 0) {
			play = false;
			finish = false;
			timeleft = 20;
			player->xpos = player->xstart;
			player->ypos = player->ystart;
		}
		else if (menu->activeButtonIndex == 1) {
			audio->Update(deltaTime);
		}
	}

	if (IsKeyUp("NextButton")) {
		if (menu->activeButtonIndex < NUM_BUTTON - 1) {
			menu->activeButtonIndex++;
			SDL_Delay(150);
		}
	}

	if (IsKeyUp("PrevButton")) {
		if (menu->activeButtonIndex > 0) {
			menu->activeButtonIndex--;
			SDL_Delay(150);
		}
	}

	if (!play && timeleft > 0)
	{
		if (millisecond > 0)
		{
			millisecond -= deltaTime;
		}
		else
		{
			timeleft -= 1;
			millisecond = 500;
			if (timeleft == 0) {
				gameover = true;
			}
			else if(finish) {
				timeleft = 999;
			}
		}
	}

	player -> UpdatePlayerSpriteAnim(deltaTime);
	ControlPlayerSprite(deltaTime);

	if (finish) {
		if (IsKeyDown("Menu")) {
			finish = false;
			play = true;
		}
	}
}

void Demo::Render()
{
	if (play) {
		//Setting Viewport
		glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

		//Clear the color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set the background color
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


		menu->RenderText("UPDOOR", (GetScreenWidth() / 2 - 150), 20, 3.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));

		menu->RenderButton();
		menu->RenderText("Assets used in this game are not used for any commercials business", 0, (GetScreenHeight() - 40), 1.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
	}
	else {
		if (gameover) {
			//Setting Viewport
			glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

			//Clear the color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Set the background color
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			menu->RenderText("GAMEOVER ", (GetScreenWidth() / 2 - 180), (GetScreenHeight()/2-100), 3.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
			menu->RenderText("Press Enter to Retry ", (GetScreenWidth() / 2 - 80), (GetScreenHeight() / 2), 1.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
			
			if (IsKeyDown("SelectButton")) {
				gameover = false;
				play = false;
				timeleft = 20;
				player->xpos = player->xstart;
				player->ypos = player->ystart;
				RenderPlay();
			}
		}
		else if (finish) {
			//Setting Viewport
			glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

			//Clear the color and depth buffer
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//Set the background color
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

			menu->RenderText("YOU WIN!", (GetScreenWidth() / 2 - 180), (GetScreenHeight() / 2 - 100), 3.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
			menu->RenderText("Press M for return to Menu ", (GetScreenWidth() / 2 - 150), (GetScreenHeight() / 2), 1.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
		}
		else if(!play){
			RenderPlay();
		}
	}	

}

void Demo::RenderPlay() {
	//Setting Viewport
	glViewport(0, 0, GetScreenWidth(), GetScreenHeight());

	//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set the background color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	player->DrawPlayerSprite();
	for (int i = 0; i < 5; i++) {
		tile->DrawCrateSprite(tile->widtharray[i], tile->heightarray[i], tile->xposarray[i], tile->yposarray[i]);
	}
	for (int i = 0; i < 2; i++) {
		trap->DrawTrapSprite(trap->widtharray[i], trap->heightarray[i], trap->xposarray[i], trap->yposarray[i]);
	}
	door->DrawDoorSprite(door->widthdoor, door->heightdoor, door->xposdoor, door->yposdoor);
	menu->RenderText("Time Remaining : " + to_string(timeleft) + " second", 10, 10, 1.0f, vec3(255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f));
}

void Demo::ControlPlayerSprite(float deltaTime)
{
	player->walk_anim = false;
	player->oldxpos = player->xpos;
	player->oldypos = player->ypos;

	if (IsKeyDown("Move Right")) {
		player->xpos += deltaTime * player->xVelocity;
		player->flip = 0;
		player->walk_anim = true;
	}

	if (IsKeyDown("Move Left")) {
		player->xpos -= deltaTime * player->xVelocity;
		player->flip = 1;
		player->walk_anim = true;
	}

	if (IsKeyDown("Jump")) {
		if (player->onGround) {
			player->yVelocity = -12.0f;
			player->onGround = false;
		}
	}

	if (IsKeyUp("Jump")) {
		if (player->yVelocity < -6.0f) {
			player->yVelocity = -6.0f;
		}
	}

	player->yVelocity += player->gravity * deltaTime;
	player->ypos += deltaTime * player->yVelocity;

	if (player->ypos > (player->yposGround+player->frame_height)) {
		player->ypos = 0;
		player->xpos = 0;
	}

	if (player->xpos > (GetScreenWidth()-player->frame_width)|| player->xpos < 0) {
		player->xpos = player->oldxpos;
	}

	// check collision between bart and crate
	for (int i = 0; i < 5; i++) {
		if (IsCollided(player->xpos, player->ypos, player ->frame_width, player->frame_height, tile->xposarray[i], tile->yposarray[i], tile->widtharray[i], tile->heightarray[i])) {
			if (player->xpos < tile->xposarray[i] + tile->widtharray[i] && player->xpos + player->frame_width > tile->xposarray[i]) {
				player->ypos = player->oldypos;
				player->yVelocity = 0;
				if (player->ypos < tile->yposarray[i])
				{
					player->onGround = true;
				}
			}
			if (player->ypos < tile->yposarray[i] + tile->heightarray[i] && player->ypos + player->frame_height > tile->yposarray[i]) {
				player->yVelocity += player->gravity * deltaTime;
				player->ypos += deltaTime * player->yVelocity;
				player->xpos = player->oldxpos;
			}
		}
	}
	// die condition when player collide with trap
	for (int i = 0; i < 2; i++) {
		if (IsCollided(player->xpos, player->ypos, player->frame_width, player->frame_height, trap->xposarray[i], trap->yposarray[i], trap->widtharray[i], tile->heightarray[i])) {
			player->xpos = player->xstart;
			player->ypos = player->ystart;
		}
	}

	// win condition when player collide with door
	if (IsCollided(player->xpos, player->ypos, player->frame_width, player->frame_height, door->xposdoor, door->yposdoor, door->widthdoor, door->heightdoor)) {
		finish = true;
	}
}

bool Demo::IsCollided(float x1, float y1, float width1, float height1,
	float x2, float y2, float width2, float height2) {
	return (x1 < x2 + width2 && x1 + width1 > x2 && y1 < y2 + height2 && y1 + height1 > y2);
}

int main(int argc, char** argv) {
	Engine::Game &game = Demo();
	game.Start("Updoor", 1440, 960, false, WindowFlag::WINDOWED, 60, 0.5);

	return 0;
}

