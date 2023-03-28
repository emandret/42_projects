/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void skip(const char *s, char c, int *i)
{
    while (s[*i] && s[*i] == c)
        (*i)++;
}

static int count_words(const char *s, char c)
{
    int i;
    int words;

    i     = 0;
    words = 0;
    while (s[i])
    {
        skip(s, c, &i);
        if (s[i] && s[i] != c)
        {
            while (s[i] && s[i] != c)
                i++;
            words++;
        }
    }
    return (words);
}

static void add(char **s, char c)
{
    size_t len;
    char *new;

    if (*s)
    {
        len      = ft_strlen(*s);
        new      = ft_strnew(len + 1);
        new      = ft_strcpy(new, *s);
        new[len] = c;
        ft_ptrswap((void **) &new, (void **) s);
        ft_memdel((void **) &new);
    }
    else
    {
        *s    = ft_strnew(1);
        *s[0] = c;
    }
}

char **ft_strsplit(const char *s, char c)
{
    int    i;
    int    j;
    char **t;

    t = NULL;
    if ((t = (char **) ft_memalloc(sizeof(char *) * (count_words(s, c) + 1))))
    {
        i = 0;
        j = 0;
        while (s[i])
        {
            skip(s, c, &i);
            if (s[i] && s[i] != c)
            {
                while (s[i] && s[i] != c)
                    add(t + j, s[i++]);
                j++;
                t[j] = NULL;
            }
        }
    }
    return (t);
}
