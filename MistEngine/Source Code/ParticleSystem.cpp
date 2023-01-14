#include "Application.h"
#include "ParticleSystem.h"

//#include "Random.h"


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

		if (ParticleList[i].LifeTime <= 0.0f)
		{
			ParticleList[i].Active = false;
			continue;
		}

		ParticleList[i].LifeTime -= Application::GetApp()->dt;
		ParticleList[i].pos += ParticleList[i].speed * Application::GetApp()->dt;	
		ParticleList[i].SetTransformMatrix();
	}
}

void ParticleSystem::Emit(ParticleProps& particleProps)
{
	Particle& particle = ParticleList[ListIndex];
	particle.Active = true;
	particle.pos = particleProps.pos;
	particle.scale = particleProps.scale;

	text = particleProps.texture;
	// Velocity
	particle.speed = particleProps.speed;
	//particle.speed.x += particleProps.speedVariation.x * (Random::Float() - 0.5f);
	//particle.speed.y += particleProps.speedVariation.y * (Random::Float() - 0.5f);
	//particle.speed.z += particleProps.speedVariation.z * (Random::Float() - 0.5f);

	// Color
	Color = particleProps.Color;

	particle.LifeTime = particleProps.LifeTime;

	ListIndex = ++ListIndex % ParticleList.size();
}

void ParticleSystem::ParticleBuffer()
{
	uint indices[]
	{
		// Front
		0, 1, 2, // ABC
		2, 3, 0, // BDC
	};

	float vertices[]
	{
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f,//a
		 0.5f, -0.5f, 0.0f, 1.0f, 1.0f,//b
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f,//c
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,//d

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
	else {
		glColor4f(Color.x, Color.y, Color.z, Color.w);
	}
	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);

	for (int i = 0; i < ParticleList.size(); i++)
	{
		if (!ParticleList[i].Active)
			continue;

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

float4x4 Particle::GetTransformMatrix()
{
	return transformMat;
}