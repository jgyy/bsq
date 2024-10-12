/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:49:44 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 17:56:01 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

void display_map(Map *map) {
    for (int i = 0; i < map->rows; i++) {
        printf("%s\n", map->grid[i]);
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

size_t ft_strlen(const char *s) {
    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }
    return len;
}

char *ft_strcpy(char *dst, const char *src) {
    char *original_dst = dst;
    while ((*dst++ = *src++) != '\0')
        ;
    return original_dst;
}
