/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 18:49:22 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 20:35:47 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void get_uniforms(t_shp *shp)
{
    shp->texture       = glGetUniformLocation(shp->id, "TextureSampler");
    shp->texture_level = glGetUniformLocation(shp->id, "TextureLevel");
    shp->model         = glGetUniformLocation(shp->id, "Model");
    shp->view          = glGetUniformLocation(shp->id, "View");
    shp->projection    = glGetUniformLocation(shp->id, "Projection");
    shp->light_pos     = glGetUniformLocation(shp->id, "LightPos");
    shp->normal_tint   = glGetUniformLocation(shp->id, "NormalTint");
}

static inline float delta_frame(void)
{
    static float last_frame;
    float        diff_ms;
    float        now;

    now        = glfwGetTime();
    diff_ms    = now - last_frame;
    last_frame = now;
    return (diff_ms);
}

static inline float fade(float *level)
{
    if (g_scene.texture)
    {
        *level = (*level >= 1.0f) ? 1.0f : *level + 0.005f;
        return (*level);
    }
    *level = (*level <= 0.0f) ? 0.0f : *level - 0.005f;
    return (*level);
}

static void draw(GLFWwindow *window, t_vbo vbo, t_shp shp)
{
    float texture_level;
    float diff_ms;

    texture_level = 0.0f;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    while (!glfwWindowShouldClose(window))
    {
        diff_ms = delta_frame();
        key_input_callback(window);
        if (g_scene.auto_rotate)
            mat_rotate_origin(g_model, quat_create(diff_ms, Y_AXIS));
        glClearColor(0.0f, 0.2f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUniformMatrix4fv(shp.model, 1, GL_FALSE, (float *) g_model);
        glUniformMatrix4fv(shp.view, 1, GL_FALSE, (float *) g_view);
        glUniformMatrix4fv(shp.projection, 1, GL_FALSE, (float *) g_projection);
        glUniform1f(shp.texture_level, fade(&texture_level));
        glUniform1ui(shp.normal_tint, g_scene.normal_tint);
        glDrawArrays(GL_TRIANGLES, 0, vbo.size);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(int argc, char *argv[])
{
    GLFWwindow *window;
    t_vbo       vbo;
    t_shp       shp;

    if (argc != 3)
    {
        fprintf(stderr, "Usage: ./scop model.obj texture.bmp\n");
        exit(EXIT_FAILURE);
    }
    window = window_init_context();
    vbo    = vbo_create(parse_obj(argv[1]));
    shp.id = import_shaders("shaders/vs.glsl", "shaders/fs.glsl");
    glUseProgram(shp.id);
    get_uniforms(&shp);
    glUniform1i(shp.texture, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, get_texture(argv[2]));
    glUniform3fv(shp.light_pos, 1, (float *) &VEC4(0.0f, 0.0f, 2.0f, 1.0f));
    mat_mvp();
    draw(window, vbo, shp);
    glDeleteBuffers(1, &vbo.id);
    glDeleteVertexArrays(1, &vbo.vao);
    glfwTerminate();
    return (0);
}
