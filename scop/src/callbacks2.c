/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 20:18:28 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 19:30:59 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

static bool mouse_double_click(int action)
{
    static double last_keyrelease;
    double        diff_ms;
    double        now;

    now = glfwGetTime();
    if (action == GLFW_RELEASE)
    {
        diff_ms         = now - last_keyrelease;
        last_keyrelease = now;
        return (diff_ms > 0.01f && diff_ms < 0.2f);
    }
    return (false);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    (void) window;
    (void) xoffset;
    if (g_scene.fov_angle >= 1.0f && g_scene.fov_angle <= 45.0f)
        g_scene.fov_angle -= yoffset;
    if (g_scene.fov_angle <= 1.0f)
        g_scene.fov_angle = 1.0f;
    if (g_scene.fov_angle >= 45.0f)
        g_scene.fov_angle = 45.0f;
    mat_perspective(g_projection, ((float) WIN_WIDTH / (float) WIN_HEIGHT), 0.1f, 100.0f);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos)
{
    static double old_xpos;
    static double old_ypos;
    t_quat        rot;

    (void) window;
    if (g_scene.user_rotate && old_xpos > 0.0f && old_ypos > 0.0f)
    {
        rot = quat_create(RAD(old_xpos - xpos), Y_AXIS);
        if (g_scene.do_roll)
            rot = quat_multiply(rot, quat_create(RAD(old_ypos - ypos), X_AXIS));
        else
            rot = quat_multiply(rot, quat_create(RAD(old_ypos - ypos), Z_AXIS));
        mat_rotate_origin(g_model, rot);
    }
    old_xpos = xpos;
    old_ypos = ypos;
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    (void) window;
    (void) mods;
    if (button == GLFW_MOUSE_BUTTON_LEFT && mouse_double_click(action))
        g_scene.auto_rotate = !g_scene.auto_rotate;
    if ((button == GLFW_MOUSE_BUTTON_LEFT || button == GLFW_MOUSE_BUTTON_RIGHT) && action == GLFW_PRESS)
    {
        g_scene.user_rotate = true;
        if (button == GLFW_MOUSE_BUTTON_LEFT)
            g_scene.do_roll = true;
        else if (button == GLFW_MOUSE_BUTTON_RIGHT)
            g_scene.do_roll = false;
    }
    else
    {
        g_scene.user_rotate = false;
        g_scene.do_roll     = false;
    }
}
