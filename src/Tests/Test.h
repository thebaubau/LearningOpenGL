#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <Window.h>

namespace Test {
	class Test {
	public:
		Test() {};
		virtual ~Test() {};

		virtual void OnCreate() {};
		virtual void OnUpdate(float deltaTime) {};
		virtual void OnRender() {};
		virtual void OnImGuiRender() {};
	};

	class TestMenu : public Test {
	public:
		TestMenu(Test*& currentTestPointer);

		void OnImGuiRender() override;

		template<typename T, typename... Args>
		void RegisterTest(const std::string& name, Args&... args) {
			std::cout << "Registering Test " << name << std::endl;

			m_Tests.push_back(std::make_pair(name, [&args...]() { return new T(args...); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
	};
};
