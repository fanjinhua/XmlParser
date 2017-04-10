#pragma once

#include <string>
#include <cassert>
#include "dom.h"

namespace xml
{
	using namespace DOM;
	typedef std::string::iterator Pointer;
	class Parser
	{
	public:
		

	public:
		Parser(Document* doc, const char * filename);
		~Parser();
		void parse();

	private:
		//Document* m_root;
		Document* root_;
		const string* content_;
		const string* load_file(const char* filename);
		void parse_str();
		void parse_element(Pointer p);
	};
}
