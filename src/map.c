/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:44:33 by nikita            #+#    #+#             */
/*   Updated: 2020/12/29 11:15:59 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_depart(char c, t_params *params, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (params->depart != 'x')
			params->multijoueurs = 1;
		params->depart = c;
		params->dx = i;
		params->dy = j;
		return (1);
	}
	return (0);
}

int		ft_parsing_map(char *fichier, t_params *params)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	if (!(params->map = malloc(sizeof(char*) * params->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, params);
		if (params->insidemap == 1 && ft_check_tabulation(str) == 0 &&
				params->count < params->nblines)
			params->check_tabulation = 1;
		if ((params->insidemap = ft_is_map(str, params)) == 1)
		{
			params->count++;
			ft_copy_map(str, params);
		}
		free(str);
	}
	close(fd);
	ft_init_sprite(params);
	return (0);
}

void	ft_map(char *str, t_params *params)
{
	int			i;
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(str, params) == 1)
	{
		if (params->f == -1 || params->c == -1 || params->no == NULL ||
				params->so == NULL || params->we == NULL ||
				params->ea == NULL || params->sp == NULL)
			params->error = 2;
		if ((i = ft_strlen(str)) > ssizeline)
			ssizeline = i;
		snblines = snblines + 1;
	}
	else if (params->nblines > 0)
		params->error = 2;
	params->nblines = snblines;
	params->sizeline = ssizeline;
}
