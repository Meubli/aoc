#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 10000

bool check_update(int* update, int update_size, int* incorrect_indexes, int peers[MAX_LINE_LENGTH][2], int peers_count)
{

    bool incorrect = false;
    for (int i = 0; i < update_size && !incorrect; i++) {
        for (int peer_index = 0; peer_index < peers_count && !incorrect; peer_index++) {
            if (peers[peer_index][0] == update[i]) {
                for (int j = 0; j < update_size && !incorrect; j++) {
                    if (peers[peer_index][1] == update[j]) {
                        if (i > j) {
                            incorrect_indexes[0] = i;
                            incorrect_indexes[1] = j;
                            incorrect = true;
                        }
                    }
                }
            }
        }
    }
    return !incorrect;
}

int process(const char* filename, bool switch_incorrect_indexes)
{
    FILE* file = fopen(filename, "r");

    // Vérifier si le fichier s'est bien ouvert
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    int peers[MAX_LINE_LENGTH][2] = { [0 ... MAX_LINE_LENGTH - 1] = { 0, 0 } };

    int update[MAX_LINE_LENGTH] = { [0 ... MAX_LINE_LENGTH - 1] = 0 };

    size_t peers_count = 0;
    size_t update_size = 0;

    int total = 0;
    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // `fgets` lit une ligne entière ou jusqu'à la taille de `line`
        size_t len = strlen(line);
        int x = 0;

        bool is_list_line = false;

        for (int i = 0; i < len; i++) {
            if (isdigit(line[i])) {
                x = x * 10 + (line[i] - '0');
            } else if (x != 0) {
                if (line[i] == '|') {
                    peers[peers_count][0] = x;
                    x = 0;
                }
                if (line[i] == ',') {
                    is_list_line = true;
                    update[update_size] = x;
                    update_size++;
                    x = 0;
                }
            }

            if (i == len - 1 && x != 0) {
                if (!is_list_line) {
                    peers[peers_count][1] = x;
                    peers_count++;
                } else {
                    update[update_size] = x;
                    update_size++;
                }
                x = 0;
            }
        }
        if (is_list_line) {
            int incorrect_indexes[2] = { 0, 0 };
            if (check_update(update, update_size, incorrect_indexes, peers, peers_count)) {
                if (!switch_incorrect_indexes)
                    total += update[update_size / 2];
            } else {
                if (switch_incorrect_indexes) {
                    do {
                        int tmp = update[incorrect_indexes[0]];
                        update[incorrect_indexes[0]] = update[incorrect_indexes[1]];
                        update[incorrect_indexes[1]] = tmp;
                    } while (!check_update(update, update_size, incorrect_indexes, peers, peers_count));
                    total += update[update_size / 2];
                }
            }
            update_size = 0;
        }
    }

    // Vérifier si la lecture s'est arrêtée à cause d'une erreur
    if (ferror(file)) {
        perror("Erreur de lecture du fichier");
    }

    fclose(file);

    return total;
}

int part_one(const char* filename)
{
    return process(filename, false);
}

int part_two(const char* filename)
{
    return process(filename, true);
}
