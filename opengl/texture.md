# Texture
-[Learn opengl](https://learnopengl.com/Getting-started/Textures
-[OpenGL Programming](https://en.wikibooks.org/wiki/OpenGL_Programming]

In order to map a texture to the triangle we need to tell each vertex of the triangle which part of the texture it corresponds to. Each vertex should thus have a texture coordinate associated with them that specifies what part of the texture image to sample from. Fragment interpolation then does the rest for the other fragments.

Texture coordinates range from 0 to 1 in the x and y axis (2D texture images). Retrieving the texture color using texture coordinates is called sampling. Texture coordinates start at (0,0) for the lower left corner of a texture image to (1,1) for the upper right corner of a texture image. The following image shows how we map texture coordinates to the triangle: 
![https://learnopengl.com/img/getting-started/tex_coords.png]

## Texture types

## Sample Types

## Image


## Load Texture
```
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
int width, height, nrChannels;
unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
if (data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
```

## Vetices 
```
float vertices[] = {  // with attributes, such as color,textcoord,normal,frog
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
};

glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(6*sizeof(float)));
glEnableVertexAttribArray(2);  

glBindBuffer(GL_ARRAY_BUFFER, vbo); glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

#version 330 core
layout (location = 0) in vec3 aPos;     // location only for vetex shader, first component
layout (location = 1) in vec3 aColor;   // second component
layout (location = 2) in vec2 aTexCoord;// third component

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}
```

## [glVertexAttribPointer](https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glVertexAttribPointer.xhtml)
```
void glVertexAttribPointer (GLuint index,	GLint size,	GLenum type,GLboolean normalized,	GLsizei stride,	const void * pointer);
void glVertexAttribIPointer(GLuint index,	GLint size,	GLenum type, GLsizei stride, const void * pointer);
void glVertexAttribLPointer(GLuint index,	GLint size,	GLenum type, GLsizei stride, const void * pointer);
```
For example:
```
glVertexAttribPointer(0, 3, GL_FLOAT, false, Vertex.SIZE * 4, 0);
```
Need tell OpenGL where to get the data for attribute 0 (first argument) from, and how to read it. 
- the data is read from the buffer currently bound to GL_ARRAY_BUFFER 
- it has 3 components
- the components are float values
- vertices are read with a stride of 20 bytes
- starting at byte 0 of the buffer

## [Vetex with additional attributes](https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_03)


