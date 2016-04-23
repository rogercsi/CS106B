# Simple C++

### Perfect Number

Greek mathematicians took a special interest in numbers that are equal to the sum of their proper divisors (a proper divisor of N is any divisor less than N itself). They called such numbers perfect numbers. For example, 6 is a perfect number because it is the sum of 1, 2, and 3, which are the integers less than 6 that divide evenly into 6. Similarly, 28 is a perfect number because it is the sum of 1, 2, 4, 7, and 14.

Predicate function `isPerfect` takes an integer `n` and returns `true` if `n` is perfect, and `false` otherwise.

### Soundex

The Soundex algorithm produces a code for a surname based on the way it sounds, rather than how it is spelled. The surnames Vaska, Vasque, and Vussky are all assigned the same Soundex code V200 because of their similar pronunciation, despite their differences in spelling.

The program allows the user to enter a name and prints its Soundex code as determined by
the algorithm. 

### Vote

The program prompts the user to enter the voting simulation parameters, then performs 500
simulation trials and reports the ratio - an estimate of the percentage chance of an invalid election result when electronic voting systems with a given error rate are used.