#include "main.h"

void print_buffer(char buffer[], int *buff_index);

/**
* _printf - Printf function to produce output according to format.
* @format: format.
* Return: the number of chars printed.
*/

int _printf(const char *format, ...)
{
/*declare and initialize*/
int i, printed = 0, printed_chars = 0;
int flags, width, precision, size, buff_index = 0;

va_list list;

char buffer[BUFF_SIZE];

if (format == NULL)
return (-1);

va_start(list, format); /* initialize the va_list */

for (i = 0; format && format[i] != '\0'; i++)
{
if (format[i] != '%')
{
buffer[buff_index++] = format[i];
if (buff_index == BUFF_SIZE)
print_buffer(buffer, &buff_index);
/* prints(1, &format[i], 1);*/
printed_chars++;
}
else
{
/* Print the buffer*/
print_buffer(buffer, &buff_index);


/* Get the flags from the format string*/
flags = get_flags(format, &i);

/* Get the width from the format string*/
width = get_width(format, &i, list);

/* Get the precision from the format string*/
precision = get_precision(format, &i, list);

/* Get the size from the format string */
size = get_size(format, &i);
++i;
printed = handle_print(format, &i, list, buffer,
flags, width, precision, size);
if (printed == -1)
return (-1);
printed_chars += printed;
}
}

print_buffer(buffer, &buff_index);

va_end(list);

return (printed_chars);
}

/**
* print_buffer - Prints the contents of the buffer if it exist
* @buffer: Array of characters (chars)
* @buff_index: Index at which to add next char, represents the length.
*/
void print_buffer(char buffer[], int *buff_index)
{
if (*buff_index > 0)
write(1, &buffer[0], *buff_index);

*buff_index = 0;
}
