/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int ft_memcmp(const void *s1, const void *s2, size_t n)
{
    size_t i;

    if (s1 == s2 || n == 0)
        return (0);
    i = 0;
    while (i < n)
    {
        if (((const unsigned char *) s1)[i] != ((const unsigned char *) s2)[i])
        {
            return (((const unsigned char *) s1)[i] - ((const unsigned char *) s2)[i]);
        }
        i++;
    }
    return (0);
}
