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
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
    // x&y=~~(x&y)=~(~x|~y)
    return ~(~x | ~y);
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    // 1 byte = 8 bits, shift x to the right by 8 * n
    return x >> (n << 3) & 0xff;
}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
    // if x is negative, arithmetic right shift will fill n 1s to the left
    // so we need to get digit like 000..111..
    return x >> n & ~(1 << 31 >> n << 1);
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    // count 1s in adjacent bits by 1, 2, 4, 8, 16 
    int result, mask1, mask2, mask3, mask4, mask5;
    
    mask1 = (0x55) | (0x55 << 8) | (0x55 << 16) | (0x55 << 24);
    mask2 = (0x33) | (0x33 << 8) | (0x33 << 16) | (0x33 << 24);
    mask3 = (0x0f) | (0x0f << 8) | (0x0f << 16) | (0x0f << 24);
    mask4 = (0xff) | (0xff << 16);
    mask5 = (0xff) | (0xff << 8);
    result = (x & mask1) + ((x >> 1) & mask1);
    result = (result & mask2) + ((result >> 2) & mask2);
    result = (result + (result >> 4)) & mask3;
    result = (result + (result >> 8)) & mask4;
    result = (result + (result >> 16)) & mask5;

    return result;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
    // we need to judge the symbol bit in x,
    // x+(~x+1)=0, so the symbol bit in the result of x|(`x+1)
    // can't be 0 when x!=0
    return ~((x | (~x + 1)) >> 31) & 1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    // if negative number is changed into ~x and can be represented
    // as an n-bit, it will in in range of 0~2^(n-1)
    int isNeg, shift;

    isNeg = x >> 31;
    shift = n + ~0;

    return (isNeg & !((~x) >> shift)) | (!isNeg & !(x >> shift));
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    // if x is positive, x/(2^n)=x>>n
    // if x is negative, x/(2^n)=~((~x+1)>>n)+1.
    // And if the n bits on the right are not all 0s,
    // the result is (x>>n)+1
    int result, isNeg, bias;

    isNeg = x >> 31;
    bias = isNeg & ((1 << n) + ~0);
    result = (x + bias) >> n;

    return result;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
    return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    // if x>0, then the sign bit is 0.
    // But if x=0, we need to judge.
    return !((x >> 31) | !x);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    // x<=y -> y-x>=0
    // if x and y has the same symbol, y-x can't overflow and we just need to
    // judge y-x>=0.
    // if x nad y has the different symbol, y-x will overflow but the symbol of
    // y-x must be the same as x.
    int sub, symx, symxy, sym;

    sub = y + (~x + 1);
    symx = (x >> 31) & 1;
    symxy = symx ^ ((y >> 31) & 1);
    sym = !(sub >> 31);
    
    return ((!symxy) & sym) | (symxy & symx);

}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
    // because int is 32-bit, so the result <= 31
    // we can first judge high 16 bits, if they are all 0s,
    // then we shift right 16 bits and judge high 8 bits.
    int s, b1, b2, b3, b4, b5;
    
    s = !!(x >> 16);
    b1 = s << 4;
    x = x >> b1;
    s = !!(x >> 8);
    b2 = s << 3;
    x = x >> b2;
    s = !!(x >> 4);
    b3 = s << 2;
    x = x >> b3;
    s = !!(x >> 2);
    b4 = s << 1;
    x = x >> b4;
    s = !!(x >> 1);
    b5 = s;
    
    return b1 + b2 + b3 + b4 + b5;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
    // the 32 bit floating-point decimal includes
    // 1 bit symbol bits, 8 bit order codes, and 23 bit mantissa.
    // if x=NaN, order codes are all 1s and mantissa are not
    // all 0s.
    if((((uf >> 23) & 0xff) ^ 0xff) || !(uf & ((1 << 23) - 1)))
        uf = uf ^ (1 << 31);

    return uf;
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
    // 1. get sign bit by x&(1<<31)
    // 2. init order codes:
    // if x=0, then exp=0;
    // if x=-2^31 then exp=127+31=158
    // 3. get mantissa by get the highest bit of 1
    unsigned sign;
    int index, exp, frac, mask, delta;
    
    sign = x & (1 << 31);
    exp = (x >> 31) ? 158 : 0;
    frac = 0;
    mask = (1 << 23) - 1;
    index = 30;
    
    if(x << 1) {
        if(x < 0)
            x = -x;
        while(!((x >> index) & 1))
            --index;
        exp = index + 127;
        x = x << (31 - index);
        frac = mask & (x >> 8);
        x = x & 0xff;
        delta = x > 128 || ((x == 128) && (frac & 1));
        frac += delta;
        if(frac >> 23) {
            frac = frac & mask;
            exp += 1;
        }
    }
    
    return sign | (exp << 23) | frac;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    // 1. get sign bit by uf&(1<<31)
    // 2. get order codes by (uf>>23)&0xff
    // if exp=0, then frac left shift 1 bit;
    // if exp=0xff, then uf is special value(-¡Þ,+¡Þ,NaN);
    // else frac add 1.(note: frac overflow)
    // 3. get mantissa.
    
    unsigned sign;
    int exp, frac;
    
    sign = uf & (1 << 31);
    exp = (uf >> 23) & 0xff;
    frac = uf & ((1 << 23) - 1);
    
    if(exp ^ 0xff) {
        if(!exp)
            frac = frac << 1;
        else {
            ++exp;
            if(exp == 255)
                frac = 0;
        }
    }
    
    return sign | (exp << 23) | frac;
}
