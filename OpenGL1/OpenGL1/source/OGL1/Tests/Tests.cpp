#include <OGL1/Tests/Tests.h>

#include <imGUI/imgui.h>

namespace Test
{
	TestMenu::TestMenu(Tests*& currentTestPointer) : m_CurrentTest(currentTestPointer)
	{
	}

	void TestMenu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}