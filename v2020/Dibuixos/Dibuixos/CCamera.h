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

#ifndef __CCAMERA_H__

#define	__CCAMERA_H__

class CCamera
{
public:

	CCamera();
	CCamera(int screenWidth, int screenHeight);

	void SetViewport(int x, int y, int width, int height);
	glm::vec4 GetViewport() const;

	void SetProjectionRH(float fov, float aspectRatio, float zNear, float zFar);

	void ApplyViewMatrix();

	void SetPosition(const glm::vec3& pos);
	glm::vec3 GetPosition() const;

	// Translate the camera by some amount. If local is TRUE (default) then the translation should
	// be applied in the local-space of the camera. If local is FALSE, then the translation is 
	// applied in world-space.
	void Translate(const glm::vec3& delta, bool local = true);

	void SetRotation(const glm::quat& rot);
	glm::quat GetRotation() const;

	void SetEulerAngles(const glm::vec3& eulerAngles);
	glm::vec3 GetEulerAngles() const;

	// Rotate the camera by some amount.
	void Rotate(const glm::quat& rot);

	glm::mat4 GetProjectionMatrix();
	glm::mat4 GetViewMatrix();

protected:

	void UpdateViewMatrix();

	glm::vec4 m_Viewport;

	glm::vec3 m_Position;
	glm::quat m_Rotation;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;

private:
	bool m_ViewDirty;
};

#endif // !__CCAMERA_H__