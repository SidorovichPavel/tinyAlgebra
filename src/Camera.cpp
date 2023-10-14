

#include <tinyalgebralib/Camera.hpp>

namespace ta
{

	Camera::Camera(const vec3 pos, const vec3 target, vec3 up)
		:
		mPosition(pos),
		mDirection(normalize(target - pos)),
		mUp(normalize(up)),
		mRotate(mat4(1.f)),
		mPitch(0.f),
		mYaw(0.f),
		mRoll(0.f),
		useQuaternions(false)
	{
		mRight = cross(mDirection, mUp);

		mStartDirection = mDirection;
		mStartUp = mUp;
		mStartRight = mRight;
	}

	Camera::~Camera()
	{}

	Camera& Camera::operator+=(const vec3& vec)noexcept
	{
		mPosition += vec;
		return *this;
	}

	Camera& Camera::operator-=(const vec3& vec)noexcept
	{
		mPosition -= vec;
		return *this;
	}

	vec3 Camera::get_direction() const noexcept
	{
		return mDirection;
	}

	vec3 Camera::get_right() const noexcept
	{
		return mRight;
	}

	vec3 Camera::get_up() const noexcept
	{
		return mUp;
	}

	vec3 Camera::get_position() const noexcept
	{
		return mPosition;
	}

	void Camera::update_vertors() noexcept
	{
		mDirection = vec3(mRotate * vec4(mStartDirection, 1.f));
		mRight = vec3(mRotate * vec4(mStartRight, 1.f));
		mUp = vec3(mRotate * vec4(mStartUp, 1.f));
	}

	//angle pls in radians
	void Camera::update_angles(float pitch, float yaw, float roll)
	{
		mPitch += pitch; mYaw += yaw; mRoll += roll;
		mRotate = mat4(1.f);

		mRotate = rotate(mRotate, mStartDirection, mRoll);
		mRotate = rotate(mRotate, mStartUp, mYaw);
		mRotate = rotate(mRotate, mStartRight, mPitch);

		update_vertors();
	}

	void Camera::use_quaternoins(bool _mode)
	{
		useQuaternions = _mode;
	}

}