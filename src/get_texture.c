/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 12:06:47 by nikita            #+#    #+#             */
/*   Updated: 2020/12/25 12:23:23 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_get_texture_adress(t_params *params)
{
	params->texture[0].addr = (int *)mlx_get_data_addr(params->texture[0].img,
			&params->texture[0].bits_per_pixel,
			&params->texture[0].line_length, &params->texture[0].endian);
	params->texture[1].addr = (int *)mlx_get_data_addr(params->texture[1].img,
			&params->texture[1].bits_per_pixel,
			&params->texture[1].line_length, &params->texture[1].endian);
	params->texture[2].addr = (int *)mlx_get_data_addr(params->texture[2].img,
			&params->texture[2].bits_per_pixel,
			&params->texture[2].line_length, &params->texture[2].endian);
	params->texture[3].addr = (int *)mlx_get_data_addr(params->texture[3].img,
			&params->texture[3].bits_per_pixel,
			&params->texture[3].line_length, &params->texture[3].endian);
	params->texture[4].addr = (int *)mlx_get_data_addr(params->texture[4].img,
			&params->texture[4].bits_per_pixel,
			&params->texture[4].line_length, &params->texture[4].endian);
}

void	ft_get_texture(t_params *params)
{
	if (!(params->texture[0].img = mlx_xpm_file_to_image(params->data.mlx_ptr,
					params->no, &(params->texture[0].width),
					&(params->texture[0].height))))
		ft_error(params, "Ошибка текстуры SO\n");
	if (!(params->texture[1].img = mlx_xpm_file_to_image(params->data.mlx_ptr,
					params->so, &(params->texture[1].width),
					&(params->texture[1].height))))
		ft_error(params, "Ошибка текстуры NO\n");
	if (!(params->texture[2].img = mlx_xpm_file_to_image(params->data.mlx_ptr,
					params->we, &(params->texture[2].width),
					&(params->texture[2].height))))
		ft_error(params, "Ошибка текстуры EA\n");
	if (!(params->texture[3].img = mlx_xpm_file_to_image(params->data.mlx_ptr,
					params->ea, &(params->texture[3].width),
					&(params->texture[3].height))))
		ft_error(params, "Ошибка текстуры WE\n");
	if (!(params->texture[4].img = mlx_xpm_file_to_image(params->data.mlx_ptr,
					params->sp, &(params->texture[4].width),
					&(params->texture[4].height))))
		ft_error(params, "Ошибка спрайта S\n");
	ft_get_texture_adress(params);
}
