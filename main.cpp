#include <iostream>
#include "utils.h"
#include "json_document/json.hpp"
#include "boost/filesystem.hpp"
#include "ExtraLifeDataScraper.h"

int main() {
    //First, let's check to make sure that the file exists at <program installation location>/data/config.json exists
    //If it does not exist, we will create it and write the default configuration to it
    //If it does exist, we will read the configuration from it
    std::string dataPath = getInstallationPath() + "/data/config.json";
    if (!boost::filesystem::exists(dataPath) {
        std::cout << "Configuration file does not exist. Creating it now." << std::endl;
        //Create the file and write the default configuration to it
        json::document config;
        config["participant"]["screenName"] = "Not Configured";
        config["participant"]["id"] = 531921;
        //Write the configuration to the file
        std::ofstream file(dataPath);
        config.write(file);
        file.close();
    } else {
        std::cout << "Configuration file exists. Reading configuration." << std::endl;
        //Read the configuration from the file
        std::ifstream file(dataPath);
        json::document config;
        config.read(file);
        file.close();
    }
    ExtraLifeDonationScraper::updateDonations(config["participant"]["id"].as<std::string>());
}
