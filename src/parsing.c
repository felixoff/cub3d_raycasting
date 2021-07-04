/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:44:40 by nikita            #+#    #+#             */
/*   Updated: 2020/12/29 12:30:21 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int		ft_path_texture2(char *str, t_params *params, int j)
{
	if (!is_whitespace(str[j]) && str[j] != '\0')
		params->error = 2;
	while (is_whitespace(str[j]))
		j++;
	if (str[j] != '\0')
		params->error = 2;
	return (0);
}

int				ft_path_texture(char *str, char **texture,
t_params *params, int j)
{
	params->count2 = 0;
	if (*texture != NULL)
	{
		params->error = 2;
		return (0);
	}
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
			|| ft_strlen2(str) <= 2)
		params->error = 2;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			params->error = 2;
		j++;
	}
	if (!(*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)))))
		params->error = 2;
	while (str[j] != '\0' && str[j] != ' ')
	{
		(*texture)[params->count2] = str[j];
		params->count2++;
		j++;
	}
	(*texture)[params->count2] = '\0';
	return (ft_path_texture2(str, params, j));
}

void			ft_texture(char *str, t_params *params)
{
	int			i;
	static int	j = 0;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		ft_path_texture(str, &params->no, params, i + 3);
	else if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		ft_path_texture(str, &params->so, params, i + 3);
	else if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		ft_path_texture(str, &params->we, params, i + 3);
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		ft_path_texture(str, &params->ea, params, i + 3);
	else if (str[i] == 'S' && str[i + 1] == ' ')
		ft_path_texture(str, &params->sp, params, i + 2);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
			&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C'
			&& str[0] > 65 && str[0] < 122)
		params->error = 2;
	j++;
}

static void		ft_parsing2(char *str, t_params *params)
{
	if (params->rx > 0 && params->c > 0 && params->sp != NULL &&
	params->ea != NULL && params->we != NULL && params->no != NULL &&
	params->so != NULL && params->f > 0 && params->nblines > 0 &&
	ft_charinstr(str, '1') == 0 && ft_charinstr(str, '0') == 0)
		params->error = 2;
	if (params->error == 2)
		ft_error(params, "Ошибка в процессе парсинга\n");
}

void			ft_parsing(char *fichier, t_params *params)
{
	int			fd;
	int			ret;
	char		*str;

	ret = 1;
	str = NULL;
	if ((fd = open(fichier, O_DIRECTORY)) != -1)
		ft_error(params, "Невалидно: это директория\n");
	if ((fd = open(fichier, O_RDONLY)) == -1)
		ft_error(params, "Невалидный файл\n");
	params->error = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, params);
		ft_parsing2(str, params);
		ft_color_resolution(&str, params, 0);
		ft_texture(str, params);
		ft_map(str, params);
		free(str);
	}
	close(fd);
	if (params->sizeline == 0 || params->nblines == 0)
		ft_error(params, "Пустая карта\n");
	ft_parsing_map(fichier, params);
}
