/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetri_class.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:26:36 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:35 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_tetri *new_tetri(void)
{
    t_tetri *new_tetri;

    new_tetri = NULL;
    if ((new_tetri = (t_tetri *) ft_memalloc(sizeof(t_tetri))))
        set_null(&new_tetri);
    return (new_tetri);
}

void set_null(t_tetri **tetri)
{
    unsigned int i;

    i = 0;
    while (i < NB_HASH)
        (*tetri)->block[i++] = NULL;
    (*tetri)->id   = 0;
    (*tetri)->next = NULL;
    (*tetri)->prev = NULL;
}

void offset_x(t_tetri **tetri, int offset_x)
{
    unsigned int i;

    i = 0;
    while (i < NB_HASH)
        (*tetri)->block[i++]->x += offset_x;
}

void offset_y(t_tetri **tetri, int offset_y)
{
    unsigned int i;

    i = 0;
    while (i < NB_HASH)
        (*tetri)->block[i++]->y += offset_y;
}

void offset_reset(t_tetri **tetri)
{
    offset_x(tetri, ((*tetri)->block[0]->x) * -1);
    offset_y(tetri, ((*tetri)->block[0]->y) * -1);
}
