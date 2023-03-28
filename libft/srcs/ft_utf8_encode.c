/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utf8_encode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

wchar_t ft_utf8_encode(unsigned int wchar)
{
    int           len;
    unsigned char s[4];
    unsigned int  lshift;

    if (!(len = ft_wctomb(s, wchar)))
        return (0);
    if (!(lshift = (len - 1) * 8))
        return (wchar);
    wchar = 0;
    while (len--)
    {
        wchar |= s[len] << lshift;
        lshift -= 8;
    }
    return (wchar);
}
