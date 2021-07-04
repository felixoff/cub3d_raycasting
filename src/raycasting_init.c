/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:38:41 by ebourdit          #+#    #+#             */
/*   Updated: 2020/12/25 12:19:45 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_dir(t_params *params)
{
	if (params->depart == 'N')
		params->ray.dirx = -1;
	if (params->depart == 'S')
		params->ray.dirx = 1;
	if (params->depart == 'E')
		params->ray.diry = 1;
	if (params->depart == 'W')
		params->ray.diry = -1;
	if (params->depart == 'N')
		params->ray.plany = 0.66;
	if (params->depart == 'S')
		params->ray.plany = -0.66;
	if (params->depart == 'E')
		params->ray.planx = 0.66;
	if (params->depart == 'W')
		params->ray.planx = -0.66;
}

void	ft_initialisation2(t_params *params)
{
	if (!(params->s.zbuffer = (double *)malloc(sizeof(double) * params->rx)))
		exit(0);
	params->data.forward = 0;
	params->data.back = 0;
	params->data.left = 0;
	params->data.right = 0;
	params->data.rotate_right = 0;
	params->data.rotate_left = 0;
	params->ray.posx = (double)params->dx + 0.5;
	params->ray.posy = (double)params->dy + 0.5;
	params->ray.dirx = 0;
	params->ray.diry = 0;
	params->ray.planx = 0;
	params->ray.plany = 0;
	ft_init_dir(params);
}

int		ft_mlx(t_params *params)
{
	ft_initialisation2(params);
	if (!(params->data.mlx_ptr = mlx_init()))
		ft_error(params, "Невозможно инициализировать библиотеку\n");
	mlx_get_screen_size(params->data.mlx_ptr,
		&params->screenx, &params->screeny);
	params->rx = (params->rx > params->screenx) ? params->screenx : params->rx;
	params->ry = (params->ry > params->screeny) ? params->screeny : params->ry;
	ft_get_texture(params);
	params->data.img = mlx_new_image(params->data.mlx_ptr,
		params->rx, params->ry);
	params->data.addr = (int *)mlx_get_data_addr(params->data.img,
		&params->data.bits_per_pixel, &params->data.line_length,
			&params->data.endian);
	if (params->save == 1)
		ft_raycasting(params);
	params->data.mlx_win = mlx_new_window(params->data.mlx_ptr, params->rx,
		params->ry, "Hi sjennett!");
	params->data.img2 = mlx_new_image(params->data.mlx_ptr,
		params->rx, params->ry);
	params->data.addr2 = (int *)mlx_get_data_addr(params->data.img2, &params->
		data.bits_per_pixel, &params->data.line_length, &params->data.endian);
	return (ft_mlx2(params));
}

int		ft_mlx2(t_params *params)
{
	mlx_hook(params->data.mlx_win, 33, 1L << 17, ft_exit, params);
	mlx_hook(params->data.mlx_win, 2, 1L << 0, ft_key_press, params);
	mlx_loop_hook(params->data.mlx_ptr, ft_raycasting, params);
	mlx_hook(params->data.mlx_win, 3, 1L << 1, ft_key_release, params);
	mlx_loop(params->data.mlx_ptr);
	return (0);
}
