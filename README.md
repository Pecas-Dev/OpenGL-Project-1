# OpenGL1 Texture Rendering Project with Dear ImGUI

 <br>

---

## Project Description

This project showcases **texture rendering in OpenGL**, using **custom shaders** and **UI controls built with Dear ImGUI**. The program renders two textures of [**Yoshi**](https://play.nintendo.com/themes/friends/yoshi/), on two separate squares, allowing **real-time control** of their **positions** and **background color** through the UI. Developed entirely from scratch, this project explores OpenGL’s rendering pipeline, including vertex and fragment shaders, buffers, and texture handling. The use of Dear ImGUI demonstrates the integration of UI elements to control and modify object properties dynamically.

---

 <br>

![OpenGL-1](https://github.com/user-attachments/assets/cbee46eb-4128-4784-a489-d52392538533)

 <br>
 
--------------------------------

## Features

- **Window Creation**: Set up from scratch to create a rendering window.
- **Rendering Pipeline**: Custom implementation of the OpenGL rendering pipeline, including shaders and texture handling.
- **Textures**: Two Yoshi textures are rendered on two squares, created from triangles.
- **UI Controls**: Dear ImGUI integration to allow real-time modification of texture positions and background color.

---

 <br>

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
layout (location = 0) out vec4 color;

in vec2 vTextureCoordinates;

uniform vec4 uColor;
uniform sampler2D uTexture;

void main()
{
    vec4 textureColor = texture(uTexture, vTextureCoordinates);
    color = textureColor;
}
```

 <br>

---

## Directory Structure

```
Project Root
├── OpenGL1.sln                      // Visual Studio solution file
├── .gitattributes
├── .gitignore
├── bin                              // Binary files
├── Dependencies                     // External dependencies
│   ├── x86
│   │   ├── GLEW
│   │   └── GLFW
│   └── x64
│       ├── GLEW
│       └── GLFW
│
├── Release                          // Pre-compiled executables
│   ├── OpenGL1_x64.bat              // Run x64 OpenGL1
│   ├── OpenGL1_x86.bat              // Run x86 OpenGL1
│   └── Platforms
│       ├── x64                      // 64-bit builds
│       │   └── OGL-P1               // Contains the necessary files to run the executable.
│       │       └── Assets
│       │           ├── Shaders
│       │           └── Textures
│       └── Win32                    // 32-bit builds
│           └── OGL-P1               // Contains the necessary files to run the executable.
│               └── Assets
│                   ├── Shaders
│                   └── Textures
│
└── OpenGL1
    ├── Assets                       // Stores shaders, and textures.
    │   ├── Textures
    │   └── Shaders
    │
    └── Project                      // Contains the source code for the OpenGL1 Project.
        ├── include
        └── source
```

---

<br>

## Installation & Running

<br>

**Clone the repository:**

```bash
git clone https://github.com/Pecas-Dev/OpenGL-Project-1.git
```

### Pre-compiled Executables

The easiest way to run the simulation is using the pre-compiled executables:

1. Navigate to the `Release` folder.
2. Choose the appropriate version for your system (`x64` or `86`).
3. Run the `OpenGL1_x64.bat` or `OpenGL1_x86.bat`or file.

### Building from Source

To build the project from source:

1. Open `OpenGL1.sln` in Visual Studio.
2. Choose your configuration (**Debug/Release**) and platform (**x64/x86**).
3. Build the solution.
4. Run the program.

<br>

---

## Controls

- Use Dear ImGUI UI controls to move textures and change the background color.

<br>

## Credits

This project was created by _**Pecas Dev**_.
