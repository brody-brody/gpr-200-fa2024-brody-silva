#version 330 core
	out vec4 FragColor;
	in vec3 ourColor;

	uniform float time;
		
	void main()
	{
		FragColor = vec4(ourColor.x * (sin(2.5 * time) + 1.0), 
						 ourColor.y * (sin(2.5 * time - ourColor.x) + 1.0), 
						 ourColor.z * (sin(2.5 * time) + 1.0), 1.0);
	};