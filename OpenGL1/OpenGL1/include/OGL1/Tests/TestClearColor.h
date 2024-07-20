#pragma once

#include <OGL1/Tests/Tests.h>

namespace Test
{
	class TestClearColor : public Tests
	{
	private:
		float m_ClearColor[4];

	public:
		TestClearColor();
		~TestClearColor();

		void OnUpdate(float delta) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};
}