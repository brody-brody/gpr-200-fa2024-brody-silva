#version 330 core
	out vec4 FragColor;

	in vec3 FragPos;
	in vec2 TexCoord;
	in vec3 Normal;

	uniform sampler2D texture1;
	uniform vec3 lightPos; 
	uniform vec3 lightColor;
	uniform vec3 viewPos;
	uniform float ambientK;
	uniform float diffuseK;
	uniform float specularK;
	uniform float shininess;
		
	void main()
	{
		vec3 image = texture(texture1, TexCoord).rgb;
		// ambient lighting
		vec3 ambient = ambientK * lightColor * image;
  	
		// diffusion
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lightPos - FragPos);
		float diff = max(dot(norm, lightDir), 0.0);
		diff *= diffuseK;
		vec3 diffuse = diff * lightColor * image;

		// specular
		vec3 viewDir = normalize(viewPos - FragPos);
		vec3 halfwayDir = normalize(lightDir + viewDir);
		float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
		spec *= specularK;
		vec3 specular = spec * lightColor * image;
            
		vec3 result = (ambient + diffuse + specular);

		FragColor = vec4(result, 1.0f);
	};