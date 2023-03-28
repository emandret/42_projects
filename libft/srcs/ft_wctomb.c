/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wctomb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_wctomb(unsigned char *s, unsigned int wchar)
{
    int          len;
    unsigned int rshift;
    unsigned int mask[2];
    int          i;

    if (!s || !(len = ft_wcsize(wchar)))
        return (0);
    rshift  = (len - 1) * 6;
    mask[0] = 0xFF;
    mask[1] = 0xC0;
    if (len > 2)
        mask[1] += (len - 1) * 16;
    i = 0;
    while (i < len)
    {
        s[i++]  = (wchar >> rshift & mask[0]) | mask[1];
        mask[0] = 0x3F;
        mask[1] = 0x80;
        rshift -= 6;
    }
    return (len);
}
