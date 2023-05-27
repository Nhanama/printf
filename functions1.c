#include "main.h"
/* Function for printing HEXX number in lower or uppercase */
/**
 * print_hexa - prints a hexadecimal in lowercase or uppercase
 * @flags: this calculates number of active flags
 * @width: gets width size
 * @size: specifies size
 * @size: size specification for printf
 * @types: argument lists
 * @buffer: array handling print
 * @map_to: array of values numbers are mapped to
 * @flag_ch: also calculates the active flags
 * @precision: accurately specifies precision
 * Return: number of characters to be printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int n = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[n--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[n--] = map_to[num % 16];
		num /= 16;
	}
	if (flags & F_HASH && init_num != 0)
	{
		buffer[n--] = flag_ch;
		buffer[n--] = '0';
	}

	n++;

	return (write_unsgnd(0, n, buffer, flags, width, precision, size));
}
/* Function to print UNSIGNED NUMBER in HEXADECIMAL */
/**
 * print_hexadecimal - prints number in hexadecimal format
 * @flags: this calculates number of active flags
 * @width: gets width size
 * @size: size specification for printf
 * @types: argument lists
 * @buffer: array handling print
 * @precision: accurately specifies precision
 * Return: number of characters to be printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/* Function to print unsigned number in octadecimal */
/**
 * print_octal - prints a number in octadecimal
 * @flags: calculates the number of active flags
 * @width: gets width size
 * @size: size specification for printf
 * @types: argument lists
 * @buffer: array handling print
 * @precision: accurately specifies precision
 * Return: number of characters to be printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int v = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[v--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[v--] = (num % 8) + '0';
		num /= 8;
	}
	if (flags & F_HASH && init_num != 0)
		buffer[v--] = '0';

	v++;

	return (write_unsgnd(0, v, buffer, flags, width, precision, size));
}
/* Function to print unsigned number in Uppercase Hexadecimal */
/**
 * print_hexa_upper - prints in uppercase
 * @flags: calculates the number of active flags
 * @width: gets width size
 * @size: size specification for printf
 * @types: argument lists
 * @buffer: array handling print
 * @precision: accurately specifies precision
 * Return: number of characters to be printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/* function to print unsigned integer */
/**
 * print_unsigned - print unsigned integer
 * @flags: calculates the number of active flags
 * @width: gets width size
 * @size: size specification for printf
 * @types: argument lists
 * @buffer: array handling print
 * @precision: accurately specifies precision
 * Return: number of characters to be printed
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

