#include <stdio.h>
#include <stdlib.h>

// will use the following function to print integers for %d as putchar expects char values
void print_int(int num);

// will use the following function to convert integers to hex for %x
void print_hex(int num);

// will use the following function to print strings for %s
void print_str(const char* str);

// use putchar()

// format specifier syntax %[parameter][flags][width][.precision][length]type
    // parameter:
        // n$ (specifies index, because given parameters not sequential)
    // flags: (in order of can be overwritten to cant be)
        // # 0x added for hex
        // 0 (when width specified prepend 0s instead of spaces)
        // - (left align)
        // space (print space for pos nums)
        // + (print plus for pos nums)
        // ' (apply thousands grouping to decimals)
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

void print_str(const char* str) {
    // for each char in the str, output it
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}

// write test functions and put in ada