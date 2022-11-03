#include "BaseScene.h"
#include "ShaderProgram.h"
using namespace std;

const int VERTICE_COUNT = 42;

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

void BaseScene::SetupScene()
{
	m_animatedVShader.GenerateFrom("animatedRainbowVertex.shader", VERTEX);
	m_rainbowVShader.GenerateFrom("rainbowVertex.shader", VERTEX);
	m_rainbowFShader.GenerateFrom("rainbowFragment.shader", FRAGMENT);


	m_simpleProgram.GenerateFrom(m_rainbowVShader, m_rainbowFShader);
	m_animatedProgram.GenerateFrom(m_animatedVShader, m_rainbowFShader);
	
	m_simpleProgram.Use();

	//Create one ID to be given at object generation
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);


	//Binds the buffer linked to this ID to the vertex array buffer to be rendered. Put 0 instead of vbo to reset the value.
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	//Finally send the vertices array in the array buffer 
	float verticeArray[VERTICE_COUNT];
	std::copy(m_vertices.begin(), m_vertices.end(), verticeArray);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticeArray), verticeArray, GL_STATIC_DRAW);
	//How do we split informations of the array
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


}

void BaseScene::UpdateScene()
{
	//// Get the time in seconds 
	float timeValue = (float)SDL_GetTicks() / 1000;
	float sinColor = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(m_simpleProgram.GetID(), "ourColor");

	//glUseProgram(m_simpleProgram.GetID());
	m_simpleProgram.Use();
	glUniform3f(vertexColorLocation, 1, 1, 1);


	//VAO to use next
	glBindVertexArray(m_vao);

	//OMG WE FINALLY DRAW ! We use the GL_TRIANGLES primitive type
	//We draw from vertex 0 and we will be drawing 3 vertices
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//glUseProgram(m_animatedProgram.GetID());
	m_animatedProgram.Use();
	int vertexOffsetLocation = glGetUniformLocation(m_animatedProgram.GetID(), "offset");
	glUniform3f(vertexOffsetLocation, sinColor - 0.3f, sinColor / 2, 0.0f);
	glBindVertexArray(m_vao);

	glDrawArrays(GL_TRIANGLES, 4, 3);
}


