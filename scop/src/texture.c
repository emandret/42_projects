/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 19:10:08 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 21:31:38 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static uint8_t *parse_bmp(const char *path, unsigned int *width, unsigned int *height)
{
    FILE     *stream;
    t_bmp_hdr file_header;
    t_bmp_dib dib_header;
    t_bmp_rgb color_table;
    uint8_t  *data;

    if (!(stream = fopen(path, "rb")))
        return (NULL);
    if (fread(&file_header, 1, sizeof(t_bmp_hdr), stream) != sizeof(t_bmp_hdr))
        return (NULL);
    if (fread(&dib_header, 1, sizeof(t_bmp_dib), stream) != sizeof(t_bmp_dib))
        return (NULL);
    if (fread(&color_table, 1, sizeof(t_bmp_rgb), stream) != sizeof(t_bmp_rgb))
        return (NULL);
    *width  = dib_header.width;
    *height = dib_header.height;
    if (fseek(stream, file_header.offbits, SEEK_SET) == -1)
        return (NULL);
    if (!(data = (uint8_t *) malloc(sizeof(uint8_t) * dib_header.size_image)))
        return (NULL);
    if (fread(data, 1, dib_header.size_image, stream) != dib_header.size_image)
        return (NULL);
    return (data);
}

unsigned int get_texture(const char *path)
{
    unsigned int texture;
    unsigned int width;
    unsigned int height;
    uint8_t     *data;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (!(data = parse_bmp(path, &width, &height)))
    {
        fprintf(stderr, "Failed to load texture: %s\n", path);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    free(data);
    return (texture);
}
