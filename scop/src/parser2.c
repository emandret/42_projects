/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 13:38:33 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 21:21:06 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void triangulate(t_growable *gb, size_t count, unsigned int faces[][MAX_FACES])
{
    t_indices face[3];
    size_t    n;

    n = 0;
    while (n <= (count - 3))
    {
        face[0][0] = faces[0][0];
        face[0][1] = faces[1][0];
        face[0][2] = faces[2][0];
        gb_push(gb, &face[0]);
        face[1][0] = faces[0][n + 1];
        face[1][1] = faces[1][n + 1];
        face[1][2] = faces[2][n + 1];
        gb_push(gb, &face[1]);
        face[2][0] = faces[0][n + 2];
        face[2][1] = faces[1][n + 2];
        face[2][2] = faces[2][n + 2];
        gb_push(gb, &face[2]);
        n++;
    }
}

void parse_polyface(t_growable *gb, char *line)
{
    size_t       n;
    unsigned int face[3][MAX_FACES];
    char        *tok;

    n = 0;
    memset(&face, 0, sizeof(face));
    while ((tok = strsep(&line, TOK_MARKER)) && *tok)
    {
        if (n < MAX_FACES)
        {
            sscanf(tok, "%u/%u", &face[0][n], &face[1][n]);
            sscanf(tok, "%u//%u", &face[0][n], &face[2][n]);
            sscanf(tok, "%u/%u/%u", &face[0][n], &face[1][n], &face[2][n]);
        }
        n++;
    }
    if (n < 3 || n > MAX_FACES)
    {
        fprintf(stderr, "Error: face count is too low/high (%zu)\n", n);
        exit(EXIT_FAILURE);
    }
    triangulate(gb, n, face);
}
