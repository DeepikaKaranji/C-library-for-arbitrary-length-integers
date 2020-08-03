# C-library-for-arbitrary-length-integers
This project is a C library called "intal.h" which supports operations on integers stored as NULL terminated strings.

## Introduction:

An integer is a variable that specifically holds a numerical value. 
The integer datatypes supported by C are:
Read as (Type, storage size, value range)
- int ,	2 or 4 bytes ,-32,768 to 32,767 or -2,147,483,648 to 2,147,483,647
- unsigned int , 2 or 4 bytes , 0 to 65,535 or 0 to 4,294,967,295
- short , 2 bytes , -32,768 to 32,767
- unsigned short , 2 bytes , 0 to 65,535
- long , 8 bytes , -9223372036854775808 to 9223372036854775807
- unsigned long , 8 bytes , 0 to 18446744073709551615

Numbers which with 1000 digits cannot be stored as any of the integer datatypes mentioned above.

With this in mind, I have created a C library that will allow various operations on integers of arbitrary length.

### **INTAL Definition:**
An intal is a nonnegative integer of arbitrary length. 
The integer is stored as a null-terminated string of ASCII characters. 
An intal is represented as a string of decimal digits ('0' thru '9') that are stored in the big-endian style. 
That is, the most significant digit is at the head of the string. 
An integer 25, for example, is stored in a string s as '2' at s[0], '5' at s[1], and null char at s[2].

## Functions Implemented

1. Add
2. Difference
3. Compare
4. Multiply
5. Modulus
6. Exponent
7. Greatest Commn Divisor
8. Nth Fibonacci number
9. Factorial
10. Binomial Coefficient C(n,k)
11. Offset of largest intal in array
12. Offset of smallest intal in array
13. Search Intal in array
14. Binary Search
15. Sort an array of N intals


## Approach and Implementation:

- For any intal function, I first copy the intals into character pointers and strip the intals of any leading zeros.
The same action is performed while returning the result of any function. 
- For basic operations of addition, multiplication, subtraction and division(high school method),
I iterate through each element of the operand intals in a specific way and perform digit wise operation on it, convert back
to char * datatype and later concatenate and return. 
- For the modulus function, I utilize the equation Dividend = Quotient * Divisor + Remainder.
- For the more complex operations like power, factorial, etc, I utilise the basic functions along with some helpers like collect function, 
swap function (to swap pointers to the intals) along the way. 
Wherever '0' needs to be returned, another helper make_zero() is used to create the zero intal.
- Before returning, all character pointers which were defined are freed. 
- To implement an nlogn sort, I have used merge sort technique. 
- To convert an integer into the intal return type, I define a helper function called itostr.

One issue I faced was that calloc() was not initialising the dynamically allocated
character pointers with '0', which is why I had to loop through the array and initialise with '0'.
Additonally, I witnessed some strange behaviour where x-y would result in a segfault but x-y/2-1 worked perfectly. 

## Use Cases

Storing large numbers as intals (strings) to perform various operations on them is very practical and useful.
Use cases of intals could be in scientific computation which require high integer precision.
Additonally, string manipulation is easier to perform, which will give us more flexibilty to play with the numbers and potentially speedup the computation.


## Future Work

I'd first like to fix the unpredictable behaviour mentioned above.
A few other functionalities that could improve this library are 
- Matrix operations on intals
[Basic operations, Transpose, adjecent matrix, coefficient matrix, Gauss-Jordan, etc.]
- Quick sort
- Karatsuba multiplication

I believe that my implementation currently can handle integers of arbitary length, 
because I dont assume 1000 as MAX length anywhere with '\0' in the 1001th position.
But multiplication of 2 1000 digit numbers may result in overflow. 
To handle this, When the datatype grows, we could create a new memory location with the resized value and copy the elements to it, delete the old one.




