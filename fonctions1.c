#include "main.h"

/**
 * print_unsigned - Print an unsigned number
 * @args: List of arguments
 * @buffer: Buffer for printing
 * @flags: Active formatting flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_unsigned(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    int index = BUFF_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);

    num = convert_to_unsigned(num, size);

    if (num == 0)
        buffer[index--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[index--] = (num % 10) + '0';
        num /= 10;
    }

    index++;

    return (write_unsigned_result(0, index, buffer, flags, width, precision, size));
}

/**
 * print_octal - Print an unsigned number in octal notation
 * @args: List of arguments
 * @buffer: Buffer for printing
 * @flags: Active formatting flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_octal(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    int index = BUFF_SIZE - 2;
    unsigned long int num = va_arg(args, unsigned long int);
    unsigned long int initial_num = num;

    UNUSED(width);

    num = convert_to_unsigned(num, size);

    if (num == 0)
        buffer[index--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';

    while (num > 0)
    {
        buffer[index--] = (num % 8) + '0';
        num /= 8;
    }

    if (flags & F_HASH && initial_num != 0)
        buffer[index--] = '0';

    index++;

    return (write_unsigned_result(0, index, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - Print an unsigned number in hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer for printing
 * @flags: Active formatting flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_hexadecimal(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    return (print_hexadecimal_case(args, "0123456789abcdef", buffer,
        flags, 'x', width, precision, size));
}

/**
 * print_hexadecimal_upper - Print an unsigned number in upper hexadecimal notation
 * @args: List of arguments
 * @buffer: Buffer for printing
 * @flags: Active formatting flags
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_hexadecimal_upper(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    return (print_hexadecimal_case(args, "0123456789ABCDEF", buffer,
        flags, 'X', width, precision, size));
}

/**
 * print_hexadecimal_case - Print a hexadecimal number in lowercase or uppercase
 * @args: List of arguments
 * @hex_map: Mapping array for hexadecimal characters
 * @buffer: Buffer for printing
 * @flags: Active formatting flags
 * @flag_ch: Flag character for hexadecimal notation
 * @width: Width specification
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_hexadecimal_case(va_list
