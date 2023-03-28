/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 02:43:57 by emandret          #+#    #+#             */
/*   Updated: 2019/01/16 03:58:30 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
#define FT_SSL_H

#include "ft_printf.h"
#include "ssl_types.h"
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

#define SHA256_MSG_BLOCK_SIZE 64
#define SHA256_HASH_SIZE 32

#define MD5_MSG_BLOCK_SIZE 64
#define MD5_HASH_SIZE 16

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

#define READ_BUFSIZE 10

#define FLAG_STDIN (1 << 0)
#define FLAG_PRINT (1 << 1)
#define FLAG_QUIET (1 << 2)
#define FLAG_REVERSE (1 << 3)
#define FLAG_STRING (1 << 4)

#define HEX_BASE "0123456789abcdef"

/*
** Registers AUTOMATA
*/
#define RA0 (g_register[0])
#define RB1 (g_register[1])
#define RC2 (g_register[2])
#define RD3 (g_register[3])
#define RE4 (g_register[4])
#define RF5 (g_register[5])
#define RG6 (g_register[6])
#define RH7 (g_register[7])

/*
** Registers TEMPORARY
*/
#define RT1 (g_register[8])
#define RT2 (g_register[9])

extern uint32_t g_register[];

typedef struct s_sha256
{
    uint32_t intermediate_hash[SHA256_HASH_SIZE / 4];
    uint32_t length_low;
    uint32_t length_high;
    uint16_t message_block_index;
    uint8_t  message_block[SHA256_MSG_BLOCK_SIZE];
    int      computed;
    int      corrupted;
} t_sha256;

typedef struct s_md5
{
    uint32_t state[4];
    uint32_t count[2];
    uint8_t  buffer[64];
} t_md5;

void parse_flags(int ac, char *av[], int *i, int *flags);

/*
** Message Digest commands
*/
int   md5_handler(int ac, char *av[]);
int   sha256_handler(int ac, char *av[]);
void  parse_flags(int ac, char *av[], int *i, int *flags);
void  read_stdin(int flags);
char *read_fd(const int fd);
char *hash2str(uint8_t *digest, const size_t hash_size);

#endif
