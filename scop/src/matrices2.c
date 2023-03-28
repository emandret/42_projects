/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:03:00 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 18:06:17 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void mat_multiply_internal(float dst[][4], const float src[][4])
{
    float  res[4][4];
    size_t n;
    size_t i;
    size_t j;
    size_t k;

    mat_clear(res);
    n = 0;
    while (n < 64)
    {
        i = n / 16;
        j = n / 4 % 4;
        k = n % 4;
        res[i][j] += dst[i][k] * src[k][j];
        n++;
    }
    mat_copy(dst, res);
}

void mat_multiply(size_t n, float mat[][4], ...)
{
    va_list ap;

    va_start(ap, mat);
    while (n > 1)
    {
        mat_multiply_internal(mat, ((float(*)[4]) va_arg(ap, void *)));
        n--;
    }
    va_end(ap);
}

void mat_scale(float mat[][4], t_vec4 scale_vector)
{
    float scale[4][4];

    mat_identity(scale);
    scale[0][0] = scale_vector.x;
    scale[1][1] = scale_vector.y;
    scale[2][2] = scale_vector.z;
    mat_multiply_internal(mat, scale);
}

void mat_translate(float mat[][4], t_vec4 translation_vector)
{
    float translate[4][4];

    mat_identity(translate);
    translate[3][0] = translation_vector.x;
    translate[3][1] = translation_vector.y;
    translate[3][2] = translation_vector.z;
    mat_multiply_internal(mat, translate);
}

void mat_rotate(float mat[][4], t_quat quaternion)
{
    float rotate[4][4];

    quat_to_matrix(rotate, quaternion);
    mat_multiply_internal(mat, rotate);
}
