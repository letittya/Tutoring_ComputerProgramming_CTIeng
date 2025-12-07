/*

Implement a function void packBytes(char t[], unsigned n, unsigned long v[], unsigned cap); 
which takes an array of bytes (t) together with the number of elements (n) and packs groups of four 
consecutive elements from t into elements of v, without exceeding the capacity (cap). Pad elements with 0x0 if needed.

I.e. 0xAB, 0x12, 0xCD, 0xDE, 0x3A -> 0xAB12CDDE, 0x3A000000

*/

