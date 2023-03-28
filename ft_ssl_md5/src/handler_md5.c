/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_md5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:40:04 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 02:47:09 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

static char *md5(char *msg)
{
    t_md5   context;
    uint8_t digest[16];
    size_t  len;

    context.count[0] = 0;
    context.count[1] = 0;
    context.state[0] = 0x67452301;
    context.state[1] = 0xefcdab89;
    context.state[2] = 0x98badcfe;
    context.state[3] = 0x10325476;
    len              = strlen(msg);
    md5_update(&context, (uint8_t *) msg, len);
    md5_final(digest, &context);
    return (hash2str(digest, MD5_HASH_SIZE));
}

static void print_strings(int ac, char *av[], int *i, int *flags)
{
    while (*i < ac && (*flags & FLAG_STRING) && av[*i])
    {
        parse_flags(ac, av, i, flags);
        if (*flags & FLAG_QUIET)
            printf("%s\n", md5(av[*i]));
        else if (*flags & FLAG_REVERSE)
            printf("%s \"%s\"\n", md5(av[*i]), av[*i]);
        else
            printf("MD5 (\"%s\") = %s\n", av[*i], md5(av[*i]));
        *flags &= ~FLAG_STRING;
        ++*i;
    }
}

static void print_files(int ac, char *av[], int *i, int *flags)
{
    int   fd;
    char *stdin;

    while (*i < ac)
    {
        if ((fd = open(av[*i], O_RDONLY)) == -1)
            printf("md5: %s: No such file or directory\n", av[*i]);
        else
        {
            stdin = md5(read_fd(fd));
            if (*flags & FLAG_QUIET)
                printf("%s\n", stdin);
            else if (*flags & FLAG_REVERSE)
                printf("%s %s\n", stdin, av[*i]);
            else
                printf("MD5 (%s) = %s\n", av[*i], stdin);
        }
        ++*i;
    }
}

int md5_handler(int ac, char *av[])
{
    int   flags;
    int   i;
    char *stdin;

    flags = 0;
    i     = 0;
    parse_flags(ac, av, &i, &flags);
    if ((!av[i] || (flags & FLAG_PRINT)) && (stdin = read_fd(0)))
    {
        if (flags & FLAG_PRINT)
            printf("%s%s\n", stdin, md5(stdin));
        else
            printf("%s\n", md5(stdin));
    }
    print_strings(ac, av, &i, &flags);
    print_files(ac, av, &i, &flags);
    return (0);
}
