#include "main.h"
/* FUNCTION TO PRINT PERCENTAGE SIGN */
/**
 * print_percent - this prints the sign 'percent'
 * @width: Variable for width
 * @size: Size
 * @types: argument lists
 * @precision: specifications
 * @buffer: Buffer for handling print
 * @flags:  Takes a record of active flags
 * Return: number of characters to be printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/* Function to print a binary */
/**
 * print_binary - this prints an unsigned value
 * @width: Variable for width
 * @size: Size
 * @types: argument lists
 * @precision: specifications
 * @buffer: Buffer for handling print
 * @flags:  Takes a record of active flags
 * Return: number of characters to be printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int a, b, c, sum;
	unsigned int n[32];

	UNUSED(size);
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(precision);
	UNUSED(width);

	a = va_arg(types, unsigned int);
	b = 2147483648; /* (2 ^ 31) */
	n[0] = a / b;

	for (i = 1; i < 32; i++)
	{
		b /= 2;
		n[c] = (a / b) % 2;
	}
	for (c = 0, sum = 0, count = 0; c < 32; c++)
	{
		sum += n[c];
		if (sum || c == 31)
		{
			char z = '0' + n[c];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
/* Functions to print a string */
/**
 * print_string - Prints a string of characters
 * @width: Variable for width
 * @size: Size
 * @types: argument lists
 * @precision: specifications
 * @buffer: Buffer for handling print
 * @flags:  Takes a record of active flags
 * Return: number of characters to be printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)

{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(precision);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(width);
	UNUSED(flags);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}
/* Function to print a character */
/**
 * print_char - Function to print a characer
 * * @width: Variable for width
 * @size: Size
 * @types: argument lists
 * @precision: specifications
 * @buffer: Buffer for handling print
 * @flags:  Takes a record of active flags
 * Return: number of characters to be printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/* Function to print integer */
/**
 * print_int - Fucntion to print integer
 * @width: Variable for width
 * @size: Size
 * @types: argument lists
 * @precision: specifications
 * @buffer: Buffer for handling print
 * @flags:  Takes a record of active flags
 * Return: number of characters to be printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)

{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

