/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 23:02:39 by emandret          #+#    #+#             */
/*   Updated: 2017/08/24 22:05:09 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_bool handle_chdir(char ***env, char *dir)
{
    char cwd[4096];

    if (getcwd(cwd, 4095) && !chdir(dir))
    {
        sh_builtin_setenv(env, (char *[3]){ "OLDPWD", cwd, NULL });
        sh_builtin_setenv(env, (char *[3]){ "PWD", dir, NULL });
        ft_memdel((void **) &dir);
        return (TRUE);
    }
    return (FALSE);
}

static char *handle_shortcuts(char ***env, char **args)
{
    char *prev;
    char *home;

    if ((home = ft_getenv(*env, "HOME")))
    {
        if (!*args)
            return (ft_strdup(home));
        if (ft_strchr(*args, '~'))
            return (ft_strrep(*args, "~", home));
    }
    if ((prev = ft_getenv(*env, "OLDPWD")) && *args && '-' == **args)
    {
        ft_putendl(prev);
        return (ft_strdup(prev));
    }
    return (NULL);
}

t_code sh_builtin_cd(char ***env, char **args)
{
    char *dir;

    if (args[1])
        return (C_2MANY);
    if (!(dir = handle_shortcuts(env, args)))
        dir = ft_strdup(*args);
    if (handle_chdir(env, dir))
        return (C_OK);
    return (C_NODIR);
}
