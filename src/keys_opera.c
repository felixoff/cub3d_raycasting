/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_opera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/12/25 11:54:41 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_key_press(int keycode, t_params *params)
{
	if (keycode == FORWARD_W_Z)
		params->data.forward = 1;
	else if (keycode == BACK_S_S)
		params->data.back = 1;
	else if (keycode == LEFT_A_Q)
		params->data.left = 1;
	else if (keycode == RIGHT_D_D)
		params->data.right = 1;
	else if (keycode == ROTATE_LEFT)
		params->data.rotate_left = 1;
	else if (keycode == ROTATE_RIGHT)
		params->data.rotate_right = 1;
	else if (keycode == 65307)
		ft_error(params, "Спасибо за игру!)\n");
	return (1);
}

int		ft_key_release(int keycode, t_params *params)
{
	if (keycode == FORWARD_W_Z)
		params->data.forward = 0;
	else if (keycode == BACK_S_S)
		params->data.back = 0;
	else if (keycode == LEFT_A_Q)
		params->data.left = 0;
	else if (keycode == RIGHT_D_D)
		params->data.right = 0;
	else if (keycode == ROTATE_LEFT)
		params->data.rotate_left = 0;
	else if (keycode == ROTATE_RIGHT)
		params->data.rotate_right = 0;
	return (1);
}
