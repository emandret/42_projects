/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_unicod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:29:31 by emandret          #+#    #+#             */
/*   Updated: 2017/04/20 00:02:20 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_printf.h"

void pf_buffer_putwchar(t_buffer *buffer, wchar_t c)
{
    if (c <= 0x7F)
        pf_buffer_putchar(buffer, c);
    else if (c <= 0x7FF)
    {
        pf_buffer_putchar(buffer, (c >> 6) + 0xC0);
        pf_buffer_putchar(buffer, (c & 0x3F) + 0x80);
    }
    else if (c <= 0xFFFF)
    {
        pf_buffer_putchar(buffer, (c >> 12) + 0xE0);
        pf_buffer_putchar(buffer, ((c >> 6) & 0x3F) + 0x80);
        pf_buffer_putchar(buffer, (c & 0x3F) + 0x80);
    }
    else if (c <= 0x10FFFF)
    {
        pf_buffer_putchar(buffer, (c >> 18) + 0xF0);
        pf_buffer_putchar(buffer, ((c >> 12) & 0x3F) + 0x80);
        pf_buffer_putchar(buffer, ((c >> 6) & 0x3F) + 0x80);
        pf_buffer_putchar(buffer, (c & 0x3F) + 0x80);
    }
}

void pf_buffer_putwnstr(t_buffer *buffer, wchar_t *s, int n)
{
    while (n-- > 0 && *s != L'\0')
        pf_buffer_putwchar(buffer, *s++);
}
