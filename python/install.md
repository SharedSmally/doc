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

$ python3 install PyOpenGL PyOpenGL_accelerate
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
```
scintilla.Lexer = Lexer.Cpp;
```
    - [Auto completion](https://github.com/jacobslusser/ScintillaNET/wiki/Basic-Autocompletion)   
- [Customized Editor](https://www.pythonstudio.us/wxpython/creating-a-custom-editor.html)

## GLCanvas
- [GLCanvas wiki](https://wiki.wxwidgets.org/WxGLCanvas)
- [GlCanvas sample](https://wiki.wxpython.org/GLCanvas%20update)
- [PyGame](https://stackabuse.com/advanced-opengl-in-python-with-pygame-and-pyopengl/)
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
