/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcsize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int ft_wcsize(wchar_t wc)
{
    if (wc <= 0x007F)
        return (1);
    if (wc <= 0x07FF)
        return (2);
    if (wc <= 0xFFFF)
        return (3);
    if (wc <= 0x10FFFF)
        return (4);
    return (0);
}
