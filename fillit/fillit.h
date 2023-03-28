/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 10:46:23 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:18 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
#define FILLIT_H

#define NB_HASH 4
#define BUF_SIZE 21

#include "libft.h"
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef enum e_bool
{
    false,
    true
} t_bool;

typedef struct s_block
{
    int x;
    int y;
} t_block;

typedef struct s_tetri
{
    t_block        *block[NB_HASH];
    unsigned int    id;
    struct s_tetri *next;
    struct s_tetri *prev;
} t_tetri;

typedef struct s_map
{
    int    size;
    char **map;
} t_map;

/*
** Map
*/

t_map *new_map(int size);
void   rebuild_map(t_map **map);
void   place_tetri(t_map **map, t_block *coord, t_tetri *tetri);
void   del_tetri(t_map **map, t_block *coord, t_tetri *tetri);

/*
** Solver
*/

int    minimal_size(int nb_tetri);
t_bool check_map(t_map *map, t_block *coord, t_tetri *tetri);
t_map *resolve(t_tetri *first_node);
t_bool solve(t_map **map, t_tetri *node);

/*
** Linked list and file
*/

int      list_size(t_tetri *first_node);
t_tetri *get_node(t_tetri *first_node, unsigned int id);

/*
** Coord methods
*/

t_block *new_block(int x, int y);

/*
** Tetri methods
*/

t_tetri *new_tetri(void);
void     set_null(t_tetri **tetri);
void     add_block(t_tetri **tetri, t_block *block);
void     add_letter(t_tetri **tetri, char letter);
void     offset_x(t_tetri **tetri, int offset_x);
void     offset_y(t_tetri **tetri, int offset_y);
void     offset_reset(t_tetri **tetri);

/*
** File functions
*/

t_bool   build_list(t_tetri **first_node, t_tetri **current_node, char *buf);
t_bool   read_file(int fd, char *buf, t_tetri **first_node);
t_tetri *open_file(char *path);

/*
** Parsing functions
*/

t_bool   check_square(const char *str);
t_bool   is_adja(t_block *block1, t_block *block2);
t_bool   check_adja(t_tetri *tetri);
t_tetri *parse(const char *str);

/*
** Display
*/

void print_map(t_map *map);

#endif
