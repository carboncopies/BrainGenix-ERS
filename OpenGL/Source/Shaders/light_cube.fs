#version 330 core
out vec4 FragColor;

in vec4 lightColor;

void main()
{
    FragColor = lightColor;//vec4(1.0, 0.5, 0.5, 1.0); // set all 4 vector values to 1.0

} 
