#include "dom.h"

namespace xml
{
namespace DOM
{
	Document::Document() : Node(), doctype_(), element_(nullptr)
	{

	}
	Element Document::create_Element(DOMString tag_name)
	{
		return Element();
	}
	DocumentFragment Document::create_DocumentFragment() noexcept
	{
		return DocumentFragment();
	}
	Text Document::create_TextNode(DOMString data) noexcept
	{
		return Text();
	}
	Comment Document::createComment(DOMString data) noexcept
	{
		return Comment();
	}
	Attr Document::createAttribute(DOMString name)
	{
		return Attr();
	}
	EntityReference Document::createEntityReference(DOMString name)
	{
		return EntityReference();
	}
}
}