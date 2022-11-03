#include <iostream>

#include <SDL.h>
#include "glew.h"
#include <fstream>
#include <string>

#include "Window.h"
#include "Color.h"
#include "BaseScene.h"
#include "SceneID.h"
using namespace std;

Scene* SceneSelector(SceneID id);

int main(int argc, char* argv[])
{
	//Creating a new window w/ dimensions and background color (optional) 
	Window window(800, 600, Color::PINK);

	//Use a SceneID (see SceneID.h) to quickly setup the correct scene for the build!
	Scene* scene = SceneSelector(BASE_SCENE);
	if (scene == nullptr) return 1; //Scene doesn't exist yet

	//Preparing shaders, shader programs, vao and vbo
	scene->SetupScene();


	//Loop that keeps the window alive
	bool isRunning = true;
	while (isRunning) {
		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			//If the user tries to quit the window, stop execution
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}
		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
		//Drawing the shapes and filling the buffer
		scene->UpdateScene();
		//Swap the buffers --> Display the newly computed one, hide the one displayed last frame
		window.Update();

	}
	
	// Quit
	window.Close();


	return 0;
}

Scene* SceneSelector(SceneID id) {
	switch (id) {
		case BASE_SCENE: {
			return new BaseScene();
			break;
		}
		case TESSELLATION: {
			break;
		}
		case GEOMETRY: {
			break;
		}
		case MIP_MAP: {
			break;
		}
		default: {
			return nullptr;
		}
	}
}