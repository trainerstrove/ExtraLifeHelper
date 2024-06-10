//
// Created by chris on 2024-06-10.
//

#pragma once

#include <string>
#include "json.hpp"

class ExtraLifeDonationScraper {
private:
    std::string lastDonationDatetime;
public:
    ExtraLifeDonationScraper();
    void updateDonations(const std::string& participantID);
};