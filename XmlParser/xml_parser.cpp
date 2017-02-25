#include "xml_parser.h"

namespace xml
{
	Parser::Parser(Document * doc, const char * filename) : root_(doc), content_(load_file(filename))
	{
	}

	void Parser::parse()
	{
		assert(root_ != nullptr);
	}

	const string & Parser::load_file(const char * filename)
	{
		string data;

		return data;
	}
}