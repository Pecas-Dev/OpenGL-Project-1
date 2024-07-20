#pragma once

#include <vector>
#include <string>
#include <functional>

namespace Test
{
	class Tests
	{
	public:
		Tests() {};
		virtual ~Tests() {};

		virtual void OnUpdate(float delta) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	class TestMenu : public Tests
	{
	private:
		Tests*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Tests*()>>> m_Tests;

	public:
		TestMenu(Tests*& currentTestPointer);

		void OnImGuiRender() override;


		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
		}
	};
}