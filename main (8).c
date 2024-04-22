#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "dp_functions.h"

// Function to skip whitespace and empty lines
void skip_whitespace_and_empty_lines(FILE *file) {
    int ch;
    while ((ch = fgetc(file)) != EOF && isspace(ch)) {
        ;
    }
    if (ch != EOF) {
        ungetc(ch, file);
    }
}

int main() {

    int k, m, n;

    // Opening file
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Assign k, m, and n from the first line of the file
    fscanf(file, "%d %d %d", &k, &m, &n);
    skip_whitespace_and_empty_lines(file);

    // Allocate memory for sequence and matrix
    int *sequence = (int *)malloc(k * sizeof(int));
    int **matrix = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        matrix[i] = (int *)malloc(n * sizeof(int));
    }

    // Read sequence from the second line
    for (int i = 0; i < k; i++) {
        fscanf(file, "%d", &sequence[i]);
    }
    skip_whitespace_and_empty_lines(file);

    // Read matrix from subsequent lines
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%d", &matrix[i][j]);
        }
    }

    // Close the file
    fclose(file);

    // Call the function that computes the optimal alignment and returns the result
    AlignmentResult result = find_optimal_alignment(sequence, k, matrix, m, n);

    // Open the output file to write the result
    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        // Free allocated memory before returning
        free(sequence);
        for (int i = 0; i < m; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return 1;
    }

    // Write the results to the output file
    fprintf(output_file, "%d\n", result.score);
    fprintf(output_file, "%d %d\n", result.start_row + 1, result.start_col + 1);
    for (int i = 0; i < k - 1; i++) {
        fprintf(output_file, "%c ", result.path[i]);
    }
    fprintf(output_file, "\n");

    // Close the output file
    fclose(output_file);

    // Free allocated memory
    free(sequence);
    free(result.path);
    for (int i = 0; i < m; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}