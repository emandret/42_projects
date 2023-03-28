/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_conv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/25 20:07:41 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static t_conversion get_lower_conv(char c)
{
    if (c == 's')
        return (S);
    if (c == 'p')
        return (P);
    if (c == 'd')
        return (D);
    if (c == 'i')
        return (I);
    if (c == 'o')
        return (O);
    if (c == 'u')
        return (U);
    if (c == 'x')
        return (X);
    if (c == 'c')
        return (C);
    return (C_NONE);
}

static t_conversion get_upper_conv(char c)
{
    if (c == 'S')
        return (SS);
    if (c == 'C')
        return (CC);
    if (c == 'D')
        return (DD);
    if (c == 'O')
        return (OO);
    if (c == 'U')
        return (UU);
    if (c == 'X')
        return (XX);
    if (c == '%')
        return (ESC);
    return (C_NONE);
}

static t_conversion get_conv(char c)
{
    if (get_lower_conv(c) != C_NONE)
        return (get_lower_conv(c));
    if (get_upper_conv(c) != C_NONE)
        return (get_upper_conv(c));
    return (C_NONE);
}

void pf_parse_conv(const char **s, t_format *format)
{
    format->conversion = get_conv(**s);
    if (format->conversion != C_NONE)
        (*s)++;
}
