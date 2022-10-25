#pragma once
#include "OpenGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "FmodManager.h"

class GUI
{
public:
	GUI();
	~GUI();

	bool init_window();
	void run();
	void shutdown_gui();


};


