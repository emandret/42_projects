/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/17 19:35:29 by emandret          #+#    #+#             */
/*   Updated: 2017/06/27 00:44:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*
** The final output
*/

static void print_output(t_opts *opts, t_node *node, int *lens)
{
    if (opts->l)
    {
        ft_printf("%s%c %*hu %-*s  %-*s  %*s %s ",
                  ls_get_perms(node->type, node->stat->st_mode),
                  node->acl,
                  lens[0],
                  node->stat->st_nlink,
                  lens[1],
                  node->pw_name,
                  lens[2],
                  node->gr_name,
                  lens[3],
                  ls_get_devsize(node),
                  ls_get_filetime(node->stat->st_mtime));
    }
    ft_putstr(node->filename);
    if (opts->l && 'l' == node->type)
        ft_printf(" -> %s", node->target);
    ft_putchar('\n');
}

/*
** Print the filename for each node in the list
*/

void ls_print(t_opts *opts, t_node *first, t_bool show_d)
{
    int *lens;

    lens = ls_get_strlens(opts, first);
    if (show_d && opts->l)
        ft_printf("total %d\n", ls_total_blocks(opts, first));
    while (first)
    {
        if (('l' == first->type || 'd' != first->target_type || opts->l) && (!IS_HIDDEN(first->filename) || opts->a) &&
            ('d' != first->type || show_d))
            print_output(opts, first, lens);
        first = first->next;
    }
}
