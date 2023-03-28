#version 330 core

// Input variables from the vertex shader output
in vec3 pos;
in vec2 uv;
in vec3 color;
in vec3 normal;

in vec3 fragPos;
in vec3 lightNorm;

// Output variable for the framebuffer (by default at location 0)
out vec4 _fragColor;

// Texture mimap and blending level uniforms
uniform sampler2D TextureSampler;
uniform float TextureLevel;
uniform vec3 LightPos;
uniform bool NormalTint;

vec4 triplanarTextureMap(float textureScale, float triplanarBlendSharpness)
{
	// Find our UVs for each axis based on world position of the fragment.
	vec2 xUV = pos.zy / textureScale;
	vec2 yUV = pos.xz / textureScale;
	vec2 zUV = pos.xy / textureScale;

	// Now do texture samples from our diffuse map with each of the 3 UV sets we've just made.
	vec4 xDiff = texture(TextureSampler, xUV);
	vec4 yDiff = texture(TextureSampler, yUV);
	vec4 zDiff = texture(TextureSampler, zUV);

	// Get the absolute value of the world normal.
	// Put the blend weights to the power of BlendSharpness, the higher the value,
	// the sharper the transition between the planar maps will be.
	vec3 blendWeights = pow(abs(normal), vec3(triplanarBlendSharpness));

	// Divide our blend mask by the sum of its components, this will make x+y+z=1
	blendWeights = blendWeights / (blendWeights.x + blendWeights.y + blendWeights.z);

	// Finally, blend together all three samples based on the blend mask.
	vec4 textureProjection = xDiff * blendWeights.x + yDiff * blendWeights.y + zDiff * blendWeights.z;

	return (textureProjection);
}

void main()
{
	vec4 texel;

	// Creating the texture triplanar projection if UVs are not present
	if (all(equal(uv, vec2(0.0)))) {
		texel = triplanarTextureMap(2.0, 50.0);
	}
	else {
		texel = texture(TextureSampler, uv);
	}

	// Normal coloration
	if (NormalTint) {
		texel = mix(vec4(normal, 1.0), texel, TextureLevel);
	} else {
		texel = mix(vec4(color, 1.0), texel, TextureLevel);
	}

	// Light settings
	vec3 lightColor = vec3(1.0);
	vec3 viewPos = vec3(0.0, 0.0, 10.0);

	// Ambient
	float ambientStrength = 0.5;
	vec3 ambient = ambientStrength * lightColor;

	// Diffuse
	vec3 lightDir = normalize(LightPos - fragPos);
	vec3 diffuse = max(dot(lightNorm, lightDir), 0.0) * lightColor;

	// Specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, lightNorm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	// Lighting result
	vec3 lighting = ambient + diffuse + specular;

	// Fragment color output
	_fragColor = vec4(lighting, 1.0) * texel;
}
