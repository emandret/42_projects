/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 18:42:53 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 20:45:51 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
#define SCOP_H

#include "datatypes.h"
#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define WIN_WIDTH 1024
#define WIN_HEIGHT 768
#define WIN_TITLE "Scop"

#define SQ(n) ((n) * (n))
#define RAD(angle) ((angle) *M_PI / 180.0f)

#define FSIZE(n) (sizeof(float) * (n))

#define VBO_VERTEX 11
#define VBO_STRIDE FSIZE(VBO_VERTEX)
#define VBO_OFFSET(i) ((void *) FSIZE(i))

#define VEC4(x, y, z, w) ((t_vec4){ { (x) }, { (y) }, { (z) }, { (w) } })
#define X_AXIS VEC4(1.0f, 0.0f, 0.0f, 1.0f)
#define Y_AXIS VEC4(0.0f, 1.0f, 0.0f, 1.0f)
#define Z_AXIS VEC4(0.0f, 0.0f, 1.0f, 1.0f)

#define TOK_MARKER " \r\n"
#define MAX_LENGTH 1024
#define MAX_FACES 32
#define IS_EQUAL(s1, s2) (!strcmp((s1), (s2)))

/*
** Model min and max coordinates
*/
extern t_vec4 g_min;
extern t_vec4 g_max;
extern t_vec4 g_origin;

/*
** Mouse controls.
*/
extern t_scene g_scene;

/*
** The MVP matrices.
*/
extern float g_model[][4];
extern float g_view[][4];
extern float g_projection[][4];

/*
** growable.c
*/
void   gb_init(t_growable *gb, size_t data_size, size_t count);
void   gb_copy(t_growable *gb, size_t index, void *data);
void   gb_push(t_growable *gb, void *data);
t_vec4 gb_vec4(t_growable *gb, size_t index);

/*
** parser.c, parser2.c
*/
t_mesh parse_obj(const char *path);
void   parse_polyface(t_growable *f, char *line);

/*
** buffer.c
*/
t_vbo vbo_create(t_mesh mesh);

/*
** shaders.c
*/
unsigned int import_shaders(const char *vs_path, const char *fs_path);

/*
** texture.c
*/
unsigned int get_texture(const char *path);

/*
** normals.c
*/
void generate_normals(t_mesh *mesh, unsigned int faces[][3]);

/*
** vectors.c, vectors2.c
*/
float  vec4_magnitude(t_vec4 vec);
t_vec4 vec4_norm(t_vec4 vec);
t_vec4 vec4_add(t_vec4 v1, t_vec4 v2);
t_vec4 vec4_sub(t_vec4 v1, t_vec4 v2);
t_vec4 vec4_multiply(t_vec4 vec, const float scalar);
t_vec4 vec4_multiply_matrix(t_vec4 vec, const float mat[][4]);
float  vec4_dot(t_vec4 v1, t_vec4 v2);
t_vec4 vec4_cross(t_vec4 v1, t_vec4 v2);

/*
** matrices.c, matrices2.c, matrices3.c
*/
void mat_clear(float mat[][4]);
void mat_copy(float dst[][4], const float src[][4]);
void mat_identity(float mat[][4]);
void mat_add(float dst[][4], const float src[][4]);
void mat_sub(float dst[][4], const float src[][4]);
void mat_multiply(size_t n, float mat[][4], ...);
void mat_scale(float mat[][4], t_vec4 scale_vector);
void mat_translate(float mat[][4], t_vec4 translation_vector);
void mat_rotate(float mat[][4], t_quat quaternion);
void mat_add(float dst[][4], const float src[][4]);
void mat_sub(float dst[][4], const float src[][4]);
void mat_rotate_origin(float mat[][4], t_quat quaternion);
void mat_perspective(float mat[][4], float aspect_ratio, float near, float far);
void mat_look_at(float view[][4], t_vec4 eye, t_vec4 target, t_vec4 up);
void mat_mvp(void);

/*
** quaternions.c
*/
t_quat quat_create(float angle, t_vec4 rotation_axis);
t_quat quat_multiply(t_quat q1, t_quat q2);
void   quat_to_matrix(float mat[][4], t_quat quat);

/*
** window.c
*/
GLFWwindow *window_init_context(void);

/*
** callbacks.c, callbacks2.c
*/
void error_callback(int error, const char *description);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_input_callback(GLFWwindow *window);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

#endif
