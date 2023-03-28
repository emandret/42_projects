/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datatypes.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:23:17 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 20:04:52 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATATYPES_H
#define DATATYPES_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

/*
** Each face vertex is represented by three indices.
*/
typedef unsigned int t_indices[3];

/*
** The OpenGL Vertex Buffer Object to render vertices on screen.
*/
typedef struct s_vbo
{
    unsigned int vao;
    unsigned int id;
    size_t       size;
    float       *data;
} t_vbo;

/*
** The SHader Program structure which stores uniform identifiers.
*/
typedef struct s_shp
{
    unsigned int id;
    unsigned int texture;
    unsigned int texture_level;
    unsigned int model;
    unsigned int view;
    unsigned int projection;
    unsigned int light_pos;
    unsigned int normal_tint;
} t_shp;

/*
** The scene global settings.
*/
typedef struct s_scene
{
    bool  user_rotate;
    bool  auto_rotate;
    bool  do_roll;
    bool  texture;
    bool  wireframe;
    bool  normal_tint;
    float fov_angle;
} t_scene;

/*
** A growable array for storing the mesh data.
*/
typedef struct s_growable
{
    void  *start;
    void  *end;
    size_t data_size;
    size_t count;
} t_growable;

/*
** The mesh is the parsed data from the .obj file.
*/
typedef struct s_mesh
{
    t_growable v;
    t_growable vt;
    t_growable vn;
    t_growable f;
} t_mesh;

/*
** A 4D vector type used for representing coordinates and colors.
*/
typedef struct s_vec4
{
    union
    {
        float x;
        float u;
        float r;
    };
    union
    {
        float y;
        float v;
        float g;
    };
    union
    {
        float z;
        float b;
    };
    union
    {
        float w;
        float a;
    };
} t_vec4;

/*
** A quaternion is a 4D hypercomplex number which represent a rotation in 3D.
*/
typedef t_vec4 t_quat;

/*
** The bitmap file header contains the general informations about an image.
*/
typedef struct s_bmp_hdr
{
    uint8_t  type[2];
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t offbits;
} __attribute__((__packed__)) t_bmp_hdr;

/*
** The Device Independent Bitmap or DIB contains the detailed informations
** about the image and define the pixel format.
*/
typedef struct s_bmp_dib
{
    uint32_t size;
    uint32_t width;
    uint32_t height;
    uint16_t planes;
    uint16_t bitcount;
    uint32_t compression;
    uint32_t size_image;
    uint32_t x_pels_per_meter;
    uint32_t y_pels_per_meter;
    uint32_t clr_used;
    uint32_t clr_important;
} __attribute__((__packed__)) t_bmp_dib;

/*
** The color table defines the color used by the image.
*/
typedef struct s_bmp_rgb
{
    uint32_t r;
    uint32_t g;
    uint32_t b;
} __attribute__((__packed__)) t_bmp_rgb;

#endif
