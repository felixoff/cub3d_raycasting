/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_save.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:44:00 by nikita            #+#    #+#             */
/*   Updated: 2020/12/24 15:37:27 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_error2(t_params *params)
{
	if (params->map)
		free(params->map);
	if (params->s.order)
		free(params->s.order);
	if (params->s.dist)
		free(params->s.dist);
	if (params->sxy)
		free(params->sxy);
	if (params->s.zbuffer)
		free(params->s.zbuffer);
	ft_exit(params);
}

void	ft_error(t_params *params, char *str)
{
	int i;

	i = -1;
	params->indicateur3 = 1;
	write(1, "Ошибка\n", 6);
	write(1, str, ft_strlen(str));
	if (params->no)
		free(params->no);
	if (params->so)
		free(params->so);
	if (params->we)
		free(params->we);
	if (params->ea)
		free(params->ea);
	if (params->sp)
		free(params->sp);
	if (params->map)
	{
		while (++i < params->nblines)
			free(params->map[i]);
	}
	ft_error2(params);
}

int		ft_exit(t_params *params)
{
	if (params->indicateur3 == 0)
		ft_error(params, "Неопределенная ошибка\n");
	if (params->data.img)
		mlx_destroy_image(params->data.mlx_ptr, params->data.img);
	if (params->texture[0].img)
		mlx_destroy_image(params->data.mlx_ptr, params->texture[0].img);
	if (params->texture[1].img)
		mlx_destroy_image(params->data.mlx_ptr, params->texture[1].img);
	if (params->texture[2].img)
		mlx_destroy_image(params->data.mlx_ptr, params->texture[2].img);
	if (params->texture[3].img)
		mlx_destroy_image(params->data.mlx_ptr, params->texture[3].img);
	if (params->texture[4].img)
		mlx_destroy_image(params->data.mlx_ptr, params->texture[4].img);
	if (params->data.mlx_win)
		mlx_destroy_window(params->data.mlx_ptr, params->data.mlx_win);
	exit(0);
}

void	ft_header(t_params *params, int fd)
{
	int	tmp;

	write(fd, "BM", 2);
	tmp = 14 + 40 + 4 * params->rx * params->ry;
	write(fd, &tmp, 4);
	tmp = 0;
	write(fd, &tmp, 2);
	write(fd, &tmp, 2);
	tmp = 54;
	write(fd, &tmp, 4);
	tmp = 40;
	write(fd, &tmp, 4);
	write(fd, &params->rx, 4);
	write(fd, &params->ry, 4);
	tmp = 1;
	write(fd, &tmp, 2);
	write(fd, &params->data.bits_per_pixel, 2);
	tmp = 0;
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
	write(fd, &tmp, 4);
}

void	ft_save(t_params *params)
{
	int	fd;
	int	x;
	int	y;

	y = params->ry;
	if ((fd = open("./image.bmp", O_CREAT | O_RDWR)) == -1)
		ft_error(params, "Невозможно считать файл .bmp\n");
	ft_header(params, fd);
	while (y >= 0)
	{
		x = 0;
		while (x < params->rx)
		{
			write(fd, &params->data.addr[y * params->data.line_length / 4 + x],
				4);
			x++;
		}
		y--;
	}
	system("chmod 777 image.bmp");
	ft_error(params, "Сохранение прошло успешно --save ok\n");
}
