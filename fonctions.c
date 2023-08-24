#include "main.h"

/* Print Character */
int printCharacter(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    char c = va_arg(args, int);

    return (writeCharacter(c, buffer, flags, width, precision, size));
}

/* Print String */
int printString(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    int length = 0, i;
    char *str = va_arg(args, char *);

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

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

/* Print Percent Sign */
int printPercent(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    UNUSED(args);
    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);
    return (write(1, "%%", 1));
}

/* Print Integer */
int printInteger(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    int i = BUFF_SIZE - 2;
    int isNegative = 0;
    long int n = va_arg(args, long int);
    unsigned long int num;

    n = convertSizeNumber(n, size);

    if (n == 0)
        buffer[i--] = '0';

    buffer[BUFF_SIZE - 1] = '\0';
    num = (unsigned long int)n;

    if (n < 0)
    {
        num = (unsigned long int)((-1) * n);
        isNegative = 1;
    }

    while (num > 0)
    {
        buffer[i--] = (num % 10) + '0';
        num /= 10;
    }

    i++;

    return (writeNumber(isNegative, i, buffer, flags, width, precision, size));
}

/* Print Binary */
int printBinary(va_list args, char buffer[],
    int flags, int width, int precision, int size)
{
    unsigned int n, m, i, sum;
    unsigned int binaryDigits[32];
    int count;

    UNUSED(buffer);
    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    n = va_arg(args, unsigned int);
    m = 2147483648; /* 2^31 */
    binaryDigits[0] = n / m;

    for (i = 1; i < 32; i++)
    {
        m /= 2;
        binaryDigits[i] = (n / m) % 2;
    }

    for (i = 0, sum = 0, count = 0; i < 32; i++)
    {
        sum += binaryDigits[i];
        if (sum || i == 31)
        {
            char digit = '0' + binaryDigits[i];
            write(1, &digit, 1);
            count++;
        }
    }

    return (count);
}
