/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/25 20:05:52 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static void handle_escape(t_buffer *buffer, t_format *format)
{
    format->min_field--;
    if (!format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
    pf_buffer_putchar(buffer, '%');
    if (format->flags.space_right)
        pf_buffer_putnchar(buffer, ' ', format->min_field);
}

int pf_dispatcher(t_buffer *buffer, t_format *format, va_list ap, t_handler *handlers)
{
    int i;

    if (format->conversion == C_NONE)
        return (-1);
    if (format->conversion == ESC)
    {
        handle_escape(buffer, format);
        return (0);
    }
    i = 0;
    while (i < CONVERSION_NUMBER && format->conversion != ((t_conversion) i))
        i++;
    if (format->conversion == ((t_conversion) i))
        (*handlers[i])(buffer, format, ap);
    return (0);
}

t_handler *pf_init_handlers(void)
{
    t_handler *handlers;

    if (!(handlers = (t_handler *) ft_memalloc(sizeof(t_handler) * CONVERSION_NUMBER)))
        return (NULL);
    handlers[S]  = &pf_handle_str;
    handlers[SS] = &pf_handle_wstr;
    handlers[P]  = &pf_handle_ptr;
    handlers[D]  = &pf_handle_num;
    handlers[DD] = &pf_handle_num;
    handlers[I]  = &pf_handle_num;
    handlers[O]  = &pf_handle_oct;
    handlers[OO] = &pf_handle_oct;
    handlers[U]  = &pf_handle_uns;
    handlers[UU] = &pf_handle_uns;
    handlers[X]  = &pf_handle_hex;
    handlers[XX] = &pf_handle_hex;
    handlers[C]  = &pf_handle_chr;
    handlers[CC] = &pf_handle_wchr;
    return (handlers);
}
