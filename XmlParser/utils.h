#pragma once

#include <stdexcept>

namespace xml
{
namespace DOM
{
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
}
}
