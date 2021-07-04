/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:44:54 by nikita            #+#    #+#             */
/*   Updated: 2020/12/24 15:12:38 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_texture(t_params *params)
{
	if (params->ray.side == 0 && params->ray.raydirx < 0)
		params->t.texdir = 0;
	if (params->ray.side == 0 && params->ray.raydirx >= 0)
		params->t.texdir = 1;
	if (params->ray.side == 1 && params->ray.raydiry < 0)
		params->t.texdir = 2;
	if (params->ray.side == 1 && params->ray.raydiry >= 0)
		params->t.texdir = 3;
	if (params->ray.side == 0)
		params->t.wallx = params->ray.posy + params->ray.perpwalldist \
						* params->ray.raydiry;
	else
		params->t.wallx = params->ray.posx + params->ray.perpwalldist \
						* params->ray.raydirx;
	params->t.wallx -= floor((params->t.wallx));
}

int		ft_color_column(t_params *params)
{
	int j;
	int i;

	j = -1;
	params->ray.drawend = params->ry - params->ray.drawstart;
	i = params->ray.drawend;
	while (++j < params->ray.drawstart)
		params->data.addr[j * params->data.line_length / 4 +
			params->ray.x] = params->c;
	if (j <= params->ray.drawend)
		ft_draw_texture(params, params->ray.x, j);
	j = i;
	while (++j < params->ry)
		params->data.addr[j * params->data.line_length / 4 +
			params->ray.x] = params->f;
	return (0);
}

void	ft_draw_texture(t_params *params, int x, int y)
{
	y = params->ray.drawstart - 1;
	ft_init_texture(params);
	params->t.step = 1.0 * params->texture[0].height / params->ray.lineheight;
	params->t.texx = (int)(params->t.wallx * (double)params->texture
			[params->t.texdir].width);
	if (params->ray.side == 0 && params->ray.raydirx > 0)
		params->t.texx = params->texture[params->t.texdir].width -
			params->t.texx - 1;
	if (params->ray.side == 1 && params->ray.raydiry < 0)
		params->t.texx = params->texture[params->t.texdir].width -
			params->t.texx - 1;
	params->t.texpos = (params->ray.drawstart - params->ry / 2 +
			params->ray.lineheight / 2) * params->t.step;
	while (++y <= params->ray.drawend)
	{
		params->t.texy = (int)params->t.texpos &
			(params->texture[params->t.texdir].height - 1);
		params->t.texpos += params->t.step;
		if (y < params->ry && x < params->rx)
			params->data.addr[y * params->data.line_length / 4 + x] =
				params->texture[params->t.texdir].addr[params->t.texy *
					params->texture[params->t.texdir].line_length /
					4 + params->t.texx];
	}
}

void	ft_stepsidedist(t_params *params)
{
	if (params->ray.raydirx < 0)
	{
		params->ray.stepx = -1;
		params->ray.sidedistx = (params->ray.posx - params->ray.mapx) \
							* params->ray.deltadistx;
	}
	else
	{
		params->ray.stepx = 1;
		params->ray.sidedistx = (params->ray.mapx + 1.0 - params->ray.posx) \
							* params->ray.deltadistx;
	}
	if (params->ray.raydiry < 0)
	{
		params->ray.stepy = -1;
		params->ray.sidedisty = (params->ray.posy - params->ray.mapy) \
							* params->ray.deltadisty;
	}
	else
	{
		params->ray.stepy = 1;
		params->ray.sidedisty = (params->ray.mapy + 1.0 - params->ray.posy) \
							* params->ray.deltadisty;
	}
	ft_incrementray(params);
}
