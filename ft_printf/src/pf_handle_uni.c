/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_uni.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/21 18:40:20 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

void pf_handle_wchr(t_buffer *buffer, t_format *format, va_list ap)
{
    wchar_t c;

    format->min_field--;
    if ((c = (wchar_t) va_arg(ap, wchar_t)))
    {
        if (!format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        pf_buffer_putwchar(buffer, c);
        if (format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
    }
    else
    {
        if (!format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        pf_buffer_putchar(buffer, '\0');
        if (format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
    }
}

void pf_handle_wstr(t_buffer *buffer, t_format *format, va_list ap)
{
    wchar_t *s;

    if ((s = (wchar_t *) va_arg(ap, wchar_t *)))
    {
        pf_compute_str(format, ft_wstrlen(s));
        if (!format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        pf_buffer_putwnstr(buffer, s, format->precision);
        if (format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
    }
    else
        pf_buffer_putstr(buffer, "(null)");
}
