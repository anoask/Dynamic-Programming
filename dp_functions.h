#ifndef DP_FUNCTIONS_H
#define DP_FUNCTIONS_H

typedef struct {
    int score; // min alignment score
    int start_row; // starting row
    int start_col; // starting column
    char *path; // optimal path
} AlignmentResult;

AlignmentResult find_optimal_alignment(const int *sequence, int k, int **matrix, int m, int n);

#endif
