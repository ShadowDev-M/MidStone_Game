#include "Camera.h"

Camera::Camera()
{
	projection = MMath::perspective(16.0f, (16.0f / 9.0f), 1.0f, 1.0f);
	orientation = Quaternion(1.0f, Vec3(0.0f, 0.0f, 0.0f));
	position = Vec3(0.0f, 0.0f, -15.0f); // camera position
	view = MMath::toMatrix4(orientation) * MMath::translate(position);

}

Camera::~Camera()
{

}

bool Camera::OnCreate()
{

	return true;
}

void Camera::OnDestroy()
{

}

void Camera::Render() const
{

}

void Camera::HandleEvents(const SDL_Event& sdlEvent)
{

}