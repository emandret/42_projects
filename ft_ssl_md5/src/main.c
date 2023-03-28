/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 02:11:38 by emandret          #+#    #+#             */
/*   Updated: 2019/01/15 18:26:33 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_cmd get_command(char *str)
{
    if (!ft_strcmp(str, "sha256"))
        return (&sha256_handler);
    if (!ft_strcmp(str, "md5"))
        return (&md5_handler);
    return (NULL);
}

int main(int ac, char *av[])
{
    t_cmd cmd;

    if (ac < 2)
    {
        ft_printf("usage: %s command [command opts] [command args]\n", av[0]);
        return (1);
    }
    if (!(cmd = get_command(av[1])))
    {
        ft_printf("%s: Error: '%s' is an invalid command.\n", av[0], av[1]);
        ft_printf("\nStandard commands:\n");
        ft_printf("\nMessage Digest commands:\n");
        ft_printf("md5\n");
        ft_printf("sha256\n");
        ft_printf("\nCipher commands:\n");
        return (1);
    }
    (*cmd)(ac - 2, av + 2);
    return (0);
}
