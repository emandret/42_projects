/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/21 19:01:16 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

void pf_handle_chr(t_buffer *buffer, t_format *format, va_list ap)
{
    unsigned char c;

    format->min_field--;
    if ((c = (unsigned char) va_arg(ap, int)))
    {
        if (!format->flags.space_right)
            pf_buffer_putnchar(buffer, ' ', format->min_field);
        pf_buffer_putchar(buffer, c);
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
