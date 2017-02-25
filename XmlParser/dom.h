#pragma once

#include <vector>
#include <string>

namespace xml
{
namespace DOM
{
	class Node;
	class Element;
	class DocumentFragment;
	class Text;
	class Comment;
	class CDATASection;
	class ProcessingInstruction;
	class Attr;
	class EntityReference;
	class NodeList;

	using DOMString = std::vector<unsigned short>;
	using std::string;

	class Document : public Node
	{
	public:
		Document() = default;
		//Document(const char* filename) : filename_(filename) {};
		//const DocumentType        doctype;
		//const DOMImplementation   implementation;
		//const Element             documentElement;
		Element					  create_Element(DOMString tagName);// raises(DOMException);
		DocumentFragment          create_DocumentFragment() noexcept;
		Text                      create_TextNode(DOMString data) noexcept;
		Comment                   createComment(DOMString data) noexcept;
		CDATASection              createCDATASection(DOMString data); //raises(DOMException);
		ProcessingInstruction     createProcessingInstruction(DOMString target, DOMString data);// raises(DOMException);
		Attr                      createAttribute(DOMString name); //raises(DOMException);
		EntityReference           createEntityReference(DOMString name); //raises(DOMException);
		NodeList                  getElementsByTagName(DOMString tagname) noexcept;
	private:

	};



	class DocumentFragment : public Node {};

	class Node 
	{
	public:

		// NodeType
		const unsigned short      ELEMENT_NODE = 1;
		const unsigned short      ATTRIBUTE_NODE = 2;
		const unsigned short      TEXT_NODE = 3;
		const unsigned short      CDATA_SECTION_NODE = 4;
		const unsigned short      ENTITY_REFERENCE_NODE = 5;
		const unsigned short      ENTITY_NODE = 6;
		const unsigned short      PROCESSING_INSTRUCTION_NODE = 7;
		const unsigned short      COMMENT_NODE = 8;
		const unsigned short      DOCUMENT_NODE = 9;
		const unsigned short      DOCUMENT_TYPE_NODE = 10;
		const unsigned short      DOCUMENT_FRAGMENT_NODE = 11;
		const unsigned short      NOTATION_NODE = 12;
	private:
		const DOMString& nodeName;
		const DOMString& nodeValue;
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		unsigned short nodeType;
		Node* parentNode;
		NodeList* childNodes;
		Node* firstChild;
		Node* lastChild;
		Node* previousSibling;
		Node* nextSibling;
		NamedNodeMap attributes;
		Document*  ownerDocument;

		virtual Node* insertBefore(Node* newChild, Node* refChild); //raise(DOMException);
		virtual Node* replaceChild(Node* newChild, Node* oldChild); //raise(DOMException);
		virtual Node* removeChild(Node* oldChild);// raises(DOMException);
		virtual Node* appendChild(Node* newChild); //raises(DOMException);
		virtual bool hasChildNodes() = 0;
		virtual Node* cloneNode(bool deep);
	};

	class NodeList 
	{
	public:
		Node* item(unsigned long index);
	private:
		const unsigned long length;
	};

	class NamedNodeMap 
	{
	public:
		Node* getNamedItem(DOMString name);
		Node* setNamedItem(Node* arg);// raises(DOMException);
		Node* removeNamedItem(DOMString name);// raises(DOMException);
		Node* item(unsigned long index);
	private:
		const unsigned long length;
	};

	class CharacterData : public Node 
	{
		DOMString            data;
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		unsigned long        length;
		DOMString   substringData(unsigned long offset, unsigned long count);// raises(DOMException);
		void appendData(DOMString arg);// raises(DOMException);
		void insertData(unsigned long offset, DOMString arg);// raises(DOMException);
		void deleteData(unsigned long offset, unsigned long count);// raises(DOMException);
		void replaceData(unsigned long offset, unsigned long count, DOMString arg);// raises(DOMException);
	};

	class Attr : public Node 
	{
		DOMString            name;
		bool              specified;
		DOMString            value;
	};

	class Element : public Node 
	{
	public:
		const DOMString tagName;
		DOMString                 getAttribute(DOMString name);
		void                      setAttribute(DOMString name, DOMString value);// raises(DOMException);
		void                      removeAttribute(DOMString name);// raises(DOMException);
		Attr                      getAttributeNode(DOMString name);
		Attr                      setAttributeNode(Attr newAttr);// raises(DOMException);
		Attr                      removeAttributeNode(Attr oldAttr);// raises(DOMException);
		NodeList                  getElementsByTagName(DOMString name);
		void                      normalize();
	};

	class Text : public CharacterData 
	{
		Text* splitText(unsigned long offset);// raises(DOMException);
	};

	class Comment : public CharacterData
	{

	};
}
}