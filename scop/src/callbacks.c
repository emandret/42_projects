/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:05:37 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 20:05:22 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static inline void user_move_input(GLFWwindow *window)
{
    float xpos;
    float ypos;

    xpos = 0.0f;
    ypos = 0.0f;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        xpos += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        xpos -= 0.1f;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        ypos += 0.1f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        ypos -= 0.1f;
    g_origin.x += xpos;
    g_origin.y += ypos;
    mat_translate(g_model, VEC4(xpos, ypos, 0.0f, 1.0f));
}

void error_callback(int error, const char *description)
{
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
    glfwTerminate();
    exit(EXIT_FAILURE);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    (void) window;
    glViewport(0, 0, width, height);
}

void key_input_callback(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        g_scene.texture = !g_scene.texture;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        g_scene.normal_tint = !g_scene.normal_tint;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        g_scene.wireframe = !g_scene.wireframe;
        if (g_scene.wireframe)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    user_move_input(window);
}
