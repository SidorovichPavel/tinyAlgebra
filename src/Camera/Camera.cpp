#include "Camera.hpp"
#include "../glm/ext.hpp"
#include "../glm/matrix.hpp"

namespace ta
{

	Camera::Camera(const glm::vec3 _Pos, const glm::vec3 _Target, glm::vec3 _Up, const float _Aspect, const float _Fovy)
		:
		mPosition(_Pos),
		mDirection(normalize(_Target - _Pos)),
		mUp(normalize(_Up)),
		mAspect(_Aspect),
		mFovy(_Fovy),
		mRotate(glm::mat4(1.f)),
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

	Camera& Camera::operator+=(const glm::vec3& _Vec)noexcept
	{
		mPosition += _Vec;
		return *this;
	}

	Camera& Camera::operator-=(const glm::vec3& _Vec)noexcept
	{
		mPosition -= _Vec;
		return *this;
	}

	void Camera::set_fovy(float _Angle) noexcept
	{
		mFovy = _Angle;
	}

	glm::mat4 Camera::get_perspective(float _Near, float _Far) const noexcept
	{
		return glm::perspective(glm::radians(mFovy), mAspect, _Near, _Far);
	}

	glm::mat4 Camera::get_view() const noexcept
	{
		return glm::lookAt(mPosition,
			mPosition + mDirection,
			mUp);
	}

	glm::mat4 Camera::get_mat4(float _Near, float _Far) const noexcept
	{
		return get_perspective(_Near, _Far) * get_view();
	}

	glm::vec3 Camera::get_direction() const noexcept
	{
		return mDirection;
	}

	glm::vec3 Camera::get_right() const noexcept
	{
		return mRight;
	}

	glm::vec3 Camera::get_up() const noexcept
	{
		return mUp;
	}

	glm::vec3 Camera::get_position() const noexcept
	{
		return mPosition;
	}

	void Camera::update_Fovy(uint16_t _Keys, int16_t _Delta, int32_t x, int32_t y) noexcept
	{
		if (_Delta > 0)
			if (mFovy > 30.f)
				mFovy -= 5.f;
		if (_Delta < 0)
			if (mFovy < 70.f)
				mFovy += 5.f;
	}

	void Camera::update_aspect(uint16_t x, uint16_t y)noexcept
	{
		if (y != 0)
			mAspect = static_cast<float>(x) / static_cast<float>(y);
		else
			mAspect = 0.01f;
	}

	void Camera::update_vertors() noexcept
	{
		mDirection = glm::vec3(mRotate * glm::vec4(mStartDirection, 1.f));
		mRight = glm::vec3(mRotate * glm::vec4(mStartRight, 1.f));
		mUp = glm::vec3(mRotate * glm::vec4(mStartUp, 1.f));
	}

	//angle pls in radians
	void Camera::update_angles(float _Pitch, float _Yaw, float _Roll)
	{
		mPitch += _Pitch; mYaw += _Yaw; mRoll += _Roll;
		mRotate = glm::mat4(1.f);

		mRotate = glm::rotate(mRotate, mRoll, mStartDirection);
		mRotate = glm::rotate(mRotate, mYaw, mStartUp);
		mRotate = glm::rotate(mRotate, mPitch, mStartRight);
		update_vertors();
	}

	void Camera::use_quaternoins(bool _mode)
	{
		useQuaternions = _mode;
	}

}