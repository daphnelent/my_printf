#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


// will use the following function to print integers for %d accounting for all the modifiers
void print_formatted_int(int num, int width, int zero_padding, int precision, int left_align, int show_sign, int space_sign, int *chars_printed);
// prints the actual number
void print_int(int num, int *chars_printed);

// get the width of the number so know how much padding needed 
int width_int(int num);

// will use the following function to print hex numbers for %x accounting for all the modifiers
void print_formatted_hex(int num, int width, int zero_padding, int precision, int left_align, int hashtag, int *chars_printed);

// get the width of the hex so know how much padding needed 
int width_hex(unsigned int num);

// print the str with all its formattimg
void print_formatted_str(const char* str, int width, int precision, int left_align, int zero_padding, int *chars_printed);

// will use the following function to print strings for %s
void print_str(const char* str, int precision, int *chars_printed);

// get the width of the str so know how much padding needed 
int width_str(const char* str);

// pad the formatted string to required width
void pad_output(int totalWidth, int width, int zero_padding, int *chars_printed);

// will use the following function to help parse the string
const char* parsed_string(const char* format, va_list args, int *chars_printed);


void my_printf(const char* format, ...) {

    int chars_printed = 0;
    // va_list will have the variable arguments, and copy will as well so we can count and store
    va_list args, args_copy;
    // va_start initializes the va_list of argumets for use, format is last param before the elipses
    va_start(args, format);

    // using a copy to count the number of args so can make a list of args
    va_copy(args_copy, args); 
  


    // loop through the format string
    while (*format != '\0') {

        // if we encounter a % that we need to format properly
        if (*format == '%') {
            format++;

            // check if it is another %, because %% just prints %
            if (*format == '%') {
                putchar('%');
                chars_printed++;
            }

            // if its not, then check what type it is and apply modifiers
            else {
                format = parsed_string(format, args, &chars_printed);
                if (format == -1){
                    return -1;
                }
            }

        }
        else {
            putchar(*format);
            chars_printed++;
        }
        format++;
    }
    // end the variable arguments because done using them
    va_end(args);

    // should return number of chars printed excluding null "\0" to end output

}




// implement 3 new things printf should do (1. switch to lowercase, 2. switch to uppercase, 3. switch to binary)

// gets how many chars the number will take up
int width_int(int num){
    if (num == 0) return 1;
    else {
        // take off lowest digit each recursive call to count digits
        if (num / 10 == 0)  { 
            return 1;
            }
        return 1 + width_int(num / 10);
    }
}

// gets how many chars the number will be in hex
int width_hex(unsigned int num){
    if (num == 0) return 1;
    else {
        // take off lowest digit each recursive call to count digits
        if (num / 16 == 0)  { 
            return 1;
            }
        return 1 + width_hex(num / 16);
    }
}

// returns number of charecters in the given string
int width_str(const char *str) {
    int chars = 0;
    while (*str != '\0'){
        chars++;
        str++;
    }
    return chars;
}

// pad the output to get to the desired width
void pad_output(int totalWidth, int width, int zero_padding, int *chars_printed){
    char pad = ' ';
    // if we need more charecters to meet the minimum width
    if (totalWidth < width){
        // check to see if zero padding flag is set
        if (zero_padding == 1){
            pad = '0';
        }
        // print the padding
        for (int i = width; i > totalWidth; i--) {
            putchar(pad);
            (*chars_printed)++;
        }
    
    }
}

void print_formatted_int(int num, int width, int zero_padding, int precision, int left_align, int show_sign, int space_sign, int *chars_printed){
    // get the number of digit charecters in out number
    int digits = width_int(num);
    int totalWidth;
    // get the total width of the number itself
    if (num < 0 || show_sign == 1 || space_sign == 1){
        totalWidth = 1 + digits;
    }
    else {
        totalWidth = digits;
    }

    // calculate how many extra digits may need to be added because of the precision modifier
    precision -= digits;
    // if extra digits are needed, add them to the total width of charecters 
    if (precision > 0){
        totalWidth += precision;
    }

    // if the left align flag is not set, insert the padding
    if (left_align == 0){
        pad_output(totalWidth, width, zero_padding, &chars_printed);
    }
    
    // for negatives
    if (num < 0) {
        // prepend negative sign
        putchar('-');
        (*chars_printed)++;
        // convert to positive to get numbers
        num = -num;
    }
    // add necessary signs based on flags 
    else {
        if (show_sign == 1){
            putchar('+');
            (*chars_printed)++;
        }
        else if (space_sign == 1) {
            putchar(' ');
            (*chars_printed)++;
        }
    }

    // add necessary digits to get to minimum as dictated by precision flag
    while (precision > 0){
        putchar('0');
        (*chars_printed)++;
        precision--;
    }

    // print the actual number
    print_int(num, &chars_printed);

    // if left align flag is set, insert padding here
    if (left_align == 1){
        pad_output(totalWidth, width, zero_padding, &chars_printed);
    }

}

void print_int(int num, int *chars_printed) {

    // if the number is more than 1 digit, print the largest place digits first
    if (num / 10) {
        print_int(num / 10, &chars_printed);
    }

    // print the last digit (due to recursion this will print each digit)
    putchar((num % 10 + '0'));
    (*chars_printed)++;
}

