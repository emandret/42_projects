/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/22 01:45:26 by emandret          #+#    #+#             */
/*   Updated: 2017/08/22 09:02:26 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void set(void **btins, unsigned int *i, char *name, t_builtin func)
{
    btins[(*i)++] = (void *) name;
    btins[(*i)++] = (void *) func;
}

static void check(char *btin, t_code code)
{
    if (code == C_OK)
        return;
    else if (code == C_NODIR)
        sh_error(btin, "no such file or directory");
    else if (code == C_ALLOC)
        sh_error(btin, "memory allocation failed");
    else if (code == C_NOARG)
        sh_error(btin, "not enough arguments");
    else if (code == C_2MANY)
        sh_error(btin, "too many arguments");
    else if (code == C_NOVAL)
        sh_error(btin, "value is not defined");
}

void **sh_init_builtins(void)
{
    void       **btins;
    unsigned int i;

    if (!(btins = ft_memalloc(sizeof(void *) * (BUILTINS * 2 + 2))))
        return (NULL);
    i = 0;
    set(btins, &i, "echo", &sh_builtin_echo);
    set(btins, &i, "cd", &sh_builtin_cd);
    set(btins, &i, "setenv", &sh_builtin_setenv);
    set(btins, &i, "unsetenv", &sh_builtin_unsetenv);
    set(btins, &i, "env", &sh_builtin_env);
    set(btins, &i, "exit", &sh_builtin_exit);
    set(btins, &i, NULL, NULL);
    return (btins);
}

t_bool sh_call_builtins(void **btins, char ***env, char **args)
{
    unsigned int i;

    if (!btins)
        return (FALSE);
    i = 0;
    while (btins[i] && btins[i + 1])
    {
        if (ft_strequ(args[0], (char *) btins[i]))
        {
            check((char *) btins[i], ((t_builtin) btins[i + 1])(env, &args[1]));
            return (TRUE);
        }
        i += 2;
    }
    return (FALSE);
}
