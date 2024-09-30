#version 330 core
	out vec4 FragColor;

	in vec3 ourColor;
	in vec2 TexCoord;

	uniform sampler2D water;
	uniform sampler2D fish;
	uniform float uniTime;
		
	void main()
	{
		float waveX = sin(TexCoord.x * 10 + uniTime) * 0.1;
		float waveY = sin(TexCoord.y * 10 + uniTime) * 0.1;
		vec2 wavyTexCoord = vec2(TexCoord.x + waveY, TexCoord.y + waveX);

		FragColor = mix(texture(water, wavyTexCoord), texture(fish, wavyTexCoord), 0.3f);
	};