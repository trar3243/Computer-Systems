/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) 
{
  int res; 
    x = ~(x);
    y = ~(y);
    res = x & y;
    res = ~res;  
    return res;
}
/*
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) 
{
    int x = 85; // last 8 = 0101 0101
    x = (x << 8); 
    x = (x|85); 
    x = (x << 8); 
    x = (x|85);
    x = (x << 8);
    x = (x|85); 
    return x;
}
/*
 * minusOne - return a value of -1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int minusOne(void) 
{
    int x = 0; 
    x = ~(x); // 1111 * 32 
    return x;
}
/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) 
{
    int c = 85; 
    int y = c; // last 8 =   0101 0101
    y = (y << 8); 
    y = (y|c); 
    y = (y << 8); 
    y = (y|c);
    y = (y << 8);
    y = (y|c);



    x = (y & x); 
    y = (~y); 
    y = (y^x);
    y = (~y); 
    y = !y; 

    return y; 
}
/*
 * anyOddBit - return 1 if any odd-numbered bit in word set to 1
 *   Examples anyOddBit(0x5) = 0, anyOddBit(0x7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyOddBit(int x) 
{
    int c = 170; // 1010 1010 
    int y = c; 
    y = (y << 8); 
    y = (y|c); 
    y = (y << 8); 
    y = (y|c);
    y = (y << 8);
    y = (y|c); // y = 1010 * 8 
    y = (y&x);// if any are odd, then y > 0 
    y = !!y; 

    return y;
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) 
{
    int maskn = 0xff; // 1111 1111
    int maskm = 0xff; 
    int mask; 
    int newMaskn; //these are necesarry because later I will be doing arithmetic right shifts... 
    int newMaskm; 
    n = n << 3; //multiply by 8 
    m = m << 3;

    maskn = (maskn << n);
    newMaskn = maskn;

    maskm = (maskm << m); 
    newMaskm = maskm; 

    mask = (maskn | maskm); // mask = ff00ff00 if m = 3 n = 1 
    maskn = maskn & x; 
    maskm = maskm & x; // now each mask has the imprint of x byte indices, holes otherwise 
    x = ((~mask) & x); //~mask = 00 ff 00 ff if m = 3 n = 1, so now x has holes in the specified byte indices  

    maskn = maskn >> n; 
    maskn = maskn << m; 
    maskn = maskn & newMaskm; //in the case of arithmetic right shifts 

    maskm = maskm >> m; 
    maskm = maskm << n; 
    maskm = maskm & newMaskn;//in the case of arithmetic right shifts 

    x = (x|maskn);
    x = (x|maskm);

    return x;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) 
{
    int result = x + y; 
    int finalRes; 
    int A; 
    int B; 
    //compare MSB of x and y and result 
    // if x and y have the same sign but result has different, then bad; right shift by 31 
    x = x >> 31; 
    y = y >> 31; 
    result = result >> 31; 
    result = ~result; 


    A = x & y & result;
    B = ~(x | y | result); 
    finalRes = !(A | B);
    //if you look at a truth table, the only false is when res is + and both the others are negative or res is negative when both x and y are positive; therefore, if we bitwise negate res, 
    //then all of them being the same is the only issue 



    return(finalRes); 
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional1(int x, int y, int z) 
{
  int retVal; 
  int retVal2; 
    //if x then y; else z 
    x = !!x; // if x == 0, then this equals 0; else, 1 
    x = x << 31; 
    x = x >> 31;  //now entirely populated with fs or 0s 

    //if x then y; otherwise, retVal is all 0s 
    retVal = (x&y); 

    //else, z 
    retVal2 = ((~x)&z) ; // retVal2 will = z when x is all zeros because then we are masking with all ones; otherwise, retVal2 = 0 because we are masking with all zeros 

    retVal = retVal + retVal2; //either y + 0 or 0+z

    return retVal; 

}
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) 
{

    //greater than comparison by subtracting or adding negative then checking msb 
    //if x and y are positive and x > y then x + - y is positive and MSB = 0 
    //if x and y are positive and x < y then x - y is negative and MSB = 1 
    //range: 48 - 57 inclusive 

    //is it greater than 57? 
    int upperTest = x; 
    int lowerTest = x; 
    int negfiftyeight = ~58 + 1; 
    int negfortyeight = ~48 + 1; 
    int result; 

    upperTest = upperTest + negfiftyeight;//if it is 57 or less than 57, then this negative (that is good). If it violates the upper range, then newX > 0 
    upperTest = upperTest >> 31; //this should be all ones. If this is all zeroes, then we have a violation 

    lowerTest = lowerTest + negfortyeight; //this should be positive or zero 
    lowerTest = lowerTest >> 31;//this should be all zeroes 
    lowerTest = ~lowerTest;// this should be all ones 

    result = lowerTest & upperTest; 
    result = !!result; 
    


    return result; 
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) 
{
    int mask = 255; //1111 1111 
    // step 1: convert n to number of bits by multiplying by 8 
    n = n << 3; 
    //step 2: create mask with holes at the byte index 
    mask = mask << n; 
    mask = ~mask; 
    //step 3: create holes in x using mask 
    x = x & mask; 
    //step 4: correctly index c 
    c = c << n; 
    //step 5: fill in the holes 
    x = x | c; 

    return x; 

}
/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3
 */
