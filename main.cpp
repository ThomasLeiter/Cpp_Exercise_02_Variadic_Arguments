#include <iostream>
#include <string>
#include <cstdarg>
#include <vector>

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
	va_end(args);
}

template<typename... Ts>
void cpp_printf(const std::string &fmt, Ts...);

/*
 * Naive implementation of an output function
 * mocking printf from C language.
 * Variadic templates are used for implementation.
 *
 * Recursion anchor without additional parameters.
 */
template<>
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
			cpp_printf(std::string(++it,fmt.cend()),tail ...);
			return;
		} else {
			std::cout << *it;
		}
	}
}

template<typename T>
/* 
 * Prints out the string fmt, 
 * replacing all instances of '%'
 * with arguments from vector args.
 * Type T will usually be inferred 
 * by the compiler.
 * 
 * Undefined behaviour if args.size() 
 * does not match the number of
 * placeholders in fmt.
 */
void vector_printf(const std::string &fmt, const std::vector<T>& args){
	// Iterator for the std::vector
	auto vit = args.cbegin(); 
	// Iterate over fmt and output
	for (auto sit = fmt.cbegin(); sit != fmt.cend(); ++sit){
		if (*sit == '%'){
			std::cout << *vit++;
		} else {
			std::cout << *sit;
		}
	}
}

template<typename T>
/* 
 * Prints out the string fmt, 
 * replacing all instances of '%'
 * with arguments from initializer_list args.
 * Type T cannot be inferred by
 * the compiler and has to be given!
 * 
 * Undefined behaviour if args.size() 
 * does not match the number of
 * placeholders in fmt.
 */
void init_list_printf(const std::string &fmt, std::initializer_list<T> args){
	// Iterator for std::initializer_list
	// Note that there is no constant iterator cbegin()!
	auto vit = args.begin();
	for (auto sit = fmt.begin(); sit != fmt.end(); ++sit){
		if (*sit == '%'){
			std::cout << *vit++;
		} else {
			std::cout << *sit;
		}
	}
}



int main()
{
	cstyle_printf("The %s programming language is from year %d. \nCurrent version C++%d. GCC support since version %f.\n\n", "C++", 1985, 20, 10.1);
	cpp_printf("The % programming language is from year %. \nCurrent version C++%. GCC support since version %.\n\n", "C++", 1985, 20, 10.1);

	vector_printf("% blind mice, hiding from % cat. 2 cute, isn't it?\n\n", std::vector{3,1,2});
	init_list_printf<int>("% blind mice, hiding from % cat. 2 cute, isn't it?\n\n", {3,1,2});
}