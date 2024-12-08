#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMBERS 100
struct equation {
    uint64_t result;
    uint64_t numbers[MAX_NUMBERS];
    size_t number_count;
};
typedef struct equation Equation;

uint64_t part_one(const char* filename)
{
    FILE* file = fopen(filename, "r");

    // Vérifier si le fichier s'est bien ouvert
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    uint64_t total = 0;

    int line_number = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        // `read` contient la uint64_tueur de la ligne lue
        // if (line[read - 1] == '\n') {
        //     printf("Ligne : %suint64_tueur (sans \\n) : %zd\n", line, read - 1);
        // } else {
        //     printf("Ligne : %suint64_tueur : %zd\n", line, read);
        // }
        Equation eq;
        uint64_t result = 0;
        uint64_t number = 0;
        size_t number_count = 0;

        bool is_result = true;
        bool is_number = false;
        for (int i = 0; i < read; i++) {
            if (line[i] == ' ' && i == read - 1) {
                perror("espace en fin de ligne");
            }
            if (isdigit(line[i])) {
                if (is_result)
                    result = 10 * result + (line[i] - '0');
                else {
                    number = 10 * number + (line[i] - '0');
                    is_number = true;
                }
            } else if (line[i] == ':') {
                eq.result = result;
                result = -1;
                is_result = false;
            } else if (line[i] == ' ' && is_number || line[i] == '\n') {

                if (number <= 0) {
                    perror("error");
                }
                eq.numbers[number_count] = number;
                number = 0;
                number_count++;
            }
        }

        eq.number_count = number_count;

        if (number_count <= 1) {
            perror("un seul nombre");
            continue;
        }
        // print equation
        // printf("%ld: ", eq.result);
        // for (size_t i = 0; i < eq.number_count; i++) {
        //     printf("%ld ", eq.numbers[i]);
        // }
        // printf("\n");

        int possibilities = 1 << (number_count - 1);

        bool solution_exists = false;

        for (int i = 0; i < possibilities; i++) {
            uint64_t test = eq.numbers[0];
            for (int j = 1; j < number_count; j++) {
                int op = (i >> (j - 1)) & 1;
                if (op == 1) {
                    test *= eq.numbers[j];
                } else {
                    test += eq.numbers[j];
                }
            }

            if (test == eq.result) {
                solution_exists = true;

                break;
            }
        }

        if (solution_exists) {
            total += eq.result;
            // printf("%lu\n", eq.result);
            // printf("total: %lu\n", total);
        }
    }

    free(line); // Libérer la mémoire allouée
    fclose(file);
    return total;
}
uint64_t part_two(const char* filename)
{
    FILE* file = fopen(filename, "r");

    // Vérifier si le fichier s'est bien ouvert
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    uint64_t total = 0;

    int line_number = 0;
    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        // `read` contient la uint64_tueur de la ligne lue
        // if (line[read - 1] == '\n') {
        //     printf("Ligne : %suint64_tueur (sans \\n) : %zd\n", line, read - 1);
        // } else {
        //     printf("Ligne : %suint64_tueur : %zd\n", line, read);
        // }
        Equation eq;
        uint64_t result = 0;
        uint64_t number = 0;
        size_t number_count = 0;

        bool is_result = true;
        bool is_number = false;
        for (int i = 0; i < read; i++) {
            if (line[i] == ' ' && i == read - 1) {
                perror("espace en fin de ligne");
            }
            if (isdigit(line[i])) {
                if (is_result)
                    result = 10 * result + (line[i] - '0');
                else {
                    number = 10 * number + (line[i] - '0');
                    is_number = true;
                }
            } else if (line[i] == ':') {
                eq.result = result;
                result = -1;
                is_result = false;
            } else if (line[i] == ' ' && is_number || line[i] == '\n') {

                if (number <= 0) {
                    perror("error");
                }
                eq.numbers[number_count] = number;
                number = 0;
                number_count++;
            }
        }

        eq.number_count = number_count;

        if (number_count <= 1) {
            perror("un seul nombre");
            continue;
        }
        // print equation
        // printf("%ld: ", eq.result);
        // for (size_t i = 0; i < eq.number_count; i++) {
        //     printf("%ld ", eq.numbers[i]);
        // }
        // printf("\n");

        int possibilities = powl(3, number_count - 1);

        bool solution_exists = false;

        for (int i = 0; i < possibilities; i++) {
            uint64_t test = eq.numbers[0];
            int num = i;
            for (int j = 1; j < number_count; j++) {
                int digit = num % 3;
                if (digit == 0) {
                    test *= eq.numbers[j];
                } else if (digit == 1) {
                    test += eq.numbers[j];
                } else {
                    // concate test with eq.numbers[j] as string, then convert to uint64_t and affect to test
                    int length = snprintf(NULL, 0, "%lu%lu", test, eq.numbers[j]);
                    char* concat = malloc(length + 1);
                    snprintf(concat, length + 1, "%lu%lu", test, eq.numbers[j]);
                    char* end;
                    test = strtol(concat, &end, 10);

                    free(concat);
                }
                num /= 3;
            }

            if (test == eq.result) {
                solution_exists = true;

                // break;
            }
        }

        if (solution_exists) {
            total += eq.result;
            // printf("%lu\n", eq.result);
            // printf("total: %lu\n", total);
        }
    }

    free(line); // Libérer la mémoire allouée
    fclose(file);
    return total;
}
