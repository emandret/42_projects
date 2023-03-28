/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_sha256.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 02:17:13 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:52:19 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

char *sha256(char *msg)
{
    t_sha256 context;
    uint8_t  digest[SHA256_HASH_SIZE];
    size_t   len;

    len = strlen((const char *) msg);
    sha256_init(&context);
    sha256_input(&context, (uint8_t *) msg, len);
    sha256_result(&context, digest, SHA256_HASH_SIZE);
    return (hash2str(digest, SHA256_HASH_SIZE));
}

char *read_fd(const int fd)
{
    char *str;
    char *buf;
    int   ret;

    str = ft_strdup("");
    buf = ft_strnew(READ_BUFSIZE);
    while ((ret = read(fd, buf, READ_BUFSIZE)))
    {
        if (ret == -1)
            return (NULL);
        buf[ret] = '\0';
        str      = ft_strjoin(str, buf);
    }
    return (str);
}

void print_strings(int ac, char *av[], int *i, int *flags)
{
    while (*i < ac && (*flags & FLAG_STRING) && av[*i])
    {
        parse_flags(ac, av, i, flags);
        if (*flags & FLAG_QUIET)
            printf("%s\n", sha256(av[*i]));
        else if (*flags & FLAG_REVERSE)
            printf("%s \"%s\"\n", sha256(av[*i]), av[*i]);
        else
            printf("SHA256 (\"%s\") = %s\n", av[*i], sha256(av[*i]));
        *flags &= ~FLAG_STRING;
        ++*i;
    }
}

void print_files(int ac, char *av[], int *i, int *flags)
{
    int   fd;
    char *stdin;

    while (*i < ac)
    {
        if ((fd = open(av[*i], O_RDONLY)) == -1)
            printf("sha256: %s: No such file or directory\n", av[*i]);
        else
        {
            stdin = sha256(read_fd(fd));
            if (*flags & FLAG_QUIET)
                printf("%s\n", stdin);
            else if (*flags & FLAG_REVERSE)
                printf("%s %s\n", stdin, av[*i]);
            else
                printf("SHA256 (%s) = %s\n", av[*i], stdin);
        }
        ++*i;
    }
}

int sha256_handler(int ac, char *av[])
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
            printf("%s%s\n", stdin, sha256(stdin));
        else
            printf("%s\n", sha256(stdin));
    }
    print_strings(ac, av, &i, &flags);
    print_files(ac, av, &i, &flags);
    return (0);
}
