/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/10/13 00:55:59 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

intmax_t pf_get_signed(t_format *format, va_list ap)
{
    if (format->modifier == M_NONE)
        return ((int) va_arg(ap, intmax_t));
    if (format->modifier == HH)
        return ((char) va_arg(ap, intmax_t));
    if (format->modifier == H)
        return ((short int) va_arg(ap, intmax_t));
    if (format->modifier == L)
        return ((long int) va_arg(ap, intmax_t));
    if (format->modifier == LL)
        return ((long long int) va_arg(ap, intmax_t));
    if (format->modifier == Z)
        return ((ssize_t) va_arg(ap, intmax_t));
    return (va_arg(ap, intmax_t));
}

uintmax_t pf_get_unsigned(t_format *format, va_list ap)
{
    if (format->modifier == M_NONE)
        return ((unsigned int) va_arg(ap, uintmax_t));
    if (format->modifier == HH)
        return ((unsigned char) va_arg(ap, uintmax_t));
    if (format->modifier == H)
        return ((unsigned short int) va_arg(ap, uintmax_t));
    if (format->modifier == L)
        return ((unsigned long int) va_arg(ap, uintmax_t));
    if (format->modifier == LL)
        return ((unsigned long long int) va_arg(ap, uintmax_t));
    if (format->modifier == Z)
        return ((size_t) va_arg(ap, uintmax_t));
    return (va_arg(ap, uintmax_t));
}

void pf_compute_num(t_format *format, int len)
{
    if (format->flags.zero_padding && format->precision > 0)
        format->flags.zero_padding = false;
    if (format->min_field <= len)
        format->min_field = 0;
    if (format->precision <= len)
        format->precision = 0;
    if (format->min_field > len)
        format->min_field -= len;
    if (format->precision > len)
        format->precision -= len;
    if (format->min_field <= format->precision)
        format->min_field = 0;
    if (format->min_field > format->precision)
        format->min_field -= format->precision;
    if (format->flags.zero_padding)
        format->precision = format->min_field;
}

void pf_compute_str(t_format *format, int len)
{
    if (!format->has_precision)
        format->precision = len;
    if (format->precision < len)
        format->min_field += len - format->precision;
    if (format->min_field < len)
        format->min_field -= format->precision;
    if (format->min_field <= len)
        format->min_field = 0;
    if (format->min_field > len)
        format->min_field -= len;
}
