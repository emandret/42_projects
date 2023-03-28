/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:38:55 by emandret          #+#    #+#             */
/*   Updated: 2017/04/21 19:00:34 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

void pf_handle_str(t_buffer *buffer, t_format *format, va_list ap)
{
    char *s;

    if ((s = (char *) va_arg(ap, char *)))
    {
        pf_compute_str(format, ft_strlen(s));
        if (!format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        pf_buffer_putnstr(buffer, s, format->precision);
        if (format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
    }
    else
        pf_buffer_putstr(buffer, "(null)");
}
