#include "Application.h"
#include "ParticleSystem.h"
#include "Random.h"
#include "Camera.h"
#include "Transform.h"
#include "ModuleScene.h"

ParticleSystem::ParticleSystem() {
	
	ParticleList.resize(1000);	
}

ParticleSystem::~ParticleSystem()
{

}

void ParticleSystem::Update() {

	for (int i = 0; i < ParticleList.size(); i++)
	{
		if (!ParticleList[i].Active)
			continue;

		if (ParticleList[i].LifeRemaining <= 0.0f)
		{
			ParticleList[i].Active = false;
			continue;
		}

		ParticleList[i].LifeRemaining -= Application::GetApp()->dt;
		ParticleList[i].pos += ParticleList[i].speed * Application::GetApp()->dt;
		ParticleList[i].SetTransformMatrix();
	}
}

void ParticleSystem::Emit(ParticleProps& particleProps)
{
	Particle& particle = ParticleList[ListIndex];
	particle.Active = true;
	particle.pos = particleProps.pos;
	particle.beginScale = particleProps.beginScale + particleProps.scaleVariaton * (Random::RandomFloat() - 0.5f); //Random number between -0.5 / 0.5
	particle.endScale = particleProps.endScale;

	text = particleProps.texture;
	// Velocity
	particle.speed = particleProps.speed;
	particle.speed.x += particleProps.speedVariation.x * (Random::RandomFloat() - 0.5f);
	particle.speed.y += particleProps.speedVariation.y * (Random::RandomFloat() - 0.5f);
	particle.speed.z += particleProps.speedVariation.z * (Random::RandomFloat() - 0.5f);

	// Color
	particle.Color = particleProps.Color;
	particle.endColor = particleProps.endColor;

	particle.LifeTime = particleProps.LifeTime;
	particle.LifeRemaining = particleProps.LifeTime;

	ListIndex = --ListIndex % ParticleList.size();
}

void ParticleSystem::ParticleBuffer()
{
	uint indices[]
	{
		0, 1, 2, 
		2, 3, 0, 
	};

	float vertices[]
	{
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, //0
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, //1
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, //2
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, //3

	};

	//Fill buffers with vertices
	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, (GLuint*)&(id_vertices));
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * VERTICES, vertices, GL_STATIC_DRAW);

	//Fill buffers with indices
	glGenBuffers(1, (GLuint*)&(id_indices));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 6, indices, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);

}

void ParticleSystem::Render() {

	//Vertices
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertices);

	glVertexPointer(3, GL_FLOAT, sizeof(float) * VERTICES, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * VERTICES, (void*)(sizeof(float) * 3));
	//bind and use other buffers


	if (text) {

		glBindTexture(GL_TEXTURE_2D, textID);

	}

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	for (int i = 0; i < ParticleList.size(); i++)
	{
		if (!ParticleList[i].Active)
			continue;


		float life = ParticleList[i].LifeRemaining / ParticleList[i].LifeTime;
		ParticleList[i].scale = Lerp(ParticleList[i].endScale, ParticleList[i].beginScale, life);
		float4 printColor = Lerp(ParticleList[i].endColor, ParticleList[i].Color, life);
		ParticleList[i].SetTransformMatrix();

		Billboard(ParticleList[i]);

		if (!text) {
			glColor4f(printColor.x, printColor.y, printColor.z, printColor.w);
		}

		glPushMatrix();
		
		glMultMatrixf(ParticleList[i].GetTransformMatrix().ptr());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);

		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	//cleaning texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);

}

void Particle::SetTransformMatrix()
{
	float x = rot.x * DEGTORAD;
	float y = rot.y * DEGTORAD;
	float z = rot.z * DEGTORAD;

	Quat q = Quat::FromEulerXYZ(x, y, z);

	transformMat = float4x4::FromTRS(pos, q, scale).Transposed();
}

void Particle::SetTransform(float4x4 matrix)
{
	Quat rotation;
	matrix.Decompose(pos, rotation, scale);

	rot = rotation.ToEulerXYZ();
}

float4x4 Particle::GetTransformMatrix()
{
	return transformMat;
}

void ParticleSystem::Billboard(Particle &particle) {

	float3 right, up, look;
	CCamera* cam;

	if (Application::GetApp()->scene->sceneSelected) {
		cam = Application::GetApp()->camera->sceneCam;
	}
	else {
		cam = Application::GetApp()->renderer3D->mainCam;
	}

	look = float3(cam->FrustumCam.pos - particle.pos).Normalized();
	up = cam->FrustumCam.up;
	right = up.Cross(look);

	float4x4 transform = float4x4::identity;
	transform[0][0] = right.x * particle.scale.x;
	transform[1][0] = right.y;
	transform[2][0] = right.z;

	transform[0][1] = up.x;
	transform[1][1] = up.y * particle.scale.y;
	transform[2][1] = up.z;

	transform[0][2] = look.x;
	transform[1][2] = look.y;
	transform[2][2] = look.z * particle.scale.z;
	
	transform[0][3] = particle.pos.x;
	transform[1][3] = particle.pos.y;
	transform[2][3] = particle.pos.z;

	transform[3][0] = 0;
	transform[3][1] = 0;
	transform[3][2] = 0;
	transform[3][3] = 1;

	transform.Transpose();

	particle.transformMat = transform;
}


