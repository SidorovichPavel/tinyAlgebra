#pragma once

#include <cstdint>

#include <tinyalgebralib/math/math.hpp>

namespace ta
{

	class Camera
	{
		vec3 position_;
		vec3 direction_;
		vec3 up_;
		vec3 right_;
		vec3 start_direction_;
		vec3 start_up_;
		vec3 start_right_;

		mat4 rotate_;

		float pitch_;
		float yaw_;
		float roll_;

		bool use_quaternions_;

		void update_vertors() noexcept;
	public:
		Camera(const vec3 pos, const vec3 target, vec3 up);
		Camera(const Camera&) = default;
		Camera(Camera&&) = default;
		~Camera();

		mat4 get_view() const noexcept;
		vec3 position() const noexcept;

		void apply_move(const ta::vec3& move, float distance);

		void update_angles(float pitch, float yaw, float roll);
		void use_quaternoins(bool mode = true);
	};

}