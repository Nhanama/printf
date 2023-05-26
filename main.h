#ifndef MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/*FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
/**
 * struct fmt - Struct operator
 *
 * @fmt: The format for printf.
 * @fn: The function associated with printf statement.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};
/**
 * typedef struct fmt fmt_t - Structure operator
 *
 * @fmt: The format for printf.
 * @fm_t: The function associated with printf.
 */
typedef struct fmt fmt_t;

int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);
/** FUNCTIONS FOR PRINTF*/
/* Funcion for printf memory address */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);
/* Functions to print numbers in a function */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);
/* Functions handling specifiers */
int get_size(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_flags(const char *format, int *i);
int get_precision(const char *format, int *i, va_list list);
/* Function that print non printable characters */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);
/* Funtions for printing printf strings and characters */
int print_percent(va_list types, char buffer[],
		int flags, int width, int precision, int size);
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
/* Function to print strings in rot 13 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
/* Function to reverse a string */
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);
/* UTILS */
long int convert_size_unsgnd(unsigned long int num, int size);
int is_digit(char);
int append_hexa_code(char, char[], int);
long int convert_size_number(long int num, int size);
int is_printable(char);
/* width handler in printf */
int write_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);
#endif /* MAIN_H */