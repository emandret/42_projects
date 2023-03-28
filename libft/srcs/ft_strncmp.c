/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    if (n < 1)
        return (0);
    i = 0;
    while (i < (n - 1) && (unsigned char) s1[i] == (unsigned char) s2[i] && (unsigned char) s1[i] &&
           (unsigned char) s2[i])
        i++;
    return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
