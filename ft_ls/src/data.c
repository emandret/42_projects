/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/31 17:11:19 by emandret          #+#    #+#             */
/*   Updated: 2017/06/27 00:30:34 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*
** Return the corresponding character of a supported Unix file type
*/

static char get_type(mode_t mode)
{
    if (S_ISREG(mode))
        return ('-');
    if (S_ISDIR(mode))
        return ('d');
    if (S_ISLNK(mode))
        return ('l');
    if (S_ISCHR(mode))
        return ('c');
    if (S_ISBLK(mode))
        return ('b');
    if (S_ISFIFO(mode))
        return ('p');
    if (S_ISSOCK(mode))
        return ('s');
    return ('\0');
}

/*
** Get info about the file a symbolic link points to
*/

static t_bool link_data(char *fpath, t_node *node)
{
    ssize_t ret;
    t_stat *st;

    if (!(st = (t_stat *) ft_memalloc(sizeof(t_stat))))
        return (FALSE);
    if ((ret = readlink(fpath, node->target, 255)) == -1)
        return (FALSE);
    node->target[ret] = '\0';
    if (ft_strcmp(node->filename, node->target))
    {
        if (stat(fpath, st) == -1)
            return (FALSE);
        if (!(node->target_type = get_type(st->st_mode)))
            return (FALSE);
    }
    return (TRUE);
}

/*
** Get ACL info
*/

static char get_acl(char *fpath)
{
    ssize_t acl;

    if ((acl = listxattr(fpath, NULL, 1, XATTR_NOFOLLOW)) != -1 && acl)
        return ('@');
    return (' ');
}

/*
** Get info about the file located at 'fpath' and create a new filenode
*/

t_bool ls_node_data(char *fpath, t_node *node)
{
    t_user  *user;
    t_group *group;

    if (!(node->stat = (t_stat *) ft_memalloc(sizeof(t_stat))))
        return (FALSE);
    if (lstat(fpath, node->stat) == -1)
        return (FALSE);
    if (!(node->type = get_type(node->stat->st_mode)))
        return (FALSE);
    if ('l' == node->type && !link_data(fpath, node))
        return (FALSE);
    if (!(user = getpwuid(node->stat->st_uid)))
        return (FALSE);
    node->pw_name = ft_strdup(user->pw_name);
    if (!(group = getgrgid(node->stat->st_gid)))
        return (FALSE);
    node->gr_name = ft_strdup(group->gr_name);
    node->acl     = get_acl(fpath);
    return (TRUE);
}
