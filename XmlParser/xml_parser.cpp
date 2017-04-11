#include "xml_parser.h"
#include "utils.h"
#include <fstream>
#include <stack>

namespace xml
{
	std::vector<unsigned char> Space{ ' ', '\t', '\r', '\n' };
	std::vector<unsigned char> NameExclusive{ ' ', '\t', '\r', '\n', '/','>', '?' };
	//AttValue
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
		while (std::getline(fin, buf))
			*data += buf;

		fin.close();
		return data;
	}

	void Parser::parse_element(Pointer p)
	{
		string name;
		if (*p == '<')
		{
			if (match(p + 1, NameExclusive))
				throw ParseException("NameStartChar doesn't match.");
			while (!match(p, Space))
				name += *p++;

			/* Attribute */
			name = "";
			skip(p, Space);
			while (!match(p, Space))
				name += *p++;
			skip(p, Space);
			if (*p == '=')
				++p;
			skip(p, Space);

		}
	}
}