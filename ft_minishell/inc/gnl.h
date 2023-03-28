/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:23:11 by emandret          #+#    #+#             */
/*   Updated: 2017/08/22 07:52:39 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
#define GNL_H

#define GNL_BUFF_SIZE 32

#include "../libft/src/printf/inc/ft_printf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_this
{
    int            fd;
    char          *left;
    struct s_this *next;
} t_this;

int get_next_line(const int fd, char **line);

#endif
