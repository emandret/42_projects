/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strsub(const char *s, unsigned int start, size_t len)
{
    char *new;
    size_t i;

    if ((new = ft_strnew(len)))
    {
        i = 0;
        while (i < len)
        {
            new[i] = s[start + i];
            i++;
        }
        new[i] = '\0';
    }
    return (new);
}