int rotateRight(int x, int n) 
{
    int mask = 1; 
    int maskB = 1; 
    mask = mask << 31; 
    mask = mask >> (31 + (~n + 1)); //1111 1111 1111 1111 1111 1111 1111 0000
    mask = ~mask; //0000 0000 0000 0000 0000 0000 0000 1111
    mask = mask & x; //0000 0000 0000 0000 0000 0000 0000 0001
    mask = mask << (32 + (~n + 1)); // 0001 0000 0000 0000 0000 0000 0000 0000  
    
    x = x >> n;// f8765432 or 08765432(in case MSB is 0)
    

    maskB = maskB << (31 + !n); //!n is for special case when n = 0 
    maskB = maskB >> (n + ~0); //1111 0000 0000... 0000 maskB shifted right by n - 1 since the MSB is already filled 
    

    maskB = ~maskB; // 0000 1111....1111
    
    x = x & maskB; 

    x = x | mask;


    return x;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value (Tmax), and when negative overflow occurs,
 *          it returns minimum negative value (Tmin)
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) 
{
    int result = x + y; 
    int resultB = result; 
    int finalRes; 
    int R1;
    int R2;
    int A; 
    int B; 
    int bothNeg; 

    //compare MSB of x and y and result 
    // if x and y have the same sign but result has different, then bad; right shift by 31 
    x = x >> 31; 
    y = y >> 31; 
    bothNeg = x & y; 

    result = result >> 31; 
    result = ~result; 


    A = x & y & result;
    B = ~(x | y | result); 
    finalRes = !(A | B);
    result = resultB; 




    result = result & ((finalRes << 31) >> 31); 
    R1 = !(finalRes); 
    R2 = R1; 
    R1 = R1 << 31; 
    R1 = R1 + (~(!bothNeg) + 1) ;

    R2 = ((R2 << 31) >> 31); 
    R2 = R2 & R1; 
    R2 = R2 + result; 


    return(R2); 
}
/*
 * Extra credit
 */
/*
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) 
{
    int mask = 1; 
    if ((uf << 1) >> 24 == 0xff && (uf << 9) > 0) // frac = 23 bits 
    {
        return uf;
    }
    mask = mask << 31; 
    mask = ~mask; 
    uf = uf & mask; 
    return uf; 
}

#include <iostream> 
using namespace std;

int main()
{
    cout << bitOr(5,6) <<endl;
    cout << evenBits() <<endl;
    cout << minusOne() <<endl;
    cout << allEvenBits(6) <<endl;
    cout << anyOddBit(5) <<endl;
    cout << byteSwap(5,6, 1) <<endl;
    cout << addOK(5,6) <<endl;
    cout << conditional1(5,6, 1) <<endl;
    cout << isAsciiDigit(5) <<endl;
    cout << replaceByte(5,6, 1) <<endl;
    cout << rotateRight(5,6) <<endl;
    cout << satAdd(5,6) <<endl;
    cout << float_abs(5.8) <<endl;
    return 0; 
}