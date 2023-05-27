#include "main.h"
/* Functions to print a string in ROT13 */
/**
 * print_rot13string - Print a string character using ROT13
 * @flags: prints active flags
 * @size: Size specification
 * @types: argument list
 * @precision: Precision
 * @buffer: Buffer array for handling print
 * @width: width
 * Return: Numbers of characters to be printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;
	char *str;
	unsigned int m, n;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (m = 0; str[m]; m++)
	{
		for (n = 0; in[n]; n++)
		{
			if (in[n] == str[m])
			{
				c = out[n];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!in[n])
		{
			c = str[m];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
/* Function for pprinting a pointer */
/**
 * print_pointer - this prints the value of a pointer
 * @flags: prints active flags
 * @size: Size specification
 * @types: argument list
 * @precision: Precision
 * @buffer: Buffer array for handling print
 * @width: width
 * Return: Numbers of characters to be printed
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}
/* Function to print in reverse */
/**
 * print_reverse - prints the reverse of a string
 * @flags: prints active flags
 * @size: Size specification
 * @types: argument list
 * @precision: Precision
 * @buffer: Buffer array for handling print
 * @width: width
 * Return: Numbers of characters to be printed
 */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int b, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (b = 0; str[b]; b++)
		;

	for (b = b - 1; b >= 0; b--)
	{
		char z = str[b];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/* Function for printing a non-printable character */
/**
 * print_non_printable - this prints ascii codes in hexadecimal format
 * @flags: prints active flags
 * @size: Size specification
 * @types: argument list
 * @precision: Precision
 * @buffer: Buffer array for handling print
 * @width: width
 * Return: Numbers of characters to be printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[n] != '\0')
	{
		if (is_printable(str[n]))
			buffer[n + offset] = str[n];
		else
			offset += append_hexa_code(str[n], buffer, n + offset);

		n++;
	}

	buffer[n + offset] = '\0';

	return (write(1, buffer, n + offset));
}

