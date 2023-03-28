#version 330 core

// Input variables from the VBO
layout (location = 0) in vec3 _pos;
layout (location = 1) in vec2 _uv;
layout (location = 2) in vec3 _color;
layout (location = 3) in vec3 _normal;

// Output variables for the fragment shader
out vec3 pos;
out vec2 uv;
out vec3 color;
out vec3 normal;

out vec3 fragPos;
out vec3 lightNorm;

// MVP matrix uniform
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	pos = _pos;
	uv = _uv;
	color = _color;
	normal = _normal;

	fragPos = vec3(Model * vec4(_pos, 1.0));
	// lightNorm = normalize(transpose(inverse(mat3(Model))) * _normal);
	lightNorm = normalize(mat3(Model) * _normal);

	gl_Position = Projection * View * vec4(fragPos, 1.0);
}
