#pragma once

#include <cstdint>

#include <tinyalgebralib/math/math.hpp>

namespace ta
{

	class Camera
	{
		vec3 mPosition;
		vec3 mDirection;
		vec3 mUp;
		vec3 mRight;
		vec3 mStartDirection;
		vec3 mStartUp;
		vec3 mStartRight;

		mat4 mRotate;

		float mPitch;
		float mYaw;
		float mRoll;

		bool useQuaternions;

		void update_vertors() noexcept;
	public:
		Camera(const vec3 pos, const vec3 target, vec3 up);
		Camera(const Camera&) = default;
		Camera(Camera&&) = default;
		~Camera();

		Camera& operator+=(const vec3& vec)noexcept;
		Camera& operator-=(const vec3& vec)noexcept;

		mat4 get_view()const noexcept;
		vec3 get_direction() const noexcept;
		vec3 get_right() const noexcept;
		vec3 get_up() const noexcept;
		vec3 get_position() const noexcept;

		void update_angles(float pitch, float yaw, float roll);
		void use_quaternoins(bool mode = true);
	};

}