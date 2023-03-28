/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_atoi(const char *nptr)
{
    int sign;
    int res;
    int i;

    sign = 1;
    res  = 0;
    i    = 0;
    while (ft_is_whitespace(nptr[i]))
        i++;
    if (nptr[i] == '-' || nptr[i] == '+')
    {
        if (nptr[i++] == '-')
            sign = -1;
    }
    while (nptr[i] >= '0' && nptr[i] <= '9')
        res = res * 10 + (nptr[i++] - '0');
    return (res * sign);
}
