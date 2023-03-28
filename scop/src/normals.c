/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:07:42 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 17:08:39 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void compute_normals(t_mesh *mesh, t_indices face)
{
    t_vec4 pt[3];
    t_vec4 vn;

    face[0]--;
    face[1]--;
    face[2]--;
    pt[0] = gb_vec4(&mesh->v, face[0]);
    pt[1] = gb_vec4(&mesh->v, face[1]);
    pt[2] = gb_vec4(&mesh->v, face[2]);
    vn    = vec4_norm(vec4_cross(vec4_sub(pt[1], pt[0]), vec4_sub(pt[2], pt[0])));
    pt[0] = vec4_add(gb_vec4(&mesh->vn, face[0]), vn);
    pt[1] = vec4_add(gb_vec4(&mesh->vn, face[1]), vn);
    pt[2] = vec4_add(gb_vec4(&mesh->vn, face[2]), vn);
    gb_copy(&mesh->vn, face[0], &pt[0]);
    gb_copy(&mesh->vn, face[1], &pt[1]);
    gb_copy(&mesh->vn, face[2], &pt[2]);
}

void generate_normals(t_mesh *mesh, unsigned int faces[][3])
{
    size_t    i;
    t_indices face;
    t_vec4    vn;

    gb_init(&mesh->vn, sizeof(t_vec4), mesh->f.count * 100);
    i = 0;
    while (i < (mesh->f.count / 3))
    {
        face[0]             = faces[i * 3 + 0][0];
        face[1]             = faces[i * 3 + 1][0];
        face[2]             = faces[i * 3 + 2][0];
        faces[i * 3 + 0][2] = face[0];
        faces[i * 3 + 1][2] = face[1];
        faces[i * 3 + 2][2] = face[2];
        compute_normals(mesh, face);
        i++;
    }
    i = 0;
    while (i < mesh->f.count)
    {
        vn = vec4_norm(gb_vec4(&mesh->vn, faces[i][2] - 1));
        gb_copy(&mesh->vn, faces[i][2] - 1, &vn);
        i++;
    }
}
