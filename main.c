/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:42:15 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 18:15:17 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [<filename> ...]\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        Map *map = read_map(argv[i]);
        if (map == NULL) {
            continue;
        }

        solve_map(map);
        display_map(map);

        if (i < argc - 1) {
            printf("\n");
        }

        free_map(map);
    }

    return 0;
}
