
#include "main.h"

/**
* print_char - Prints a char in the function
* @types: List all the arguments
* @buffer: Buffer array to handle print function
* @flags:  Calculates active flags used in the func
* @width: Width specifications
* @precision: Precision specification
* @size: Size specification
* Return: Num_of_chars_printed
*/
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
char c = va_arg(types, int);

return (handle_write_char(c, buffer, flags, width, precision, size));
}

/**
* print_string - function to Print a string
* @types: List all the arguments
* @buffer: Buffer array to handle print in the function
* @flags:  Calculates active flags used in the function
* @width: get width or width specifier
* @precision: Precision specification
* @size: Size specifier
* Return: Num_of_chars_printed
*/
int print_string(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
int length = 0, i;
char *str = va_arg(types, char *);

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);
if (str == NULL)
{
str = "(null)";
if (precision >= 6)
str = " ";
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
/**
* print_percent - Prints a percent sign or modulus
* @types: Lists all the arguments in the func
* @buffer: Buffer array to handle print function
* @flags:  Calculates active flags in the function
* @width: get width or is a width specifier
* @precision: Precision specification
* @size: Size specifier in the function
* Return: Number of chars printed
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

/**
* print_int - Print int in the function
* @types: Lists all the arguments in the function
* @buffer: Buffer array to handle print in the function
* @flags:  Calculates active flags in the function .
* @width: get width or is a width specifier .
* @precision: Precision specification
* @size: Size specifier in the function
* Return: Num_of_chars_printed
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

/**
* print_binary - Prints an unsigned number in the function
* @types: Lists all the arguments in the function
* @buffer: Buffer array to handle print in the function
* @flags:  Calculates active flags in the function .
* @width: get width or is a width specifier .
* @precision: Precision specification
* @size: Size specifier in the function in the function
* Return: Num_of_chars_printed
*/

int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
unsigned int n, m, i, sum;
unsigned int a[32];
int count;

UNUSED(buffer);
UNUSED(flags);
UNUSED(width);
UNUSED(precision);
UNUSED(size);

n = va_arg(types, unsigned int);
m = 2147483648; /* (2 ^ 31) */
a[0] = n / m;
for (i = 1; i < 32; i++)
{
m /= 2;
a[i] = (n / m) % 2;
}
/*Iterating from i = 0 to i < 32 to perform a calculation*/
for (i = 0, sum = 0, count = 0; i < 32; i++)
{
sum += a[i];
if (sum || i == 31)
{
char z = '0' + a[i];

write(1, &z, 1);
count++;
}
}
return (count);
}
