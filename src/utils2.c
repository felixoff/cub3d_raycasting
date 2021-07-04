/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:45:12 by nikita            #+#    #+#             */
/*   Updated: 2020/12/25 11:56:13 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int		ft_charinstr(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_atoi2(const char *str, t_params *params)
{
	int		sum;

	sum = 0;
	if (str[params->i] != ' ' || ft_charinstr((char *)str, ',') == 1)
		params->error = 2;
	while (str[params->i] == ' ' || str[params->i] == '\t'
			|| str[params->i] == ',' || str[params->i] == '\n'
			|| str[params->i] == '\r' || str[params->i] == '\v'
			|| str[params->i] == '\f')
		params->i++;
	if (str[params->i] == '-' || str[params->i] == '+')
		params->error = 2;
	while (str[params->i] >= '0' && str[params->i] <= '9')
	{
		if (sum > 21474636)
			break ;
		sum = (sum * 10) + (str[params->i] - 48);
		params->i++;
	}
	while (str[params->i] >= '0' && str[params->i] <= '9')
		params->i++;
	return (sum);
}

int		ft_number_rows(const char *str)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ',')
			j++;
	}
	return (j);
}
