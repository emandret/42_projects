/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:20:56 by emandret          #+#    #+#             */
/*   Updated: 2019/01/10 14:55:51 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

float vec4_magnitude(t_vec4 vec)
{
    return (sqrtf(SQ(vec.x) + SQ(vec.y) + SQ(vec.z) + SQ(vec.w)));
}

t_vec4 vec4_norm(t_vec4 vec)
{
    t_vec4 res;
    float  mag;

    mag   = vec4_magnitude(vec);
    res.x = vec.x / mag;
    res.y = vec.y / mag;
    res.z = vec.z / mag;
    res.w = vec.w / mag;
    return (res);
}

t_vec4 vec4_add(t_vec4 v1, t_vec4 v2)
{
    t_vec4 res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    res.w = v1.w;
    return (res);
}

t_vec4 vec4_sub(t_vec4 v1, t_vec4 v2)
{
    t_vec4 res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    res.w = v1.w;
    return (res);
}
