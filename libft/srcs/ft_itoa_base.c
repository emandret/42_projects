/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t get_len(int n, unsigned int base)
{
    size_t len;

    len = 1;
    if (n < 0)
    {
        n = -n;
        len++;
    }
    while (n /= base)
        len++;
    return (len);
}

static void to_string(char **s, int *i, int n, unsigned int base)
{
    char t[16];

    ft_strcpy(t, "0123456789ABCDEF");
    if (!n)
        **s = '0';
    (*i)--;
    while (n > 0)
    {
        (*s)[*i] = t[n % base];
        n /= base;
        (*i)--;
    }
}

char *ft_itoa_base(int n, unsigned int base)
{
    char *s;
    int   i;
    bool  is_neg;

    if (n == -2147483648)
        return (ft_strdup("-2147483648"));
    s = NULL;
    i = get_len(n, base);
    if (base >= 2 && base <= 16 && (s = ft_strnew(i)))
    {
        if (!n)
        {
            to_string(&s, &i, n, base);
            return (s);
        }
        if ((is_neg = (n < 0)))
            n = ABS(n);
        to_string(&s, &i, n, base);
        if (is_neg)
            s[i] = '-';
    }
    return (s);
}
