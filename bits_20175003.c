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
	
	int a;
	a = ~(~x|~y);
  
  return a;

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

	int nbit, sol;
	nbit = n << 3;		// makes nbyte to nbit
	x = x >> nbit;		// shift x as nbit to the right
	sol = x & 0x000000FF;	// sol = x's least significant bit

  return sol;

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
	
	int all, sol, sign, trim;
	all = 0x01 << (31);
	trim = (all >> n) << 1;		//trim = 0xFF...0000
		
	sol = x >> n;			//shift x n-times
	sign = (x >> 31) & 0x1;		//if x is negetive, x = 0x01	
	//When x is positive: returns x>>n, x is negative: trims most sig bits to zero
	trim = trim & ((sign << 31) >> 31); 
	//if sign is 0x01, (sign >> 31) >> 31 => 0xFFFFFFFF, else(positive), 0
	sol = trim ^ sol;
  return sol;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {

	int acc, bitcount, sx;
	
	acc = 0;			// accumulator
	bitcount = 0x01 + (0x01 << 8) + (0x01 << 16) + (0x01 << 24);		
	// bitcount = 0000 0001 0000 0001 0000 0001 0000 0001
	sx = x;				// to set shifted x

	acc = sx & bitcount;		// check 0000 000x
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check 0000 00x0
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check 0000 0x00
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check 0000 x000
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check 000x 0000
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check 00x0 0000
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check 0x00 0000
	sx = sx >> 1;
	acc = acc + (sx & bitcount);	// check x000 0000

	// in here, acc = 0x(0a0b0c0d), and we want a+b+c+d
	// to do this, we have to shift acc and get final result
	
	acc = acc + (acc >> 16);	//shift to get d+b in least significant 0000 0000, and get c+a in most significant bit 0000 0000
	acc = acc + (acc >> 8);		//shift to get (c+a)+(d+b) in least significant 0000 0000

	acc = (acc & 0xFF);		//masking 1111 1111 to get the answer (since maximum answer is 32)

  	return acc;
}
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {

	int checker;
	
	x = x | (x >> 16);
	x = x | (x >> 8);
	x = x | (x >> 4);
	x = x | (x >> 2);
	x = x | (x >> 1);		// Making MSB to LSB all 1	

	checker = (~x & 0x01);		// check

	return checker;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {

	int x = 0x01 << 31;
	
  	return x;
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

	int signbits, ifzero, sol;

	signbits = (x >> 31); 		// sign = 0xFFFFFFFF if x is negetive
	ifzero = !(!(x ^ 0x00)); 	// if x is zero, ifzero = 0, else, ifzero = -2
	x = x >> (n + ~ifzero + 1);	// shifts x as x >> n - 1 only when n is not zero. If n is zero, do nothing!
	sol = signbits ^ x;
	// if x is positive, sol = x >> n-1
	// else, (x >> n-1)'s 1's complement, i.e. x >> n's 2's complement
	
	return !sol;	// if sol still has the value, then bitshifting n was not enough to remove all 1's in x

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

	int trim, sol;
	
	trim = 0x01 << 31;
	trim = trim >> 31;			// trim = 0xFFFFFFFF

	trim = trim + (0x01 << n);		// get trimmer to make 0x000...0FFFF(make F's count as n)
	sol = (x >> 31) & trim; 		// if x is negative, sol >> n will be followed
	sol = (sol+x) >> n;			// for the case when x is positive, x >> n should be followed
						// trivial, dividing 2^n will be shifting n times in binary
   	return sol;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {	

	return (~x) + 0x01;	// 2's complement of x = -x
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {

	int sign, ifzero;

	sign = (x >> 31) & 0x01; 	// get the sign of the x, if x is negetive, sign = 0x01
	ifzero = !(0x0 ^ x);   		// get whether x is zero or not, if x is zero, ifzero = 0x01

  	return !(sign + ifzero);
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	
	int xsign, ysign, minusx, minus, signD, sol1, sol2;
  	
	xsign = (x >> 31) & 0x01;
	ysign = (y >> 31) & 0x01;	// get x's sign, y's sign (positive: 0x00)

	minusx = (~x) + 0x01;		// 2's complement of x, i.e, -x
	minus = (y + minusx) >> 31;	// minus = (y - x)'s sign. if minus is negetive, then minus = 0xFFFFFFFF
	
	signD = xsign^ysign; 		// if sign is same, signD = 0x00
	
	sol1 = signD & xsign;		// if sign is different, and x is negetive, sol1 = 0x01
	sol2 = (!signD) & (!minus);	// if sign is same, !minus is the answer

	return sol1 + sol2;
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {

	int MSB, bitcount, sx;
	
	MSB = 0;	// to get MSB of x
		
	// I will use the code from Bang(int x)
	x = x | (x >> 16);
	x = x | (x >> 8);
	x = x | (x >> 4);
	x = x | (x >> 2);
	x = x | (x >> 1);	// make MSB to LSB all 1

	// Now using the code from bitcount
	
	bitcount = 0x01 + (0x01 << 8) + (0x01 << 16) + (0x01 << 24);
	sx = x;

	MSB = sx & bitcount;
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);
	sx = sx >> 1;
	MSB = MSB + (sx & bitcount);

	MSB = MSB + (MSB >> 16);
	MSB = MSB + (MSB >> 8);
	MSB = MSB & 0xFF;

	MSB = ~(((~MSB)+1)+1)+1;	// Making MSB - 1

	         
	return MSB;	//return MSB - 1
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
						// Based on IEEE 754 Standard
	if((uf & 0x7F800000) == 0x7F800000)	// condition when uf is NaN
		if((uf & 0x007FFFFF) != 0)	// We should find Quiet|Signaling NaN
			return uf;		// when uf is Quiet|Signaling NaN, returns uf
	// I really don't know the reason why I should only get Quiet|Signaling NaN
	
	uf = uf ^ 0x80000000;			// masking sign as to make -uf
						// not using 2's complement because this is bit-level representation
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

	int exp, frac, sign, absx, MSB, check, bound;
				//making x to float value x
	if(x==0)
		return 0;

	if(x==0x80000000)
		return 0xCF000000;

	// made all exceptions
	// we should always remember
	// IEEE 754: signbit | exponent(8btis) | fraction(23bits)
	
	exp = 0; 
	frac = 0;				//define exponent, fraction
	sign = 0x80000000 & x;
	absx = x;				//define sign, abs(x)

	if (sign)
		absx = -x;			//get the absolute value of x

	
	MSB = 1;				//To get MSB
	check = absx >> MSB;
	
	while(check){
		MSB = MSB + 1;
		check = absx >> MSB;
	}

	MSB = MSB - 1;				//Now we have MSB
			
	// to get fraction
	

	absx = absx << (31-MSB);		// absx => push to get fraction
	frac = 0x7FFFFF & (absx >> 8);		// From fraction definition
	
	bound = 0;				// Fraction is in 1~2 boundary

	if(MSB > 23) {				// When MSB is larger than fraction boundary
		bound = absx & 0xFF;
		if(bound > 128)			// when bound > 0x80, it is over 1 boundary, add 1
			frac++;

		if(bound == 128)		// when bound == 0x80, frac has value, it is also the condition to add 1
			if(frac & 0x01)
				frac++;

		if(frac >> 23){
			exp = exp + 1;		// frac overflow, exp will take that
			frac = 0;
		}
	}	

	exp = exp + MSB + 127;			// because of exp-127
	exp = exp << 23;			// exp : 2^(exp - 127) is real value

 	return sign | exp | frac;		// Remember IEEE 754 standard
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
  	
	int sign;

	if((uf & 0x7F800000) == 0x7F800000)     // condition when uf is not a number
		return uf;			// when uf is NaN, returns uf

	sign = 0x80000000 & uf;			// get the sign of uf(since it is unsigned)

	
	if((uf & 0x7F800000) == 0){		// i.e. when there are no exponents
		uf = uf << 1;			// shifting all << 1
		
		if(uf ^ sign)			// if sign is shifted, we should rearrange it
			uf = uf + sign;		

		return uf;		
	} else
		return uf + (0x01 << 23);	// adding exponents + 1
		
	
}
