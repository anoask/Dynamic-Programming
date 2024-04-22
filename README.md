# Dynamic-Programming
Implementation of an algorithm designed to find the optimal alignment between a given sequence and a matrix of values

Dynamic Programming Algorithm:
find_optimal_alignment: This function takes the sequence and the matrix to compute an "optimal alignment". 
It initializes a 3D dynamic programming table D to store intermediate scores and a corresponding Path table for backtracking.
The algorithm iteratively updates the D table based on the absolute difference between sequence elements and matrix values, adjusting scores according to predefined movement directions (left, right, up, down).
The final part of the function reconstructs the alignment path from the DP table, starting from the position with the minimum score at the last sequence element.

