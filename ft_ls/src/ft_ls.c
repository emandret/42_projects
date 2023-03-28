/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:34:09 by emandret          #+#    #+#             */
/*   Updated: 2017/06/27 00:43:08 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int main(int argc, char *argv[])
{
    int     i;
    t_node *first;
    t_opts *opts;
    t_bool  no_arg;

    i      = 1;
    first  = NULL;
    opts   = ls_parse_opts(argc, argv, &i);
    no_arg = TRUE;
    if (argc > 1)
    {
        if (i < argc)
            no_arg = FALSE;
        while (i < argc)
            first = ls_add_node("", argv[i++], first);
    }
    if (no_arg && !first)
        first = ls_add_node("", ".", first);
    ft_ls(opts, first);
    return (0);
}

/*
** Dispatch filenodes to the appropriate functions
*/

void ft_ls(t_opts *opts, t_node *first)
{
    t_node *content;

    content = NULL;
    ls_lst_order(opts, &first);
    ls_print(opts, first, FALSE);
    if (ls_lst_size(first) > 1 && ls_lst_dirs(first) > 0)
    {
        opts->path = TRUE;
        if (ls_lst_size(first) != ls_lst_dirs(first))
            opts->endl = TRUE;
    }
    while (first)
    {
        if ('d' == first->type || ('l' == first->type && 'd' == first->target_type && !opts->l))
            ls_probe_dir(opts, "", first->filename);
        first = first->next;
    }
}

/*
** Print an error on STDERR
*/

void ls_error(char *filename)
{
    ft_putstr_fd("ls: ", 2);
    perror(filename);
}
