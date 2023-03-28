/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 21:45:23 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 21:21:14 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline float ftok(char **line)
{
    char *tok;

    if (!(tok = strsep(line, TOK_MARKER)) || !*tok)
    {
        fprintf(stderr, "Error: cannot parse vertex\n");
        exit(EXIT_FAILURE);
    }
    return (atof(tok));
}

static inline void parse_position(t_growable *gb, char *line)
{
    t_vec4 pos;

    pos     = VEC4(ftok(&line), ftok(&line), ftok(&line), 1.0f);
    g_min.x = fmin(g_min.x, pos.x);
    g_max.x = fmax(g_max.x, pos.x);
    g_min.y = fmin(g_min.y, pos.y);
    g_max.y = fmax(g_max.y, pos.y);
    g_min.z = fmin(g_min.z, pos.z);
    g_max.z = fmax(g_max.z, pos.z);
    gb_push(gb, &pos);
}

static inline void parse_line(t_mesh *m, char *line)
{
    char *tok;

    if ((tok = strsep(&line, TOK_MARKER)) && *tok)
    {
        if (IS_EQUAL(tok, "v"))
            parse_position(&m->v, line);
        else if (IS_EQUAL(tok, "vt"))
            gb_push(&m->vt, &VEC4(ftok(&line), ftok(&line), 0.0f, 1.0f));
        else if (IS_EQUAL(tok, "vn"))
            gb_push(&m->vn, &VEC4(ftok(&line), ftok(&line), ftok(&line), 1.0f));
        else if (IS_EQUAL(tok, "f"))
            parse_polyface(&m->f, line);
    }
}

t_mesh parse_obj(const char *path)
{
    FILE  *file;
    t_mesh mesh;
    char   line[MAX_LENGTH];

    if (!(file = fopen(path, "r")))
    {
        perror(path);
        exit(EXIT_FAILURE);
    }
    memset(&mesh, 0, sizeof(mesh));
    gb_init(&mesh.v, sizeof(t_vec4), 8);
    gb_init(&mesh.vt, sizeof(t_vec4), 8);
    gb_init(&mesh.vn, sizeof(t_vec4), 8);
    gb_init(&mesh.f, sizeof(t_indices), 24);
    while (fgets(line, MAX_LENGTH, file))
        parse_line(&mesh, line);
    if (!mesh.vn.start)
        generate_normals(&mesh, ((unsigned int(*)[3]) mesh.f.start));
    return (mesh);
}
