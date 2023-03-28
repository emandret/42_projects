/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emandret <emandret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 01:32:49 by emandret          #+#    #+#             */
/*   Updated: 2019/01/11 18:08:25 by emandret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scop.h"

t_vec4 g_min;
t_vec4 g_max;
t_vec4 g_origin;

t_scene g_scene;

float g_model[4][4];
float g_view[4][4];
float g_projection[4][4];
