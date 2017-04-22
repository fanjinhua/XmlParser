#pragma once

#include <string>
#include <cassert>
#include "dom.h"

namespace xml
{
	using namespace DOM;
	typedef std::string PString;
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
		const PString* content_;
		const PString* load_file(const char* filename);
		void parse_str();
		void parse_element(Pointer p, Node* node);
	};

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

	inline void Parser::parse()
	{
		assert(root_ != nullptr);
		Pointer p;
		Node *node = root_->create_Element();
		root_->append_child(node);
		parse_element(p, node);

	}

	inline const PString* Parser::load_file(const char * filename)
	{
		std::ifstream fin(filename);
		PString* data = new PString;
		PString buf;
		while (std::getline(fin, buf))
			*data += buf;

		fin.close();
		return data;
	}

	inline void Parser::parse_element(Pointer p, Node* node)
	{
		Node* e;
		PString name;
		if (*p == '<')
		{
			if (match(p + 1, NameExclusive))
				throw ParseException("NameStartChar doesn't match.");
			while (!match(p, Space))
				name += *p++;
			e = new Element(name);
			skip(p, Space);
			while (*p != '>')  /* Attributes */
			{
				name = "";
				while (!match(p, Space))
					name += *p++;
				skip(p, Space);
				if (*p == '=')
					++p;
				skip(p, Space);
			}
			if (*p != '>')
				throw ParseException("start tag doesn't match.");

			/* text */

		}
	}
}
