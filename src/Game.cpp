#include "Dependencies\ImGui\imgui.h"
#include "Dependencies\ImGui\imgui_impl_glfw.h"
#include "Dependencies\ImGui\imgui_impl_opengl3.h"
#include "Game.h"
#include <Tests\Test3DCubes.h>
#include <Tests\TestClearColor.h>
#include <Tests\TestLighting.h>

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 920;

void Game::Run() {
	window.setScreenWidth(SCREEN_WIDTH);
	window.setScreenHeight(SCREEN_HEIGHT);
	window.setWindowName("Learning OpenGL");

	window.init();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window.getWindow(), true);
#ifdef __EMSCRIPTEN__
	ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
	ImGui_ImplOpenGL3_Init("#version 460");

	std::cout << "Game running" << std::endl;

	auto gameWindow = window.getWindow();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	Test::Test* currentTest = nullptr;
	Test::TestMenu* testMenu = new Test::TestMenu(currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<Test::TestClearColor>("Clear Color");
	testMenu->RegisterTest<Test::Test3DCubes>("Textured 3D Cubes", gameWindow);
	testMenu->RegisterTest<Test::TestLighting>("Lighting", gameWindow);

	while (!glfwWindowShouldClose(gameWindow)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (currentTest) {
			currentTest->OnUpdate(0.0f);
			currentTest->OnRender();
			ImGui::Begin("Test");

			if (currentTest != testMenu && ImGui::Button("<-")) {
				delete currentTest;
				currentTest = testMenu;
			}

			currentTest->OnImGuiRender();
			ImGui::End();
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		window.update();
	}

	delete currentTest;
	if (currentTest != testMenu)
		delete testMenu;
}

void Game::End() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	std::cout << "Game Ended" << std::endl;
	glfwTerminate();
}
