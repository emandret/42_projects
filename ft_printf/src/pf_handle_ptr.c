/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/21 19:42:39 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

void pf_handle_ptr(t_buffer *buffer, t_format *format, va_list ap)
{
    char *s;

    s = ft_strtolower(ft_ultoa_base((intmax_t) va_arg(ap, void *), 16));
    format->min_field -= 2;
    pf_compute_num(format, ft_strlen(s));
    if (!format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
    if (!format->has_precision)
        pf_buffer_putstr(buffer, "0x");
    pf_buffer_putstr(buffer, s);
    if (format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
    ft_memdel((void **) &s);
}
