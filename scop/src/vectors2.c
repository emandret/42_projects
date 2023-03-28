/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:23:14 by emandret          #+#    #+#             */
/*   Updated: 2019/01/10 15:37:28 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec4 vec4_multiply(t_vec4 vec, const float scalar)
{
    t_vec4 res;

    res.x = vec.x * scalar;
    res.y = vec.y * scalar;
    res.z = vec.z * scalar;
    res.w = vec.w * scalar;
    return (res);
}

t_vec4 vec4_multiply_matrix(t_vec4 vec, const float mat[][4])
{
    t_vec4 res;

    res.x = mat[0][0] * vec.x + mat[1][0] * vec.y + mat[2][0] * vec.z + mat[3][0] * vec.w;
    res.y = mat[0][1] * vec.x + mat[1][1] * vec.y + mat[2][1] * vec.z + mat[3][1] * vec.w;
    res.z = mat[0][2] * vec.x + mat[1][2] * vec.y + mat[2][2] * vec.z + mat[3][2] * vec.w;
    res.w = mat[0][3] * vec.x + mat[1][3] * vec.y + mat[2][3] * vec.z + mat[3][3] * vec.w;
    return (res);
}

float vec4_dot(t_vec4 v1, t_vec4 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec4 vec4_cross(t_vec4 v1, t_vec4 v2)
{
    t_vec4 res;

    res.x = v1.y * v2.z - v1.z * v2.y;
    res.y = v1.z * v2.x - v1.x * v2.z;
    res.z = v1.x * v2.y - v1.y * v2.x;
    res.w = v1.w;
    return (res);
}
