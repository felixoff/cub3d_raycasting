/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 11:15:44 by nikita            #+#    #+#             */
/*   Updated: 2020/12/29 12:34:36 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int						ft_murs_util(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

static int				ft_copy_map2(char *str, t_params *params, int i, int k)
{
	int j;

	j = 0;
	while (str[k] != '\0' && (j < params->sizeline))
	{
		if (ft_depart(str[k], params, i, j) == 1)
			params->map[i][j] = '0';
		else if (str[k] == ' ')
			if (i == 0 || str[k - 1] == '0' || str[k + 1] == '0')
				params->map[i][j] = '0';
			else
				params->map[i][j] = params->map[i - 1][j];
		else
			params->map[i][j] = str[k];
		j++;
		k++;
	}
	while (k <= (params->sizeline - 1))
	{
		params->map[i][j] = '1';
		j++;
	}
	params->map[i][j] = '\0';
	return (0);
}

int						ft_copy_map(char *str, t_params *params)
{
	static int	i = 0;
	int			j;
	int			k;
	int			d;

	j = 0;
	k = 0;
	d = i;
	params->map[i] = NULL;
	while (is_whitespace(str[k]))
		k++;
	while (str[j] != '\0')
		j++;
	j--;
	while (is_whitespace(str[j]))
		j--;
	params->sizeline = j - k + 1;
	j = 0;
	if (!(params->map[i] = malloc(sizeof(char) * params->sizeline + 1)))
		return (0);
	i++;
	return (ft_copy_map2(str, params, d, k));
}
