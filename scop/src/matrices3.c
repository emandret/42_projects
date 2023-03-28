/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 18:23:28 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 19:30:53 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Create the affine transformation to rotate the object around its own center.
*/

void mat_rotate_origin(float mat[][4], t_quat quaternion)
{
    mat_translate(mat, vec4_multiply(g_origin, -1));
    mat_rotate(mat, quaternion);
    mat_translate(mat, g_origin);
}

/*
** Create the perspective matrix which modifies each vertex position to create
** a realistic perspective effect.
*/

void mat_perspective(float mat[][4], float aspect_ratio, float near, float far)
{
    float half_fov_tan;

    mat_clear(mat);
    half_fov_tan = tan(RAD(g_scene.fov_angle)) / 2;
    mat[0][0]    = 1 / (half_fov_tan * aspect_ratio);
    mat[1][1]    = 1 / (half_fov_tan);
    mat[2][2]    = -(far + near) / (far - near);
    mat[2][3]    = -1;
    mat[3][2]    = -(2 * far * near) / (far - near);
}

/*
** Align the view matrix according to the camera eye vector and the model
** target vector, each relative to the world up vector.
*/

void mat_look_at(float view[][4], t_vec4 eye, t_vec4 target, t_vec4 up)
{
    t_vec4 vecz;
    t_vec4 vecx;
    t_vec4 vecy;

    vecz = vec4_norm(vec4_sub(eye, target));
    vecx = vec4_norm(vec4_cross(up, vecz));
    vecy = vec4_cross(vecz, vecx);
    mat_identity(view);
    memcpy(&view[0], ((float[]){ vecx.x, vecy.x, vecz.x }), sizeof(float[3]));
    memcpy(&view[1], ((float[]){ vecx.y, vecy.y, vecz.y }), sizeof(float[3]));
    memcpy(&view[2], ((float[]){ vecx.z, vecy.z, vecz.z }), sizeof(float[3]));
    view[3][0] = -vec4_dot(vecx, eye);
    view[3][1] = -vec4_dot(vecy, eye);
    view[3][2] = -vec4_dot(vecz, eye);
}

/*
** Initialize the MVP.
*/

void mat_mvp(void)
{
    float scale;

    mat_identity(g_model);
    mat_translate(g_model,
                  VEC4(-(g_min.x + (fabsf(g_max.x - g_min.x) / 2)),
                       -(g_min.y + (fabsf(g_max.y - g_min.y) / 2)),
                       -(g_min.z + (fabsf(g_max.z - g_min.z) / 2)),
                       1.0f));
    scale = 1.0f / fmax(fmax(g_max.y, g_max.x), g_max.z);
    mat_scale(g_model, VEC4(scale, scale, scale, 1.0f));
    mat_identity(g_view);
    mat_look_at(g_view, VEC4(0.0f, 0.0f, 10.0f, 1.0f), VEC4(0.0f, 0.0f, 0.0f, 1.0f), VEC4(0.0f, 1.0f, 0.0f, 1.0f));
    g_scene.fov_angle = 45.0f;
    mat_perspective(g_projection, ((float) WIN_WIDTH / (float) WIN_HEIGHT), 0.1f, 100.0f);
}
