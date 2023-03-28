/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_sha256.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 02:17:13 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:53:08 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

static uint32_t g_h0[SHA256_HASH_SIZE / 4] = { 0x6A09E667, 0xBB67AE85, 0x3C6EF372, 0xA54FF53A,
                                               0x510E527F, 0x9B05688C, 0x1F83D9AB, 0x5BE0CD19 };

static void sha256_finalize(t_sha256 *context, uint8_t pad_byte)
{
    int i;

    sha256_pad(context, pad_byte);
    i = 0;
    while (i < SHA256_MSG_BLOCK_SIZE)
        context->message_block[i++] = 0;
    context->length_low  = 0;
    context->length_high = 0;
    context->computed    = 1;
}

void sha256_init(t_sha256 *context)
{
    if (!context)
        return;
    context->length_low          = 0;
    context->length_high         = 0;
    context->message_block_index = 0;
    ft_memcpy(context->intermediate_hash, g_h0, sizeof(uint32_t) * 8);
    context->computed  = 0;
    context->corrupted = 0;
}

int sha256_result(t_sha256 *context, uint8_t digest[], int hash_size)
{
    int i;

    if (!context || !digest)
        return (0);
    if (context->corrupted)
        return (context->corrupted);
    if (!context->computed)
        sha256_finalize(context, 0x80);
    i = 0;
    while (i < hash_size)
    {
        digest[i] = (uint8_t) (context->intermediate_hash[i >> 2] >> 8 * (3 - (i & 0x03)));
        i++;
    }
    return (1);
}

static bool sha256_add_length(t_sha256 *context, size_t length)
{
    uint32_t add_tmp;

    add_tmp            = context->length_low;
    context->corrupted = ((context->length_low += length) < add_tmp) && (++(context)->length_high == 0);
    return (context->corrupted);
}

int sha256_input(t_sha256 *context, const uint8_t *message_array, size_t length)
{
    if (!length)
        return (1);
    if (!context || !message_array)
        return (0);
    if (context->computed)
    {
        context->corrupted = -1;
        return (-1);
    }
    if (context->corrupted)
        return (context->corrupted);
    while (length-- && !context->corrupted)
    {
        context->message_block[context->message_block_index++] = (*message_array & 0xFF);
        if (!sha256_add_length(context, 8) && (context->message_block_index == SHA256_MSG_BLOCK_SIZE))
            sha256_process(context);
        message_array++;
    }
    return (1);
}
