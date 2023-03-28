/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 23:02:39 by emandret          #+#    #+#             */
/*   Updated: 2017/08/23 20:28:08 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_code sh_builtin_unsetenv(char ***env, char **args)
{
    unsigned int i;
    unsigned int j;
    char **new;

    if (!*args)
        return (C_NOARG);
    if (!ft_getenv(*env, *args))
        return (C_NOVAL);
    if (!(new = (char **) ft_memalloc(sizeof(char *) * (ft_tabsize(*env) - 1))))
        return (C_ALLOC);
    i = 0;
    j = 0;
    while ((*env)[i])
    {
        if ('=' == ft_strcmp((*env)[i], *args))
            i++;
        if ((*env)[i])
            new[j++] = ft_strdup((*env)[i++]);
    }
    new[j] = NULL;
    ft_tabswap(env, &new);
    ft_tabfree((void **) new);
    return (C_OK);
}
