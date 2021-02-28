# Shader Tools
## Turorials
- [Learn OpenGL](https://learnopengl.com/G)


## [Shadertoy](https://www.shadertoy.com/)
- [Create a new image](https://www.shadertoy.com/new)
- [Document](https://www.shadertoy.com/howto)
- Input Uniforms:
```
uniform vec3      iResolution;           // viewport resolution (in pixels)
uniform float     iTime;                 // shader playback time (in seconds)
uniform float     iTimeDelta;            // render time (in seconds)
uniform int       iFrame;                // shader playback frame
uniform float     iChannelTime[4];       // channel playback time (in seconds)
uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
uniform vec4      iMouse;                // mouse pixel coords. xy: current (if MLB down), zw: click
uniform samplerXX iChannel0..3;          // input channel. XX = 2D/Cube
uniform vec4      iDate;                 // (year, month, day, time in seconds)
uniform float     iSampleRate;           // sound sample rate (i.e., 44100)
```
- Shaders
```
Image shaders
void mainImage( out vec4 fragColor, in vec2 fragCoord );
fragCoord: pixel coordinates to compute a color. in pixel units [-0.5,0.5] with resolution of iResolution.
fragColor: result color

Sound shaders
vec2 mainSound( float time )
  time: the time in seconds of the sound sample to calculate the wave amplitude with sample rate of iSampleRate
  
VR shaders
void mainVR( out vec4 fragColor, in vec2 fragCoord, in vec3 fragRayOri, in vec3 fragRayDir )
fragRayOri/fragRayDir: ray origin and direction that goes through that pixel in the virtual world given in tracker space
```
 
## Visual Codes
- glslCanvas
- glslViewer
- GLSL Linter
