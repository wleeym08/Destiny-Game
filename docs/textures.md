# Textures

Texture is important for creating programs with graphics. 

## Mechanism

In OpenGL, we are allowed to store multiple texture buffers in the graphic cards. Usually there will be more than 80 available slots for us to switch from different textures. A texture can be generated from image files. OpenGL can load data from bitmap files and convert them into textures. For images of other formats, we need to use other libraries to convert them into BMP format before we use them. After we store a texture in a slot, we can bind it and specify the UV coordinates of the part we want to crop and use from it. It will be similar to providing the coordinates for vertex position. Needless to say, shaders with proper settings are also needed to use together with textures.

## Example

Here is an example of loading data from a bitmap (BMP) file and generating textures.

```
void loadBmpFile(char* fileName, GLuint* tObj) {
	char type[2];
	int dataStart;
	int imageSize;
	int width, height;
	unsigned char* data = NULL;
	float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	FILE* file = fopen(fileName, "rb");

	if (!file) {
		fprintf(stderr, "ERROR: CANNOT OPEN FILE\n");
		return;
	}

	fread(type, 1, 2, file);
	fseek(file, 0x0A, SEEK_SET); // grab data position
	fread(&dataStart, 4, 1, file);
	fseek(file, 0x22, SEEK_SET); // grab image size
	fread(&imageSize, 4, 1, file);
	fseek(file, 0x12, SEEK_SET); // grab width
	fread(&width, 4, 1, file);
	fread(&height, 4, 1, file); // grab height
	data = (unsigned char*)malloc(imageSize * sizeof(unsigned char));
	fseek(file, dataStart, SEEK_SET);
	fread(data, 1, imageSize, file);
	fclose(file);

	glGenTextures(1, tObj);
	glBindTexture(GL_TEXTURE_2D, *tObj);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glBindTexture(GL_TEXTURE_2D, 0);

	free(data);
}
```