
# OpenGL1 Texture Rendering Project with Dear ImGUI

 <br>

## Project Description

This project showcases texture rendering in OpenGL, using custom shaders and UI controls built with Dear ImGUI. The program renders two textures of Yoshi, the popular character from Super Mario, on two separate squares, allowing real-time control of their positions and background color through the UI. Developed entirely from scratch, this project explores OpenGL’s rendering pipeline, including vertex and fragment shaders, buffers, and texture handling. The use of Dear ImGUI demonstrates the integration of UI elements to control and modify object properties dynamically.

 <br>

![OpenGL-1](https://github.com/user-attachments/assets/cbee46eb-4128-4784-a489-d52392538533)

 <br>
 
--------------------------------

## Features

- **Window Creation**: Set up from scratch to create a rendering window.
- **Rendering Pipeline**: Custom implementation of the OpenGL rendering pipeline, including shaders and texture handling.
- **Textures**: Two Yoshi textures are rendered on two squares, created from triangles.
- **UI Controls**: Dear ImGUI integration to allow real-time modification of texture positions and background color.

---------------------------------


## Shaders

### Vertex Shader
Handles the transformation of 3D coordinates into screen space and passes texture coordinates to the fragment shader.

```glsl
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinate;

out vec2 vTextureCoordinates;

uniform mat4 uModelViewProjectionMatrix;

void main()
{
    gl_Position = uModelViewProjectionMatrix * position;
    vTextureCoordinates = textureCoordinate;
}
```

### Fragment Shader
Renders the texture color on the object, blending it with the background color.

```glsl
ayout (location = 0) out vec4 color;

in vec2 vTextureCoordinates;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{
    vec4 textureColor = texture(uTexture, vTextureCoordinates);
    color = textureColor;
}
```

## Directory Structure
- **Dependencies**: External libraries like GLEW and GLFW required for OpenGL rendering.
- **Release**: Contains the final executable of the project.
- **OpenGL1**: The main project folder containing:
- **Assets**: Stores shaders and textures used in the project.
- **Include**: Contains header files, including external libraries like glm, ImGUI, and stb_image.
- **Source**: Contains C++ source files and main.cpp (App.cpp).

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/Pecas-Dev/OpenGL-Project-1.git
```
2. Navigate to the Release folder within the project directory. Inside, you will find an executable that allows you to run the app directly.

3. If you prefer to build the project manually, open the solution in Visual Studio, choose the x86 Platform, and build the project.

4. Once the program is running, you can use the Dear ImGUI interface to manipulate the textures and background color in real-time.
   
## Controls

- Use Dear ImGUI UI controls to move textures and change the background color.

## Credits

This project was created by _**Pecas Dev**_.
