/*
MIT License

Copyright (c) 2019 Sistema Solar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "pch.h"
#include "CCamera.h"

CCamera::CCamera()
: m_Viewport(0)
, m_Position(0)
, m_Rotation()
, m_ProjectionMatrix(1)
, m_ViewMatrix(1)
, m_ViewDirty(false)
{}

CCamera::CCamera(int screenWidth, int screenHeight)
	: m_Viewport(0, 0, screenWidth, screenHeight)
	, m_Position(0)
	, m_Rotation()
	, m_ProjectionMatrix(1)
	, m_ViewMatrix(1)
	, m_ViewDirty(false)
{

}

void CCamera::SetViewport(int x, int y, int width, int height)
{
	m_Viewport = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);
}

glm::vec4 CCamera::GetViewport() const
{
	return m_Viewport;
}

void CCamera::SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar)
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}

void CCamera::ApplyViewMatrix()
{
	UpdateViewMatrix();
}

void CCamera::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
	m_ViewDirty = true;
}

glm::vec3 CCamera::GetPosition() const
{
	return m_Position;
}

void CCamera::Translate(const glm::vec3& delta, bool local /* = true */)
{
	if (local)
	{
		m_Position += m_Rotation * delta;
	}
	else
	{
		m_Position += delta;
	}
	m_ViewDirty = true;
}

void CCamera::SetRotation(const glm::quat& rot)
{
	m_Rotation = rot;
	m_ViewDirty = true;
}

glm::quat CCamera::GetRotation() const
{
	return m_Rotation;
}

void CCamera::SetEulerAngles(const glm::vec3& eulerAngles)
{
	m_Rotation = glm::quat(glm::radians(eulerAngles));
}

glm::vec3 CCamera::GetEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(m_Rotation));
}

void CCamera::Rotate(const glm::quat& rot)
{
	m_Rotation = m_Rotation * rot;
	m_ViewDirty = true;
}

glm::mat4 CCamera::GetProjectionMatrix()
{
	return m_ProjectionMatrix;
}

glm::mat4 CCamera::GetViewMatrix()
{
	UpdateViewMatrix();
	return m_ViewMatrix;
}

void CCamera::UpdateViewMatrix()
{
	if (m_ViewDirty)
	{
		glm::mat4 translate = glm::translate(-m_Position);
		// Since we know the rotation matrix is orthonormalized, we can simply 
		// transpose the rotation matrix instead of inversing.
		glm::mat4 rotate = glm::transpose(glm::toMat4(m_Rotation));

		m_ViewMatrix = rotate * translate;

		m_ViewDirty = false;
	}
}

