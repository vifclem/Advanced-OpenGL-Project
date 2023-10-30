#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;

void main()
{
    FragColor = ourColor;
}

/*
float timeValue = (float)SDL_GetTicks() / 1000;
		float redColor = (sin(timeValue) / 2.0f) + 0.5f;
		float greenColor = (sin(timeValue + 2) / 2.0f) + 0.5f;
		float blueColor = (sin(timeValue + 4) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, redColor, greenColor, blueColor, 1.0f);
		/*