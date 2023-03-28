/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 17:49:19 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:24 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void print_map(t_map *map)
{
    int i;

    i = 0;
    while (i < map->size)
    {
        ft_putendl(map->map[i]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    t_tetri *first_node;
    t_map   *map;

    if (argc == 2)
    {
        if (!(first_node = open_file(argv[1])))
        {
            ft_putendl("error");
            exit(-1);
        }
        map = resolve(first_node);
        print_map(map);
    }
    else
        ft_putendl("usage: ./fillit target_file");
    return (0);
}
