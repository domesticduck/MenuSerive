
#pragma once

#include <spc/spcbase.h>
#include <sstream>
#include <vector>
#include <string>

namespace spc {
	
	class MenuService : public SPCBase {
	public:
		// メインプロシージャ
		void onInitialize();
		
	};

}

spc::MenuService spcApp;
