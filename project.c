#include <stdio.h>

// use putchar()

// format specifier syntax %[parameter][flags][width][.precision][length]type
    // parameter:
        // n$ (specifies index, because given parameters not sequential)
    // flags: (in order of can be overwritten to cant be)
        // # (this one idg at all)
        // 0 (when width specified prepend 0s instead of spaces)
        // - (left align)
        // space (print space for pos nums)
        // + (print plus for pos nums)
        // ' (apply thousands grouping to decimals)
    // width
        // minimum num of chars- never truncated just if val is less, left pad w spaces
        // if * is width, read from parameters
    // precision 
        // rounded to that many decimals following the . (can also be * and taken as parameter)
        // or for strings max # of chars
    // length 
        // 
    // type
        // % - prints %, no other parameters accepted
        // d- print an int
        // x- unsigned int as hex number in lower case letters
        // c- char
        // s- null-terminated string



// should return number of chars printed excluding null "\0" to end output