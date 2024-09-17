#include "../Global.h"
#include <filesystem>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace fs = std::filesystem;

namespace ConfigManager {
    namespace Config {
        int MouseYawSensitivity = 0;
        int MousePitchSensitivity = 0;
        float XFactorAiming = 0.0f;
        int ADSMouseSensitivity1x = 0;
        int ADSMouseSensitivity2xHalf = 0;
    }

    // Define the variables here
    std::string configPath = "./Config.ini";
    INIReader reader(configPath); // Use the appropriate constructor

    void init() {
        if (!std::filesystem::exists(configPath)) {
            std::cout << "Config file not found. Creating default config file.\n";
            
            makedefault();
        }
        reader = INIReader(configPath); // Reinitialize reader after creating default config
        load();
    }

    void makedefault() {
        char* userProfile = nullptr;
        size_t len = 0;
        if (_dupenv_s(&userProfile, &len, "USERPROFILE") != 0 || userProfile == nullptr) {
            std::cerr << "Error: USERPROFILE environment variable not found." << std::endl;
            return;
        }

        fs::path basePath = fs::path(userProfile) / "Documents" / "MyGames" / "Rainbow Six - Siege";
        free(userProfile); // Free the memory allocated by _dupenv_s
        fs::path newestFilePath;
        std::filesystem::file_time_type newestTime;

        for (const auto& entry : fs::directory_iterator(basePath)) {
            if (fs::is_directory(entry)) {
                for (const auto& subEntry : fs::directory_iterator(entry)) {
                    if (fs::is_directory(subEntry)) {
                        fs::path gameSettingsPath = subEntry.path() / "GameSettings.ini";
                        if (fs::exists(gameSettingsPath)) {
                            auto currentFileTime = fs::last_write_time(gameSettingsPath);
                            if (newestFilePath.empty() || currentFileTime > newestTime) {
                                newestTime = currentFileTime;
                                newestFilePath = gameSettingsPath;
                            }
                        }
                    }
                }
            }
        }

        if (!newestFilePath.empty()) {
			configPath = newestFilePath.string();
			load();
			printf("Found GameSettings.ini file at %s\n", newestFilePath.string().c_str());
        }
        else {
            std::cerr << "No Gamesettings.ini file found in the specified directory." << std::endl;
        }
    }



    void load() {
        if (reader.ParseError() < 0) {
            std::cout << "Can't load '" << configPath << "'\n";
            return;
        }

        Config::MouseYawSensitivity = reader.GetInteger("INPUT", "MouseYawSensitivity", 0);
        Config::MousePitchSensitivity = reader.GetInteger("INPUT", "MousePitchSensitivity", 0);
        Config::XFactorAiming = static_cast<float>(reader.GetReal("INPUT", "XFactorAiming", 0.0f)); // Explicit cast to float
        Config::ADSMouseSensitivity1x = reader.GetInteger("INPUT", "ADSMouseSensitivity1x", 0);
        Config::ADSMouseSensitivity2xHalf = reader.GetInteger("INPUT", "ADSMouseSensitivity2xHalf", 0);
    }

    void save() {
        std::ofstream configFile(configPath);
        configFile << "[INPUT]\n";
        configFile << "MouseYawSensitivity = " << Config::MouseYawSensitivity << "\n";
        configFile << "MousePitchSensitivity = " << Config::MousePitchSensitivity << "\n";
        configFile << "XFactorAiming = " << Config::XFactorAiming << "\n";
        configFile << "ADSMouseSensitivity1x = " << Config::ADSMouseSensitivity1x << "\n";
        configFile << "ADSMouseSensitivity2xHalf = " << Config::ADSMouseSensitivity2xHalf << "\n";
        configFile.close();
    }
} // namespace ConfigManager
