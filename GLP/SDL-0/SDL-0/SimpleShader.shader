#version 330 core

in vec3 pos;
in vec3 color;
out vec4 ourColor;


uniform vec2 updatePos;
out vec4 newPos;
in float redColor;



void main()
{
    
    gl_Position = vec4(pos.x + updatePos.x, pos.y + updatePos.y, pos.z, 1);
    ourColor = vec4(color, 1.0);
    newPos =  gl_Position;

}



