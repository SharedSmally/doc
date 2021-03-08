# Install python 3
```
$ python --version
Python 2.7.18
$ sudo apt-get install python3.8 python3.8-dev python3.8-distutils python3.8-venv
$ python3.8 -m venv dev3.8/
$ source dev3.8/bin/activate
$ which python
$HOME/dev3.8/bin/python
$ python --version
Python 3.8.5
$ pip3 install numpy
$ pip3 install wxpython
$ pip3 install matplot

$ pip3 install PyOpenGL PyOpenGL_accelerate  (OpenGL2); need OpenGL3.0 for shader, use Modern GL
# pip3 install PyOpenGL==3.0.2
$ python3 install pygame 
```
Install eclipse with pydev


## Editors
- Grid Editor
    - wx.grid.GridCellAutoWrapStringEditor  (multi-line text control)
    - wx.grid.GridCellBooleanEditor:  An editor for Boolean cell data
    - wx.grid.GridCellChoiceEditor: An editor for a specific list of options. 
    - wx.grid.GridCellEnumEditor: Derives from wx.grid.GridCellChoiceEditor and manages equating the numeric data value to the string presented to the user.
    - wx.grid.GridCellFloatEditor: for floating point numbers with a specific precision. 
    - wx.grid.GridCellNumberEditor: for entering integer numbers. 
    - wx.grid.GridCellTextEditor:  The default editor for entering string data.
- Rich Text Editor:[RichTextCtrl](https://wxpython.org/Phoenix/docs/html/wx.richtext.RichTextCtrl.html)
- STC Styled Editor:[wxStyledTextCtrl](https://wxpython.org/Phoenix/docs/html/wx.stc.StyledTextCtrl.html#phoenix-title-wx-stc-styledtextctrl) and [API](https://wxpython.org/Phoenix/docs/html/wx.stc.StyledTextCtrl.html)
    - [Automatic Syntax Highlighting](https://github.com/jacobslusser/ScintillaNET/wiki/Automatic-Syntax-Highlighting): using Lexer.
    - [Lexer](https://wiki.wxpython.org/StyledTextCtrl%20Lexer%20Quick%20Reference)
    - [Customized Lexer](https://wiki.wxwidgets.org/Adding_a_custom_lexer_with_syntax_highlighting_and_folding_to_a_WxStyledTextCtrl)
```
scintilla.Lexer = Lexer.Cpp;
```
    - [Auto completion](https://github.com/jacobslusser/ScintillaNET/wiki/Basic-Autocompletion)   
- [Customized Editor](https://www.pythonstudio.us/wxpython/creating-a-custom-editor.html)

## GLCanvas
- [GLCanvas wiki](https://wiki.wxwidgets.org/WxGLCanvas)
- [GlCanvas sample](https://wiki.wxpython.org/GLCanvas%20update)
- [PyGame](https://stackabuse.com/advanced-opengl-in-python-with-pygame-and-pyopengl/)
- [Opengl Tutorial](https://open.gl/drawing)
- [PyOpenGL tutorial](http://pyopengl.sourceforge.net/context/documentation.html)
- [OpenGLContext tutorial](http://pyopengl.sourceforge.net/context/documentation.html): fails to install using: ```pip3 install openglcontext```

## GLCanvas Samples
- [Sample1](# https://wiki.wxpython.org/GLCanvas%20update): keys.sort() => sorted(keys)
- [Sample2](https://wiki.wxpython.org/GLCanvas)
- [Sample3](https://community.khronos.org/t/rubberband-problems-using-opengl-wxpython/57581): Add self.context = glcanvas.GLContext(self)

For the older (before wx 2.7.x) and simpler method, create a wxGLCanvas window using one of the three constructors that implicitly create a rendering context, call wxGLCanvas::SetCurrent to direct normal OpenGL commands to the window, and then call wxGLCanvas::SwapBuffers to show the OpenGL buffer on the window.

For the newer (wx 2.7.x+) method, create a wxGLCanvas window using the constructor that does not create an implicit rendering context, create an explicit instance of a wxGLContext that is initialized with the wxGLCanvas yourself, then use either wxGLCanvas::SetCurrent with the instance of the wxGLContext or wxGLContext::SetCurrent with the instance of the wxGLCanvas to bind the OpenGL state that is represented by the rendering context to the canvas, and then call wxGLCanvas::SwapBuffers to swap the buffers of the OpenGL canvas and thus show your current output.

To set up the attributes for the canvas (number of bits for the depth buffer, number of bits for the stencil buffer and so on) you should set up the correct values of the attribList parameter. The values that should be set up and their meanings will be described below.

```
import pygame as pg
from pygame.locals import *

from OpenGL.GL import *
from OpenGL.GLU import *

cubeVertices = ((1,1,1),(1,1,-1),(1,-1,-1),(1,-1,1),(-1,1,1),(-1,-1,-1),(-1,-1,1),(-1,1,-1))
cubeEdges = ((0,1),(0,3),(0,4),(1,2),(1,7),(2,5),(2,3),(3,6),(4,6),(4,7),(5,6),(5,7))
cubeQuads = ((0,3,6,4),(2,5,6,3),(1,2,5,7),(1,0,4,7),(7,4,6,5),(2,3,0,1))

def wireCube():
    glBegin(GL_LINES)
    for cubeEdge in cubeEdges:
        for cubeVertex in cubeEdge:
            glVertex3fv(cubeVertices[cubeVertex])
    glEnd()

def solidCube():
    glBegin(GL_QUADS)
    for cubeQuad in cubeQuads:
        for cubeVertex in cubeQuad:
            glVertex3fv(cubeVertices[cubeVertex])
    glEnd()

def main():
    pg.init()
    display = (1680, 1050)
    pg.display.set_mode(display, DOUBLEBUF|OPENGL)

    gluPerspective(45, (display[0]/display[1]), 0.1, 50.0)

    glTranslatef(0.0, 0.0, -5)

    while True:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                quit()

        glRotatef(1, 1, 1, 1)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        solidCube()
        #wireCube()
        pg.display.flip()
        pg.time.wait(10)

if __name__ == "__main__":
    main()
```
