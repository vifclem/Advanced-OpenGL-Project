#include "ScreensaverScene.h"

using namespace std;

const int VERTICE_INFO_COUNT = 40;
const int POSITION = 0;
const int POSITION_SIZE = 2; // 2 position infos per vertex

ScreensaverScene::ScreensaverScene() {
	Shape2D::CreateEllipse(m_vertices, Vector2F(), Vector2F(0.25, 0.15), (VERTICE_INFO_COUNT-8) / 2);
	Shape2D::CreateRectangle(m_vertices, Vector2F(-0.25f, -0.25f), Vector2F(0.5f, 0.3f));
	//CreateCircle(m_vertices, Vector2F(),  0.25f, (VERTICE_INFO_COUNT-8) / 2);
}

//Load the correct shaders from your files
void ScreensaverScene::LoadShaders() {
	m_vertexShader.LoadFrom("vertexMove.shader", VERTEX);
	m_fragmentShader.LoadFrom("simpleFragment.shader", FRAGMENT);
}

void ScreensaverScene::CreateShaderPrograms() {
	m_simpleProgram.Compose(m_vertexShader, m_fragmentShader);
}

void ScreensaverScene::VerticeInformationSlicer() {
	//Put the vector information in a float array, then in the array buffer 
	float verticeArray[VERTICE_INFO_COUNT];
	std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticeArray), verticeArray, GL_STATIC_DRAW);
	//Now we split informations of the array : 2 float infos for the position / vertex
	// Position attribute												
	glVertexAttribPointer(POSITION, POSITION_SIZE, GL_FLOAT, GL_FALSE, POSITION_SIZE * sizeof(float), (void*)0);
	glEnableVertexAttribArray(POSITION); //const POSITION = 0
	
}

void ScreensaverScene::SetupScene()
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

void ScreensaverScene::UpdateScene()
{
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinusoidValue = (sin(timeValue) / 2.0f) + 0.5f;
	/*====================================================
	FIRST SHAPE : ELLIPSE COMPOSED OF 20 POINTS / SIMPLE VERTEX COLOR PROGRAM
	======================================================*/
	//Selecting the correct shading program (vertex + fragment)
	m_simpleProgram.Use();

	//In which program to find uniform variable to change and what it is called
	int vertexOffsetLocation = glGetUniformLocation(m_simpleProgram.GetID(), "offset");
	glUniform3f(vertexOffsetLocation, sinusoidValue/2, 0.0f, 0.0f);

	//Drawing

	int currentIndex = 0;
	currentIndex = Shape2D::DrawEllipse(currentIndex, (VERTICE_INFO_COUNT - 8) / 2);
	currentIndex = Shape2D::DrawRectangle(currentIndex);

}


