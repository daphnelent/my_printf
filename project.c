#include <stdio.h>

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




// write test functions