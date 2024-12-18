#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// will use the following function to print integers for %d as putchar expects char values
void print_int(int num);

// will use the following function to convert integers to hex for %x
void print_hex(int num);

// will use the following function to print strings for %s
void print_str(const char* str);

// will use the following function to help parse the string
const char* parsed_string(const char* format, va_list args);


void my_printf(const char* format, ...) {
    // va_list will have the variable arguments
    va_list args;
    // va_start initializes the va_list of argumets for use, format is last param before the elipses
    va_start(args, format);

    // loop through the format string
    while (*format != '\0') {

        // if we encounter a % that we need to format properly
        if (*format == '%') {
            format++;

            // check if it is another %, because %% just prints %
            if (*format == '%') {
                putchar('%');
            }

            // if its not, then check what type it is and apply modifiers
            else {
                format = parsed_string(format, args);
            }

        }
        else {
            putchar(*format);
        }
    }
    // end the variable arguments because done using them
    va_end(args);
}




// implement 3 new things printf should do (1. switch to lowercase, 2. switch to uppercase, 3. switch to binary)



// should return number of chars printed excluding null "\0" to end output


void print_int(int num){
    // for negatives
    if (num < 0) {
        // prepend negative sign
        putchar('-');
        // convert to positive to get numbers
        num = -num;
    }

    // if the number is more than 1 digit, print the largest place digits first
    if (num / 10) {
        print_int(num / 10);
    }

    // print the last digit (due to recursion this will print each digit)
    putchar((num % 10 + '0'));
}

void print_hex(int num) {
    // Fixed size for maximum of 8 hex digits (bc an int is 32 bits) + null terminator
    char hexString[9];  
    // create a string/array of all possible hexidecimal digits
    const char hexChars[] = "0123456789abcdef";
    int tempCounter = num;
    int numDigits = 0;

    // count number of digits
    do {
        numDigits++;
        tempCounter /= 16;
    } while (tempCounter > 0);

    // insert null terminator at end of hexidecimal number
    hexString[numDigits] = '\0';

    // get the digits from rightmost to leftmost digit
    for (int digit = numDigits - 1; digit >= 0; digit--) {
        hexString[digit] = hexChars[num % 16];
        num /= 16;
    }

    // print the chars
    for (int hexChar = 0; hexString[hexChar] != '\0'; hexChar++){
        putchar(hexString[hexChar]);

    }
    
}

const char* parsed_string(const char* format, va_list args) {
    int parameter = 0;
    int width = 0; 
    int width_param = 0;
    int zero_padding = 0;
    int left_align = 0;
    int show_sign = 0; 
    int hashtag = 0;
    int space_sign = 0;
    char length = '\0';
    char type = '\0';
    int precision = 0;

    // first check for parameter index
    // if we have a digit (might be parameter if followed by $)
    while (*format >= '0' && *format <= '9'){
        parameter *= 10;
        parameter += (*format - '0');
        format++;
    }
    if (*format == "$") {
        format ++;
        }
    // if there is no $ following the number, then it must've been the width or zero flag, there is no parameter
    else {
        if (parameter == 0) {
            zero_padding = '0';
        }
        else {
            width = parameter;
            parameter = 0;
        }
    }

    // now we move to parse out the flags
    while (*format == '#' || *format == 0 || *format == '-' || *format == ' ' || *format == '+') {
        if (*format == '#') {
            hashtag = 1;
        }
        else if (*format == 0) {
            zero_padding = 1;
        }
        else if (*format == '-'){
            left_align = 1;
        }
        else if (*format == ' '){
            if (!show_sign) {
                space_sign = 1;
            }
        }
        else if (*format == '+') {
            show_sign = 1;
            space_sign = 0;
        }
        format++;
    }

    // now move to handling width
    if (*format == '*') {
        // check for index parameter for non sequential arguments
        while (*format >= '0' && *format <= '9'){
            width_param *= 10;
            width_param += (*format - '0');
            format++;
        }
        // if no parameter number given for width, means just sequential from argumets. mark width as -1 to show must get from parameter
        width = -1;
    }
    else {
        while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0');
                format++;
            }
    }
    // now handle precision
    if (*format == '.') {
        format++;
        while (*format >= '0' && *format <= '9') {
                precision = precision * 10 + (*format - '0');
                format++;
        }

    // now move to handling length
    if (*format == 'h' || *format == 'l') {
            length = *format;  
            format++; 
        }

    // now move to handling type
    type = *format;
    if (type == '\0') return format;  // Incomplete

    format++;

}
    // flags: (in order of can be overwritten to cant be)
        // # 0x added for hex
        // 0 (when width specified prepend 0s instead of spaces)
        // - (left align)
        // space (print space for pos nums)
        // + (print plus for pos nums)
    // width
        // minimum num of chars- never truncated just if val is less, left pad w spaces
        // if * is width, read from parameters
    // length 
        // interpret the var thats on the stack as this type
    // type
        // % - prints %, no other parameters accepted
        // d- print an int
        // x- unsigned int as hex number in lower case letters
        // c- char
        // s- null-terminated string


// write test functions and put in ada