/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/21 18:50:49 by emandret          #+#    #+#             */
/*   Updated: 2017/05/31 16:06:41 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static void no_arg_output(t_buffer *buffer, t_format *format)
{
    format->min_field--;
    if (format->flags.space_left || format->flags.space_right)
        format->min_field--;
    pf_compute_num(format, 0);
    if (format->flags.space_left)
        pf_buffer_putchar(buffer, ' ');
    if (!format->flags.zero_padding && !format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
    pf_buffer_putnchar(buffer, '0', format->precision);
    if (!format->has_precision && !format->flags.zero_padding)
        pf_buffer_putchar(buffer, '0');
    if (format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
}

void pf_handle_uns(t_buffer *buffer, t_format *format, va_list ap)
{
    uintmax_t n;
    char     *s;

    if ((n = pf_get_unsigned(format, ap)))
    {
        s = ft_ultoa_base(n, 10);
        pf_compute_num(format, ft_strlen(s));
        if (!format->flags.zero_padding && !format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        pf_buffer_putnchar(buffer, '0', format->precision);
        pf_buffer_putstr(buffer, s);
        if (format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        ft_memdel((void **) &s);
    }
    else
        no_arg_output(buffer, format);
}
