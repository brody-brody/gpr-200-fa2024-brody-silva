#version 330 core
	layout (location = 0) in vec3 aPos;
	layout (location = 1) in vec3 aColor;

	uniform float time;

	out vec3 ourColor;

	void main()
	{
		// angle of the rotation follows the sin(time)
		float angle = sin(0.25*time) * radians(720.0);

		// storing a rotation matrix
		mat3 rotation = mat3(
			cos(angle), -sin(angle), 0.0,
			sin(angle),  cos(angle), 0.0,
			0.0,         0.0,        1.0
		);
	
		vec3 rotatedPos = rotation * aPos;

		// y pos is affected by time to bounce around
		gl_Position = vec4(rotatedPos.x, (rotatedPos.y + (0.25)*(sin(2*time))), aPos.z, 1.0);
		ourColor = aColor;
	}; 