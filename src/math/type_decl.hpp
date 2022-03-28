#pragma once

#include "Vector.hpp"
#include "Matrix.hpp"

namespace ta
{
	using vec2f = Vector<float, 2>;
	using vec2i = Vector<int, 2>;
	using vec2u = Vector<unsigned int, 2>;

	using vec3f = Vector<float, 3>;
	using vec3i = Vector<int, 3>;
	using vec3u = Vector<unsigned int, 3>;

	using vec4f = Vector<float, 4>;
	using vec4i = Vector<int, 4>;
	using vec4u = Vector<unsigned int, 4>;

	using vec2 = vec2f;
	using vec3 = vec3f;
	using vec4 = vec4f;

	using mat2x2f = Matrix<float, 2, 2>;
	using mat2x2i = Matrix<int, 2, 2>;
	using mat2x2u = Matrix<unsigned int, 2, 2>;

	using mat3x3f = Matrix<float, 3, 3>;
	using mat3x3i = Matrix<int, 3, 3>;
	using mat3x3u = Matrix<unsigned int, 3, 3>;
	
	using mat4x4f = Matrix<float, 4, 4>;
	using mat4x4i = Matrix<int, 4, 4>;
	using mat4x4u = Matrix<unsigned int, 4, 4>;

	using mat2 = mat2x2f;
	using mat3 = mat3x3f;
	using mat4 = mat4x4f;
}