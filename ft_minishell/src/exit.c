/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 23:02:39 by emandret          #+#    #+#             */
/*   Updated: 2017/08/22 05:27:04 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_code sh_builtin_exit(char ***env, char **args)
{
    int exit_code;

    (void) env;
    if (args[1])
        return (C_2MANY);
    exit_code = 0;
    if (*args)
        exit_code = ft_atoi(*args);
    exit(exit_code);
}
