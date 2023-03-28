/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/10/07 05:50:41 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static void no_arg_output(t_buffer *buffer, t_format *format)
{
    format->min_field--;
    if (format->flags.enforce_sign || format->flags.space_left || format->flags.space_right)
        format->min_field--;
    pf_compute_num(format, 0);
    if (format->flags.space_left)
        pf_buffer_putchar(buffer, ' ');
    if (!format->flags.zero_padding && !format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
    if (format->flags.enforce_sign)
        pf_buffer_putchar(buffer, '+');
    if (!format->has_precision && !format->flags.zero_padding)
        format->precision++;
    pf_buffer_putnchar(buffer, '0', format->precision);
    if (format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
}

static void putsign(t_format *format, t_buffer *buffer, bool is_neg)
{
    if (format->flags.enforce_sign && !is_neg)
        pf_buffer_putchar(buffer, '+');
    if (is_neg)
        pf_buffer_putchar(buffer, '-');
}

static char *num_ltoa(intmax_t n)
{
    if (n < LONG_MIN || n > LONG_MAX)
        return (ft_strdup("9223372036854775808"));
    return (ft_ltoa_base(n, 10));
}

void pf_handle_num(t_buffer *buffer, t_format *format, va_list ap)
{
    intmax_t n;
    char    *s;

    if ((n = pf_get_signed(format, ap)))
    {
        s = num_ltoa(ABS(n));
        if (format->flags.enforce_sign || n < 0)
            format->min_field--;
        pf_compute_num(format, ft_strlen(s));
        if (!(format->flags.enforce_sign || n < 0) && (format->flags.zero_padding || format->flags.space_left))
            format->min_field--;
        if (format->flags.space_left && n >= 0)
            pf_buffer_putchar(buffer, ' ');
        if (!format->flags.zero_padding && !format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        putsign(format, buffer, n < 0);
        pf_buffer_putnchar(buffer, '0', format->precision);
        pf_buffer_putstr(buffer, s);
        if (format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        ft_memdel((void **) &s);
    }
    else
        no_arg_output(buffer, format);
}
