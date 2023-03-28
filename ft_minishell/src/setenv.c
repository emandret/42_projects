/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 23:02:39 by emandret          #+#    #+#             */
/*   Updated: 2017/08/24 21:50:41 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_code sh_builtin_setenv(char ***env, char **args)
{
    unsigned int i;
    char **new;
    char *val;

    if (!*args)
        return (C_NOARG);
    if (ft_getenv(*env, *args))
        sh_builtin_unsetenv(env, args);
    val = ft_strjoin(*args, "=");
    if (args[1])
        val = ft_strjoin_free(val, args[1]);
    if (!(new = (char **) ft_memalloc(sizeof(char *) * (ft_tabsize(*env) + 1))))
        return (C_ALLOC);
    i = 0;
    while ((*env)[i])
    {
        new[i] = ft_strdup((*env)[i]);
        i++;
    }
    new[i++] = val;
    new[i]   = NULL;
    ft_tabswap(env, &new);
    ft_tabfree((void **) new);
    return (C_OK);
}
