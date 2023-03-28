/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:32:08 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:40:10 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_block *new_block(int x, int y)
{
    t_block *new_block;

    new_block = NULL;
    if ((new_block = (t_block *) ft_memalloc(sizeof(t_block))))
    {
        new_block->x = x;
        new_block->y = y;
    }
    return (new_block);
}

void add_block(t_tetri **tetri, t_block *block)
{
    unsigned int i;

    i = 0;
    while (i < NB_HASH && (*tetri)->block[i] != NULL)
        i++;
    (*tetri)->block[i] = block;
}
