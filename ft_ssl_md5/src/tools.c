/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 02:17:13 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:53:20 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char *hash2str(uint8_t *digest, const size_t hash_size)
{
    char  *str;
    size_t i;
    size_t j;

    if (!(str = ft_strnew(hash_size * 2)))
        return (NULL);
    i = 0;
    j = 0;
    while (i < hash_size)
    {
        str[j++] = HEX_BASE[digest[i] / 16 % 16];
        str[j++] = HEX_BASE[digest[i] % 16];
        i++;
    }
    return (str);
}

void print_usage(char *option)
{
    ft_putstr("unknown option '");
    ft_putstr(option);
    ft_putstr("'\noptions are\n");
    ft_putstr("-p  echo STDIN to STDOUT and append the checksum to STDOUT\n");
    ft_putstr("-q  quiet mode\n");
    ft_putstr("-r  reverse the format of the output\n");
    ft_putstr("-s  print the sum of the given string\n");
}

void parse_flags(int ac, char *av[], int *i, int *flags)
{
    while (*i < ac && av[*i][0] == '-')
    {
        if (av[*i][1] == 'p')
            *flags |= FLAG_PRINT;
        else if (av[*i][1] == 'q')
            *flags |= FLAG_QUIET;
        else if (av[*i][1] == 'r')
            *flags |= FLAG_REVERSE;
        else if (av[*i][1] == 's')
        {
            *flags |= FLAG_STRING;
            ++*i;
            break;
        }
        else
        {
            print_usage(av[*i]);
            exit(1);
        }
        ++*i;
    }
}
