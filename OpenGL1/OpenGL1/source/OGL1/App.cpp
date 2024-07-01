#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <OGL1/Renderer/Renderer.h>
#include <OGL1/VertexBuffer/VertexBuffer.h>
#include <OGL1/IndexBuffer/IndexBuffer.h>
#include <OGL1/VertexArray/VertexArray.h>
#include <OGL1/VertexBufferLayout/VertexBufferLayout.h>
#include <OGL1/Shaders/Shaders.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "My OpenGL1 Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(2);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error!!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		float positions[] = {
			-0.5f, -0.5f, //0
			 0.5f, -0.5f, //1
			 0.5f,  0.5f, //2
			-0.5f,  0.5f, //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		Renderer renderer;

		// VERTEX ARRAY OBJECT
		unsigned vertexArrayObject;
		GLCall(glGenVertexArrays(1, &vertexArrayObject));
		GLCall(glBindVertexArray(vertexArrayObject));

		// VERTEX BUFFER
		VertexArray vertexArray;
		VertexBuffer vertexBuffer(positions, 4 * 2 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		vertexArray.AddBuffer(vertexBuffer, layout);


		// INDEX BUFFER
		IndexBuffer indexBuffer(indices, 6);

		Shaders shader("Assets/Shaders/Shader.shader");
		shader.Bind();
		shader.SetUniform4f("uColor", 0.8f, 0.3f, 0.8f, 1.0f);

		/*GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, GL_STATIC_DRAW));*/


		vertexArray.Unbind();
		vertexBuffer.Unbind();
		indexBuffer.Unbind();
		shader.Unbind();


		float r = 0.0f;
		float g = 0.0f;
		float rIncrement = 0.05f;
		float gIncrement = 0.025f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("uColor", r, g, 0.8f, 1.0f);

			renderer.Draw(vertexArray, indexBuffer, shader);


			// RED INCREMENET
			if (r > 1.0f)
			{
				rIncrement = -0.05f;
			}
			else if (r < 0.0f)
			{
				rIncrement = 0.05f;
			}

			r += rIncrement;

			// GREEN INCREMENT
			if (g > 1.0f)
			{
				gIncrement = -0.025f;
			}
			else if (g < 0.0f)
			{
				gIncrement = 0.025f;
			}

			g += gIncrement;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	glfwTerminate();

	return 0;
}