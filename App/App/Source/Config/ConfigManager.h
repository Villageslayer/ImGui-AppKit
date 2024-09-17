#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>


namespace ConfigManager {
	// Config File
	namespace Config {
		extern int userX;
		extern int userY;
		extern int user1x;
		extern int user25x;
	};
	extern std::string configPath;

	extern INIReader reader; // Use the appropriate constructor

	
	void init();
	void makedefault();
	void load();
	void save();

};// namespace ConfigManager