/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 13:19:56 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:55 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_bool check_square(const char *str)
{
    unsigned int i;
    unsigned int hash;
    unsigned int dot;
    unsigned int endl;

    i    = 0;
    endl = 0;
    hash = 0;
    dot  = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n' && (i + 1) % 5 == 0)
            endl++;
        if (str[i] == '#')
            hash++;
        if (str[i] == '.')
            dot++;
        i++;
    }
    if (endl != NB_HASH || hash != NB_HASH || dot != 12)
        return (false);
    return (true);
}

t_bool is_adja(t_block *block1, t_block *block2)
{
    t_block *adja;

    adja = new_block(0, 0);
    if ((block1->x == (block2->x + 1) && block1->y == block2->y) ||
        (block1->x == (block2->x - 1) && block1->y == block2->y))
        adja->x++;
    if ((block1->y == (block2->y + 1) && block1->x == block2->x) ||
        (block1->y == (block2->y - 1) && block1->x == block2->x))
        adja->y++;
    if ((adja->x == 1 && adja->y == 0) || (adja->x == 0 && adja->y == 1))
        return (true);
    return (false);
}

t_bool check_adja(t_tetri *tetri)
{
    unsigned int i;
    unsigned int j;
    unsigned int count;
    t_bool       adja;

    i    = 0;
    adja = false;
    while (i < NB_HASH)
    {
        j     = 0;
        count = 0;
        while (j < NB_HASH)
        {
            if (is_adja(tetri->block[i], tetri->block[j]))
                count++;
            j++;
        }
        if (count == 0)
            return (false);
        if (count > 1)
            adja = true;
        i++;
    }
    return (adja);
}

t_tetri *parse(const char *str)
{
    unsigned int i;
    t_block     *block;
    t_tetri     *tetri;

    i     = 0;
    block = new_block(0, 0);
    tetri = new_tetri();
    while (str[i] != '\0')
    {
        if (str[i] == '#')
        {
            add_block(&tetri, block);
            block = new_block(block->x, block->y);
        }
        block->x++;
        i++;
        if (str[i] == '\n')
        {
            block->x = 0;
            block->y++;
            i++;
        }
    }
    offset_reset(&tetri);
    return (tetri);
}
