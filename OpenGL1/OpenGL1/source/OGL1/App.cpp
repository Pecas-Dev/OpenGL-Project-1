#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imGUI/imgui.h>
#include <imGUI/imgui_impl_glfw_gl3.h>

#include <OGL1/Renderer/Renderer.h>
#include <OGL1/VertexBuffer/VertexBuffer.h>
#include <OGL1/IndexBuffer/IndexBuffer.h>
#include <OGL1/VertexArray/VertexArray.h>
#include <OGL1/VertexBufferLayout/VertexBufferLayout.h>
#include <OGL1/Shaders/Shaders.h>
#include <OGL1/Textures/Textures.h>

#include <OGL1/Tests/TestClearColor.h>

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
	window = glfwCreateWindow(960, 540, "My OpenGL1 Project", NULL, NULL);
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
			 -50.0f, -50.0f, 0.0f, 0.0f, //0
			  50.0f, -50.0f, 1.0f, 0.0f, //1
			  50.0f,  50.0f, 1.0f, 1.0f, //2
			 -50.0f,  50.0f, 0.0f, 1.0f  //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		Renderer renderer;

		// VERTEX ARRAY OBJECT
		unsigned vertexArrayObject;
		GLCall(glGenVertexArrays(1, &vertexArrayObject));
		GLCall(glBindVertexArray(vertexArrayObject));

		// VERTEX BUFFER
		VertexArray vertexArray;
		VertexBuffer vertexBuffer(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		vertexArray.AddBuffer(vertexBuffer, layout);


		// INDEX BUFFER
		IndexBuffer indexBuffer(indices, 6);


		// MATRICES
		glm::mat4 projectionMatrix = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


		// SHADER
		Shaders shader("Assets/Shaders/Shader.shader");
		shader.Bind();


		// TEXTURES
		Textures textureGreenYoshi("Assets/Textures/textureYoshi.png");
		Textures texturePurpleYoshi("Assets/Textures/textureYoshi_Pink.png");

		vertexArray.Unbind();
		vertexBuffer.Unbind();
		indexBuffer.Unbind();
		shader.Unbind();


		// ImGUI
		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);


		// TESTS
		Test::Tests* currentTest = nullptr;
		Test::TestMenu* testMenu = new Test::TestMenu(currentTest);

		currentTest = testMenu;

		testMenu->RegisterTest<Test::TestClearColor>("Clear Color");

		Test::TestClearColor test;


		// TRANSLATIONS
		glm::vec3 translationGreenYoshi(200, 200, 0);
		glm::vec3 translationPurpleYoshi(400, 200, 0);


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			renderer.Clear();

			ImGui_ImplGlfwGL3_NewFrame();

			if (currentTest)
			{
				currentTest->OnUpdate(0.0f);
				currentTest->OnRender();
				ImGui::Begin("Test");

				if (currentTest != testMenu && ImGui::Button("<-"))
				{
					delete currentTest;
					currentTest = testMenu;
				}

				currentTest->OnImGuiRender();
				ImGui::End();
			}

			{
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translationGreenYoshi);
				glm::mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

				shader.Bind();

				textureGreenYoshi.Bind(0);
				shader.SetUniform1i("uTexture", 0);

				shader.SetUniformMat4f("uModelViewProjectionMatrix", modelViewProjectionMatrix);
				renderer.Draw(vertexArray, indexBuffer, shader);
			}

			{
				glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), translationPurpleYoshi);
				glm::mat4 modelViewProjectionMatrix = projectionMatrix * viewMatrix * modelMatrix;

				shader.Bind();

				texturePurpleYoshi.Bind(0);
				shader.SetUniform1i("uTexture", 0);

				shader.SetUniformMat4f("uModelViewProjectionMatrix", modelViewProjectionMatrix);
				renderer.Draw(vertexArray, indexBuffer, shader);
			}


			// ImGUI
			{
				ImGui::SliderFloat3("T. Green Yoshi", &translationGreenYoshi.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("T. Purple Yoshi", &translationPurpleYoshi.x, 0.0f, 960.0f);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		delete currentTest;

		if(currentTest != testMenu)
		{
			delete testMenu;
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	return 0;
}