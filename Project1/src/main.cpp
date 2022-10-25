#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h>
#include <iostream>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

//#include "GUI.h"
#include "FmodManager.h"
#include "XML.h"
#include "Sound_UI.h"

#define MAX_CHANNEL 255
#define MASTER_CH	"Master"
#define BGM_CH1		"BGM1"
#define BGM_CH2		"BGM2"
#define BGM_CH3		"BGM3"
#define	FX1_CH		"fx1"
#define FX2_CH		"fx2"

XML xml;
FModManager fmodmanager;
GLFWwindow* window = nullptr;

Sound_UI sound_UI(&fmodmanager,&xml);

void key_callback(GLFWwindow* window, const int key, int scancode, const int action, const int mods);
bool init_window();
void run();
void shutdown_gui();



int main(int argc, char* argv[])
{
	//FModManager fmod;
	//GUI gui;
	bool result = false;
	

	result = init_window();
	if(!result)
	{
		return -1;
	}

	//init fmod
	result = fmodmanager.Fmod_init(MAX_CHANNEL, FMOD_INIT_NORMAL);
	if (!result)
	{
		return -2;
	}

	result = fmodmanager.create_channel(MASTER_CH);
	result = fmodmanager.create_channel(BGM_CH1);
	result = fmodmanager.create_channel(BGM_CH2);
	result = fmodmanager.create_channel(BGM_CH3);
	result = fmodmanager.create_channel(FX1_CH);
	result = fmodmanager.create_channel(FX2_CH);
	if (!result)
	{
		return -3;
	}

	result = fmodmanager.set_channel_parent(BGM_CH1, MASTER_CH);
	result = fmodmanager.set_channel_parent(BGM_CH2, MASTER_CH);
	result = fmodmanager.set_channel_parent(BGM_CH3, MASTER_CH);
	result = fmodmanager.set_channel_parent(FX1_CH, MASTER_CH);
	result = fmodmanager.set_channel_parent(FX2_CH, MASTER_CH);
	if (!result)
	{
		return -4;
	}

	//read XML file
	xml.readXML();

	result = fmodmanager.set_channel_vol(MASTER_CH, 0.5f);
	//result = fmodmanager.create_stream("bgm1", xml.my_music[0], FMOD_LOOP_NORMAL, false);
	//result = fmodmanager.create_stream("bgm2", xml.my_music[1], FMOD_LOOP_NORMAL, false);
	//result = fmodmanager.create_stream("bgm3", xml.my_music[2], FMOD_LOOP_NORMAL, false);
	result = fmodmanager.create_sound("fx1", xml.my_fx_path[0], FMOD_DEFAULT, false);
	result = fmodmanager.create_sound("fx2", xml.my_fx_path[1], FMOD_DEFAULT, false);
	result = fmodmanager.create_sound("fx3", xml.my_fx_path[2], FMOD_DEFAULT, false);
	result = fmodmanager.create_sound("fx4", xml.my_fx_path[3], FMOD_DEFAULT, false);
	result = fmodmanager.create_sound("fx5", xml.my_fx_path[4], FMOD_DEFAULT, false);
	result = fmodmanager.create_sound("fx6", xml.my_fx_path[5], FMOD_DEFAULT, false);
	result = fmodmanager.create_sound("fx7", xml.my_fx_path[6], FMOD_DEFAULT, false);
	//result = fmodmanager.play_sound("bgm1", BGM_CH1);

	result = fmodmanager.create_dsp("echo", FMOD_DSP_TYPE_ECHO, 500.f);
	result = fmodmanager.create_dsp("dist", FMOD_DSP_TYPE_DISTORTION, 0.5f);
	result = fmodmanager.create_dsp("chorus", FMOD_DSP_TYPE_CHORUS, 50.f);
	result = fmodmanager.create_dsp("lpf", FMOD_DSP_TYPE_LOWPASS, 5000.f);
	result = fmodmanager.create_dsp("hpf", FMOD_DSP_TYPE_HIGHPASS, 5000.f);
	result = fmodmanager.create_dsp("fader", FMOD_DSP_TYPE_FADER, 0.f);
	result = fmodmanager.create_dsp("pitch", FMOD_DSP_TYPE_PITCHSHIFT, 1.f);
	result = fmodmanager.create_dsp("delay", FMOD_DSP_TYPE_DELAY, 0.f);
	result = fmodmanager.create_dsp("tremolo", FMOD_DSP_TYPE_TREMOLO, 5.f);

	
	run();

	fmodmanager.shutdown();
	shutdown_gui();

	return 0;
}

