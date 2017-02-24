#pragma once

#include <string>
#include "dom.h"

namespace xml
{
	using std::string;
	using namespace DOM;
	class Parser
	{
	public:
		void parse();
	private:
		string content_;

	};
}
