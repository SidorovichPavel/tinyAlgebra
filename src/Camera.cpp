#include <cmath>

#include <tinyalgebralib/Camera.hpp>

namespace ta
{

	Camera::Camera(const vec3 pos, const vec3 target, vec3 up)
		:
		position_(pos),
		direction_(normalize(target - pos)),
		up_(normalize(up)),
		rotate_(mat4(1.f)),
		pitch_(0.f),
		yaw_(0.f),
		roll_(0.f),
		use_quaternions_(false)
	{
		right_ = cross(up_, direction_);

		start_direction_ = direction_;
		start_up_ = up_;
		start_right_ = right_;
	}

	Camera::~Camera()
	{}

	mat4 Camera::get_view()const noexcept
	{
		return ta::look_at(position_, position_ + direction_, up_);
	}

	void Camera::move_front(float dist)
	{
		position_ += direction_ * dist;
	}

	void Camera::move_back(float dist)
	{
		position_ -= direction_ * dist;
	}

	void Camera::move_right(float dist)
	{
		position_ += right_ * dist;
	}

	void Camera::move_left(float dist)
	{
		position_ -= right_ * dist;
	}

	void Camera::update_vertors() noexcept
	{
		direction_ = vec3(vec4(start_direction_, 1.f) * rotate_);
		right_ = vec3(vec4(start_right_, 1.f) * rotate_);
		//up_ = vec3(vec4(start_up_, 1.f) * rotate_);
	}

	//angle pls in radians
	void Camera::update_angles(float pitch, float yaw, float roll)
	{
		pitch_ += pitch; yaw_ += yaw; roll_ += roll;

		rotate_ = mat4(1.f);

		rotate_ = rotate(rotate_, start_direction_, ta::rad(roll_));
		rotate_ = rotate(rotate_, start_up_, ta::rad(yaw_));
		rotate_ = rotate(rotate_, start_right_, ta::rad(pitch_));

		update_vertors();
	}

	void Camera::use_quaternoins(bool _mode)
	{
		use_quaternions_ = _mode;
	}

}