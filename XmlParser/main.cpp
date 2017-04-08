#include "xml_parser.h"
#include "dom.h"

int main()
{
	xml::DOM::Document doc;
	xml::Parser p(doc, "test.xml");
	return 0;
}