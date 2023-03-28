/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shaders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 19:25:48 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 17:49:07 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

/*
** Attempt to read the shader source file into a null-terminated string or
** return a null pointer in case of error.
*/

static char *shader_read_file(const char *path)
{
    int    fd;
    size_t size;
    char  *buf;

    if ((fd = open(path, O_RDONLY)) == -1)
    {
        perror(path);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    size = lseek(fd, 0, SEEK_END);
    if (!(buf = malloc(sizeof(char) * (size + 1))))
    {
        fprintf(stderr, "Failed to allocate memory: %s\n", strerror(errno));
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    lseek(fd, 0, SEEK_SET);
    read(fd, buf, size);
    buf[size] = '\0';
    close(fd);
    return (buf);
}

/*
** Compile the shader source code for the given shader object identifier.
*/

static void shader_compile(unsigned int id, const char *code)
{
    int  success;
    char infolog[1024];

    glShaderSource(id, 1, &code, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 1024, NULL, infolog);
        fprintf(stderr, "Shader compilation error: %s\n", infolog);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

/*
** Create a shader program for the given shader object and return it.
*/

static unsigned int shaders_link(unsigned int vs_id, unsigned int fs_id)
{
    unsigned int program;
    int          success;
    char         infolog[1024];

    program = glCreateProgram();
    glAttachShader(program, vs_id);
    glAttachShader(program, fs_id);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infolog);
        fprintf(stderr, "Shader link error: %s\n", infolog);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glDeleteShader(vs_id);
    glDeleteShader(fs_id);
    return (program);
}

/*
** Import the vertex and fragment shaders source files.
*/

unsigned int import_shaders(const char *vs_path, const char *fs_path)
{
    unsigned int vs_id;
    unsigned int fs_id;
    char        *vs_src;
    char        *fs_src;

    vs_id  = glCreateShader(GL_VERTEX_SHADER);
    fs_id  = glCreateShader(GL_FRAGMENT_SHADER);
    vs_src = shader_read_file(vs_path);
    fs_src = shader_read_file(fs_path);
    shader_compile(vs_id, vs_src);
    shader_compile(fs_id, fs_src);
    free(vs_src);
    free(fs_src);
    return (shaders_link(vs_id, fs_id));
}
