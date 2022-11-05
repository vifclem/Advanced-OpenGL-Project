#include "BaseScene.h"
using namespace std;

const int VERTICE_COUNT = 42;
const int POSITION = 0;
const int POSITION_SIZE = 3; // 3 position infos per vertex
const int COLOR = 1;
const int COLOR_SIZE = 3; // 3 color infos per vertex

BaseScene::BaseScene() {
	m_vertices = {
				// positions             // colors
				0.5f, -0.5f, 0.1f, 1.0f, 0.0f, 0.0f,	// A
				-0.5f, -0.5f, 0.1f, 0.0f, 1.0f, 0.0f,	// B
				0.5f, 0.5f, 0.1f, 0.0f, 0.0f, 1.0f,		// C
				-0.5f, 0.5f, 0.1f, 1.0f, 1.0f, 1.0f,	// D
				0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f,		// E
				-0.1f, -0.4f, 0.0f, 0.0f, 1.0f, 1.0f,	// F
				-0.8f, -0.1f, 0.0f, 1.0f, 0.0f, 1.0f	// G
	};
}

//Load the correct shaders from your files

void BaseScene::LoadShaders() {
	m_animatedVShader.LoadFrom("animatedRainbowVertex.shader", VERTEX);
	m_rainbowVShader.LoadFrom("rainbowVertex.shader", VERTEX);
	m_rainbowFShader.LoadFrom("rainbowFragment.shader", FRAGMENT);
}

void BaseScene::CreateShaderPrograms() {
	m_simpleProgram.Compose(vector<Shader*>{&m_rainbowVShader, & m_rainbowFShader});
	m_animatedProgram.Compose(vector<Shader*>{&m_animatedVShader, & m_rainbowFShader});

	m_simpleProgram.Use();
}

void BaseScene::VerticeInformationSlicer() {
	//Put the vector information in a float array, then in the array buffer 
	float* verticeArray = new float[m_vertices.size()]();
	std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), verticeArray, GL_STATIC_DRAW);
	//Now we split informations of the array : 3 infos for the position / 3 infos for the color
	// 
	int totalAttributesSize = POSITION_SIZE + COLOR_SIZE;
	// Position attribut
	glVertexAttribPointer(POSITION, POSITION_SIZE, GL_FLOAT, GL_FALSE, totalAttributesSize * sizeof(float), (void*)0);

	glEnableVertexAttribArray(POSITION); //const POSITION = 0
	// Color attribute											6 float infos / vertex total

	glVertexAttribPointer(COLOR, COLOR_SIZE, GL_FLOAT, GL_FALSE, totalAttributesSize * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(COLOR);	//const COLOR = 1

	delete[] verticeArray;
}

void BaseScene::SetupScene()
{
	LoadShaders();
	CreateShaderPrograms();

	//Create one ID to be given at object generation and store it in m_vao via reference
	glGenVertexArrays(1, &m_vao);
	//Binding the VAO 
	//   /!\ If you have multiple VAOs, you should bind the correct VAO after each change
	glBindVertexArray(m_vao);

	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	VerticeInformationSlicer();
}

void BaseScene::UpdateScene()
{
	//// Get the time in seconds and use it to oscillate a sinusoid value
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue) / 2.0f) + 0.5f;

	/*====================================================
	FIRST SHAPE : SQUARE COMPOSED OF 2 TRIANGLES (4 POINTS) / SIMPLE VERTEX COLOR PROGRAM
	======================================================*/
	//Selecting the correct shading program (vertex + fragment)
	m_simpleProgram.Use();

	//We finally draw ! We use the GL_TRIANGLE_STRIP primitive type to use 4 points instead of 6
	//We draw from vertex 0 and we will be drawing 4 vertices
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	/*====================================================
	SECOND SHAPE : TRIANGLE (3 NEXT POINTS) / POSITION AND COLOR ANIMATION PROGRAM
	======================================================*/
	//Changing the shading program
	m_animatedProgram.Use();

	//In which program to find uniform variable to change and what it is called
	int vertexOffsetLocation = glGetUniformLocation(m_animatedProgram.GetID(), "offset");
	glUniform3f(vertexOffsetLocation, sinusoidValue - 0.3f, sinusoidValue / 2, 0.0f);
	//We draw from vertex 4 and we will be drawing 3 vertices
	glDrawArrays(GL_TRIANGLES, 4, 3);
}