void print_formatted_hex(int num, int width, int zero_padding, int precision, int left_align, int hashtag, int *chars_printed){
    // these conditions undo zero padding in printf
    if (precision >= 0) zero_padding = 0;
    if (left_align == 1) zero_padding = 0;
    // Treat the number as unsigned for correct hex conversion
    unsigned int unsigned_num = (unsigned int)num;
    // Fixed size for maximum of 8 hex digits (bc an int is 32 bits) + null terminator
    char hexString[9];  
    // create a string/array of all possible hexidecimal digits
    const char hexChars[] = "0123456789abcdef";
    int numDigits = width_hex(unsigned_num);

    // insert null terminator at end of hexidecimal number so we know when found the end
    hexString[numDigits] = '\0';

    // update precision to be the number of zeros we will have to prepend to ensure enough digits
    precision -= numDigits;

    int totalWidth = numDigits;

    // if we will be prepending zero digits, account for them in the width of chars
    if (precision > 0){
        totalWidth += precision;
    }
    
    // if # flag is set, were going to add 0x which contributes to total width
    if (hashtag == 1){
        totalWidth += 2;
    }

    // insert spaces padding in output
    if (left_align == 0 && zero_padding == 0){
        pad_output(totalWidth, width, zero_padding, &chars_printed);
    }

    // account for # flag
    if (hashtag == 1){
        putchar('0');
        putchar('x');
        (*chars_printed) += 2;
    }

    // insert zeros padding in output
    if (left_align == 0 && zero_padding == 1){
        pad_output(totalWidth, width, zero_padding, &chars_printed);
    }

    // account for precision digit requirements
    while (precision > 0){
        putchar('0');
        (*chars_printed)++;
        precision--;
    }
    

    // get the digits from rightmost to leftmost digit
    for (int digit = numDigits - 1; digit >= 0; digit--) {
        hexString[digit] = hexChars[unsigned_num % 16];
        unsigned_num /= 16;
    }

    // print the chars
    for (int hexChar = 0; hexString[hexChar] != '\0'; hexChar++){
        putchar(hexString[hexChar]);
        (*chars_printed)++;

    }

    if (left_align == 1){
        pad_output(totalWidth, width, zero_padding, &chars_printed);
        (*chars_printed)++;
    }
}

void print_formatted_str(const char* str, int width, int precision, int left_align, int zero_padding, int *chars_printed){
    // get the num of chars in the string
        int numChars = width_str(str);

        // reduce the number of chars to be the precision
        if (numChars > precision && precision >= 0){
            numChars = precision;
        }

        if (left_align == 0){
            pad_output(numChars, width, zero_padding, &chars_printed);
        }

        print_str(str, precision, &chars_printed);

        if (left_align == 1){
            pad_output(numChars, width, zero_padding, &chars_printed);
        }
}

void print_str(const char* str, int numChars, int *chars_printed) {
    while (numChars > 0){
        putchar(*str);
        str++;
        numChars--;
        (*chars_printed)++;
    }
}



const char* parsed_string(const char* format, va_list args, int *chars_printed) {
    int width = 0; 
    int zero_padding = 0;
    int left_align = 0;
    int show_sign = 0; 
    int hashtag = 0;
    int space_sign = 0;
    char length = '\0';
    char type = '\0';
    int precision = -1;

    // now we move to parse out the flags
    while (*format == '#' || *format == '0' || *format == '-' || *format == ' ' || *format == '+') {
        if (*format == '#') {
            hashtag = 1;
        }
        else if (*format == '0') {
            zero_padding = 1;
        }
        else if (*format == '-'){
            left_align = 1;
            // left alignment undoes zero padding effects
            zero_padding = 0;
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
        width = va_arg(args, int);
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
        precision = 0;
        while (*format >= '0' && *format <= '9') {
                precision = precision * 10 + (*format - '0');
                format++;
        }
    }

    // now move to handling length (POTENTIALLY ADD LL AND HH LATER)
    if (*format == 'h'){
        length = 'h';
        format++;
    }
    
    else if (*format == 'l'){
        length = 'l';
        format++;
        }

    // now move to handling type
    type = *format;


    if (type == 'd') {
        if (length == 'h') {
            short num = va_arg(args, int);
            print_formatted_int(num, width, zero_padding, precision, left_align, show_sign, space_sign, &chars_printed);
        }
        else if (length == 'l') {
            long num = va_arg(args, long);
            print_formatted_int(num, width, zero_padding, precision, left_align, show_sign, space_sign, &chars_printed);
        }
        else {
            int num = va_arg(args, int);
            print_formatted_int(num, width, zero_padding, precision, left_align, show_sign, space_sign, &chars_printed);
        }
    }
    
    else if (type == 'x'){
        if (length == 'h') {
            short num = va_arg(args, int);
            print_formatted_hex(num, width, zero_padding, precision, left_align, hashtag, &chars_printed);
        }
        else if (length == 'l') {
            long num = va_arg(args, long);
            print_formatted_hex(num, width, zero_padding, precision, left_align, hashtag, &chars_printed);
        }
        else {
            int num = va_arg(args, int);
            print_formatted_hex(num, width, zero_padding, precision, left_align, hashtag, &chars_printed);
        }
    }

    else if (type == 'c'){
        // ensure zero padding flag not set
        zero_padding = 0;
        if (left_align != 1) {
            // width of 1 for 1 char
            pad_output(1, width, zero_padding, &chars_printed);
            putchar(va_arg(args, char));
            (*chars_printed)++;
        }
        else {
            putchar(va_arg(args, char));
            (*chars_printed)++;
            pad_output(1, width, zero_padding, &chars_printed);
        }
    }

    else if (type == 's'){
        // ensure zero padding flag not set
        zero_padding = 0;

        // create a pointer to the string
        const char *str = va_arg(args, char*); 

        print_formatted_str(str, width, precision, left_align, zero_padding, &chars_printed);


    }
    // if not a valid type, throw an error
    else {
        return -1;
    }

    return format;
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





