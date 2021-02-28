# opengl functions

## Tutorials
- [Learn opengl](https://learnopengl.com/Getting-started/Textures
- [OpenGL Programming](https://en.wikibooks.org/wiki/OpenGL_Programming]


```
#include <GL/gl.h>
```
Components:
- Objects
- Viewer
- Light Source
- Material Properties

- VAO: Vertex Array Object
- VBO: Vertex Buffer Object
- IBO: Index buffer object.

- GLSL: OpenGL Shading Language
- SDL: Simple DirectMedia Layer

## Objects
### [Vertex Specification](https://www.khronos.org/opengl/wiki/Vertex_Specification)
### [Primitives](https://www.khronos.org/opengl/wiki/Primitive)
```
void glBegin(	GLenum mode);
   xxx   
void glEnd()
```
#### Point primitives
- GL_POINTS:
#### Line primitives
- GL_LINES: Vertices 0 and 1 are considered a line. Vertices 2 and 3 are considered a line. And so on. If the user specifies a non-even number of vertices, then the extra vertex is ignored.
- GL_LINE_STRIP: The adjacent vertices are considered lines. Thus, if you pass n vertices, you will get n-1 lines. If the user only specifies 1 vertex, the drawing command is ignored.
- GL_LINE_LOOP: As line strips, except that the first and last vertices are also used as a line. Thus, you get n lines for n input vertices. If the user only specifies 1 vertex, the drawing command is ignored. The line between the first and last vertices happens after all of the previous lines in the sequence.
#### Triangle primitives
- GL_TRIANGLES: Vertices 0, 1, and 2 form a triangle. Vertices 3, 4, and 5 form a triangle. And so on.
- GL_TRIANGLE_STRIP: Every group of 3 adjacent vertices forms a triangle. The face direction of the strip is determined by the winding of the first triangle. Each successive triangle will have its effective face order reversed, so the system compensates for that by testing it in the opposite way. A vertex stream of n length will generate n-2 triangles.
- GL_TRIANGLE_FAN: The first vertex is always held fixed. From there on, every group of 2 adjacent vertices form a triangle with the first. So with a vertex stream, you get a list of triangles like so: (0, 1, 2) (0, 2, 3), (0, 3, 4), etc. A vertex stream of n length will generate n-2 triangles.   
#### Quad primitives
- GL_QUADS: Vertices 0-3 form a quad, vertices 4-7 form another, and so on. The vertex stream must be a number of vertices divisible by 4 to work.
- GL_QUAD_STRIP: Similar to triangle strips, a quad strip uses adjacent edges to form the next quad. In the case of quads, the third and fourth vertices of one quad are used as the edge of the next quad. So vertices 0-3 are a quad, 2-5 are a quad, and so on. A vertex stream of n length will generate (n - 2) / 2 quads. As with triangle strips, the winding order of quads is changed for every other quad.
    
The modern way is to use VAOs with VBOs (and IBOs).


### Misc
Hippodraw: https://www.slac.stanford.edu/grp/ek/hippodraw/lib/hierarchy.html

