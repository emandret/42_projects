/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:01:18 by emandret          #+#    #+#             */
/*   Updated: 2018/12/30 20:29:22 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

GLFWwindow *window_init_context(void)
{
    GLFWwindow *window;

    glfwInit();
    glfwSetErrorCallback(&error_callback);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, &framebuffer_size_callback);
    // glfwSetKeyCallback(window, &key_input_callback);
    // glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    glfwSetCursorPosCallback(window, &cursor_position_callback);
    glfwSetScrollCallback(window, &scroll_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    return (window);
}
