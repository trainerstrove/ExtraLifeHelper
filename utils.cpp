//
// Created by chris on 2024-06-10.
//

#include "utils.h"
#include <boost/filesystem.hpp>

std::string getInstallationPath() {
    boost::filesystem::path path = boost::filesystem::system_complete(boost::filesystem::path(""));
    return path.string();
}