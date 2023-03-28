/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 23:02:39 by emandret          #+#    #+#             */
/*   Updated: 2017/08/23 20:25:28 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void sh_error(char *name, char *error)
{
    ft_putstr_fd(name, 2);
    ft_putstr_fd(": ", 2);
    ft_putendl_fd(error, 2);
}

char **sh_get_paths(char **env, char **old_paths)
{
    char *path;

    if (old_paths)
        ft_tabfree((void **) old_paths);
    if (!(path = ft_getenv(env, "PATH")))
        path = "/";
    return (ft_strsplit(path, ':'));
}
