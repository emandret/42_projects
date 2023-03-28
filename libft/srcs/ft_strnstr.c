/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnstr(const char *big, const char *little, size_t len)
{
    unsigned int i;
    unsigned int pos;
    size_t       slen;

    i    = 0;
    slen = ft_strlen(little);
    if (slen == 0)
        return ((char *) big);
    while (big[i] && (slen + i) <= len)
    {
        pos = 0;
        while (little[pos] == big[pos + i])
        {
            if (pos == (slen - 1))
                return ((char *) big + i);
            pos++;
        }
        i++;
    }
    return (NULL);
}
