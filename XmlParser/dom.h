#pragma once

#include <vector>
#include <string>

namespace xml
{
namespace DOM
{
	using std::string;
	using std::vector;
	class Node;
	class Element;
	class Document;
	class DocumentType;
	class DocumentFragment;
	class Text;
	class Comment;
	class CDATASection;
	class ProcessingInstruction;
	class Attr;
	class EntityReference;
	class NodeList;

	using DOMString = std::vector<unsigned short>;

	class Node
	{
	public:
		// node_type
		typedef unsigned short NodeType;
		const NodeType      ELEMENT_NODE = 1;
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
		virtual bool hasChildNodes() = 0;

	protected:
		Node() : node_name_(vector<unsigned short>()), node_value_(vector<unsigned short>()), node_type_(0),
			parent_(nullptr), child_nodes_(nullptr), first_child_(nullptr), last_child_(nullptr),
			previous_sibling_(nullptr), next_sibling_(nullptr), attributes_(nullptr), owner_document(nullptr) {}

		const DOMString& node_name_;
		const DOMString& node_value_;
		// raises(DOMException) on setting
		// raises(DOMException) on retrieval
		NodeType node_type_;
		Node* parent_;
		NodeList* child_nodes_;
		Node* first_child_;
		Node* last_child_;
		Node* previous_sibling_;
		Node* next_sibling_;
		NamedNodeMap* attributes_;
		Document*  owner_document;

		virtual Node* insertBefore(Node* newChild, Node* refChild); //raise(DOMException);
		virtual Node* replaceChild(Node* newChild, Node* oldChild); //raise(DOMException);
		virtual Node* removeChild(Node* oldChild);// raises(DOMException);
		virtual Node* appendChild(Node* newChild); //raises(DOMException);
		virtual Node* cloneNode(bool deep);
	};

	class Document : public Node
	{
	public:
		Document();
		//const DOMImplementation   implementation;
		//const Element             documentElement;
		Element					  create_Element(DOMString tag_name);// raises(DOMException);
		DocumentFragment          create_DocumentFragment() noexcept;
		Text                      create_TextNode(DOMString data) noexcept;
		Comment                   createComment(DOMString data) noexcept;
		CDATASection              createCDATASection(DOMString data); //raises(DOMException);
		ProcessingInstruction     createProcessingInstruction(DOMString target, DOMString data);// raises(DOMException);
		Attr                      createAttribute(DOMString name); //raises(DOMException);
		EntityReference           createEntityReference(DOMString name); //raises(DOMException);
		NodeList                  getElementsByTagName(DOMString tagname) noexcept;

		virtual bool hasChildNodes() { return true; }
	private:
		DocumentType         doctype_;
		Element*              element_;
	};



	class DocumentFragment : public Node {};

	

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

	class DocumentType : public Node
	{
	public:
		DocumentType() {}
		DOMString name_;
		NamedNodeMap         entities;
		NamedNodeMap         notations;
	};
}
}