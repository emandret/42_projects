/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 11:18:19 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:50 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** Verifie si aux coord on peut placer le tetri
*/

t_bool check_map(t_map *map, t_block *coord, t_tetri *tetri)
{
    t_block     *check_pos;
    unsigned int i;

    i = 0;
    while (i < NB_HASH)
    {
        check_pos = new_block(coord->x + tetri->block[i]->x, coord->y + tetri->block[i]->y);
        if ((check_pos->x < 0 || check_pos->x > map->size - 1 || check_pos->y < 0 || check_pos->y > map->size - 1))
            return (false);
        if (map->map[check_pos->y][check_pos->x] != '.')
            return (false);
        i++;
    }
    return (true);
}

t_bool solve(t_map **map, t_tetri *node)
{
    t_block *my_pos;

    if (node == NULL)
        return (true);
    my_pos = new_block(0, 0);
    while (my_pos->y < (*map)->size)
    {
        my_pos->x = 0;
        while (my_pos->x < (*map)->size)
        {
            if (check_map(*map, my_pos, node))
            {
                place_tetri(map, my_pos, node);
                if (solve(map, node->next))
                    return (true);
                else
                    del_tetri(map, my_pos, node);
            }
            my_pos->x++;
        }
        my_pos->y++;
    }
    return (false);
}

t_map *resolve(t_tetri *first_node)
{
    t_map *map;

    map = new_map(minimal_size(list_size(first_node)));
    while (solve(&map, first_node) == false)
    {
        map->size++;
        rebuild_map(&map);
    }
    return (map);
}
