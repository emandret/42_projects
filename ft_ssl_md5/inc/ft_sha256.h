/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 02:43:57 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 04:00:48 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
#define FT_SHA256_H

#include "ft_ssl.h"

#define SHR(bits, w) ((w) >> (bits))
#define ROTL(bits, w) (((w) << (bits)) | ((w) >> (32 - (bits))))
#define ROTR(bits, w) (((w) >> (bits)) | ((w) << (32 - (bits))))

#define SHA_CH(x, y, z) (((x) & ((y) ^ (z))) ^ (z))
#define SHA_MAJ(x, y, z) (((x) & ((y) | (z))) | ((y) & (z)))
#define SHA_PARITY(x, y, z) ((x) ^ (y) ^ (z))

#define SHA256_BSIGMA0(w) (ROTR(2, w) ^ ROTR(13, w) ^ ROTR(22, w))
#define SHA256_BSIGMA1(w) (ROTR(6, w) ^ ROTR(11, w) ^ ROTR(25, w))
#define SHA256_SIGMA0(w) (ROTR(7, w) ^ ROTR(18, w) ^ SHR(3, w))
#define SHA256_SIGMA1(w) (ROTR(17, w) ^ ROTR(19, w) ^ SHR(10, w))

void sha256_pad(t_sha256 *context, uint8_t pad_byte);
void sha256_process(t_sha256 *context);
void sha256_init(t_sha256 *context);
int  sha256_result(t_sha256 *context, uint8_t digest[], int hash_size);
int  sha256_input(t_sha256 *context, const uint8_t *message_array, size_t length);

#endif
