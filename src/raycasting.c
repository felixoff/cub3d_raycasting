/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/12/25 11:55:09 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_incrementray(t_params *params)
{
	while (params->ray.hit == 0)
	{
		if (params->ray.sidedistx < params->ray.sidedisty)
		{
			params->ray.sidedistx += params->ray.deltadistx;
			params->ray.mapx += params->ray.stepx;
			params->ray.side = 0;
		}
		else
		{
			params->ray.sidedisty += params->ray.deltadisty;
			params->ray.mapy += params->ray.stepy;
			params->ray.side = 1;
		}
		if (params->map[params->ray.mapx][params->ray.mapy] == '1')
			params->ray.hit = 1;
	}
	ft_drawstartend(params);
}

void	ft_drawstartend(t_params *params)
{
	if (params->ray.side == 0)
		params->ray.perpwalldist = ((double)params->ray.mapx - \
				params->ray.posx + (1 - (double)params->ray.
				stepx) / 2) / params->ray.raydirx;
	else
		params->ray.perpwalldist = ((double)params->ray.mapy - \
				params->ray.posy + (1 - (double)params->ray.
				stepy) / 2) / params->ray.raydiry;
	params->ray.lineheight = (int)(params->ry / params->ray.perpwalldist);
	params->ray.drawstart = -params->ray.lineheight / 2 + params->ry / 2;
	if (params->ray.drawstart < 0)
		params->ray.drawstart = 0;
	params->ray.drawend = params->ray.lineheight / 2 + params->ry / 2;
	if (params->ray.drawend >= params->ry || params->ray.drawend < 0)
		params->ray.drawend = params->ry - 1;
}

void	ft_init_more3(t_params *params)
{
	if (params->ray.raydiry == 0)
		params->ray.deltadistx = 0;
	else if (params->ray.raydirx == 0)
		params->ray.deltadistx = 1;
	else
		params->ray.deltadistx = sqrt(1 + (params->ray.raydiry
			* params->ray.raydiry) / (params->ray.raydirx *
			params->ray.raydirx));
	if (params->ray.raydirx == 0)
		params->ray.deltadisty = 0;
	else if (params->ray.raydiry == 0)
		params->ray.deltadisty = 1;
	else
		params->ray.deltadisty = sqrt(1 + (params->ray.raydirx *
			params->ray.raydirx) / (params->ray.raydiry *
			params->ray.raydiry));
}

void	ft_initialisation3(t_params *params)
{
	params->ray.hit = 0;
	params->ray.perpwalldist = 0;
	params->ray.camerax = 2 * params->ray.x / (double)params->rx - 1;
	params->ray.raydirx = params->ray.dirx + params->ray.planx * \
						params->ray.camerax;
	params->ray.raydiry = params->ray.diry + params->ray.plany * \
						params->ray.camerax;
	params->ray.mapx = (int)params->ray.posx;
	params->ray.mapy = (int)params->ray.posy;
	params->ray.movespeed = 0.2;
	params->ray.rotspeed = 0.073 * 1.8;
	ft_init_more3(params);
}

int		ft_raycasting(t_params *params)
{
	params->ray.x = 0;
	while (params->ray.x < params->rx)
	{
		ft_initialisation3(params);
		ft_stepsidedist(params);
		ft_color_column(params);
		params->s.zbuffer[params->ray.x] = params->ray.perpwalldist;
		params->ray.x++;
	}
	ft_sprite(params);
	if (params->save == 1)
		ft_save(params);
	mlx_put_image_to_window(params->data.mlx_ptr, params->data.mlx_win,
			params->data.img, 0, 0);
	ft_forward_back(params);
	ft_left_right(params);
	ft_rotate_right_left(params);
	ft_swap(params);
	return (0);
}
