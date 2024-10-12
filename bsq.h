/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jegoh <jegoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 17:39:40 by jegoh             #+#    #+#             */
/*   Updated: 2024/10/12 17:55:47 by jegoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
#define BSQ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

typedef struct {
    int rows;
    int cols;
    char empty;
    char obstacle;
    char full;
    char **grid;
} Map;

Map *read_map(const char *filename);
void free_map(Map *map);

void solve_map(Map *map);

void display_map(Map *map);
int max(int a, int b);
int min(int a, int b);
size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);

#endif