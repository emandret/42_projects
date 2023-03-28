/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:55:08 by emandret          #+#    #+#             */
/*   Updated: 2023/03/28 15:55:14 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool         has_newline(t_saved_fds *this_fd, char **line, char **concat);
static char        *cut_after_newline(char *buffer, char **concat);
static ssize_t      read_until_newline(t_saved_fds *this_fd, char **line);
static t_saved_fds *save_new_fd(const int fd, t_saved_fds *first);

static bool has_newline(t_saved_fds *this_fd, char **line, char **concat)
{
    char *cut;

    if (this_fd->buf_ptr != NULL && (cut = ft_strchr(this_fd->buf_ptr, '\n')))
    {
        *cut             = '\0';
        *line            = this_fd->buf_ptr;
        this_fd->buf_ptr = ft_strdup(cut + 1);
        return (true);
    }
    *concat = ft_strnew(0);
    if (this_fd->buf_ptr != NULL)
    {
        *concat = ft_strjoin_free(*concat, this_fd->buf_ptr);
        ft_memdel((void **) &this_fd->buf_ptr);
    }
    return (false);
}

static char *cut_after_newline(char *buffer, char **concat)
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

static ssize_t read_until_newline(t_saved_fds *this_fd, char **line)
{
    char   *buffer;
    char   *concat;
    ssize_t ret;

    if (has_newline(this_fd, line, &concat))
        return (1);
    buffer = ft_strnew(GNL_BUF_SIZE);
    while ((ret = read(this_fd->fd, buffer, GNL_BUF_SIZE)) > 0)
    {
        buffer[ret] = '\0';
        if ((this_fd->buf_ptr = cut_after_newline(buffer, &concat)))
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

static t_saved_fds *save_new_fd(const int fd, t_saved_fds *first)
{
    t_saved_fds *new;

    if (!(new = (t_saved_fds *) ft_memalloc(sizeof(t_saved_fds))))
        return (NULL);
    new->fd      = fd;
    new->buf_ptr = NULL;
    new->next    = NULL;
    if (first == NULL)
        return (new);
    new->next = first;
    return (new);
}

int ft_get_next_line(const int fd, char **line)
{
    static t_saved_fds *first = NULL;
    t_saved_fds        *this_fd;

    if (fd < 0 || line == NULL)
        return (-1);
    if (first != NULL)
    {
        this_fd = first;
        while (this_fd->next != NULL && this_fd->fd != fd)
            this_fd = this_fd->next;
        if (this_fd->fd == fd)
            return (read_until_newline(this_fd, line));
    }
    if ((first = save_new_fd(fd, first)))
        return (read_until_newline(first, line));
    return (-1);
}
