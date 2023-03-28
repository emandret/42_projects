/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void skip(const char *s, int *i)
{
    while (s[*i] && ft_is_whitespace(s[*i]))
        (*i)++;
}

static int count_words(const char *s)
{
    int i;
    int words;

    i     = 0;
    words = 0;
    while (s[i])
    {
        skip(s, &i);
        if (s[i] && !ft_is_whitespace(s[i]))
        {
            while (s[i] && !ft_is_whitespace(s[i]))
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

char **ft_split_whitespaces(const char *s)
{
    int    i;
    int    j;
    char **t;

    t = NULL;
    if ((t = (char **) ft_memalloc(sizeof(char *) * (count_words(s) + 1))))
    {
        i = 0;
        j = 0;
        while (s[i])
        {
            skip(s, &i);
            if (s[i] && !ft_is_whitespace(s[i]))
            {
                while (s[i] && !ft_is_whitespace(s[i]))
                    add(t + j, s[i++]);
                j++;
                t[j] = NULL;
            }
        }
    }
    return (t);
}
