/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 20:29:41 by emandret          #+#    #+#             */
/*   Updated: 2017/05/29 20:45:02 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

/*
** Return a character depending on whether 'has_perm' is true or false
*/

static char has_perm(t_bool has_perm, char perm, char not )
{
    if (has_perm)
        return (perm);
    return (not );
}

/*
** Check if a file has the setuid bit set, otherwise check if the file has the execute/explore bit
*/

static char has_suid(mode_t mode)
{
    if (mode & S_ISUID)
        return (has_perm((mode & S_IXUSR), 's', 'S'));
    return (has_perm((mode & S_IXUSR), 'x', '-'));
}

/*
** Check if a file has the setgid bit set, otherwise check if the file has the execute/explore bit
*/

static char has_sgid(mode_t mode)
{
    if (mode & S_ISGID)
        return (has_perm((mode & S_IXGRP), 's', 'S'));
    return (has_perm((mode & S_IXGRP), 'x', '-'));
}

/*
** Check if a file has the sticky bit set, otherwise check if the file has the execute/explore bit
*/

static char has_sbit(mode_t mode)
{
    if (mode & S_ISVTX)
        return (has_perm((mode & S_IXOTH), 't', 'T'));
    return (has_perm((mode & S_IXOTH), 'x', '-'));
}

/*
** Convert the binary representation of permissions to the corresponding literal form
*/

char *ls_get_perms(char type, mode_t mode)
{
    char *buf;

    if (!(buf = ft_strnew(10)))
        return (NULL);
    buf[0] = type;
    buf[1] = has_perm((mode & S_IRUSR), 'r', '-');
    buf[2] = has_perm((mode & S_IWUSR), 'w', '-');
    buf[3] = has_suid(mode);
    buf[4] = has_perm((mode & S_IRGRP), 'r', '-');
    buf[5] = has_perm((mode & S_IWGRP), 'w', '-');
    buf[6] = has_sgid(mode);
    buf[7] = has_perm((mode & S_IROTH), 'r', '-');
    buf[8] = has_perm((mode & S_IWOTH), 'w', '-');
    buf[9] = has_sbit(mode);
    return (buf);
}
