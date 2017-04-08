#include "xml_parser.h"
#include <fstream>
#include <stack>

namespace xml
{
	
	Parser::Parser(Document * doc, const char * filename) : root_(doc), content_(load_file(filename))
	{
	}

	Parser::~Parser()
	{
		delete content_;
	}

	void Parser::parse()
	{
		assert(root_ != nullptr);

	}

	const string* Parser::load_file(const char * filename)
	{
		std::ifstream fin(filename);
		string* data = new string;
		string buf;
		while (getline(fin, buf))
			*data += buf;

		fin.close();
		return data;
	}
}