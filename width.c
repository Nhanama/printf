#include "main.h"

/**
 * get_width - Calculates the width
 * @format: Formatted string for printing the arguments.
 * @i: List of arguments being printed
 * @list: list of arguments.
 *
 * Return: width.
 */

int get_width(const char *format, int *i, va_list list)
{
	int curr_v;
	int width = 0;

	for (curr_v = *i + 1; format[curr_v] != '\0'; curr_v++)
	{
		if (is_digit(format[curr_v]))
		{
			width *= 10;
			width += format[curr_v] - '0';
		}
		else if (format[curr_v] == '*')
		{
			curr_v++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*i = curr_v - 1;

	return (width);
}

