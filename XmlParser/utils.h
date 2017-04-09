#pragma once

#include <stdexcept>
#include <string>

namespace xml
{
namespace DOM
{
	using std::string;
	class DOMException : public std::exception
	{
	public:
		DOMException() : std::exception(), info_("") {}
		DOMException(const char* info) : info_(info) {}
		virtual const char* what() const noexcept
		{
			return info_;
		}
	private:
		const char* info_;
	};

	class ParseException : public DOMException
	{
	public:
		ParseException(const char* info) : DOMException(info) {}
	};

	template<typename typ, typ... V>
	struct Field
	{

	};

	using SPACE = Field<char, ' ', '\t', '\r', '\n'>;

	template<typename T, typename... V>
	void skip_field(T p, V... fil)
	{
	}

	class tokenizer
	{
	public:
		string* tokenize(string* data)
		{
			/* empty_element tags*/
			//for (string::size_type index = 0; index != data->size(); ++index)
			//{
			for (auto it = data->begin(); it != data->end(); ++it)
			{
				if (data[index] == '<')
				{
					string name;
					if (data[index + 1] == ' ')  // TODO, whitespace
						throw ParseException("WHITESPACE_FAULT");
					for (auto j = index; data[j] != ' '; ++j)
						name.push_back(data[j]);

				}
			}
		}
	};

}
}
