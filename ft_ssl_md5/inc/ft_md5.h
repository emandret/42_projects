/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 02:43:57 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:53:59 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
#define FT_MD5_H

#include "ft_ssl.h"

void encode_64bit_little_endian(uint8_t *output, uint32_t *input, size_t len);

void decode_64bit_big_endian(uint32_t *output, uint8_t *input, size_t len);
void md5_memcpy(uint8_t *output, uint8_t *input, size_t len);
void md5_memset(uint8_t *output, int value, size_t len);

void md5_update(t_md5 *context, uint8_t *input, size_t i_len);
void md5_final(uint8_t digest[16], t_md5 *context);

#endif
