/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   storage_class.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 12:51:16 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:47 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int list_size(t_tetri *first_node)
{
    int size;

    size = 1;
    while ((first_node = first_node->next) != NULL)
        size++;
    return (size);
}

t_tetri *get_node(t_tetri *first_node, unsigned int id)
{
    while (first_node->next != NULL && first_node->id != id)
        first_node = first_node->next;
    return (first_node);
}
