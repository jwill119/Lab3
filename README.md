# COSC 2030 Lab 3
# Jacob Williams

Question 1: Sum of the first n integers (as short)
- For input 20, outputs: 190


Question 2: Where overflow occurs.
- I used a loop to find the overflow; it turns out that n=256 works, but n=257 overflows the signed type short.


Question 3: Trying again with longs
- For input 20000, outputs: 199,990,000 (which is what we expect).
- According to my <climits> header, my machine uses 16-bit shorts and 64(!)-bit longs, which means we will need to go way big to overflow them. A heuristic is sqrt(0.5*2^64), which is approximately 3,037,000,500. That'll take some precise looping...
- I used an increasingly-fine-grained for-loop to find the overflow: it's between n = 3037000499 and 3037000500.
  
  
Questions 4-5: We're going to have to do the factorial recursively. Fortunately factorial grows fast. We'll detect an overflow using the isinf() function in the <cmath> header.
  - For single-precision floating point numbers, we overflow just after n = 34.
  - For double-precision floating poitns, we overflow after n = 170.


Question 6: This function is expected to return zero, but because of limitations in floating-point precision this is not the case!
  - Doubles begin acting strangely at n = 7
  - Floats hold on until n = 10 before they are thrown off.

Question 7: When we run the for loop, we run one more iteration than we would expect to (since we have "i < 4.4" as a condition, we would not expect an iteration to run when i = 4.4). This happens because the floating-point arithmetic detects a subtle difference between 3.4 + 5(0.2) and 4.4.

Question 8: When we set i as a double instead of a float, the problem goes away! This is because double-precision floating-point numbers take more memory and store distinctions more precisely.
