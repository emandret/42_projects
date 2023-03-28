/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/20 00:15:57 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

void pf_buffer_putchar(t_buffer *buffer, char c)
{
    if (buffer->i == (BUFF_SIZE - 1))
        pf_buffer_write(buffer);
    buffer->s[buffer->i] = c;
    buffer->ret++;
    buffer->i++;
}

void pf_buffer_putnchar(t_buffer *buffer, char c, int n)
{
    while (n-- > 0)
        pf_buffer_putchar(buffer, c);
}

void pf_buffer_putstr(t_buffer *buffer, char *s)
{
    while (*s != '\0')
        pf_buffer_putchar(buffer, *s++);
}

void pf_buffer_putnstr(t_buffer *buffer, char *s, int n)
{
    while (n-- > 0 && *s != '\0')
        pf_buffer_putchar(buffer, *s++);
}

int pf_buffer_write(t_buffer *buffer)
{
    buffer->s[buffer->i] = '\0';
    write(1, buffer->s, buffer->ret);
    buffer->i = 0;
    return (buffer->ret);
}
