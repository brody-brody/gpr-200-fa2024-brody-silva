#version 330 core
	out vec4 FragColor;

	in vec3 FragPos;
	in vec2 TexCoord;
	in vec3 Normal;

	uniform sampler2D texture1;
	uniform vec3 lightPos; 
	uniform vec3 lightColor;
	uniform vec3 objectColor;
		
	void main()
	{
		// ambient lighting
		float ambientStrength = 0.1;
		vec3 ambient = ambientStrength * lightColor;
  	
		// diffusion
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lightColor;
            
		vec3 result = (ambient + diffuse) * objectColor;

		FragColor = mix(vec4(result, 1.0f), texture(texture1, TexCoord), 0.5);
	};