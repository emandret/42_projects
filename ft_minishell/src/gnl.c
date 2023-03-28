/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:23:11 by emandret          #+#    #+#             */
/*   Updated: 2017/08/22 07:53:47 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/gnl.h"

static t_bool has_newline(t_this *this, char **line, char **concat)
{
    char *cut;

    if (this->left != NULL && (cut = ft_strchr(this->left, '\n')))
    {
        *cut       = '\0';
        *line      = this->left;
        this->left = ft_strdup(cut + 1);
        return (TRUE);
    }
    *concat = ft_strnew(0);
    if (this->left != NULL)
    {
        *concat = ft_strjoin_free(*concat, this->left);
        ft_memdel((void **) &this->left);
    }
    return (FALSE);
}

static char *cut_after_endl(char *buffer, char **concat)
{
    char *cut;

    if ((cut = ft_strchr(buffer, '\n')))
    {
        *cut    = '\0';
        *concat = ft_strjoin_free(*concat, buffer);
        return (ft_strdup(cut + 1));
    }
    *concat = ft_strjoin_free(*concat, buffer);
    return (NULL);
}

static ssize_t read_until_endl(t_this *this, char **line)
{
    char   *buffer;
    char   *concat;
    ssize_t ret;

    if (has_newline(this, line, &concat))
        return (1);
    buffer = ft_strnew(GNL_BUFF_SIZE);
    while ((ret = read(this->fd, buffer, GNL_BUFF_SIZE)) > 0)
    {
        buffer[ret] = '\0';
        if ((this->left = cut_after_endl(buffer, &concat)))
            break;
    }
    ft_memdel((void **) &buffer);
    if (ret > 0 || *concat != '\0')
    {
        *line = concat;
        return (1);
    }
    ft_memdel((void **) &concat);
    if (ret < 0)
        return (-1);
    return (0);
}

static t_this *load_new_fd(const int fd, t_this *first)
{
    t_this *new;

    if (!(new = (t_this *) ft_memalloc(sizeof(t_this))))
        return (NULL);
    new->fd   = fd;
    new->left = NULL;
    new->next = NULL;
    if (first == NULL)
        return (new);
    new->next = first;
    return (new);
}

int get_next_line(const int fd, char **line)
{
    static t_this *first = NULL;
    t_this *this;

    if (fd < 0 || line == NULL)
        return (-1);
    if (first != NULL)
    {
        this = first;
        while (this->next != NULL && this->fd != fd)
            this = this->next;
        if (this->fd == fd)
            return (read_until_endl(this, line));
    }
    if ((first = load_new_fd(fd, first)))
        return (read_until_endl(first, line));
    return (-1);
}
