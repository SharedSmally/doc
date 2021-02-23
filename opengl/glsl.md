# OpenGL Shading Language [GLSL](https://www.khronos.org/opengl/wiki/OpenGL_Shading_Language)
Write program running in GPU.

## Objects

##[Data Types](https://www.khronos.org/opengl/wiki/Data_Type_(GLSL))
Scalars
- bool: conditional type, values may be either true or false
- int: a signed, two's complement, 32-bit integer
- uint: an unsigned 32-bit integer
- float: an IEEE-754 single-precision floating point number
- double: an IEEE-754 double-precision floating-point number)

Vectors: Each of the scalar types have 2, 3, and 4-component vector equivalents. The n digit below can be 2, 3, or 4. 
- bvecn: a vector of booleans
- ivecn: a vector of signed integers
- uvecn: a vector of unsigned integers
- vecn: a vector of single-precision floating-point numbers
- dvecn: a vector of double-precision floating-point numbers
swizzling: use x, y, z, or w, referring to the first, second, third, and fourth components, respectively, or use xyzw, rgba (for colors), or stpq (for texture coordinates).
```
vec4 someVec;
someVec.x + someVec.y;
vec2 someVec;
vec4 otherVec = someVec.xyxx;
vec3 thirdVec = otherVec.zyy;
vec4 someVec;
someVec.wzyx = vec4(1.0, 2.0, 3.0, 4.0); // Reverses the order.
someVec.zx = vec2(3.0, 5.0); // Sets the 3rd component of someVec to 3.0 and the 1st component to 5.0
```

Matrices: floating-point, either single-precision or double-precision. Matrix types are as follows, where n and m can be the numbers 2, 3, or 4:
- matnxm: A matrix with n columns and m rows. OpenGL uses column-major matrices, which is standard for mathematics users. Example: mat3x4.
- matn: A matrix with n columns and n rows. Shorthand for matnxn

Double-precision matrices (GL 4.0 and above) can be declared with a dmat instead of mat 
```
mat3 theMatrix;
theMatrix[1] = vec3(3.0, 3.0, 3.0); // Sets the second column to all 3.0s
theMatrix[2][0] = 16.0; // Sets the first entry of the third column to 16.0.

theMatrix[1].yzx = vec3(3.0, 1.0, 2.0);
```

Opaque types
Opaque types represent some external object which the shader references in some fashion.
Opaque variables do not have "values" in the same way as regular types; they are markers that reference the real data.
They can only be used as parameters to functions. These functions return/modify the actual referenced data. 






    

