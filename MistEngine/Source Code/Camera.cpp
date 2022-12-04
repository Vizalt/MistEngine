#include "Application.h"
#include "Camera.h"
#include "Transform.h"
#include "GameObject.h"


CCamera::CCamera() : Component(nullptr)
{
	type = ComponentType::CAMERA;
	owner = nullptr;
	printCount = 0;
	SetCam();
	GenBuffer();
}

CCamera::CCamera(GameObject* owner) : Component(owner)
{
	type = ComponentType::CAMERA;
	this->owner = owner;
	printCount = 0;
	SetCam();
	GenBuffer();
}

CCamera::~CCamera()
{
	glDeleteFramebuffers(1, &cameraBuffer);
	glDeleteFramebuffers(1, &frameBuffer);
	glDeleteFramebuffers(1, &renderObjBuffer);
}


void CCamera::SetCam()
{
	FrustumCam.type = FrustumType::PerspectiveFrustum;
	FrustumCam.nearPlaneDistance = 0.1f;
	FrustumCam.farPlaneDistance = 500.f;
	FrustumCam.front = float3::unitZ;
	FrustumCam.up = float3::unitY;

	FrustumCam.verticalFov = FOV * DEGTORAD;
	FrustumCam.horizontalFov = 2.0f * atanf(tanf(FrustumCam.verticalFov / 2.0f) * 1.7f);

	FrustumCam.pos = float3(0, 0, 0);
}

void CCamera::GenBuffer()
{
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glGenTextures(1, &cameraBuffer);
	glBindTexture(GL_TEXTURE_2D, cameraBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	float color[4] = { 0.1,0.1,0.1,0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, cameraBuffer, 0);

	glGenRenderbuffers(1, &renderObjBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, renderObjBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCREEN_WIDTH, SCREEN_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderObjBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

float* CCamera::GetViewMatrix()
{

	viewMatrix = FrustumCam.ViewMatrix();

	viewMatrix.Transpose();

	return viewMatrix.ptr();
}

float* CCamera::GetProjectionMatrix()
{

	projectionMatrix = FrustumCam.ProjectionMatrix();

	projectionMatrix.Transpose();

	return projectionMatrix.ptr();
}

void CCamera::LookAt(const float3& target)
{
	FrustumCam.front = (target - FrustumCam.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(FrustumCam.front).Normalized();
	FrustumCam.up = FrustumCam.front.Cross(X);
}

void CCamera::TransformCam()
{
	//if is the scene cam it will move with input controls (ModuleCamera3D)
	if (owner == nullptr) return;

	//if not, move with gameObj transform
	FrustumCam.pos = owner->transform->position;

	//owner's global transform matrix
	float4x4 matrix = owner->transform->GetTransformMatrix();

	//Column 0 -> eix X -> worldRight || Column 1 -> eix Y -> up || Column 2  -> eix Z -> front || Column 3 -> pos
	FrustumCam.up = matrix.RotatePart().Col(1).Normalized();
	FrustumCam.front = matrix.RotatePart().Col(2).Normalized();
}

void CCamera::Inspector()
{
	if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::Text("");
		ImGui::Text("Rendered objects: %d", printCount);
		ImGui::Text("");

		if (ImGui::SliderInt("FOV", &FOV, 5, 180)) {
			FrustumCam.verticalFov = FOV * DEGTORAD;
			FrustumCam.horizontalFov = 2.0f * atanf(tanf(FrustumCam.verticalFov / 2.0f) * 1.7f);
		}
		if (ImGui::Button("Reset FOV")) {
			FOV = 60.0f;

			FrustumCam.verticalFov = FOV * DEGTORAD;
			FrustumCam.horizontalFov = 2.0f * atanf(tanf(FrustumCam.verticalFov / 2.0f) * 1.7f);
		}


		ImGui::SliderFloat("Near Distance", &FrustumCam.nearPlaneDistance, 0.1f, FrustumCam.farPlaneDistance);
		if (ImGui::Button("Reset Near Distance")) {
			FrustumCam.nearPlaneDistance = 0.1f;
		}

		ImGui::InputFloat("Far Distance", &FrustumCam.farPlaneDistance);
		if (ImGui::Button("Reset Far Distance")) {
			FrustumCam.farPlaneDistance = 500.f;
		}
		ImGui::Text("");
		if (ImGui::Button("Set Main Camera", ImVec2(120, 50))) {
			Application::GetApp()->renderer3D->mainCam = this;
		}
	}
}

// tests if a AaBox is within the frustrum
bool CCamera::ContainsAaBox(Mesh* refBox)
{
	float3 vCorner[8];
	int iTotalIn = 0;
	refBox->aabb.GetCornerPoints(vCorner); // get the corners of the box into the vCorner array

	Plane m_plane[6];
	FrustumCam.GetPlanes(m_plane);

	// test all 8 corners against the 6 sides
	// if all points are behind 1 specific plane, we are out
	// if we are in with all points, then we are fully in
	for (int p = 0; p < 6; ++p) {
		int iInCount = 8;
		int iPtIn = 1;
		for (int i = 0; i < 8; ++i) {
			// test this point against the planes
			if (m_plane[p].IsOnPositiveSide(vCorner[i])) { //<-- “IsOnPositiveSide” from MathGeoLib
				iPtIn = 0;
				--iInCount;
			}
		}
		// were all the points outside of plane p?
		if(iInCount == 0)
			return false;
		// check if they were all on the right side of the plane
		iTotalIn += iPtIn;
	}
	// so if iTotalIn is 6, then all are inside the view
	if (iTotalIn == 6)
		return true;
}

