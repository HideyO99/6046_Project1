#pragma once
#include "OpenGL.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include "imgui/imgui_impl_glfw.h"
//#include "imgui/imgui_impl_opengl3.h"
#include "FmodManager.h"
#include "imgui/imgui.h"

#define MASTER_CH	"Master"
#define BGM_CH1		"BGM1"
#define BGM_CH2		"BGM2"
#define BGM_CH3		"BGM3"
#define	FX1_CH		"fx1"
#define FX2_CH		"fx2"

class Sound_UI
{
public:
	Sound_UI(FModManager* fmod,XML* a_xml);
	~Sound_UI();
	
	bool iscompress[3];

	void render();

protected:
	bool MyKnob(const char* label, float* p_value, float v_min, float v_max);
	void MStoMinSec(const unsigned int ms, unsigned int* min, unsigned int* sec);


	std::string file_name_;
	std::string file_format_;
	std::string file_type_;
	int channel_;
	int bps_; //bits per sample
	float freq;
	int priority;
	unsigned int music_length;
	unsigned int music_length_min;
	unsigned int music_length_sec;
	unsigned int music_pos;
	unsigned int music_pos_min;
	unsigned int music_pos_sec;
};

