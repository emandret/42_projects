/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sha256.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 02:17:13 by emandret          #+#    #+#             */
/*   Updated: 2019/01/15 23:11:10 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

void sha256_file(char *path, t_sha256_state *state)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd == -1)
        return;
    while ((state->ret = read(fd, &state->buf, 64)) == 64)
        sha256_update_state(state);
    if (state->ret == -1)
    {
        close(fd);
        return;
    }
    sha256_update_state(sha256_pad(state));
    close(fd);
}

void sha256_stdin(t_sha256_state *state, t_action action)
{
    while ((state->ret = read(0, &state->buf, 64)) == 64)
    {
        if (action == FROM_STDIN_P && state->ret)
            ft_putstr((char *) state->buf);
        sha256_update_state(state);
    }
    if (action == FROM_STDIN_P && state->ret)
        ft_putstr((char *) state->buf);
    sha256_update_state(sha256_pad(state));
}

void sha256_msg(char *msg, t_sha256_state *state)
{
    size_t copy_length;

    if (!*msg)
        sha256_update_state(sha256_pad(state));
    while (*msg)
    {
        copy_length = ft_strlen(msg) >= 64 ? 64 : ft_strlen(msg);
        ft_memcpy(state->buf, msg, copy_length);
        state->ret = copy_length;
        msg += copy_length;
        if (state->ret == 64)
            sha256_update_state(state);
        else
            sha256_update_state(sha256_pad(state));
        ft_bzero(state->buf, 64);
    }
}
