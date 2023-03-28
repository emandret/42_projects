/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_strcount(const char *s, const char *sub)
{
    int count;

    if (!s || !sub)
        return (0);
    count = 0;
    while (s)
    {
        if ((s = ft_strstr(s, sub)))
        {
            count++;
            s += ft_strlen(sub);
        }
    }
    return (count);
}
