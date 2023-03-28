/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 23:30:57 by emandret          #+#    #+#             */
/*   Updated: 2017/05/31 16:05:07 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
#define FT_PRINTF_H

#include "pf_types.h"

int ft_printf(const char *restrict format, ...);

/*
** pf_parser
*/
t_format *pf_parser(const char **s, t_format *format, va_list ap);
void      pf_parse_flag(const char **s, t_format *format);
void      pf_parse_numb(const char **s, t_format *format, va_list ap);
void      pf_parse_modi(const char **s, t_format *format);
void      pf_parse_conv(const char **s, t_format *format);

/*
** pf_helper
*/
intmax_t  pf_get_signed(t_format *format, va_list ap);
uintmax_t pf_get_unsigned(t_format *format, va_list ap);
void      pf_compute_num(t_format *format, int len);
void      pf_compute_str(t_format *format, int len);

/*
** pf_buffer
*/
void pf_buffer_putchar(t_buffer *buffer, char c);
void pf_buffer_putnchar(t_buffer *buffer, char c, int n);
void pf_buffer_putstr(t_buffer *buffer, char *s);
void pf_buffer_putnstr(t_buffer *buffer, char *s, int n);
int  pf_buffer_write(t_buffer *buffer);

/*
** pf_unicod
*/
void pf_buffer_putwchar(t_buffer *buffer, wchar_t c);
void pf_buffer_putwnstr(t_buffer *buffer, wchar_t *s, int n);

/*
** pf_handle
*/
int        pf_dispatcher(t_buffer *buffer, t_format *format, va_list ap, t_handler *handlers);
t_handler *pf_init_handlers(void);
void       pf_handle_chr(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_esc(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_hex(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_num(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_uns(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_oct(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_ptr(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_str(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_wchr(t_buffer *buffer, t_format *format, va_list ap);
void       pf_handle_wstr(t_buffer *buffer, t_format *format, va_list ap);

#endif
