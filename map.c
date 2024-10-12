/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:47:56 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 18:15:35 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int read_first_line(FILE *file, Map *map) {
    char buffer[BUFFER_SIZE];
    if (fgets(buffer, BUFFER_SIZE, file) == NULL) {
        return 0;
    }

    int parsed = sscanf(buffer, "%d%c%c%c", &map->rows, &map->empty, &map->obstacle, &map->full);
    return parsed == 4 && map->rows > 0;
}

static int allocate_grid(Map *map) {
    map->grid = malloc(map->rows * sizeof(char *));
    if (map->grid == NULL) {
        return 0;
    }

    for (int i = 0; i < map->rows; i++) {
        map->grid[i] = NULL;
    }

    return 1;
}

static int read_map_data(FILE *file, Map *map) {
    char buffer[BUFFER_SIZE];
    int row = 0;

    while (fgets(buffer, BUFFER_SIZE, file) && row < map->rows) {
        int len = ft_strlen(buffer);
        if (buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        }

        if (row == 0) {
            map->cols = len;
        } else if (len != map->cols) {
            return 0;
        }

        map->grid[row] = malloc(map->cols + 1);
        if (map->grid[row] == NULL) {
            return 0;
        }

        for (int i = 0; i < len; i++) {
            if (buffer[i] != map->empty && buffer[i] != map->obstacle) {
                return 0;
            }
            map->grid[row][i] = buffer[i];
        }
        map->grid[row][len] = '\0';

        row++;
    }

    return row == map->rows;
}

Map *read_map(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "map error\n");
        return NULL;
    }

    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        fclose(file);
        fprintf(stderr, "map error\n");
        return NULL;
    }

    if (!read_first_line(file, map) || !allocate_grid(map) || !read_map_data(file, map)) {
        free_map(map);
        fclose(file);
        fprintf(stderr, "map error\n");
        return NULL;
    }

    fclose(file);
    return map;
}

void free_map(Map *map) {
    if (map == NULL) {
        return;
    }

    if (map->grid != NULL) {
        for (int i = 0; i < map->rows; i++) {
            free(map->grid[i]);
        }
        free(map->grid);
    }

    free(map);
}
