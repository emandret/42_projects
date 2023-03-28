/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_modi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/25 20:08:14 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static t_modifier get_modi(const char *s)
{
    if (*s == 'h' && *(s + 1) == 'h')
        return (HH);
    if (*s == 'l' && *(s + 1) == 'l')
        return (LL);
    if (*s == 'h')
        return (H);
    if (*s == 'l')
        return (L);
    if (*s == 'j')
        return (J);
    if (*s == 'z')
        return (Z);
    return (M_NONE);
}

void pf_parse_modi(const char **s, t_format *format)
{
    format->modifier = get_modi(*s);
    if (format->modifier == HH || format->modifier == LL)
        *s += 2;
    else if (format->modifier != M_NONE)
        (*s)++;
}
