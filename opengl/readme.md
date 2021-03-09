# OpenGL
## Game Engine
- [Flax](https://flaxengine.com): 
     - git source: https://github.com/FlaxEngine/FlaxEngine
     - install packages in README.txt
     - Clone repo with LFS:[git-lfs](https://www.atlassian.com/git/tutorials/git-lfs)
          -  curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash
          -  sudo apt-get install git-lfs
          -  git clone https://github.com/FlaxEngine/FlaxEngine
     - Run ./GenerateProjectFiles.sh
     - Compile using Visual Code
- [Unreal]()
- [Unity]()

- (YouTube to MP4)[https://www.youtube2video.com/en3/youtube-to-mp4]

## Linux OpenGL
- Core OpenGL (GL: glXxx): functions begin with a prefix "gl" (e.g., glColor, glVertex, glTranslate, glRotate).
- OpenGL Utility Library (GLU: gluXxx): built on-top of the core OpenGL to provide important utilities and more building models (such as qradric surfaces). 
- OpenGL Utilities Toolkit (GLUT:glutXxx): provides support to interact with the Operating System (window, key and mouse inputs); and more building models (such as sphere and torus). Alternative of GLUT includes SDL, ....
- OpenGL Extension Wrangler Library (GLEW): a cross-platform open-source C/C++ extension loading library. provides efficient run-time mechanisms for determining which OpenGL extensions are supported on the target platform(http://glew.sourceforge.net/).
- Programmable Pipeline: vertex shaders and fragment shaders, using GLSL (GL Shader Language), See http://xed.ch/h/opengl.html
```

apt-get install freeglut3 freeglut3-dev libglew-dev
apt-get install libglut3-dev glutg3-dev freeglut3-dev
apt-get install mesa-utils

sudo apt-get install libglew1.5 libglewmx1.5 libglew1.5-dev libglewmx1.5-dev glew-utils
#include <GL/glew.h>    
-lGL -lGLU -lglut -lGLEW -lm
```
Sample code
```
#include <GL/gl.h>
#include <GL/freeglut.h>

void drawTriangle()
{
    glClearColor(0.4, 0.4, 0.4, 0.4);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glBegin(GL_TRIANGLES);
       glVertex3f(-0.7, 0.7, 0);
       glVertex3f(0.7, 0.7, 0);
       glVertex3f(0, -1, 0);
    glEnd();

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL - Creating a triangle");
    glutDisplayFunc(drawTriangle);
    glutMainLoop();
    return 0;
}
```
makefile:
```
main: hello

hello: hello.cc
	g++ -o $@ $< -lGL -lglut
```
## PyOpengl
- [Document](http://pyopengl.sourceforge.net/documentation/index.html)

## Install PyOpenGL
```
sudo apt-get install python-dev 
curl https://bootstrap.pypa.io/2.7/get-pip.py  --output get-pip.py
sudo python get-pip.py
sudo pip install PyOpenGL PyOpenGL_accelerate   # no Python.h
sudo pip install image
sudo pip install glu

sudo apt-get install freeglut3-dev  # for glut

sudo apt-get install wxPython  # needs png.jpeglib,tiff, regex,GTK+
wx deps:
    python-dev 
    dpkg-dev
    build-essential
    libjpeg-dev
    libtiff-dev
    libsdl1.2-dev
    libgstreamer-plugins-base1.0-dev
    libnotify-dev
    freeglut3
    freeglut3-dev
    libsm-dev
    libgtk-3-dev
    libwebkit2gtk-4.0-dev
    libxtst-dev
```

## Sample
```
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

w,h= 500,500
def square():
    glBegin(GL_QUADS)
    glVertex2f(100, 100)
    glVertex2f(200, 100)
    glVertex2f(200, 200)
    glVertex2f(100, 200)
    glEnd()

def iterate():
    glViewport(0, 0, 500, 500)
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(0.0, 500, 0.0, 500, 0.0, 1.0)
    glMatrixMode (GL_MODELVIEW)
    glLoadIdentity()

def showScreen():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    glLoadIdentity()
    iterate()
    glColor3f(1.0, 0.0, 3.0)
    square()
    glutSwapBuffers()

glutInit()
glutInitDisplayMode(GLUT_RGBA)
glutInitWindowSize(500, 500)
glutInitWindowPosition(0, 0)
wind = glutCreateWindow("OpenGL Coding Practice")
glutDisplayFunc(showScreen)
glutIdleFunc(showScreen)
glutMainLoop()
```
For wxPython
```
import wx
from wx import glcanvas
from OpenGL.GL import *
from OpenGL.GLU import *
from OpenGL.GLUT import *
from OpenGL.GL.ARB.shader_objects import *
from OpenGL.GL.ARB.fragment_shader import *
from OpenGL.GL.ARB.vertex_shader import *
import numpy as np

vertexSource = """
#version 130
in vec2 position;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
}
"""
fragmentSource = """
#version 130
out vec4 outColor;
void main()
{
    outColor = vec4(1.0, 1.0, 1.0, 1.0);
}
"""

class OpenGLCanvas(glcanvas.GLCanvas):
    def __init__(self, parent):
        glcanvas.GLCanvas.__init__(self, parent, -1, size=(640, 480))
        self.init = False
        self.context = glcanvas.GLContext(self) 

    self.Bind(wx.EVT_ERASE_BACKGROUND, self.OnEraseBackground)
    self.Bind(wx.EVT_PAINT, self.OnPaint)

def OnEraseBackground(self, event):
    pass # Do nothing, to avoid flashing on MSW.

def OnPaint(self, event):
    dc = wx.PaintDC(self)
    self.SetCurrent(self.context)
    if not self.init:
        self.InitGL()
        self.init = True
    self.OnDraw()

def InitGL(self):

    # Vertex Input
    ## Vertex Array Objects
    vao = glGenVertexArrays(1)
    glBindVertexArray(vao)

    ## Vertex Buffer Object
    vbo = glGenBuffers(1) # Generate 1 buffer

    vertices = np.array([0.0,  0.5, 0.5, -0.5, -0.5, -0.5], dtype=np.float32)

    ## Upload data to GPU
    glBindBuffer(GL_ARRAY_BUFFER, vbo)
    glBufferData(GL_ARRAY_BUFFER, vertices.nbytes, vertices, GL_STATIC_DRAW)

    # Compile shaders and combining them into a program
    ## Create and compile the vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER)
    glShaderSource(vertexShader, vertexSource)
    glCompileShader(vertexShader)

    ## Create and compile the fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER)
    glShaderSource(fragmentShader, fragmentSource)
    glCompileShader(fragmentShader)

    ## Link the vertex and fragment shader into a shader program
    shaderProgram = glCreateProgram()
    glAttachShader(shaderProgram, vertexShader)
    glAttachShader(shaderProgram, fragmentShader)
    glBindFragDataLocation(shaderProgram, 0, "outColor")
    glLinkProgram(shaderProgram)
    glUseProgram(shaderProgram)

    # Making the link between vertex data and attributes
    posAttrib = glGetAttribLocation(shaderProgram, "position")
    glEnableVertexAttribArray(posAttrib)
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0)

def OnDraw(self):
    # Set clear color
    glClearColor(0.0, 0.0, 0.0, 1.0)
#Clear the screen to black
    glClear(GL_COLOR_BUFFER_BIT)

    # draw six faces of a cube
    glDrawArrays(GL_TRIANGLES, 0, 3)

    self.SwapBuffers()

class Frame(wx.Frame):
    def __init__(self):
        wx.Frame.__init__(self, None, title="Hello World", size=(640,480))
        canvas = OpenGLCanvas(self)

app = wx.App()
frame = Frame()
frame.Show()
app.MainLoop()
```
