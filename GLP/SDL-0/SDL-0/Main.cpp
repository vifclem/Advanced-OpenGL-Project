#include <iostream>

#include <SDL.h>
#include "glew.h"
#include <fstream>
#include <string>

#include "Window.h"
#include "Color.h"
#include "BaseScene.h"
using namespace std;


int main(int argc, char* argv[])
{
	cin.get();

	Window window(800, 600, Color::PINK);
	BaseScene scene = BaseScene();
	scene.SetupScene();


	bool isRunning = true;
	while (isRunning) {
		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		scene.UpdateScene();
		window.Update();

	}
	
	// Quit
	window.Close();


	return 0;
}