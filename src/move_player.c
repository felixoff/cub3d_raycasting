/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/12/24 15:02:45 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_forward_back(t_params *params)
{
	if (params->data.forward == 1)
	{
		if (params->map[(int)(params->ray.posx + (params->ray.dirx * params->
						ray.movespeed * 2))][(int)params->ray.posy] == '0')
			params->ray.posx += params->ray.dirx * params->ray.movespeed;
		if (params->map[(int)(params->ray.posx)][(int)(params->ray.posy +
					(params->ray.diry * params->ray.movespeed * 2))] == '0')
			params->ray.posy += params->ray.diry * params->ray.movespeed;
	}
	if (params->data.back == 1)
	{
		if (params->map[(int)(params->ray.posx - (params->ray.dirx * params->
						ray.movespeed * 2))][(int)(params->ray.posy)] == '0')
			params->ray.posx -= params->ray.dirx * params->ray.movespeed;
		if (params->map[(int)(params->ray.posx)][(int)(params->ray.posy -
					(params->ray.diry * params->ray.movespeed * 2))] == '0')
			params->ray.posy -= params->ray.diry * params->ray.movespeed;
	}
}

void	ft_left_right(t_params *params)
{
	if (params->data.right == 1)
	{
		if (params->map[(int)(params->ray.posx + params->ray.diry *
					(params->ray.movespeed * 2))][(int)params->ray.posy] == '0')
			params->ray.posx += params->ray.diry * params->ray.movespeed;
		if (params->map[(int)params->ray.posx][(int)(params->ray.posy -
					params->ray.dirx *
					(params->ray.movespeed * 2))] == '0')
			params->ray.posy -= params->ray.dirx * params->ray.movespeed;
	}
	if (params->data.left == 1)
	{
		if (params->map[(int)(params->ray.posx - params->ray.diry *
					(params->ray.movespeed * 2))][(int)params->ray.posy] == '0')
			params->ray.posx -= params->ray.diry * params->ray.movespeed;
		if (params->map[(int)params->ray.posx][(int)(params->ray.posy +
					params->ray.dirx *
					(params->ray.movespeed * 2))] == '0')
			params->ray.posy += params->ray.dirx * params->ray.movespeed;
	}
}

void	ft_rotate_right_left(t_params *params)
{
	double oldplanx;
	double olddirx;

	oldplanx = params->ray.planx;
	olddirx = params->ray.dirx;
	if (params->data.rotate_right == 1)
	{
		params->ray.dirx = params->ray.dirx * cos(-params->ray.rotspeed / 2) -
			params->ray.diry * sin(-params->ray.rotspeed / 2);
		params->ray.diry = olddirx * sin(-params->ray.rotspeed / 2) +
			params->ray.diry * cos(-params->ray.rotspeed / 2);
		params->ray.planx = params->ray.planx * cos(-params->ray.rotspeed / 2)
			- params->ray.plany * sin(-params->ray.rotspeed / 2);
		params->ray.plany = oldplanx * sin(-params->ray.rotspeed / 2) +
			params->ray.plany * cos(-params->ray.rotspeed / 2);
	}
	ft_rotate_left(params, olddirx);
}

void	ft_rotate_left(t_params *params, double olddirx)
{
	double oldplanex;

	if (params->data.rotate_left == 1)
	{
		olddirx = params->ray.dirx;
		oldplanex = params->ray.planx;
		params->ray.dirx = params->ray.dirx * cos(params->ray.rotspeed / 2) -
			params->ray.diry * sin(params->ray.rotspeed / 2);
		params->ray.diry = olddirx * sin(params->ray.rotspeed / 2) + params->
			ray.diry * cos(params->ray.rotspeed / 2);
		params->ray.planx = params->ray.planx * cos(params->ray.rotspeed / 2) -
			params->ray.plany * sin(params->ray.rotspeed / 2);
		params->ray.plany = oldplanex * sin(params->ray.rotspeed / 2) +
			params->ray.plany * cos(params->ray.rotspeed / 2);
	}
}

void	ft_swap(t_params *params)
{
	void *tmp;

	tmp = params->data.img;
	params->data.img = params->data.img2;
	params->data.img2 = tmp;
	tmp = params->data.addr;
	params->data.addr = params->data.addr2;
	params->data.addr2 = tmp;
}
