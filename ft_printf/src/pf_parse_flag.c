/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/10/13 00:55:57 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static void enable_flag(const char **s, t_format *format)
{
    if (**s == '#' || **s == '0' || **s == '-' || **s == ' ' || **s == '+')
    {
        if (**s == '#')
            format->flags.convert = true;
        if (**s == '0')
            format->flags.zero_padding = true;
        if (**s == '-')
            format->flags.space_right = true;
        if (**s == ' ')
            format->flags.space_left = true;
        if (**s == '+')
            format->flags.enforce_sign = true;
        (*s)++;
        enable_flag(s, format);
    }
}

static void choose_flag(t_format *format)
{
    if (format->flags.space_right)
        format->flags.zero_padding = false;
    if (format->flags.enforce_sign)
        format->flags.space_left = false;
}

void pf_parse_flag(const char **s, t_format *format)
{
    format->flags.convert      = false;
    format->flags.zero_padding = false;
    format->flags.space_right  = false;
    format->flags.space_left   = false;
    format->flags.enforce_sign = false;
    enable_flag(s, format);
    choose_flag(format);
}
