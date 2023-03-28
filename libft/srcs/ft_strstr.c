/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strstr(const char *big, const char *little)
{
    unsigned int i;
    unsigned int pos;
    size_t       len;

    i   = 0;
    len = ft_strlen(little);
    if (len == 0)
        return ((char *) big);
    while (big[i])
    {
        pos = 0;
        while (little[pos] == big[pos + i])
        {
            if (pos == (len - 1))
                return ((char *) big + i);
            pos++;
        }
        i++;
    }
    return (NULL);
}
