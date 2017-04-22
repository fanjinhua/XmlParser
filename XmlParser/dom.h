#pragma once

#include <vector>
#include <string>
#include <map>
namespace xml
{
namespace DOM
{
	using std::string;
	using std::vector;
	using std::map;
	class Node;
	class Element;
	class Document;
	class DocumentType;
	class DocumentFragment;
	class NamedNodeMap;
	class Text;
	class Comment;
	class CDATASection;
	class ProcessingInstruction;
	class Attr;
	class EntityReference;
	class NodeList;

	/* sequences of 16-bits */
	//typedef std::u16string DOMString;
	typedef std::string DOMString;

	class Node
	{
	public:
		typedef unsigned short NodeType;
		const NodeType      ELEMENT_NODE = 1;
		const NodeType      ATTRIBUTE_NODE = 2;
		const NodeType      TEXT_NODE = 3;
		const NodeType      CDATA_SECTION_NODE = 4;
		const NodeType      ENTITY_REFERENCE_NODE = 5;
		const NodeType      ENTITY_NODE = 6;
		const NodeType      PROCESSING_INSTRUCTION_NODE = 7;
		const NodeType      COMMENT_NODE = 8;
		const NodeType      DOCUMENT_NODE = 9;
		const NodeType      DOCUMENT_TYPE_NODE = 10;
		const NodeType      DOCUMENT_FRAGMENT_NODE = 11;
		const NodeType      NOTATION_NODE = 12;
		virtual bool has_child_nodes();
		virtual Node* insert_before(Node* newChild, Node* refChild); //raise(DOMException);
		virtual Node* replace_child(Node* newChild, Node* oldChild); //raise(DOMException);
		virtual Node* remove_child(Node* oldChild);// raises(DOMException);
		virtual Node* append_child(Node* newChild); //raises(DOMException);
		virtual Node* clone_node(bool deep);

	public:
		NodeType node_type_;
		DOMString node_name_;
		DOMString node_value_;
		Node* parent_;
		NodeList* child_nodes_;
		Node* first_child_;
		Node* last_child_;
		Node* pre_sibling_;
		Node* next_sibling_;
		//NamedNodeMap* attrs_;
		Document*  owner_document;
	protected:
		Node() : node_type_(0), node_name_(DOMString()), node_value_(DOMString()),
			parent_(nullptr), child_nodes_(nullptr), first_child_(nullptr), last_child_(nullptr),
			pre_sibling_(nullptr), next_sibling_(nullptr),/* attrs_(nullptr), */owner_document(nullptr) {}
		Node(NodeType type, DOMString name = DOMString(), DOMString value = DOMString()) : \
			node_type_(type), node_name_(name), node_value_(value),
			parent_(nullptr), child_nodes_(nullptr), first_child_(nullptr), last_child_(nullptr),
			pre_sibling_(nullptr), next_sibling_(nullptr),/* attrs_(nullptr), */owner_document(nullptr) {}
	};

	class Document : public Node
	{
	public:
		Document();
		//const DOMImplementation   implementation;
		//const Element             documentElement;
		bool has_child_nodes() override { return false; }
		Element*				  create_Element(const DOMString& tag_name);// raises(DOMException);
		DocumentFragment*         create_DocumentFragment() noexcept;
		Text*                     create_TextNode(DOMString data) noexcept;
		Comment*                  createComment(DOMString data) noexcept;
		CDATASection*             createCDATASection(DOMString data); //raises(DOMException);
		ProcessingInstruction*    createProcessingInstruction(DOMString target, DOMString data);// raises(DOMException);
		Attr*                     createAttribute(DOMString name); //raises(DOMException);
		//EntityReference           createEntityReference(DOMString name); //raises(DOMException);
		NodeList*                 getElementsByTagName(DOMString tagname) noexcept;

	protected:
		DocumentType*         doctype_;
		Element*              element_;
	};

	

	class DocumentFragment : public Node 
	{
	public:
		DocumentFragment(): Node() {}
	};

	class Attr : public Node
	{
	public:
		Attr(const DOMString& name) : Node(ATTRIBUTE_NODE, name), name_(name) {}
		void set_value(const DOMString& value)
		{
			specified_ = true;
			value_ = value;
		}
		DOMString            name_;
		bool              specified_;
		DOMString            value_;
	};

	class NamedNodeMap 
	{
	public:
		NamedNodeMap(): length_(0) {}
		Node* get_named_item(DOMString node_name) noexcept
		{
			return map_.count(node_name) ? map_[node_name] : nullptr;
		}
		Node* set_named_item(Node* new_node)// raises(DOMException);
		{
			Node* old_node = nullptr;
			if (map_.count(new_node->node_name_))
				old_node = map_[new_node->node_name_], length_--;
			
			map_[new_node->node_name_] = new_node;
			length_++;
			return old_node;
		}
		Node* remove_named_Item(DOMString node_name)// raises(DOMException);
		{
			Node* node = nullptr;
			if (map_.count(node_name))
			{
				node = map_[node_name];
				map_.erase(node_name);
				length_--;
			}
			return node;
		}
		Node* item(unsigned long index) noexcept;
	private:
		unsigned long length_;
		std::map<DOMString, Node*> map_;
	};
	class Element : public Node
	{
	public:
		Element() : Node(ELEMENT_NODE) {}
		Element(const DOMString& name) : Node(ELEMENT_NODE, name), tag_name_(name) {}
		bool has_child_nodes() override { return false; }
		DOMString tag_name_;
		DOMString                 get_attr(const DOMString& name) noexcept;
		void                      set_attr(const DOMString& name, const DOMString& value)// raises(DOMException);
		{
			Attr* new_attr = new Attr(name);
			new_attr->set_value(value);
			this->set_attr_node(new_attr);
		}
		void                      remove_attr(DOMString name);// raises(DOMException);
	private:
		NamedNodeMap			  attrs_;
		Attr*                     get_attr_node(DOMString name) noexcept;
		Attr*                     set_attr_node(Attr* new_attr)// raises(DOMException);
		{
			return attrs_.set_named_item(new_attr);
		}
		Attr*                     remove_attri_node(Attr* old_attr);// raises(DOMException);
		NodeList*                 get_elem_by_tag(DOMString name) noexcept;
		void                      normalize();
	};
#if 0
	class NodeList 
	{
	public:
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
		DocumentType():Node() {}
		bool has_child_node() { return false; }
		const DOMString name_;
		//const NamedNodeMap         entities;
		//const NamedNodeMap         notations;
	};
#endif 
}
}