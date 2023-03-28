/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:18:56 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 14:28:53 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_quat quat_create(float angle, t_vec4 rotation_axis)
{
    float  sin_a;
    t_quat quat;

    sin_a  = sin(angle / 2.0f);
    quat.x = rotation_axis.x * sin_a;
    quat.y = rotation_axis.y * sin_a;
    quat.z = rotation_axis.z * sin_a;
    quat.w = cos(angle / 2.0f);
    return (vec4_norm(quat));
}

t_quat quat_multiply(t_quat q1, t_quat q2)
{
    t_quat res;

    res.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
    res.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
    res.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
    res.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
    return (vec4_norm(res));
}

void quat_to_matrix(float mat[][4], t_quat quat)
{
    mat_identity(mat);
    mat[0][0] = 1.0f - 2.0f * (SQ(quat.y) + SQ(quat.z));
    mat[0][1] = 2.0f * (quat.x * quat.y - quat.w * quat.z);
    mat[0][2] = 2.0f * (quat.x * quat.z + quat.w * quat.y);
    mat[1][0] = 2.0f * (quat.x * quat.y + quat.w * quat.z);
    mat[1][1] = 1.0f - 2.0f * (SQ(quat.x) + SQ(quat.z));
    mat[1][2] = 2.0f * (quat.y * quat.z - quat.w * quat.x);
    mat[2][0] = 2.0f * (quat.x * quat.z - quat.w * quat.y);
    mat[2][1] = 2.0f * (quat.y * quat.z + quat.w * quat.x);
    mat[2][2] = 1.0f - 2.0f * (SQ(quat.x) + SQ(quat.y));
}
