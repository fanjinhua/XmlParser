#include "dom.h"

namespace xml
{
namespace DOM
{
	Document::Document() : Node(), doctype_(), element_(nullptr)
	{
	}
	bool Document::has_child_nodes()
	{
		return false;
	}
	Element Document::create_Element(const DOMString & tag_name)
	{
		return Element();
	}
	//EntityReference Document::createEntityReference(DOMString name)
	//{
	//	return EntityReference();
	//}
}
}