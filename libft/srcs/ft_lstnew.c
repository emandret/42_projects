/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 08:30:05 by emandret          #+#    #+#             */
/*   Updated: 2018/05/29 08:30:05 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list *ft_lstnew(const void *content, size_t content_size)
{
    t_list *new;

    if ((new = (t_list *) ft_memalloc(sizeof(t_list))))
    {
        new->content      = NULL;
        new->content_size = 0;
        new->next         = NULL;
        if (content)
        {
            if (!(new->content = ft_memalloc(content_size)))
                return (NULL);
            ft_memcpy(new->content, content, content_size);
            new->content_size = content_size;
        }
    }
    return (new);
}
