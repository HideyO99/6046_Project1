#pragma once
#include <string>
#include <pugixml/pugixml.hpp>

class XML
{
public:
	XML();
	~XML();
	
	struct MyMusic
	{
		std::string fname;
		std::string path[2];

		MyMusic();
	};

	MyMusic my_music[3];
	std::string my_fx_path[7];


	void readXML();

};

