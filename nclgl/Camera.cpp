﻿#include"Camera.h"
#include"Window.h"
#include<algorithm>
void Camera::UpdateCamera(float dt) {
	pitch -= (Window::GetMouse()->GetRelativePosition().y);
	yaw -= (Window::GetMouse()->GetRelativePosition().x);

	pitch = std::min(pitch, 90.0f);
	pitch = std::max(pitch, -90.0f);

	if (yaw < 0) {
		yaw += 360.0f;
	}
	if (yaw > 360.0f) {
		yaw -= 360.0f;
	}
	Matrix4 rotation = Matrix4::Rotation(yaw, Vector3(0, 1, 0));

	Vector3 forward = rotation * Vector3(0, 0, -1);
	Vector3 right = rotation * Vector3(1, 0, 0);

	float zSpeed = CAMERA_Z_SPEED * dt;
	float xSpeed = CAMERA_X_SPEED * dt;
	float ySpeed = CAMERA_Y_SPEED * dt;
	//控制摄像头位置
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
		position += forward * zSpeed; //forward控制速度，每30个单位移动多少距离
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
		position -= forward * zSpeed;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
		position -= right * xSpeed;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
		position += right * xSpeed;
	}
	//控制上下
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
		position.y += ySpeed;
	}
	if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
		position.y -= ySpeed;
	}
}

Matrix4 Camera::BuildViewMatrix() {
	return Matrix4::Rotation(-pitch, Vector3(1, 0, 0)) *
		Matrix4::Rotation(-yaw, Vector3(0, 1, 0)) *
		Matrix4::Translation(-position);
}