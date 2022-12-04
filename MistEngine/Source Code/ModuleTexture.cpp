#pragma once
#include "Globals.h"
#include "Application.h"
#include "ModuleTexture.h"

ModuleTexture::ModuleTexture(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleTexture::~ModuleTexture()
{
}

bool ModuleTexture::Start()
{
	
	{
		//create procedurally a checker texture
		for (int i = 0; i < CHECKERS_HEIGHT; i++) {
			for (int j = 0; j < CHECKERS_WIDTH; j++) {
				int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
				checkerImage[i][j][0] = (GLubyte)c;
				checkerImage[i][j][1] = (GLubyte)c;
				checkerImage[i][j][2] = (GLubyte)c;
				checkerImage[i][j][3] = (GLubyte)255;
			}
		}

		glEnable(GL_TEXTURE_2D);

		//Generate and bind a texture buffer
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &checkerID);
		glBindTexture(GL_TEXTURE_2D, checkerID);

		//Pick your texture settings with glTexParameter()

		//GL_TEXTURE_WRAP_S/T: How the texture behaves outside 0,1 range (s = x ; t = y)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Resize the texture (MIN->make it smaller ; MAG->make it bigger)
		//Nearest -> pixelat / Linear -> borros
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//Generate the texture
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CHECKERS_WIDTH, CHECKERS_HEIGHT,
			0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

		//Mipmap can be added or not
		glGenerateMipmap(GL_TEXTURE_2D);

		//cleaning texture
		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
	}

	//Initialize clear color
	glClearColor(0.f, 0.f, 0.f, 1.f);


	//Initialize DevIL
	ilInit();
	ilClearColour(255, 255, 255, 000);

	//texPath = "Assets/Baker_house.png";
	//LoadTexture(texPath);

	return true;
}



bool ModuleTexture::CleanUp()
{
	return true;
}

GLuint ModuleTexture::GenTexture(GLuint* imgData, GLuint width, GLuint height)
{
	//Clean textures if there is another
	GLuint TextID = 0;

	glEnable(GL_TEXTURE_2D);

	//Generate and bind a texture buffer
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &TextID);
	glBindTexture(GL_TEXTURE_2D, TextID);

	//Pick your texture settings with glTexParameter()

	//GL_TEXTURE_WRAP_S/T: How the texture behaves outside 0,1 range (s = x ; t = y)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Resize the texture (MIN->make it smaller ; MAG->make it bigger)
	//Nearest -> pixelat / Linear -> borros
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Generate the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);

	//Mipmap can be added or not
	glGenerateMipmap(GL_TEXTURE_2D);

	//cleaning texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


	return TextID;
}

GLuint ModuleTexture::LoadTexture(string path)
{
	//Texture loading success
	GLuint TextID = 0;

	//Generate and set current image ID
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	//Load image
	ILboolean success = ilLoadImage(path.c_str());

	if (path.substr(path.find_last_of(".") + 1) == "png") 
	{
		iluFlipImage();
	}

	//Image loaded successfully
	if (success == IL_TRUE)
	{
		//Convert image to RGBA
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success == IL_TRUE)
		{
			//Create texture from file pixels
			TextID = GenTexture((GLuint*)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		//Delete file from memory
		ilDeleteImages(1, &imgID);

		//Report error
		if (TextID == 0)
		{
			printf("Unable to load %s\n", path.c_str());
		}
	}
	return TextID;
}

void ModuleTexture::FreeTexture(GLuint ID)
{
	//Delete texture
	if (ID != 0)
	{
		glDeleteTextures(1, &ID);
		ID = 0;
	}
}
