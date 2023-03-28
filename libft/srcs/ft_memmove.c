/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void *ft_memmove(void *dest, const void *src, size_t n)
{
    size_t i;

    i = -1;
    if ((char *) src < (char *) dest)
    {
        while ((int) (--n) >= 0)
            *((char *) dest + n) = *((char *) src + n);
    }
    else
    {
        while (++i < n)
            *((char *) dest + i) = *((char *) src + i);
    }
    return (dest);
}
