/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/09 16:55:29 by emandret          #+#    #+#             */
/*   Updated: 2017/05/31 18:47:36 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static t_node *ls_new_node(char *path, char *filename, t_node *prev)
{
    t_node *new_node;

    if (!(new_node = (t_node *) ft_memalloc(sizeof(t_node))))
        return (NULL);
    new_node->filename = ft_strdup(filename);
    if (!ls_node_data(ft_strjoin(path, filename), new_node))
    {
        ls_error(filename);
        return (NULL);
    }
    new_node->prev = prev;
    return (new_node);
}

t_node *ls_add_node(char *path, char *filename, t_node *first)
{
    t_node *last;

    if (!first)
        return (ls_new_node(path, filename, NULL));
    last = first;
    while (last->next)
        last = last->next;
    last->next = ls_new_node(path, filename, last);
    return (first);
}

void ls_free_node(t_node *node)
{
    if (node)
    {
        ft_memdel((void **) &node->filename);
        ft_memdel((void **) &node->stat);
        ft_memdel((void **) &node);
    }
}