static void key_callback(GLFWwindow* window, const int key, int scancode, const int action, const int mods)
{
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		float cur_vol;
		fmodmanager.get_channel_vol(MASTER_CH,&cur_vol);
		std::cout << cur_vol << std::endl;
		cur_vol += 0.1f;
		if (cur_vol <= 10.f)
		{
			fmodmanager.set_channel_vol(MASTER_CH, cur_vol);
		}
	}

	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		float cur_vol;
		fmodmanager.get_channel_vol(MASTER_CH, &cur_vol);
		std::cout << cur_vol << std::endl;
		cur_vol -= 0.1f;
		if (cur_vol >= 0.f)
		{
			fmodmanager.set_channel_vol(MASTER_CH, cur_vol);
		}
	}

	if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
	{
		float cur_pan;
		fmodmanager.get_channel_group_pan(MASTER_CH, &cur_pan);
		std::cout << cur_pan << std::endl;
		cur_pan -= 0.1f;
		if (cur_pan >= -1.f)
		{
			fmodmanager.set_channel_group_pan(MASTER_CH, cur_pan);
		}
	}

	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
	{
		float cur_pan;
		fmodmanager.get_channel_group_pan(MASTER_CH, &cur_pan);
		std::cout << cur_pan << std::endl;
		cur_pan += 0.1f;
		if (cur_pan <= 1.f)
		{
			fmodmanager.set_channel_group_pan(MASTER_CH, cur_pan);
		}
	}

	if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
	{
		float pitch;
		fmodmanager.get_channel_pitch(MASTER_CH, &pitch);
		std::cout << pitch << std::endl;
		pitch += 0.1f;
		if (pitch <= 2.f)
		{
			fmodmanager.set_channel_pitch(MASTER_CH, pitch);
		}
	}

	if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
	{
		float pitch;
		fmodmanager.get_channel_pitch(MASTER_CH, &pitch);
		std::cout << pitch << std::endl;
		pitch -= 0.1f;
		if (pitch >= 0.5f)
		{
			fmodmanager.set_channel_pitch(MASTER_CH, pitch);
		}
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		bool en;
		fmodmanager.get_channel_group_enabled(MASTER_CH, &en);
		std::cout << en << std::endl;
		fmodmanager.set_channel_group_enabled(MASTER_CH, !en);
	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx1", FX1_CH);
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx2", FX1_CH);
	}

	if (key == GLFW_KEY_3 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx3", FX1_CH);
	}

	if (key == GLFW_KEY_4 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx4", FX1_CH);
	}

	if (key == GLFW_KEY_5 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx5", FX1_CH);
	}

	if (key == GLFW_KEY_6 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx6", FX1_CH);
	}

	if (key == GLFW_KEY_7 && action == GLFW_PRESS)
	{
		fmodmanager.play_sound("fx7", FX1_CH);
	}
}

bool init_window()
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

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//initialize imgui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	//platform / render bindings
	if (!ImGui_ImplGlfw_InitForOpenGL(window, true) || !ImGui_ImplOpenGL3_Init("#version 460"))
	{
		return false;
	}

	//imgui style (dark mode for the win)
	ImGui::StyleColorsDark();

	return true;
}

void run()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		//poll for user events
		glfwPollEvents();

		//clear the back buffer
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		sound_UI.render();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		//present to the user
		glfwSwapBuffers(window);
	}

}

void shutdown_gui()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}