#version 330 core
	out vec4 FragColor;
	in vec3 ourColor;

	uniform float uniTime;
		
	void main()
	{
		FragColor = vec4(ourColor.x * (sin(2.5 * uniTime) + 1.0), 
						 ourColor.y * (sin(2.5 * uniTime - ourColor.x) + 1.0), 
						 ourColor.z * (sin(2.5 * uniTime) + 1.0), 1.0);
	};