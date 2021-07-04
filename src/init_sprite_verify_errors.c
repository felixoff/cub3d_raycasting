/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_verify_errors.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:44:21 by nikita            #+#    #+#             */
/*   Updated: 2020/12/29 11:21:16 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int		ft_strlen1(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int				ft_murs(t_params *params)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < params->nblines)
	{
		if (params->map[i][j] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < params->nblines)
	{
		j = ft_strlen1(params->map[i]) - 1;
		if (params->map[i][j] != '1')
			return (1);
		i++;
	}
	if (ft_murs_util(params->map[0]) == 1)
		return (1);
	if (ft_murs_util(params->map[params->nblines - 1]) == 1)
		return (1);
	return (0);
}

void			ft_verify_errors(t_params *params)
{
	if (ft_murs(params) == 1)
		ft_error(params, "Карта не окружена 1\n");
	if (params->depart == 'x')
		ft_error(params, "Нет игрока на карте\n");
	if (params->indicateur2 != 6)
		ft_error(params, "Неправильные данные для F или C\n");
	if (params->multijoueurs == 1)
		ft_error(params, "Более одного игрока\n");
	if (params->check_tabulation == 1)
		ft_error(params, "Пустая строка на карте\n");
	if (params->wrongcharmap == 2)
		ft_error(params, "Неверный символ на карте\n");
}

void			ft_init_sprite(t_params *params)
{
	int i;
	int j;

	i = -1;
	params->s.nbspr = 0;
	ft_verify_errors(params);
	while (++i < params->nblines)
	{
		j = -1;
		while (++j < params->sizeline)
		{
			if (params->map[i][j] == '2')
				params->s.nbspr += 1;
		}
	}
	if (!(params->sxy = (t_sprxy *)malloc(sizeof(t_sprxy) * params->s.nbspr)))
		ft_error(params, "Ошибка маллока sxy*");
	if (!(params->s.order = (int *)malloc(sizeof(int) * params->s.nbspr)))
		ft_error(params, "Ошибка маллока s.order*");
	if (!(params->s.dist = (double *)malloc(sizeof(double) * params->s.nbspr)))
		ft_error(params, "Ошибка маллока s.dist*");
	ft_init_sprite2(params, 0, 0, 0);
	ft_mlx(params);
}

void			ft_init_sprite2(t_params *params, int i, int j, int v)
{
	i = i - 1;
	while (++i < params->nblines)
	{
		j = -1;
		while (++j < params->sizeline)
		{
			if (params->map[i][j] == '2')
			{
				params->sxy[v].x = (double)i + 0.5;
				params->sxy[v].y = (double)j + 0.5;
				v++;
			}
		}
	}
}
