/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_md5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:40:04 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 02:49:09 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

static const uint8_t g_pad[64] = { 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                   0,    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static const uint32_t g_const[] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
                                    5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
                                    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
                                    6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };

static const uint32_t g_magic[] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613,
                                    0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193,
                                    0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d,
                                    0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
                                    0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122,
                                    0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
                                    0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244,
                                    0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
                                    0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb,
                                    0xeb86d391 };

uint32_t g_register[10];

static void md5_compress(size_t i, uint32_t x[16])
{
    if (i < 16)
    {
        RF5 = (RB1 & RC2) | ((~RB1) & RD3);
        RG6 = i;
    }
    else if (i < 32)
    {
        RF5 = (RD3 & RB1) | ((~RD3) & RC2);
        RG6 = (5 * i + 1) % 16;
    }
    else if (i < 48)
    {
        RF5 = RB1 ^ RC2 ^ RD3;
        RG6 = (3 * i + 5) % 16;
    }
    else
    {
        RF5 = RC2 ^ (RB1 | (~RD3));
        RG6 = (7 * i) % 16;
    }
    RT1 = RD3;
    RD3 = RC2;
    RC2 = RB1;
    RB1 = RB1 + ROTATE_LEFT((RA0 + RF5 + g_magic[i] + x[RG6]), g_const[i]);
    RA0 = RT1;
}

static void md5_transform(uint32_t state[4], uint8_t block[64])
{
    size_t   i;
    uint32_t x[16];

    decode_64bit_big_endian(x, block, 64);
    RA0 = state[0];
    RB1 = state[1];
    RC2 = state[2];
    RD3 = state[3];
    i   = 0;
    while (i < 64)
    {
        md5_compress(i, x);
        i++;
    }
    state[0] += RA0;
    state[1] += RB1;
    state[2] += RC2;
    state[3] += RD3;
}

/*
** MD5 block update operation. Continues an MD5 message-digest operation,
** processing another message block, and updating the context.
*/

void md5_update(t_md5 *context, uint8_t *input, size_t i_len)
{
    size_t i;
    size_t index;
    size_t part_len;

    index = (unsigned int) ((context->count[0] >> 3) & 0x3F);
    if ((context->count[0] += ((uint32_t) i_len << 3)) < ((uint32_t) i_len << 3))
        context->count[1]++;
    context->count[1] += ((uint32_t) i_len >> 29);
    if (i_len >= (part_len = 64 - index))
    {
        md5_memcpy((uint8_t *) &context->buffer[index], (uint8_t *) input, part_len);
        md5_transform(context->state, context->buffer);
        i = part_len;
        while (i + 63 < i_len)
        {
            md5_transform(context->state, &input[i]);
            i += 64;
        }
        index = 0;
    }
    else
        i = 0;
    md5_memcpy((uint8_t *) &context->buffer[index], (uint8_t *) &input[i], i_len - i);
}

/*
** MD5 finalization. Ends an MD5 message-digest operation, writing the the
** message digest and zeroizing the context.
*/

void md5_final(uint8_t digest[16], t_md5 *context)
{
    uint8_t bits[8];
    size_t  index;
    size_t  pad_len;

    encode_64bit_little_endian(bits, context->count, 8);
    index   = (unsigned int) ((context->count[0] >> 3) & 0x3f);
    pad_len = (index < 56) ? (56 - index) : (120 - index);
    md5_update(context, (uint8_t *) g_pad, pad_len);
    md5_update(context, bits, 8);
    encode_64bit_little_endian(digest, context->state, 16);
    md5_memset((uint8_t *) context, 0, sizeof(*context));
}
