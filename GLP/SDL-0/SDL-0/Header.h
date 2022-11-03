#pragma once
#include <iostream>

#include <SDL.h>
#include "glew.h"
#include <fstream>
#include <string>
using namespace std;

string LoadShader(string fileName);
const string shaderPath = "./Shaders/";


int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	cin.get();
	//Create a simple window
	int width = 800;
	int height = 600;
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("Ma super premiere fenetre !", center, center, width, height, SDL_WINDOW_OPENGL);

	//Create an OpenGL compatible context to let glew draw on it
	SDL_GLContext Context = SDL_GL_CreateContext(Window);

	/////////SETTING UP OPENGL WITH GLEW///
	//Initialize glew
	glewExperimental = GL_TRUE;
	if (glewInit() == GLEW_OK) {
		cout << "Glew initialized successfully\n";
	}

	//Set the viewing frame through which we will see the objects
	glViewport(0, 0, width, height);

	//Put the color you want here for the background
	glClearColor(0.93f, 0.65f, 0.88f, 1.0f);


	//Use depth management
	glEnable(GL_DEPTH_TEST);

	//0 is our origin, the higher the z, the farther the object
	glDepthFunc(GL_LESS);


	//Describe the shape by its vertices

	float vertices[] = {
		// positions             // colors
			 0.5f, -0.5f, 0.1f,  1.0f, 0.0f, 0.0f,
			-0.5f, -0.5f, 0.1f,  0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.1f,  0.0f, 0.0f, 1.0f,
			-0.5f,  0.5f, 0.1f,  1.0f, 1.0f, 1.0f,
			0.3f,  0.3f, 0.0f,  1.0f, 1.0f, 0.0f,
			-0.1f,  -0.4f, 0.0f,  0.0f, 1.0f, 1.0f,
			-0.8f,  -0.1f, 0.0f,  1.0f, 0.0f, 1.0f
	};

	//Create an ID to be given at object generation
	unsigned int vbo;


	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo);

	string vs = LoadShader("animatedRainbowVertex.shader");
	const char* animatedVShaderSource = vs.c_str();
	string vsR = LoadShader("rainbowVertex.shader");
	const char* vertexShaderSource = vsR.c_str();
	string fs = LoadShader("rainbowFragment.shader");
	const char* fragmentShaderSource = fs.c_str();


	unsigned int vertexShader, animatedVShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	animatedVShader = glCreateShader(GL_VERTEX_SHADER);


	//now that we have a vertex shader, let�s put the code text inside
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(animatedVShader, 1, &animatedVShaderSource, NULL);


	//aaaaand� Compile !
	glCompileShader(vertexShader);
	glCompileShader(animatedVShader);
	//Do the same with the fragment shader !
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram, animatedShaderProgram;
	shaderProgram = glCreateProgram();
	animatedShaderProgram = glCreateProgram();

	//now attach shaders to use to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(animatedShaderProgram, animatedVShader);
	glAttachShader(animatedShaderProgram, fragmentShader);

	//and link it 
	glLinkProgram(shaderProgram);
	glLinkProgram(animatedShaderProgram);

	//now that the program is complete, we can use it 
	glUseProgram(shaderProgram);

	//Create one ID to be given at object generation
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//How do we split informations of the array
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);



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

		//// Get the time in seconds 
		float timeValue = (float)SDL_GetTicks() / 1000;
		float sinColor = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUseProgram(shaderProgram);
		glUniform3f(vertexColorLocation, 1, 1, 1);


		//VAO to use next
		glBindVertexArray(vao);

		//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
		//We draw from vertex 0 and we will be drawing 3 vertices
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glUseProgram(animatedShaderProgram);
		int vertexOffsetLocation = glGetUniformLocation(animatedShaderProgram, "offset");
		glUniform3f(vertexOffsetLocation, sinColor - 0.3f, sinColor / 2, 0.0f);
		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 4, 3);


		SDL_GL_SwapWindow(Window); // Swapbuffer
	}
	// Quit
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);


	return 0;
}

string LoadShader(string fileName) {
	ifstream myFile;
	myFile.open(shaderPath + fileName);
	if (myFile.fail()) {
		cerr << "Error - failed to open " << fileName << endl;
	}
	string fileText = "";
	string line = "";
	while (getline(myFile, line)) {
		fileText += line + '\n';
	}

	myFile.close();
	return fileText;
}