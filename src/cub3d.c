/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:43:55 by nikita            #+#    #+#             */
/*   Updated: 2020/12/29 10:51:07 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_cub(char *str, t_params *params)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
	{
		i--;
		if (i == 0)
		{
			ft_error(params, "Невалидный аргумент\n");
			return (0);
		}
	}
	if (str[i + 1] == 'c' && str[i + 2] == 'u' &&
	str[i + 3] == 'b' && str[i + 4] == '\0')
		ft_parsing(str, params);
	else
		ft_error(params, "Невалидный аргумент\n");
	return (0);
}

int		ft_check_save(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'e' && str[i - 2] == 'v' && str[i - 3] == 'a' &&
		str[i - 4] == 's' && str[i - 5] == '-' && str[i - 6] == '-'
		&& ft_strlen(str) < 7)
		return (1);
	else
		return (0);
}

void	ft_initialisation(t_params *params)
{
	params->no = NULL;
	params->so = NULL;
	params->we = NULL;
	params->ea = NULL;
	params->sp = NULL;
	params->f = -1;
	params->c = -1;
	params->rx = 0;
	params->ry = 0;
	params->nblines = 0;
	params->sizeline = 0;
	params->map = NULL;
	params->dx = 0;
	params->dy = 0;
	params->multijoueurs = 0;
	params->check_tabulation = 0;
	params->insidemap = 0;
	params->count = 0;
	params->sum = 0;
	params->wrongcharmap = 0;
	ft_init_more(params);
}

void	ft_init_more(t_params *params)
{
	params->depart = 'x';
	params->indicateur2 = 0;
	params->indicateur3 = 0;
	params->data.img = NULL;
	params->texture[0].img = NULL;
	params->texture[1].img = NULL;
	params->texture[2].img = NULL;
	params->texture[3].img = NULL;
	params->texture[4].img = NULL;
	params->data.mlx_win = NULL;
	params->map = NULL;
	params->s.order = NULL;
	params->s.dist = NULL;
	params->s.zbuffer = NULL;
	params->sxy = NULL;
}

int		main(int argc, char **argv)
{
	t_params params;

	params.save = 0;
	ft_initialisation(&params);
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			params.save = 1;
		ft_cub(argv[1], &params);
	}
	else
		write(1, "Ошибка\nНевалидные аргументы\n", 30);
}
