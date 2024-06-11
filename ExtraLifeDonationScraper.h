//
// Created by chris on 2024-06-10.
//

#pragma once

#include <string>
#include "shared_recursive_mutex.hpp"
#include "json.hpp"

class ExtraLifeDonationScraper
{
	public:
		ExtraLifeDonationScraper();

		void updateDonations(const std::string& participantID);

		std::string ETAG();
		std::string LastDonationTime();
		json::document Donations();
		json::document NewDonations();
		std::string Status();

		json::document AllData();

	private:
		SharedRecursiveMutex mtx;
		std::string etag;
		std::string lastDonationDatetime;
		json::document jDonations;
		json::document jNewDonations;
		std::string sStatus;
};