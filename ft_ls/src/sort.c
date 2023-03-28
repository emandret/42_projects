/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 02:45:17 by emandret          #+#    #+#             */
/*   Updated: 2017/06/23 21:46:58 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*
** Compare two filenames in lexicographical order
*/

t_bool ls_sort_lexi(t_node *n1, t_node *n2)
{
    return ((t_bool) (ft_strcmp(n1->filename, n2->filename) > 0));
}

/*
** Compare the creation date of two files
*/

t_bool ls_sort_time(t_node *n1, t_node *n2)
{
    return ((t_bool) (n1->stat->st_mtime < n2->stat->st_mtime));
}

/*
** Sort the linked list using the (inefficient) bubble sort
*/

void ls_lst_sort(t_node **first, t_bool (*sort)(t_node *n1, t_node *n2))
{
    t_bool  sorted;
    t_node *head;

    sorted = FALSE;
    while (!sorted && *first)
    {
        sorted = TRUE;
        head   = *first;
        while (head->next)
        {
            if ((*sort)(head, head->next))
            {
                sorted = FALSE;
                if (ls_swap_first(first, head, head->next))
                    head = *first;
            }
            else
                head = head->next;
        }
    }
}

/*
** Reverse the list
*/

void ls_lst_revr(t_node **first)
{
    t_node *head;
    t_node *prev;

    head = *first;
    prev = NULL;
    while (head)
    {
        prev       = head->prev;
        head->prev = head->next;
        head->next = prev;
        head       = head->prev;
    }
    if (prev)
        *first = prev->prev;
}
