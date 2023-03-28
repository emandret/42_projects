/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 12:02:30 by emandret          #+#    #+#             */
/*   Updated: 2017/06/27 00:29:55 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void set_bigger(char *str, int *ref)
{
    int len;

    len = ft_strlen(str);
    if (len > *ref)
        *ref = len;
}

int *ls_get_strlens(t_opts *opts, t_node *first)
{
    int *lens;

    if (!(lens = (int *) ft_memalloc(sizeof(int) * 4)))
        return (NULL);
    while (first)
    {
        if (!IS_HIDDEN(first->filename) || opts->a)
        {
            set_bigger(ft_itoa(first->stat->st_nlink), &lens[0]);
            set_bigger(first->pw_name, &lens[1]);
            set_bigger(first->gr_name, &lens[2]);
            set_bigger(ls_get_devsize(first), &lens[3]);
        }
        first = first->next;
    }
    return (lens);
}

/*
** Compute the total number of block for the linked list
*/

uintmax_t ls_total_blocks(t_opts *opts, t_node *first)
{
    uintmax_t total;

    total = 0;
    while (first)
    {
        if (!IS_HIDDEN(first->filename) || opts->a)
            total += first->stat->st_blocks;
        first = first->next;
    }
    return (total);
}

/*
** Get the device file size, or minor/major numbers
*/

char *ls_get_devsize(t_node *node)
{
    char *devsize;
    char *minor;
    char *major;

    if ('c' != node->type && 'b' != node->type)
        return (ft_ultoa_base(node->stat->st_size, 10));
    if (!(devsize = ft_strnew(10)))
        return (NULL);
    ft_chrncpy(devsize, ' ', 2);
    major = ft_itoa(major(node->stat->st_rdev));
    ft_strcpy(END(devsize), major);
    ft_memdel((void **) &major);
    ft_strcpy(END(devsize), ", ");
    minor = ft_itoa(minor(node->stat->st_rdev));
    ft_chrncpy(END(devsize), ' ', 4 - ft_strlen(minor));
    ft_strcpy(END(devsize), minor);
    ft_memdel((void **) &minor);
    return (devsize);
}

/*
** Get the creation time of a file
*/

char *ls_get_filetime(time_t last_access)
{
    time_t timestamp;
    char  *datetime;
    char  *filetime;

    if (!(filetime = ft_strnew(12)))
        return (NULL);
    time(&timestamp);
    datetime = ctime(&last_access);
    if (ABS(timestamp - last_access) > 3600 * 24 * 30 * 6)
    {
        ft_strncpy(filetime, &datetime[4], 7);
        ft_strncpy(&filetime[7], &datetime[19], 5);
    }
    else
        ft_strncpy(filetime, &datetime[4], 12);
    return (filetime);
}
