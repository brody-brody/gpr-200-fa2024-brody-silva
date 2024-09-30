#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

uniform float uniTime;

void main()
{
    float angle = abs((sin(0.5*uniTime) - 0.5) * radians(45.0));

	// storing a rotation matrix
	mat3 rotation = mat3(
		cos(angle), -sin(angle), 0.0,
		sin(angle),  cos(angle), 0.0,
		0.0,         0.0,        1.0
	);
	
	vec3 rotatedPos = rotation * aPos;

    gl_Position = vec4(rotatedPos.x, rotatedPos.y, aPos.z, 1.0f);
    ourColor = aColor;
    TexCoord = aTexCoord;
}