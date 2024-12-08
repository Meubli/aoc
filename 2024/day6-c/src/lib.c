#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LENGTH 300
#define MAX_HISTORY 1000000

struct position {
    size_t x;
    size_t y;
};
typedef struct position Position;

int part_one(const char* filename)
{
    FILE* file = fopen(filename, "r");

    // Vérifier si le fichier s'est bien ouvert
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char line[MAX_LENGTH];
    char map[MAX_LENGTH][MAX_LENGTH] = { [0 ... MAX_LENGTH - 1] = { 0 } };

    Position guard_position = { 0, 0 };
    int map_height = 0;
    int map_width = 0;
    int total = 0;
    char directions[4][2] = {
        { 0, -1 }, // ^
        { 1, 0 }, // >
        { 0, 1 }, // v
        { -1, 0 } // <
    };
    size_t guard_direction_index = 0;
    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // `fgets` lit une ligne entière ou jusqu'à la taille de `line`
        size_t len = strlen(line);

        if (map_width == 0) {
            map_width = len;
        } else if (map_width != len) {
            perror("Le fichier contient des lignes de tailles différentes");
            continue;
        }

        for (int i = 0; i < len; i++) {
            map[map_height][i] = line[i];
            if (line[i] == '^') {
                guard_position.x = i;
                guard_position.y = map_height;
            }
        }

        map_height++;
    }

    bool is_guard_present = true;
    while (is_guard_present) {
        // printf("position: %d %d\n", guard_position.x, guard_position.y);
        Position next_position = { guard_position.x + directions[guard_direction_index][0], guard_position.y + directions[guard_direction_index][1] };

        // printf("next position: %d %d\n", next_position.x, next_position.y);
        if (next_position.x < 0 || next_position.x >= map_width || next_position.y < 0 || next_position.y >= map_height) {
            is_guard_present = false;
            map[guard_position.y][guard_position.x] = 'X';
            break;
        }

        while (map[next_position.y][next_position.x] == '#') {
            guard_direction_index = (guard_direction_index + 1) % 4;
            next_position.x = guard_position.x + directions[guard_direction_index][0];
            next_position.y = guard_position.y + directions[guard_direction_index][1];
        }
        map[guard_position.y][guard_position.x] = 'X';
        guard_position.x = next_position.x;
        guard_position.y = next_position.y;
    }

    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (map[i][j] == 'X') {
                total++;
            }
            // printf("%c", map[i][j]);
        }
        // printf("\n");
    }

    // Vérifier si la lecture s'est arrêtée à cause d'une erreur
    if (ferror(file)) {
        perror("Erreur de lecture du fichier");
    }

    fclose(file);
    return total;
}
bool is_loop(char map[MAX_LENGTH][MAX_LENGTH], size_t map_width, size_t map_height, Position guard_position, size_t guard_direction_index, char directions[4][2], Position _history_positions[], size_t _history_directions_indexes[], size_t history_length)
{
    Position* history_positions = malloc(sizeof(Position) * MAX_HISTORY);
    for (int i = 0; i < history_length; i++) {
        history_positions[i] = _history_positions[i];
    }
    size_t* history_directions = malloc(sizeof(size_t) * MAX_HISTORY);
    for (int i = 0; i < history_length; i++) {
        history_directions[i] = _history_directions_indexes[i];
        history_directions[i] = _history_directions_indexes[i];
    }

    bool is_guard_present = true;
    bool is_loop = false;
    while (is_guard_present && !is_loop) {

        // printf("next position: %d %d\n", next_position.x, next_position.y);
        if (guard_position.x < 0 || guard_position.x >= map_width || guard_position.y < 0 || guard_position.y >= map_height) {
            return false;
        }

        for (int i = 0; i < history_length; i++) {
            if (history_positions[i].x == guard_position.x && history_positions[i].y == guard_position.y && history_directions[i] == guard_direction_index) {
                return true;
            }
        }

        history_positions[history_length].x = guard_position.x;
        history_positions[history_length].y = guard_position.y;
        history_directions[history_length] = guard_direction_index;
        history_length++;

        Position next_position = { guard_position.x + directions[guard_direction_index][0], guard_position.y + directions[guard_direction_index][1] };
        while (map[next_position.y][next_position.x] == '#') {
            guard_direction_index = (guard_direction_index + 1) % 4;
            next_position.x = guard_position.x + directions[guard_direction_index][0];
            next_position.y = guard_position.y + directions[guard_direction_index][1];
        }
        guard_position = next_position;
    }
    free(history_positions);
    free(history_directions);
    return false;
}
int part_two(const char* filename)
{
    FILE* file = fopen(filename, "r");

    // Vérifier si le fichier s'est bien ouvert
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    char line[MAX_LENGTH];
    char map[MAX_LENGTH][MAX_LENGTH] = { [0 ... MAX_LENGTH - 1] = { 0 } };

    Position guard_position = { 0, 0 };
    size_t map_height = 0;
    size_t map_width = 0;
    int total = 0;
    char directions[4][2] = {
        { 0, -1 }, // ^
        { 1, 0 }, // >
        { 0, 1 }, // v
        { -1, 0 } // <
    };
    size_t guard_direction_index = 0;
    // Lire le fichier ligne par ligne
    while (fgets(line, sizeof(line), file)) {
        // `fgets` lit une ligne entière ou jusqu'à la taille de `line`
        size_t len = strlen(line);

        if (map_width == 0) {
            map_width = len;
        } else if (map_width != len) {
            perror("Le fichier contient des lignes de tailles différentes");
            continue;
        }

        for (int i = 0; i < len; i++) {
            map[map_height][i] = line[i];
            if (line[i] == '^') {
                guard_position.x = i;
                guard_position.y = map_height;
            }
        }

        map_height++;
    }
    // Vérifier si la lecture s'est arrêtée à cause d'une erreur
    if (ferror(file)) {
        perror("Erreur de lecture du fichier");
    }

    fclose(file);

    Position* history_positions = malloc(sizeof(Position) * MAX_HISTORY);
    size_t* history_directions_indexes = malloc(sizeof(size_t) * MAX_HISTORY);
    size_t history_length = 0;

    while (true) {
        // printf("position: %d %d\n", guard_position.x, guard_position.y);

        // printf("next position: %d %d\n", next_position.x, next_position.y);
        if (guard_position.x < 0 || guard_position.x >= map_width || guard_position.y < 0 || guard_position.y >= map_height) {
            break;
        }
        Position next_position = { guard_position.x + directions[guard_direction_index][0], guard_position.y + directions[guard_direction_index][1] };

        history_positions[history_length].x = guard_position.x;
        history_positions[history_length].y = guard_position.y;
        history_directions_indexes[history_length] = guard_direction_index;
        history_length++;

        int next_direction_index = (guard_direction_index + 1) % 4;
        while (map[next_position.y][next_position.x] == '#') {
            next_direction_index = (guard_direction_index + 1) % 4;
            next_position.x = guard_position.x + directions[guard_direction_index][0];
            next_position.y = guard_position.y + directions[guard_direction_index][1];
        }
        char saved_char = map[next_position.y][next_position.x];
        map[next_position.y][next_position.x] = '#';
        if (saved_char != '#' && is_loop(map, map_width, map_height, guard_position, guard_direction_index, directions, history_positions, history_directions_indexes, history_length)) {
            total++;
        }
        map[next_position.y][next_position.x] = saved_char;
        guard_position.x = next_position.x;
        guard_position.y = next_position.y;
        guard_direction_index = next_direction_index;
    }

    // for (int i = 0; i < map_height; i++) {
    //     for (int j = 0; j < map_width; j++) {
    //         printf("%c", map[i][j]);
    //     }
    //     printf("\n");
    // }
    free(history_positions);
    free(history_directions_indexes);
    return total;
}
