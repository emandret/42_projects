/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/05/31 16:05:56 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

static int get_next_arg(const char *s, va_list ap)
{
    t_buffer  *buffer;
    t_format  *format;
    t_handler *handlers;
    int        ret;

    if (!(format = (t_format *) ft_memalloc(sizeof(t_format))) ||
        !(buffer = (t_buffer *) ft_memalloc(sizeof(t_buffer))) || !(handlers = pf_init_handlers()))
        return (-1);
    while (*s != '\0')
    {
        if (*s != '%')
            pf_buffer_putchar(buffer, *s++);
        if (*s == '%')
            ret = pf_dispatcher(buffer, pf_parser(&s, format, ap), ap, handlers);
    }
    if (ret != -1)
        ret = pf_buffer_write(buffer);
    ft_memdel((void **) &buffer);
    ft_memdel((void **) &format);
    ft_memdel((void **) &handlers);
    return (ret);
}

int ft_printf(const char *restrict format, ...)
{
    va_list ap;
    int     ret;

    va_start(ap, format);
    ret = get_next_arg(format, ap);
    va_end(ap);
    return (ret);
}
