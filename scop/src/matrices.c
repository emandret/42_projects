/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 19:03:00 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 18:42:40 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

void mat_clear(float mat[][4])
{
    memset(mat, 0, sizeof(float[4]) * 4);
}

void mat_copy(float dst[][4], const float src[][4])
{
    memcpy(dst, src, sizeof(float[4]) * 4);
}

void mat_identity(float mat[][4])
{
    mat_clear(mat);
    mat[0][0] = 1.0f;
    mat[1][1] = 1.0f;
    mat[2][2] = 1.0f;
    mat[3][3] = 1.0f;
}

void mat_add(float dst[][4], const float src[][4])
{
    size_t n;
    size_t i;
    size_t j;

    n = 0;
    while (n < 16)
    {
        i = n / 4 % 4;
        j = n % 4;
        dst[i][j] += src[i][j];
        n++;
    }
}

void mat_sub(float dst[][4], const float src[][4])
{
    size_t n;
    size_t i;
    size_t j;

    n = 0;
    while (n < 16)
    {
        i = n / 4 % 4;
        j = n % 4;
        dst[i][j] -= src[i][j];
        n++;
    }
}
