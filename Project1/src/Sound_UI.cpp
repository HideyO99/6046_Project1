#include "Sound_UI.h"

FModManager* fmodmanager_;
XML* xml_;

Sound_UI::Sound_UI(FModManager* fmod,XML* a_xml)
{
	fmodmanager_ = fmod;
	xml_ = a_xml;
	iscompress[0] = false;
	iscompress[1] = false;
	iscompress[2] = false;
	channel_ = 0;
	bps_ = 0;
	freq = 0.f;
	priority = 0;
	music_length = 0;
	music_length_min = 0;
	music_length_sec = 0;
	music_pos = 0;
	music_pos_min = 0;
	music_pos_sec = 0;
}

Sound_UI::~Sound_UI()
{
}

void Sound_UI::render()
{
	float curr_music_volume;
	float curr_music_pan;

	//setup ui structure
	ImGui::Begin("Audio Settings");
	ImGui::BeginChild("##BGM", ImVec2(0,100),true);
	
	{
		
		ImGui::Text("BGM1: %s",xml_->my_music[0].fname.c_str());
		ImGui::SameLine();
		ImGui::Checkbox("compress##CMPSS1", &iscompress[0]);
		ImGui::SameLine();
		if (ImGui::Button("Load##BGM1"))
		{
			fmodmanager_->stop_sound(BGM_CH1);
			fmodmanager_->remove_sound("bgm1");
			fmodmanager_->create_stream("bgm1", xml_->my_music[0], FMOD_LOOP_NORMAL, iscompress[0]);
			fmodmanager_->play_sound("bgm1", BGM_CH1);
			fmodmanager_->get_sound_name("bgm1", &file_name_);
			fmodmanager_->get_sound_format("bgm1", &file_type_, &file_format_, &channel_, &bps_);
			fmodmanager_->get_sound_defualt("bgm1", &freq, &priority);
			fmodmanager_->get_sound_lengh("bgm1", &music_length);
			MStoMinSec(music_length, &music_length_min, &music_length_sec);
		}
	}

	{
		ImGui::Text("BGM2: %s", xml_->my_music[1].fname.c_str());
		ImGui::SameLine();
		ImGui::Checkbox("compress##CMPSS2", &iscompress[1]);
		ImGui::SameLine();
		if (ImGui::Button("Load##BGM2"))
		{	
			fmodmanager_->stop_sound(BGM_CH1);
			fmodmanager_->remove_sound("bgm2");
			fmodmanager_->create_stream("bgm2", xml_->my_music[1], FMOD_LOOP_NORMAL, iscompress[1]);
			fmodmanager_->play_sound("bgm2", BGM_CH1);
			fmodmanager_->get_sound_name("bgm2", &file_name_);
			fmodmanager_->get_sound_format("bgm2", &file_type_, &file_format_, &channel_, &bps_);
			fmodmanager_->get_sound_defualt("bgm2", &freq, &priority);
			fmodmanager_->get_sound_lengh("bgm2", &music_length);
			MStoMinSec(music_length, &music_length_min, &music_length_sec);
		}
	}

	{
		ImGui::Text("BGM3: %s", xml_->my_music[2].fname.c_str());
		ImGui::SameLine();
		ImGui::Checkbox("compress##CMPSS3", &iscompress[2]);
		ImGui::SameLine();
		if (ImGui::Button("Load##BGM3"))
		{
			fmodmanager_->stop_sound(BGM_CH1);
			fmodmanager_->remove_sound("bgm3");
			fmodmanager_->create_stream("bgm3", xml_->my_music[2], FMOD_LOOP_NORMAL, iscompress[2]);
			fmodmanager_->play_sound("bgm3", BGM_CH1);
			fmodmanager_->get_sound_name("bgm3", &file_name_);
			fmodmanager_->get_sound_format("bgm3", &file_type_, &file_format_, &channel_, &bps_);
			fmodmanager_->get_sound_defualt("bgm3", &freq, &priority);
			fmodmanager_->get_sound_lengh("bgm3", &music_length);
			MStoMinSec(music_length, &music_length_min, &music_length_sec);

		}
	}
	ImGui::EndChild();

	//master volume
	{
		ImGui::BeginChild("Master_volume_ctrl", ImVec2(120, 140), true);
		FModManager::CHgroup* channel_group;
		if (!fmodmanager_->find_channel_group("master", &channel_group))
		{
			//cannot find channel group
			//do something...
		}

		float current_volume;
		bool volume_enabled;
		if (!fmodmanager_->get_channel_vol(MASTER_CH, &current_volume)) {
			//failed
		}

		if (!fmodmanager_->get_channel_group_enabled(MASTER_CH, &volume_enabled)) {
			//failed
		}

		current_volume *= 100;
		curr_music_volume = current_volume;
		ImGui::Checkbox("##master_volume", &volume_enabled);
		MyKnob("master volume", &current_volume, 0.0f, 100.0f);
		//ImGui::SliderFloat("master volume", &current_volume, 0.0f, 100.0f, "%.0f");
		current_volume /= 100;

		// WARNING: volume range (0.0-1.0) //dont go to high above 1 (you can hurt your hardware)
		if (!fmodmanager_->set_channel_vol(MASTER_CH, current_volume)) {
			//failed
		}
		//ImGui::SameLine();

		if (!fmodmanager_->set_channel_group_enabled(MASTER_CH, volume_enabled)) {
			//failed
		}

		//master pan
		{
			FModManager::CHgroup* channel_group;
			if (!fmodmanager_->find_channel_group(MASTER_CH, &channel_group))
			{
				//cannot find channel group
				//do something...
			}
			float pan;
			if (!fmodmanager_->get_channel_group_pan(MASTER_CH, &pan))
			{

			}
			channel_group->current_pan = pan;
			//curr_music_pan = pan;
			ImGui::SliderFloat("##master pan", &channel_group->current_pan, -1.0f, 1.0f, "%.2f");
			ImGui::Text("master pan");
			if (!fmodmanager_->set_channel_group_pan(MASTER_CH, channel_group->current_pan))
			{
				//error
				//do something?
			}
		}
		ImGui::EndChild();
	}
	
		ImGui::SameLine();
	//master pitch
	{
		ImGui::BeginChild("Master_pitch_ctrl", ImVec2(100, 140), true);
		{
			FModManager::CHgroup* channel_group;
			if (!fmodmanager_->find_channel_group(MASTER_CH, &channel_group))
			{
				//cannot find channel group
				//do something...
			}

			float current_pitch;
			channel_group->group_ptr->getPitch(&current_pitch);
			ImGui::VSliderFloat("##master pitch (no dsp)", ImVec2(30, 105), &current_pitch, 0.5f, 2.0f, "%.2f");
			ImGui::Text("master pitch");
			//ImGui::SliderFloat("master pitch (no dsp)", &current_pitch, 0.5f, 2.0f, "%.2f");
			channel_group->group_ptr->setPitch(current_pitch);
		}
		ImGui::EndChild();
		//ImGui::EndChild();
	}

	ImGui::SameLine();
	//music volume
	{
		ImGui::BeginChild("Music_volume_ctrl", ImVec2(120, 140), true);

		FModManager::CHgroup* channel_group;
		if (!fmodmanager_->find_channel_group(BGM_CH1, &channel_group)) 
		{
			//cannot find channel group
			//do something...
		}

		float current_volume;
		bool volume_enabled;

		if (!fmodmanager_->get_channel_vol(BGM_CH1, &current_volume)) {
			//failed
		}
		
		if (!fmodmanager_->get_channel_group_enabled(BGM_CH1, &volume_enabled)) {
			//failed
		}

		current_volume *= 100;
		if (curr_music_volume > current_volume)
		{
			curr_music_volume = current_volume;
		}
		ImGui::Checkbox("##music_volume", &volume_enabled);
		MyKnob("music volume", &current_volume, 0.0f, 100.0f);
		//ImGui::SliderFloat("music volume", &current_volume, 0.0f, 100.0f, "%.0f");
		current_volume /= 100;

		if (!fmodmanager_->set_channel_vol(BGM_CH1, current_volume)) {
			//failed
		}
		
		if (!fmodmanager_->set_channel_group_enabled(BGM_CH1, volume_enabled)) {
			//failed
		}

		//music pan
		{
			FModManager::CHgroup* channel_group;
			if (!fmodmanager_->find_channel_group(BGM_CH1, &channel_group))
			{
				//cannot find channel group
				//do something...
			}
			float pan;
			if (!fmodmanager_->get_channel_group_pan(BGM_CH1, &pan))
			{

			}
			channel_group->current_pan = pan;
			curr_music_pan = pan;
			ImGui::SliderFloat("##music pan", &channel_group->current_pan, -1.0f, 1.0f, "%.2f");
			ImGui::Text("music pan");
			if (!fmodmanager_->set_channel_group_pan(BGM_CH1, channel_group->current_pan))
			{
				//error
				//do something?
			}
		}

		ImGui::EndChild();
	}

	ImGui::SameLine();

	//FX volume
	{
		ImGui::BeginChild("FX_volume_ctrl", ImVec2(120, 140), true);

		FModManager::CHgroup* channel_group;
		if (!fmodmanager_->find_channel_group(FX1_CH, &channel_group))
		{
			//cannot find channel group
			//do something...
		}

		float current_volume;
		bool volume_enabled;
		if (!fmodmanager_->get_channel_vol(FX1_CH, &current_volume)) {
			//failed
		}

		if (!fmodmanager_->get_channel_group_enabled(FX1_CH, &volume_enabled)) {
			//failed
		}
		current_volume *= 100;
		ImGui::Checkbox("##fx_volume", &volume_enabled);
		MyKnob("fx volume", &current_volume, 0.0f, 100.0f);
		//ImGui::SliderFloat("fx volume", &current_volume, 0.0f, 100.0f, "%.0f");
		current_volume /= 100;

		// WARNING: volume range (0.0-1.0) //dont go to high above 1 (you can hurt your hardware)
		if (!fmodmanager_->set_channel_vol(FX1_CH, current_volume)) {
			//failed
		}

		if (!fmodmanager_->set_channel_group_enabled(FX1_CH, volume_enabled)) {
			//failed
		}
		ImGui::EndChild();
	}
	ImGui::BeginChild("##info", ImVec2(0, 150), true);
	{
		ImGui::Text("Name: %s", file_name_.c_str());
		ImGui::Text("Format: %s", file_format_.c_str());
		ImGui::Text("Type: %s", file_type_.c_str());
		ImGui::Text("Frequency: %.0f", freq);
		fmodmanager_->get_playback_pos(BGM_CH1,& music_pos);
		MStoMinSec(music_pos, &music_pos_min, &music_pos_sec);
		ImGui::Text("Length: %02d:%02d/%02d:%02d", music_pos_min, music_pos_sec, music_length_min,music_length_sec);
		ImGui::Text("Music Volume: %.02f", curr_music_volume);
		ImGui::Text("Music Balance: %.02f", curr_music_pan);
	}
	ImGui::EndChild();

	//nothing
	{
		//FModManager::CHgroup* channel_group;
		//if (!fmodmanager_->find_channel_group(MASTER_CH, &channel_group))
		//{
		//	//cannot find channel group
		//	//do something...
		//}

		//ImGui::SliderFloat("master pitch (using dsp)", &channel_group->dsp_pitch, 0.5f, 2.0f, "%.2f");
		//FMOD::DSP* dsp;
		//if (!fmodmanager_->get_dsp("dsp_pitch", &dsp))
		//{
		//	//dsp not found...
		//}
		//dsp->setParameterFloat(0, channel_group->dsp_pitch);
	}

	ImGui::End();

}

