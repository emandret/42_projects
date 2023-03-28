/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int count_bytes(const wchar_t *s)
{
    int i;

    i = 0;
    while (s[i++])
        ;
    return (i * sizeof(int));
}

void ft_putwstr_fd(const wchar_t *s, int fd)
{
    int     i;
    wchar_t ws[count_bytes(s)];

    i = 0;
    while (s[i])
    {
        ws[i] = ft_utf8_encode(s[i]);
        i++;
    }
    ws[i] = L'\0';
    write(fd, ws, i * sizeof(int));
}
