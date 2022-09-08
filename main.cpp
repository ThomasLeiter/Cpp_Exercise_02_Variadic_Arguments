#include <iostream>
#include <string>
#include <cstdarg>

/*
 * Naive implementation of an output function
 * mocking printf from C language.
 * %d, %s and %f will be replaced by
 * int, const char* and double arguments.
 */
void cstyle_printf(std::string fmt, ...)
{
	// Get the variadic argument list i.e. (...)
	std::va_list args;
	// Tell the compiler that this list 
	// starts behind parameter fmt.
	va_start(args, fmt);
	// Parse fmt string and replace with 
	// var_args where appropriate
	for (int i = 0; i < fmt.length(); ++i)
	{
		if (fmt[i] == '%' && i + 1 < fmt.length())
		{
			switch (fmt[i + 1])
			{
			case 'd':
				// Convert next argument to int
				std::cout << va_arg(args, int);
				break;
			case 's':
				// Convert next argument to const char *
				std::cout << va_arg(args, const char *);
				break;
			case 'f':
				// Convert next argument to double
				std::cout << va_arg(args, double);
				break;
			default:
				std::cout << fmt[i];
			}
			++i;
		}
		else
		{
			std::cout << fmt[i];
		}
	}
}

/*
 * Naive implementation of an output function
 * mocking printf from C language.
 * Variadic templates are used for implementation.
 *
 * Recursion anchor without additional parameters.
 */
void cpp_printf(const std::string &fmt)
{
	std::cout << fmt;
}

/*
 * Naive implementation of an output function
 * mocking printf from C language.
 * Variadic templates are used for implementation.
 * '%' will be replaced by next argument,
 * independant of type.
 *
 * Recursion with additional parameters.
 */
template <typename Head, typename... Tail>
void cpp_printf(const std::string &fmt, Head head, Tail... tail)
{
	for (auto it = fmt.cbegin(); it != fmt.cend(); ++it){
		if (*it == '%'){
			std::cout << head;
			// Next argument found. Recurse and exit.
			cpp_printf(std::string(it,fmt.cend()),tail ...);
			return;
		} else {
			std::cout << *it;
		}
	}
}

int main()
{
	cstyle_printf("The %s programming language is from year %d. \nCurrent version C++%d. GCC support since version %f.\n", "C++", 1985, 20, 10.1);
	cpp_printf("The %s programming language is from year %. \nCurrent version C++%. GCC support since version %.\n", "C++", 1985, 20, 10.1);
}