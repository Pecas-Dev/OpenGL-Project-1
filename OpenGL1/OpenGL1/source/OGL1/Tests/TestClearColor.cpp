#include <OGL1/Tests/TestClearColor.h>
#include <OGL1/Renderer/Renderer.h>

#include <imGUI/imgui.h>


namespace Test
{
	Test::TestClearColor::TestClearColor() : m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f }
	{
	}

	Test::TestClearColor::~TestClearColor()
	{
	}

	void Test::TestClearColor::OnUpdate(float delta)
	{
	}

	void Test::TestClearColor::OnRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void Test::TestClearColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}


