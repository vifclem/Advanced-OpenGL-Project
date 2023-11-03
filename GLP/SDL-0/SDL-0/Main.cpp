#include <iostream>
#include <SDL.h>
#include <glew.h>
#include <fstream> 
#include <string>
#include "Shapes2D.h"
#include "Window.h"
using namespace std;

#define GLEW_STATIC

string LoadShader(string fileName);

float maxX = 0.1f;
float minX = 0.0f;
float ballPosX = 0;
float ballPosY = 0;
float paddleLPosX = 0;
float paddleLPosY = 0;
float paddleRPosX = 0;
float paddleRPosY = 0;
float speedX = 0.02;
float speedY = 0.03;
int main(int argc, char* argv[])
{

	

	float vertices[] = {
		// positions             // colors

		 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, 0.0f,
		 0.0f, 0.08f, 0.0f,  0.0f, 1.0f, 0.0f,
		 0.08f, 0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
		 0.08f, 0.08f, 0.0f, 1.0f, 0.0f, 0.0f,


			 
	};

	

	
	float vertices2[] = {
		// positions             // colors


		 0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
		 0.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

		 -0.92f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.92f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,
		  -0.82f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.82f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,
		
		  0.92f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		  0.92f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,
		  0.82f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,
		  0.82f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,


	};
	

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
	}
	///////////SETTING UP SDL/////////////
	//Create a simple window
	int width = 1000;
	int height = 800;
	unsigned int center = SDL_WINDOWPOS_CENTERED;
	SDL_Window* Window = SDL_CreateWindow("My window", center, center, width, height, SDL_WINDOW_OPENGL);
	//SDL_WINDOW_OPENGL is a u32 flag !
	


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
	glClearColor(0.0f, 0.5f, 0.7f, 1.0f);


#pragma region vbo1
	//Create an ID to be given at object generation
	unsigned int vbo;
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo);

	string vs = LoadShader("SimpleShader.shader");
	const char* vertexShaderSource = vs.c_str();
	string fs = LoadShader("RGBFragShader.shader");
	const char* fragmentShaderSource = fs.c_str();



	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//now that we have a vertex shader, let’s put the code text inside
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//aaaaand… Compile !
	glCompileShader(vertexShader);


	//Do the same with the fragment shader !
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	//now attach shaders to use to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

#pragma endregion

#pragma region vbo2
	//Create an ID to be given at object generation
	unsigned int vbo2;
	//Pass how many buffers should be created and the reference of the ID to get the value set
	glGenBuffers(1, &vbo2);

	

	unsigned int shaderProgram2;
	shaderProgram2 = glCreateProgram();
	//now attach shaders to use to the program
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader);
#pragma endregion


	
#pragma region vao

	//Create one ID to be given at object generation
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);


	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#pragma endregion



#pragma region vao2
	//Create one ID to be given at object generation
	unsigned int vao2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);


	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	//Finally send the vertices array in the array buffer 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

#pragma endregion


	//and link it 
	glLinkProgram(shaderProgram);
	
	//and link it 
	glLinkProgram(shaderProgram2);
	

	


	//Use depth management
	glEnable(GL_DEPTH_TEST);

	//0 is our origin, the higher the z, the farther the object
	glDepthFunc(GL_LESS);


	//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type

	bool isRunning = true;
	while (isRunning) {
		// Inputs
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_UP:
					paddleRPosY += 0.1;
					break;
				case SDLK_DOWN:
					paddleRPosY -= 0.1;
					break;
				case SDLK_z:
					paddleLPosY += 0.1;
					break;
				case SDLK_s:
					paddleLPosY -= 0.1;
					break;
				}
			default:
				break;
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		//We draw from vertex 0 and we will be drawing 3 vertices
		// Get the time in seconds 

		ballPosX += speedX;
		ballPosY += speedY;
		
		if (ballPosX + maxX >= 1) speedX *= -1;
		else if (ballPosX + minX <= -1) speedX *= -1;
		else if (ballPosY + maxX >= 1 && speedY >0) speedY *= -1;
		else if (ballPosY + minX <= -1 && speedY < 0) speedY *= -1;

		



		glUseProgram(shaderProgram);
		int location = glGetUniformLocation(shaderProgram, "updatePos");
		glUniform2f(location, ballPosX, ballPosY);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		
		glBindVertexArray(vao2);
		glUniform2f(location, paddleRPosX, paddleRPosY);
		glDrawArrays(GL_TRIANGLE_STRIP, 6, 4);
		
		glUniform2f(location, paddleLPosX, paddleLPosY);
		glDrawArrays(GL_TRIANGLE_STRIP, 2 , 4);

		

		SDL_GL_SwapWindow(Window); // Swapbuffer
		

	}
	// Quit
	
	SDL_DestroyWindow(Window);
	SDL_GL_DeleteContext(Context);


	cin.get();
	return 0;
}

string LoadShader(string fileName) {
	ifstream myFile;
	myFile.open(fileName);
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
