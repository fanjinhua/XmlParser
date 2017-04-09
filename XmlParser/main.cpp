#include "xml_parser.h"
#include "dom.h"
#include <iostream>

int main()
{
	xml::DOM::Document doc;
	xml::Parser p(doc, "test.xml");
	std::cout << doc << std::endl;
	return 0;
}