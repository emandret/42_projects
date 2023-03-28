/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_md5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:40:04 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:01:36 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Encodes input (uint32_t) into output (uint8_t).
** Assumes len is a multiple of 4.
*/

void encode_64bit_little_endian(uint8_t *output, uint32_t *input, size_t len)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (j < len)
    {
        output[j]     = (uint8_t) (input[i] & 0xff);
        output[j + 1] = (uint8_t) ((input[i] >> 8) & 0xff);
        output[j + 2] = (uint8_t) ((input[i] >> 16) & 0xff);
        output[j + 3] = (uint8_t) ((input[i] >> 24) & 0xff);
        i++;
        j += 4;
    }
}

/*
** Decodes input (uint8_t) into output (uint32_t).
** Assumes len is a multiple of 4.
*/

void decode_64bit_big_endian(uint32_t *output, uint8_t *input, size_t len)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (j < len)
    {
        output[i] = ((uint32_t) input[j]) | (((uint32_t) input[j + 1]) << 8) | (((uint32_t) input[j + 2]) << 16) |
                    (((uint32_t) input[j + 3]) << 24);
        i++;
        j += 4;
    }
}

/*
** Note: Replace "for loop" with standard memcpy if possible.
*/

void md5_memcpy(uint8_t *output, uint8_t *input, size_t len)
{
    size_t i;

    i = 0;
    while (i < len)
    {
        output[i] = input[i];
        i++;
    }
}

/*
** Note: Replace "for loop" with standard memset if possible.
*/

void md5_memset(uint8_t *output, int value, size_t len)
{
    size_t i;

    i = 0;
    while (i < len)
    {
        ((char *) output)[i] = (char) value;
        i++;
    }
}
