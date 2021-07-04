/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:56:03 by nikita            #+#    #+#             */
/*   Updated: 2020/12/29 12:01:37 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int		ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int				is_whitespace(
	int c
)
{
	if (c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

static void		check_r(char *str, t_params *params)
{
	int i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (!str || str[i] != 'R' || str[i + 1] != ' ')
		params->error = 2;
	i = i + 1;
	while (is_whitespace(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		params->error = 2;
	while (ft_isdigit(str[i]))
		i++;
	if (!is_whitespace(str[i]))
		params->error = 2;
	while (is_whitespace(str[i]))
		i++;
	while (ft_isdigit(str[i]))
		i++;
	while (is_whitespace(str[i]))
		i++;
	if (!is_whitespace(str[i]) && str[i] != '\0')
		params->error = 2;
}

static void		check_fc(char *str, t_params *params)
{
	int i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (!str || (str[i] != 'F' && str[i] != 'C')
		|| !is_whitespace(str[i + 1]))
		params->error = 2;
	i = i + 1;
	while (is_whitespace(str[i]))
		i++;
	while (ft_isdigit(str[i]) || str[i] == ',')
		i++;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] != '\0')
		params->error = 2;
}

void			ft_color_resolution(char **str, t_params *params, int i)
{
	params->i = 1;
	if (params->sizeline > 0 && (params->no == NULL || params->so == NULL ||
				params->we == NULL || params->ea == NULL || params->sp == NULL))
		params->error = 2;
	if (*str[i] == 'R')
	{
		check_r(*str, params);
		if (params->rx != 0 && params->ry != 0)
			params->error = 2;
		params->rx = ft_atoi2(*str, params);
		params->ry = ft_atoi2(*str, params);
		if (ft_atoi2(*str, params) > 0 || params->rx == 0 || params->ry == 0)
			params->error = 2;
	}
	else if (*str[i] == 'F')
	{
		check_fc(*str, params);
		params->f = ft_atoi3(*str, params);
	}
	else if (*str[i] == 'C')
	{
		check_fc(*str, params);
		params->c = ft_atoi3(*str, params);
	}
}
