//
// Created by jim on 6/10/24.
//

#ifndef EXTRALIFEHELPER_EXTRALIFEGUI_H
#define EXTRALIFEHELPER_EXTRALIFEGUI_H

#include "easyappbase.hpp"
#include "ExtraLifeDonationScraper.h"

class ExtraLifeGUI : public EasyAppBase
{
	public:
		ExtraLifeGUI();

		void Start() override; // Optional.  This is where you would start threads, load things, etc. If it takes a long time, use a thread with THREAD instead of std::thread.
		void Render(bool * bShow) override;  // REQUIRED.  This is where you would render your window.

	private:
		ExtraLifeDonationScraper scraper;
};


#endif //EXTRALIFEHELPER_EXTRALIFEGUI_H
