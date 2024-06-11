//
// Created by jim on 6/10/24.
//

#include "ExtraLifeGUI.h"
#include "ExtraLifeDonationScraper.h"

ExtraLifeGUI::ExtraLifeGUI() :
	EasyAppBase("sample", "Sample Window")
{
	auto jrSettings = ExclusiveSettings();
	auto & jSettings = *jrSettings;
	if (!jSettings["participant"].exists("screenName")) {
		jSettings["participant"]["screenName"] = "Not Configured";
	}
	if (!jSettings["participant"].exists("id")) {
		jSettings["participant"]["id"] = 531921; // Make Soft?
	}
}

void ExtraLifeGUI::Start()
{
	scraper.updateDonations((*ExclusiveSettings())["participant"]["id"].string());
}

void ExtraLifeGUI::Render(bool */*bShow*/)
{
	if (ImGui::Button("Update")) {
		scraper.updateDonations((*ExclusiveSettings())["participant"]["id"].string());
	}
	auto jAllData = scraper.AllData();
	ImGui::Text("Status: %s", jAllData["sStatus"].c_str());
	ImGui::Text("Last Update: %s", jAllData["lastDonationDatetime"].c_str());
	ImGui::Text("etag: %s", jAllData["etag"].c_str());
	ImGui::BeginChild("Table Frame", {0, 0}, ImGuiChildFlags_FrameStyle);
	ImGui::BeginTable("Layout", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_SizingStretchSame | ImGuiTableFlags_ScrollY);
	ImGui::TableSetupColumn("Latest Donations");
	ImGui::TableSetupColumn("All Donations");
	ImGui::TableHeadersRow();

	ImGui::TableNextColumn();
	bool bDummy = true;
	ShowJson("Latest Donations", jAllData["jNewDonations"], bDummy);

	ImGui::TableNextColumn();
	bDummy = true;
	ShowJson("All Donations", jAllData["jDonations"], bDummy);

	ImGui::EndTable();
	ImGui::EndChild();
}
