#version 330 core
out vec4 FragColor;
in vec4 newPaddlePos


void main()
{
    FragColor = (newPaddlePos + 1);
	
}

