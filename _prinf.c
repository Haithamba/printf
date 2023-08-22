#include "main.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    va_list args;
    va_start(args, format);

    int printed_chars = 0;
    char buffer[BUFF_SIZE];
    int buff_ind = 0;

    for (size_t i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);
            i++;
            if (format[i] == '\0')
                break;
            int result = handle_format_specifier(format[i], args, buffer, &buff_ind);
            if (result == -1)
            {
                va_end(args);
                return -1;
            }
            printed_chars += result;
        }
    }

    print_buffer(buffer, &buff_ind);

    va_end(args);

    return printed_chars;
}

/**
 * print_buffer - Prints the contents of the buffer if it exists
 * @buffer: Array of chars
 * @buff_ind: Index at which to add the next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *buff_ind = 0;
    }
} 
