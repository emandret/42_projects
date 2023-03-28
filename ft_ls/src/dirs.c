/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/10 12:54:13 by emandret          #+#    #+#             */
/*   Updated: 2017/05/31 21:04:08 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*
** Concatenate paths
*/

static char *set_path(char *path, char *dirname)
{
    if (IS_DOTDIR(dirname))
        return (ft_strjoin(dirname, "/"));
    if ('/' != dirname[ft_strlen(dirname) - 1])
        return (ft_strjoin_free(ft_strjoin(path, dirname), "/"));
    return (dirname);
}

/*
** Print contents of a directory
*/

static void print_ctn(t_opts *opts, t_node *first, char *path)
{
    if (opts->path || (opts->path && opts->recu))
    {
        if (opts->endl)
            ft_putchar('\n');
        ft_printf("%.*s:\n", ft_strlen(path) - 1, path);
    }
    opts->endl = TRUE;
    opts->path = TRUE;
    ls_print(opts, first, TRUE);
}

/*
** Explore a directory and create a linked list of its contents
*/

t_node *ls_open_dir(DIR *stream, t_opts *opts, char *path)
{
    t_dir  *dirent;
    t_node *first;

    first = NULL;
    while ((dirent = readdir(stream)))
        first = ls_add_node(path, dirent->d_name, first);
    ls_lst_order(opts, &first);
    return (first);
}

/*
** Recursively explore nested directories and print their contents
*/

int ls_probe_dir(t_opts *opts, char *path, char *dirname)
{
    DIR    *stream;
    t_node *first;
    t_node *head;

    path = set_path(path, dirname);
    if (!(stream = opendir(path)))
    {
        ls_error(dirname);
        return (-1);
    }
    if ((first = ls_open_dir(stream, opts, path)))
    {
        print_ctn(opts, first, path);
        head = first;
        while (head)
        {
            if (opts->recu && 'd' == head->type && !IS_DOTDIR(head->filename) &&
                (!IS_HIDDEN(head->filename) || opts->a))
                ls_probe_dir(opts, path, head->filename);
            head = head->next;
        }
    }
    ls_lst_free(first);
    closedir(stream);
    return (0);
}
