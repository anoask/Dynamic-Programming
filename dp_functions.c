#include <stdlib.h>
#include <limits.h>
#include "dp_functions.h"

#define min(a, b) ((a) < (b) ? (a) : (b))

// Helper function to check if a given position is within bounds of the matrix
int withinBounds(int row, int col, int m, int n) {
    return row >= 0 && row < m && col >= 0 && col < n;
}

// Function to find the optimal alignment and return the result
AlignmentResult find_optimal_alignment(const int *sequence, int k, int **matrix, int m, int n) {
    // Initialize the dynamic programming matrix
    int ***D = (int ***)malloc((k + 1) * sizeof(int **));
    int ***Path = (int ***)malloc((k + 1) * sizeof(int **));
    for (int i = 0; i <= k; i++) {
        D[i] = (int **)malloc(m * sizeof(int *));
        Path[i] = (int **)malloc(m * sizeof(int *));
        for (int j = 0; j < m; j++) {
            D[i][j] = (int *)malloc(n * sizeof(int));
            Path[i][j] = (int *)malloc(n * sizeof(int));
            for (int l = 0; l < n; l++) {
                D[i][j][l] = INT_MAX; // Initialize to maximum possible value
                Path[i][j][l] = -1;
            }
        }
    }

    // Base case initialization
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            D[1][r][c] = abs(sequence[0] - matrix[r][c]);
            if (D[1][r][c] == 0)
                Path[1][r][c] = 0; // Mark as the starting point
        }
    }

    // Dynamic programming to fill D
    for (int i = 2; i <= k; i++) {
        for (int r = 0; r < m; r++) {
            for (int c = 0; c < n; c++) {
                int dr[] = {1, -1, 0, 0}; // Possible row directions
                int dc[] = {0, 0, 1, -1}; // Possible column directions
                for (int dir = 0; dir < 4; dir++) {
                    int new_r = r + dr[dir];
                    int new_c = c + dc[dir];
                    if (withinBounds(new_r, new_c, m, n)) {
                        int score = D[i - 1][new_r][new_c] + abs(sequence[i - 1] - matrix[r][c]);
                        if (score < D[i][r][c]) {
                            D[i][r][c] = score;
                            Path[i][r][c] = new_r * n + new_c; // Store the position in a compact form
                        }
                    }
                }
            }
        }
    }

    // Find the minimum score and its position for the last element
    int min_score = INT_MAX;
    int min_pos = -1;
    int start_pos = -1; // Variable to hold the start position of the path
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (D[k][r][c] < min_score) {
                min_score = D[k][r][c];
                min_pos = r * n + c;
            }
        }
    }

    // Reconstruct the path from the min_pos
    AlignmentResult result;
    result.score = min_score;
    result.path = (char *)malloc((k - 1) * sizeof(char));
    int current_pos = min_pos;
    for (int i = k - 1; i > 0; i--) {
        int row = current_pos / n;
        int col = current_pos % n;
        int prev_pos = Path[i + 1][row][col]; // Get the compacted previous position
        int prev_row = prev_pos / n;
        int prev_col = prev_pos % n;
        
        // Record the start position when we are at the first step of the path reconstruction
        if (i == 1) {
            result.start_row = prev_row;
            result.start_col = prev_col;
        }

        if (prev_row == row) {
            if (prev_col == col + 1)
                result.path[i - 1] = 'L';
            else
                result.path[i - 1] = 'R';
        } else {
            if (prev_row == row + 1)
                result.path[i - 1] = 'U';
            else
                result.path[i - 1] = 'D';
        }
        current_pos = prev_pos;
    }

    // Free allocated memory
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < m; j++) {
            free(D[i][j]);
            free(Path[i][j]);
        }
        free(D[i]);
        free(Path[i]);
    }
    free(D);
    free(Path);

    return result;
}
