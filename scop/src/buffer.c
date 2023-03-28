/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 13:19:00 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 20:32:50 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void copy_vertex(t_mesh mesh, unsigned int face[], float *data)
{
    t_vec4 vec[3];
    float  gray;

    if (face[0])
    {
        vec[0] = gb_vec4(&mesh.v, face[0] - 1);
        memcpy(&data[0], &vec[0], FSIZE(3));
    }
    if (face[1])
    {
        vec[1] = gb_vec4(&mesh.vt, face[1] - 1);
        memcpy(&data[3], &vec[1], FSIZE(2));
    }
    if (face[2])
    {
        gray = (float) rand() / (float) RAND_MAX;
        memcpy(&data[5], &((float[]){ gray, gray, gray }), sizeof(float[3]));
        vec[2] = gb_vec4(&mesh.vn, face[2] - 1);
        memcpy(&data[8], &vec[2], FSIZE(3));
    }
}

static inline void fill_vbo(t_mesh mesh, float *data)
{
    unsigned int(*faces)[3];
    size_t i;

    faces = (unsigned int(*)[3]) mesh.f.start;
    i     = 0;
    while (i < mesh.f.count)
    {
        copy_vertex(mesh, faces[i++], data);
        data += VBO_VERTEX;
    }
}

static inline void configure_vbo(t_vbo *vbo)
{
    glGenVertexArrays(1, &vbo->vao);
    glBindVertexArray(vbo->vao);
    glGenBuffers(1, &vbo->id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->id);
    glBufferData(GL_ARRAY_BUFFER, FSIZE(vbo->size), vbo->data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VBO_STRIDE, VBO_OFFSET(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, VBO_STRIDE, VBO_OFFSET(3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VBO_STRIDE, VBO_OFFSET(5));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, VBO_STRIDE, VBO_OFFSET(8));
    glEnableVertexAttribArray(3);
}

t_vbo vbo_create(t_mesh mesh)
{
    t_vbo vbo;

    vbo.size = mesh.f.count * VBO_VERTEX;
    if (!(vbo.data = (float *) malloc(FSIZE(vbo.size))))
    {
        fprintf(stderr, "Failed to allocate VBO: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    memset(vbo.data, 0, FSIZE(vbo.size));
    fill_vbo(mesh, vbo.data);
    configure_vbo(&vbo);
    return (vbo);
}
