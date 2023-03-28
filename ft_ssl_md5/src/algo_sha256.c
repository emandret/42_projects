/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_sha256.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 02:17:13 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:37:32 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

static const uint32_t g_k[64] = { 0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4,
                                  0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe,
                                  0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f,
                                  0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
                                  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
                                  0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
                                  0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116,
                                  0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
                                  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7,
                                  0xc67178f2 };

static void sha256_compress(t_sha256 *context, uint32_t w[])
{
    int t;

    t = 0;
    while (t < 64)
    {
        RT1 = RH7 + SHA256_BSIGMA1(RE4) + SHA_CH(RE4, RF5, RG6) + g_k[t] + w[t];
        RT2 = SHA256_BSIGMA0(RA0) + SHA_MAJ(RA0, RB1, RC2);
        RH7 = RG6;
        RG6 = RF5;
        RF5 = RE4;
        RE4 = RD3 + RT1;
        RD3 = RC2;
        RC2 = RB1;
        RB1 = RA0;
        RA0 = RT1 + RT2;
        t++;
    }
    context->intermediate_hash[0] += RA0;
    context->intermediate_hash[1] += RB1;
    context->intermediate_hash[2] += RC2;
    context->intermediate_hash[3] += RD3;
    context->intermediate_hash[4] += RE4;
    context->intermediate_hash[5] += RF5;
    context->intermediate_hash[6] += RG6;
    context->intermediate_hash[7] += RH7;
}

void sha256_process(t_sha256 *context)
{
    int      t;
    int      t4;
    uint32_t w[64];

    t  = 0;
    t4 = 0;
    while (t < 16)
    {
        w[t++] = (((uint32_t) context->message_block[t4]) << 24) | (((uint32_t) context->message_block[t4 + 1]) << 16) |
                 (((uint32_t) context->message_block[t4 + 2]) << 8) | (((uint32_t) context->message_block[t4 + 3]));
        t4 += 4;
    }
    t = 16;
    while (t < 64)
    {
        w[t] = SHA256_SIGMA1(w[t - 2]) + w[t - 7] + SHA256_SIGMA0(w[t - 15]) + w[t - 16];
        t++;
    }
    ft_memcpy(&RA0, &context->intermediate_hash[0], sizeof(uint32_t) * ((&RH7 - &RA0) + 1));
    sha256_compress(context, w);
    context->message_block_index = 0;
}

void sha256_pad(t_sha256 *context, uint8_t pad_byte)
{
    if (context->message_block_index >= (SHA256_MSG_BLOCK_SIZE - 8))
    {
        context->message_block[context->message_block_index++] = pad_byte;
        while (context->message_block_index < SHA256_MSG_BLOCK_SIZE)
            context->message_block[context->message_block_index++] = 0;
        sha256_process(context);
    }
    else
        context->message_block[context->message_block_index++] = pad_byte;
    while (context->message_block_index < (SHA256_MSG_BLOCK_SIZE - 8))
        context->message_block[context->message_block_index++] = 0;
    context->message_block[56] = (uint8_t) (context->length_high >> 24);
    context->message_block[57] = (uint8_t) (context->length_high >> 16);
    context->message_block[58] = (uint8_t) (context->length_high >> 8);
    context->message_block[59] = (uint8_t) (context->length_high);
    context->message_block[60] = (uint8_t) (context->length_low >> 24);
    context->message_block[61] = (uint8_t) (context->length_low >> 16);
    context->message_block[62] = (uint8_t) (context->length_low >> 8);
    context->message_block[63] = (uint8_t) (context->length_low);
    sha256_process(context);
}
