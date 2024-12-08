#include <assert.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1000000

char* read_file(const char* filename);

long part1(char* payload)
{
    const char* pattern = "(mul\\()([0-9]{1,3}),([0-9]{1,3})\\)";
    regex_t regex;
    regmatch_t matches[4];

    // Compiler la regex
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Erreur lors de la compilation de la regex\n");
        return -1;
    }
    long total = 0;

    char* current_pos = payload;
    while (regexec(&regex, current_pos, 4, matches, 0) == 0) {
        printf("%.*s\n", matches[0].rm_eo - matches[0].rm_so, payload + matches[0].rm_so);
        // Extraire le premier argument en tant qu'entier
        int start = matches[2].rm_so + (current_pos - payload);
        int end = matches[2].rm_eo + (current_pos - payload);
        char arg1_str[end - start + 1];
        snprintf(arg1_str, sizeof(arg1_str), "%.*s", end - start, payload + start);
        long arg1 = strtol(arg1_str, NULL, 10);

        // Extraire le deuxième argument en tant qu'entier
        start = matches[3].rm_so + (current_pos - payload);
        end = matches[3].rm_eo + (current_pos - payload);
        char arg2_str[end - start + 1];
        snprintf(arg2_str, sizeof(arg2_str), "%.*s", end - start, payload + start);
        long arg2 = strtol(arg2_str, NULL, 10);
        total += arg1 * arg2;
        // Avancer la position après la correspondance actuelle
        current_pos += matches[0].rm_eo;
    }

    return total;
}

void test_port1_1()
{
    char* payload = "mul(123,4)";

    assert(part1(payload) == 123 * 4);
}
void test_port1_2()
{
    char* payload = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

    assert(part1(payload) == 161);
}

int main()
{
    // test_port1_1();
    // test_port1_2();
    const char* filename = "input.txt";
    char* payload = read_file(filename);
    if (!payload) {
        printf("Erreur lors de la lecture du fichier.\n");
    }
    assert(part1(payload) == 187825547);

    printf("Result: %ld\n", part1(payload));

    return 0;
}

// Fonction pour lire le contenu d'un fichier
char* read_file(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    char* content = malloc(MAX_FILE_SIZE);
    if (!content) {
        perror("Erreur d'allocation mémoire");
        fclose(file);
        return NULL;
    }

    size_t bytesRead = fread(content, 1, MAX_FILE_SIZE - 1, file);
    content[bytesRead] = '\0'; // Assurez-vous que la chaîne est terminée

    fclose(file);
    return content;
}
