#include "main.h"
/* Function to write handle */
/**
 * handle_write_char - this prints a string character
 * @width: variable for width
 * @size: size specifier variable
 * @c: character types
 * @precision: precision specifier variable
 * @buffer: buffer array for handling print
 * @flags: returns active flags
 * Return: Number of characters to obe printed
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{/* Character is stored at the left side while padding is at buffer's right */
	int n = 0;
	char padd = '';

	UNUSED(size);
	UNUSED(precision);

	if (flags & F_ZERO)
		padd = '0';

	buffer[n++] = c;
	buffer[n] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (n = 0; n < width - 1; n++)
			buffer[BUFF_SIZE - n - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - n - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - n - 1], width - 1) +
					write(1, &buffer[0], 1));
	}
		return (write(1, &buffer[0], 1));
}


/* Function for writing a number */
/**
 * write_number - Prints a string character
 * @width: variable for width
 * @size: size specifier variable
 * @precision: precision specifier variable
 * @buffer: buffer array for handling print
 * @flags: returns active flags
 * @is_negative: argument lists
 * @ind: character types
 * Return: Number of characters to be printed
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padd, extra_ch));
}
/**
 * write_num - prints a number using a buffer
 * @ind: index that starts a buffer
 * @flags: returns active flags
 * @width: variable for width
 * @prec: variable
 * @buffer: buffer array for handling print
 * @padd: padding character
 * @extra_c: extra character.
 * @length: length of number
 * Return: number of characters to be printed
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_c)
{
	int j, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no character is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (j = 1; j < width - length + 1; j++)
			buffer[j] = padd;
		buffer[j] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign characters to left of buffer*/
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], j - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra chars to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], j - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra chars to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], j - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - prints unsigned integer
 * @ind: index that starts a buffer
 * @flags: returns active flags
 * @width: variable for width
 * @precision: precision specifier variable
 * @buffer: buffer array for handling print
 * @size: size of print
 * @is_negative: number which indicates if a chosen number is negative
 * Return: number of characters to be printed
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position n */
	int length = BUFF_SIZE - ind - 1, n = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no character is printed */

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (n = 0; n < width - length; n++)
			buffer[n] = padd;

		buffer[n] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], j));
		}
		else /* Asign extra chars to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], j) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - prints a memory address of a variable
 * @extra_c: Char representing extra characters
 * @flags: specifier
 * @length: num length
 * @padd_start: Index which starts a psdding
 * @padd: Character representing the padding
 * @buffer: Arrays of characteers
 * @ind: Index at which the number starts in the buffer
 * @width: Width specifier variable
 * Return: Number of characters to be written
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start)
{
	int m;

	if (width > length)
	{
		for (m = 3; m < width - length + 3; m++)
			buffer[m] = padd;
		buffer[m] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], m - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], m - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], m - padd_start) +
				write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}


