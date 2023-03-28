/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_class.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 19:28:31 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:40:03 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int minimal_size(int nb_tetri)
{
    int size;

    size = 1;
    while (size * size < nb_tetri * 4)
        size++;
    return (size);
}

t_map *new_map(int size)
{
    t_map *new;

    new = NULL;
    if ((new = (t_map *) malloc(sizeof(t_map))))
    {
        new->size = size;
        new->map  = NULL;
    }
    rebuild_map(&new);
    return (new);
}

void rebuild_map(t_map **map)
{
    int    i;
    int    j;
    char **old;
    char **new;

    new = NULL;
    if ((new = (char **) malloc(sizeof(char *) * ((*map)->size + 1))))
    {
        i = 0;
        while (i < (*map)->size)
        {
            new[i] = ft_strnew((*map)->size);
            j      = 0;
            while (j < (*map)->size)
                new[i][j++] = '.';
            i++;
        }
        new[i] = NULL;
    }
    old         = (*map)->map;
    (*map)->map = new;
    free(old);
}

/*
** Place un tetri aux coord
*/

void place_tetri(t_map **map, t_block *coord, t_tetri *tetri)
{
    unsigned int i;

    i = 0;
    while (i < NB_HASH)
    {
        (*map)->map[coord->y + tetri->block[i]->y][coord->x + tetri->block[i]->x] = 'A' + tetri->id - 1;
        i++;
    }
}

void del_tetri(t_map **map, t_block *coord, t_tetri *tetri)
{
    unsigned int i;

    i = 0;
    while (i < NB_HASH)
    {
        (*map)->map[coord->y + tetri->block[i]->y][coord->x + tetri->block[i]->x] = '.';
        i++;
    }
}
