
#include "utils.h"
#include "easyappbase.hpp"
#include "ExtraLifeDonationScraper.h"
#include "ExtraLifeGUI.h"

#include <iostream>
#include <filesystem>

#if !defined APP_NAME
#define APP_NAME "SampleApp"
#endif
#if !defined APP_VERSION_STRING
#define APP_VERSION_STRING "0.0.0"
#endif


int main() {
    //First, let's check to make sure that the file exists at <program installation location>/data/config.json exists
    //If it does not exist, we will create it and write the default configuration to it
    //If it does exist, we will read the configuration from it
//    std::string dataPath = GetAppDataFolder() + "/data/config.json";
//    if (!std::filesystem::exists(dataPath)) {
//        std::cout << "Configuration file does not exist. Creating it now." << std::endl;
//
//        //Create the file and write the default configuration to it
//        json::document config;
//        config["participant"]["screenName"] = "Not Configured";
//        config["participant"]["id"] = 531921; // Make Soft?
//
//        //Write the configuration to the file
//        config.writeFile(dataPath);
//
//    } else {
//        std::cout << "Configuration file exists. Reading configuration." << std::endl;
//
//        //Read the configuration from the file
//        std::ifstream file(dataPath);
//        json::document config;
//        config.readFile(file);
//        file.close();
//    }
//    ExtraLifeDonationScraper::updateDonations(config["participant"]["id"].as<std::string>());

	auto extraLifeGUI = EasyAppBase::GenerateWindow<ExtraLifeGUI>();

	EasyAppBase::SetMainRenderer([&]() { extraLifeGUI->Render(nullptr); });

	EasyAppBase::DisableDocking(true); // Uncomment this to disable docking (see https://github.com/ocornut/imgui/issues/2109 for details)
	EasyAppBase::DisableViewports(true); // Uncomment this to disable viewports (see https://github.com/ocornut/imgui/issues/1542 for details)
	EasyAppBase::SetNetworkThreads(4);

	return EasyAppBase::Run(APP_NAME, APP_NAME " v" APP_VERSION_STRING);
}
