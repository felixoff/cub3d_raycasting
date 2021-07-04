/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/12/25 11:57:58 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_dist_order2(t_params *params)
{
	int i;

	i = -1;
	while (++i < params->s.nbspr)
	{
		params->s.order[i] = i;
		params->s.dist[i] = ((params->ray.posx - params->sxy[i].x) *
				(params->ray.posx - params->sxy[i].x) + (params->ray.posy -
					params->sxy[i].y) * (params->ray.posy - params->sxy[i].y));
	}
}

void	ft_dist_order(t_params *params)
{
	int		i;
	int		j;
	double	tmp;

	ft_dist_order2(params);
	i = -1;
	while (++i < params->s.nbspr)
	{
		j = -1;
		while (++j < params->s.nbspr - 1)
		{
			if (params->s.dist[j] < params->s.dist[j + 1])
			{
				tmp = params->s.dist[j];
				params->s.dist[j] = params->s.dist[j + 1];
				params->s.dist[j + 1] = tmp;
				tmp = params->s.order[j];
				params->s.order[j] = params->s.order[j + 1];
				params->s.order[j + 1] = (int)tmp;
			}
		}
	}
}

void	ft_calculs(t_params *params, int i)
{
	params->s.spritex = params->sxy[params->s.order[i]].x - params->ray.posx;
	params->s.spritey = params->sxy[params->s.order[i]].y - params->ray.posy;
	params->s.invdet = 1.0 / (params->ray.planx * params->ray.diry -
			params->ray.dirx * params->ray.plany);
	params->s.transformx = params->s.invdet * (params->ray.diry *
			params->s.spritex - params->ray.dirx * params->s.spritey);
	params->s.transformy = params->s.invdet * (-params->ray.plany *
			params->s.spritex + params->ray.planx * params->s.spritey);
	params->s.spritescreenx = (int)((params->rx / 2) * (1 + params->s.transformx
				/ params->s.transformy));
	params->s.spriteheight = abs((int)(params->ry / (params->s.transformy)));
	params->s.drawstarty = -params->s.spriteheight / 2 + params->ry / 2;
	if (params->s.drawstarty < 0)
		params->s.drawstarty = 0;
	params->s.drawendy = params->s.spriteheight / 2 + params->ry / 2;
	if (params->s.drawendy >= params->ry)
		params->s.drawendy = params->ry;
	params->s.spritewidth = abs((int)(params->ry / (params->s.transformy)));
	params->s.drawstartx = -params->s.spritewidth / 2 + params->s.spritescreenx;
	if (params->s.drawstartx < 0)
		params->s.drawstartx = 0;
	params->s.drawendx = params->s.spritewidth / 2 + params->s.spritescreenx;
	if (params->s.drawendx >= params->rx)
		params->s.drawendx = params->rx;
}

void	ft_draw_spr(t_params *params, int y, int texx, int stripe)
{
	int		d;
	int		texy;

	while (y < params->s.drawendy)
	{
		d = (y) * 256 - params->ry * 128 + params->s.spriteheight * 128;
		texy = ((d * params->texture[4].height) / params->s.spriteheight) / 256;
		if (params->texture[4].addr[texy * params->texture[4].line_length / 4 +
				texx] != -16777216)
		{
			params->data.addr[y * params->data.line_length / 4 + stripe] =
				params->texture[4].addr[texy * params->texture[4].line_length /
				4 + texx];
		}
		y++;
	}
}

void	ft_sprite(t_params *params)
{
	int i;
	int y;
	int stripe;
	int texx;

	i = -1;
	ft_dist_order(params);
	while (++i < params->s.nbspr)
	{
		ft_calculs(params, i);
		stripe = params->s.drawstartx;
		while (stripe < params->s.drawendx)
		{
			texx = (int)(256 * (stripe - (-params->s.spritewidth / 2 +
							params->s.spritescreenx)) * params->texture[4].width
					/ params->s.spritewidth) / 256;
			if (params->s.transformy > 0 && stripe >= 0 && stripe < params->rx
					&& params->s.transformy < params->s.zbuffer[stripe])
			{
				y = params->s.drawstarty;
				ft_draw_spr(params, y, texx, stripe);
			}
			stripe++;
		}
	}
}
