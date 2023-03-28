/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 10:52:49 by emandret          #+#    #+#             */
/*   Updated: 2016/12/10 23:39:59 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_bool build_list(t_tetri **first_node, t_tetri **current_node, char *buf)
{
    t_tetri *tmp;
    t_tetri *new_node;

    if (check_square(buf) && check_adja((new_node = parse(buf))))
    {
        if (*first_node == NULL)
        {
            *first_node         = new_node;
            *current_node       = *first_node;
            (*current_node)->id = 1;
        }
        else
        {
            (*current_node)->next = new_node;
            tmp                   = *current_node;
            *current_node         = (*current_node)->next;
            (*current_node)->id   = tmp->id + 1;
            (*current_node)->prev = tmp;
        }
        return (true);
    }
    return (false);
}

t_bool read_file(int fd, char *buf, t_tetri **first_node)
{
    size_t   red;
    t_tetri *current_node;

    current_node = NULL;
    while ((red = read(fd, buf, BUF_SIZE)) == BUF_SIZE)
    {
        buf[BUF_SIZE - 1] = '\0';
        if (!build_list(first_node, &current_node, buf))
            return (false);
    }
    if (red == (BUF_SIZE - 1))
    {
        if (!build_list(first_node, &current_node, buf))
            return (false);
    }
    else
        return (false);
    return (true);
}

t_tetri *open_file(char *path)
{
    int      fd;
    char    *buf;
    t_tetri *first_node;

    first_node = NULL;
    if ((buf = ft_strnew(BUF_SIZE)))
        if ((fd = open(path, O_RDONLY)))
            if (!read_file(fd, buf, &first_node))
                return (NULL);
    return (first_node);
}
