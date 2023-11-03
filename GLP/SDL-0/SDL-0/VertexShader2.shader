#version 330 core

out vec4 FragColor;
uniform vec2 paddlepos;
out vec4 newPaddlePos;


void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    paddlePos = vec4(paddlepos.x, paddlepos.y, paddlepos.z, 1.0);
    newPaddlePos = paddlePos;
}
