/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 23:02:39 by emandret          #+#    #+#             */
/*   Updated: 2017/08/22 17:08:00 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_code sh_builtin_echo(char ***env, char **args)
{
    unsigned int i;

    (void) env;
    i = 0;
    while (args[i])
    {
        ft_putstr(args[i]);
        if (args[i + 1])
            ft_putchar(' ');
        i++;
    }
    ft_putchar('\n');
    return (C_OK);
}
