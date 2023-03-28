/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   growable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 11:51:14 by emandret          #+#    #+#             */
/*   Updated: 2019/04/14 16:41:40 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void gb_init(t_growable *gb, size_t data_size, size_t count)
{
    gb->start     = (uint8_t *) 0;
    gb->end       = (uint8_t *) gb->start + data_size * count;
    gb->data_size = data_size;
    gb->count     = 0;
}

void gb_copy(t_growable *gb, size_t index, void *data)
{
    size_t size;

    size = (uint8_t *) gb->end - (uint8_t *) gb->start;
    if (!gb->start)
    {
        if (!(gb->start = malloc(sizeof(uint8_t) * size)))
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        memset(gb->start, 0, sizeof(uint8_t) * size);
        gb->end = (uint8_t *) gb->start + size;
    }
    else if (gb->data_size * (index + 1) >= size)
    {
        if (!(gb->start = realloc(gb->start, sizeof(uint8_t) * size * 2)))
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        gb->end = (uint8_t *) gb->start + sizeof(uint8_t) * size * 2;
    }
    memcpy((uint8_t *) gb->start + gb->data_size * index, data, gb->data_size);
}

void gb_push(t_growable *gb, void *data)
{
    gb_copy(gb, gb->count++, data);
}

t_vec4 gb_vec4(t_growable *gb, size_t index)
{
    if (!gb->start)
        return (VEC4(0.0f, 0.0f, 0.0f, 1.0f));
    return (((t_vec4 *) gb->start)[index]);
}
