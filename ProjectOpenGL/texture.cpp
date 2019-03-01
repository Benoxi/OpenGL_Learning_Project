#include "texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>

Texture::Texture(const std::string& fileName)
{
	// this constructor much depends on what texture loader we are using! (not at all universal)

	/*unsigned*/int width, height, numComponents;
	// used for loading texture data
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponents, 4);

	if (imageData == 0)
		std::cerr << "Texture loading failed for texture: " << fileName << std::endl;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	// specefying more data about the image we are sending
	glTexParameteri(
		GL_TEXTURE_2D,
		// controls texture wraping (what happens outsinde the boundries (x and y))
		GL_TEXTURE_WRAP_S,
		// tells us what should happen in case we bridge the boundrie
		GL_REPEAT
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(
		GL_TEXTURE_2D,
		// we control what will happen when the texture goes of in to the distance (MIN) and 
		// when the texture becomes takes up more pixels than it has (MAG)
		GL_TEXTURE_MIN_FILTER,
		// interpolates between existing colors
		GL_LINEAR
	);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// sending our texture to the GPU
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	// deleteing texture data form CPU
	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	// the unit lets us numerize textures wich in turn lets us determinate wich texture is wich
	// for now everything will be enumerated as 0
	assert(unit >= 0 && unit <= 31);

	// changes wich texture OpenGL is working with RN
	glActiveTexture(GL_TEXTURE + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
