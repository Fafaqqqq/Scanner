#include "Scanner.h"
#include <iostream>
#include <stdarg.h>
#include <cstring>
#include <string>
#include <sstream>

int Scanner::Scan(const char* format, ...)
{
	std::string input;
	std::getline(std::cin, input);

	std::istringstream sin(input);

	va_list arg_pointer;
	va_start(arg_pointer, format);

	int count_percent = 0;
	int format_len = strlen(format);

	for (int i = 0; i < format_len; ++i)
	{
		if (format[i] == '%')
		{
			count_percent++;
			i++;
		}
	}

	if (!count_percent)
	{
		return count_percent;
	}

	const char* src = format;

	while (*src != '\0')
	{
		if (*src == '%')
		{
			switch (*(++src))
			{
			case 'd':
			{
				if (!(sin >> *(int*)va_arg(arg_pointer, int*)))
				{
					throw std::logic_error("Uncorrect value!");
				}
				count_percent++;
			}
			break;
			case 'c':
			{
				if (!(sin >> *(char*)va_arg(arg_pointer, char*)))
				{
					throw std::logic_error("Uncorrect value!");
				}
				count_percent++;
			}
			break;
			case 's':
			{
				if (!(sin >> *(std::string*)va_arg(arg_pointer, std::string*)))
				{
					throw std::logic_error("Uncorrect value!");
				}
				count_percent++;
			}
			break;
			case 'f':
			{
				if (!(sin >> *(double*)va_arg(arg_pointer, double*)))
				{
					throw std::logic_error("Uncorrect value!");
				}
				count_percent++;
			}
			break;
			default:
				throw std::logic_error("Uncorrect line!");
				break;
			}
			++src;
		}
		else
		{
			if (sin.get() != *(src++))
			{
				throw std::logic_error("Uncorrect line!");
			}
		}
	}

	std::string test_end;

	if (sin >> test_end)
	{
		throw std::logic_error("Uncorrect line!");
	}

	va_end(arg_pointer);

	return count_percent;
}
