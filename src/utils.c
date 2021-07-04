/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:45:05 by nikita            #+#    #+#             */
/*   Updated: 2020/12/25 11:58:41 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_atoi3_check(const char *str, t_params *params)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i] != ',')
		i++;
	if (str[i] == ',')
		j = 1;
	i++;
	while (str[i] == ' ')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while ((str[i] < '0' || str[i] > '9') && str[i])
	{
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		params->error = 2;
	if (ft_number_rows(str) != 2)
		params->error = 2;
}

int		ft_atoi3(const char *str, t_params *params)
{
	int		verify;

	verify = 0;
	if (str[params->i] != ' ')
		params->error = 2;
	ft_atoi3_check(str, params);
	while (str[params->i] == ' ' || str[params->i] == '\t' || str[params->i]
			== ',' || str[params->i] == '\n' || str[params->i] == '\r'
			|| str[params->i] == '\v' || str[params->i] == '\f')
	{
		params->i++;
		verify = 0;
		if (str[params->i] >= '0' && str[params->i] <= '9')
			params->indicateur2++;
		while (str[params->i] >= '0' && str[params->i] <= '9')
		{
			verify = (verify * 10) + str[params->i] - 48;
			params->sum = (params->sum * 10) + (str[params->i] - 48);
			params->i++;
		}
		if (verify > 255 || verify < 0)
			params->error = 2;
	}
	return (params->sum);
}

int		ft_check_tabulation(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
				&& str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

int		ft_is_map(char *str, t_params *params)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1 || ft_charinstr(str, '0') == 1)
	{
		while (str[i] != '\0')
		{
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (params->insidemap == 1)
					params->wrongcharmap = 2;
				return (0);
			}
			i++;
		}
		return (1);
	}
	return (0);
}

int		ft_strlen2(char *str)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}
