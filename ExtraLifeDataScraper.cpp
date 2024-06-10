//
// Created by chris on 2024-06-10.
//

#include "ExtraLifeDonationScraper.h"
#include "utils.h"
#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "json.hpp" // Include the header file for json::document

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

ExtraLifeDonationScraper::ExtraLifeDonationScraper() : lastDonationDatetime("") {}

void ExtraLifeDonationScraper::updateDonations(const std::string& participantID) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::string etag = ""; // Initialize with the ETag of the last response

    // Check if the donations.json file exists
    std::string dataPath = getInstallationPath() + "/data/donations.json";
    if (boost::filesystem::exists(dataPath)) {
        // Read the ETag from the donations.json file
        std::ifstream file(dataPath);
        json::document data;
        data.read(file);
        file.close();
        if (data.has_key("etag")) {
            etag = data["etag"].as<std::string>();
        }
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        std::string url = "https://public-api.donordrive.com/v1/participants/" + participantID + "/donations";
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        if (!etag.empty()) {
            // If we have an ETag from a previous response, set the If-None-Match header
            struct curl_slist *headers = NULL;
            headers = curl_slist_append(headers, ("If-None-Match: " + etag).c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        }
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // If the server returned a 304 Not Modified status, there is no need to parse the response or update the donations
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        if (http_code == 304) {
            std::cout << "No new donations." << std::endl;
        } else {
            // Parse the JSON response
            json::document donations;
            donations.parse(readBuffer);

            // Filter out donations that have a datetime earlier than the stored datetime
            for (auto& donation : donations.array_range()) {
                std::string donationDatetime = donation["createdDateUTC"].as<std::string>();
                if (donationDatetime > lastDonationDatetime) {
                    // This is a new donation
                    std::cout << "New donation: " << donation.dump(4) << std::endl;
                }
            }

            // Update the stored datetime with the datetime of the most recent donation
            if (!donations.empty()) {
                lastDonationDatetime = donations[0]["createdDateUTC"].as<std::string>();
            }

            // Get the ETag from the response headers
            char* received_etag;
            curl_easy_getinfo(curl, CURLINFO_HEADER_OUT, &received_etag);
            if (received_etag) {
                etag = received_etag;
            }
            curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &received_etag);
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}