bool Sound_UI::MyKnob(const char* label, float* p_value, float v_min, float v_max)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	float radius_outer = 20.0f;
	ImVec2 pos = ImGui::GetCursorScreenPos();
	ImVec2 center = ImVec2(pos.x + radius_outer, pos.y + radius_outer);
	float line_height = ImGui::GetTextLineHeight();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	float ANGLE_MIN = 3.141592f * 0.75f;
	float ANGLE_MAX = 3.141592f * 2.25f;

	ImGui::InvisibleButton(label, ImVec2(radius_outer * 2, radius_outer * 2 + line_height + style.ItemInnerSpacing.y));
	bool value_changed = false;
	bool is_active = ImGui::IsItemActive();
	bool is_hovered = ImGui::IsItemActive();
	if (is_active && io.MouseDelta.x != 0.0f)
	{
		float step = (v_max - v_min) / 200.0f;
		*p_value += io.MouseDelta.x * step;
		if (*p_value < v_min) *p_value = v_min;
		if (*p_value > v_max) *p_value = v_max;
		value_changed = true;
	}

	float t = (*p_value - v_min) / (v_max - v_min);
	float angle = ANGLE_MIN + (ANGLE_MAX - ANGLE_MIN) * t;
	float angle_cos = cosf(angle), angle_sin = sinf(angle);
	float radius_inner = radius_outer * 0.40f;
	draw_list->AddCircleFilled(center, radius_outer, ImGui::GetColorU32(ImGuiCol_FrameBg), 16);
	draw_list->AddLine(ImVec2(center.x + angle_cos * radius_inner, center.y + angle_sin * radius_inner), ImVec2(center.x + angle_cos * (radius_outer - 2), center.y + angle_sin * (radius_outer - 2)), ImGui::GetColorU32(ImGuiCol_SliderGrabActive), 2.0f);
	draw_list->AddCircleFilled(center, radius_inner, ImGui::GetColorU32(is_active ? ImGuiCol_FrameBgActive : is_hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg), 16);
	draw_list->AddText(ImVec2(pos.x, pos.y + radius_outer * 2 + style.ItemInnerSpacing.y), ImGui::GetColorU32(ImGuiCol_Text), label);

	if (is_active || is_hovered)
	{
		ImGui::SetNextWindowPos(ImVec2(pos.x - style.WindowPadding.x, pos.y - line_height - style.ItemInnerSpacing.y - style.WindowPadding.y));
		ImGui::BeginTooltip();
		ImGui::Text("%.3f", *p_value);
		ImGui::EndTooltip();
	}

	return value_changed;
}

void Sound_UI::MStoMinSec(const unsigned int ms, unsigned int* min, unsigned int* sec)
{
	*min = ((ms / (1000 * 60)) % 60);
	*sec = (ms / 1000) % 60;
}


