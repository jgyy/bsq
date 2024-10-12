/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:49:37 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 18:19:14 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static int **create_dp_grid(int rows, int cols) {
    int **dp = malloc(rows * sizeof(int *));
    if (dp == NULL) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        dp[i] = calloc(cols, sizeof(int));
        if (dp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dp[j]);
            }
            free(dp);
            return NULL;
        }
    }

    return dp;
}

static void free_dp_grid(int **dp, int rows) {
    for (int i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);
}

void solve_map(Map *map) {
    int **dp = create_dp_grid(map->rows, map->cols);
    if (dp == NULL) {
        return;
    }

    int max_size = 0;
    int max_i = 0, max_j = 0;

    for (int i = 0; i < map->rows; i++) {
        dp[i][0] = (map->grid[i][0] == map->empty) ? 1 : 0;
        if (dp[i][0] > max_size) {
            max_size = dp[i][0];
            max_i = i;
            max_j = 0;
        } else if (dp[i][0] == max_size) {
            if (i < max_i) {
                max_i = i;
                max_j = 0;
            }
        }
    }

    for (int j = 0; j < map->cols; j++) {
        dp[0][j] = (map->grid[0][j] == map->empty) ? 1 : 0;
        if (dp[0][j] > max_size) {
            max_size = dp[0][j];
            max_i = 0;
            max_j = j;
        } else if (dp[0][j] == max_size) {
            if (j < max_j || max_i > 0) {
                max_i = 0;
                max_j = j;
            }
        }
    }

    for (int i = 1; i < map->rows; i++) {
        for (int j = 1; j < map->cols; j++) {
            if (map->grid[i][j] == map->empty) {
                dp[i][j] = 1 + min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]));
                if (dp[i][j] > max_size) {
                    max_size = dp[i][j];
                    max_i = i;
                    max_j = j;
                } else if (dp[i][j] == max_size) {
                    int new_top = i - dp[i][j] + 1;
                    int curr_top = max_i - max_size + 1;
                    if (new_top < curr_top ||
                        (new_top == curr_top && (j - dp[i][j] + 1) < (max_j - max_size + 1))) {
                        max_i = i;
                        max_j = j;
                    }
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    for (int i = max_i - max_size + 1; i <= max_i; i++) {
        for (int j = max_j - max_size + 1; j <= max_j; j++) {
            map->grid[i][j] = map->full;
        }
    }

    free_dp_grid(dp, map->rows);
}
