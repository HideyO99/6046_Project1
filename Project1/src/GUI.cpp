#include "GUI.h"
#include "Sound_UI.h"

GLFWwindow* window = nullptr;

GUI::GUI()
{

}

GUI::~GUI()
{
}


bool GUI::init_window()
{
	//create window
	if (glfwInit() == 0)
	{
		return false;
	}

	window = glfwCreateWindow(800, 600, "Project01", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		return false;
	}

	glfwSetKeyCallback(window, key_callback);


	return true;
}

void GUI::run()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		//user input
		glfwPollEvents();

		//render
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
	}
	
}

void GUI::shutdown_gui()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

//void GUI::key_callback(GLFWwindow* window, const int key, int scancode, const int action, const int mods)
//{
//	//if (key == GLFW_KEY_UP && action == GLFW_PRESS)
//	//{
//	//	fmodmanager_->get_channel_vol(MASTER_CH)
//	//	fmodmanager_->set_channel_vol(MASTER_CH,5.f);
//	//}
//
//	//if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//	//{
//	//	fmodmanager_->play_sound("arrow", "fx");
//	//	//std::cout << "yo";
//	//}
//
//	//if (key == GLFW_KEY_1 && action == GLFW_PRESS)
//	//{
//	//	//fmodmanager_.add_dsp_effect("master", "echo");
//	//}
//
//	//if (key == GLFW_KEY_2 && action == GLFW_PRESS)
//	//{
//	//	//fmodmanager_.remove_dsp_effect("master", "echo");
//	//}
//
//	//if (key == GLFW_KEY_3 && action == GLFW_PRESS)
//	//{
//	//	//fmodmanager_.add_dsp_effect("master", "dsp_pitch");
//	//}
//}










