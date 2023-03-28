/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int trim(const char *s)
{
    int i;

    i = 0;
    while (ft_is_whitespace(s[i]))
        i++;
    return (i);
}

static int rtrim(const char *s)
{
    int i;

    i = ft_strlen(s) - 1;
    while (ft_is_whitespace(s[i]))
        i--;
    return (i);
}

char *ft_strtrim(const char *s)
{
    char *new;
    int size;
    int start;
    int end;

    start = trim(s);
    end   = rtrim(s);
    if ((size = ++end - start) < 1)
        size = 1;
    if ((new = ft_strnew(size)))
    {
        size = 0;
        while (start < end)
            new[size++] = s[start++];
    }
    return (new);
}
