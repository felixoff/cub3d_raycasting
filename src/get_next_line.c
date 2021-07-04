/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikita <nikita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 17:52:05 by sjennett          #+#    #+#             */
/*   Updated: 2020/12/25 12:44:09 by nikita           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int			checker(char *save, char **line, int *flag, char **p)
{
	*p = NULL;
	if (!(*flag = 0) && save)
	{
		if ((*p = ft_strchr(save, '\n')))
		{
			*flag = 1;
			**p = '\0';
			if (!(*line = ft_strdup(save)))
				return (-1);
			ft_strcpy(save, ++(*p));
		}
		else
		{
			if (!(*line = ft_strdup(save)))
				return (-1);
			save[0] = '\0';
		}
	}
	else
	{
		if (!(*line = malloc(sizeof(char) * 1)))
			return (-1);
		(*line)[0] = '\0';
	}
	return (1);
}

int			ft_get_line3(int *flag, char **save, char **p)
{
	*flag = 1;
	if (*save != NULL)
		free(*save);
	if (!(*save = ft_strdup(++(*p))))
		return (-1);
	return (0);
}

int			ft_get_line2(int fd, char *buffer, char **line, char **save)
{
	char	*tmp;
	int		flag;
	char	*p;
	int		reader;

	if (checker(*save, line, &flag, &p) == -1)
		return (-1);
	while (p == 0 && ((reader = read(fd, buffer, BUFFER_SIZE)) != 0))
	{
		if (reader == -1)
			return (-1);
		buffer[reader] = '\0';
		if ((p = ft_strchr(buffer, '\n')))
			if (ft_get_line3(&flag, save, &p) == -1)
				return (-1);
		tmp = *line;
		if (!(*line = ft_strjoin(tmp, buffer)))
		{
			free(tmp);
			return (-1);
		}
		free(tmp);
	}
	return (!ft_strlen(*save) && !reader && !flag) ||
	(!(reader || ft_strlen(*line) || flag == 1)) ? 0 : 1;
}

int			get_line(int fd, char **line, char **save)
{
	char		*buffer;
	int			res;

	*line = NULL;
	if (!(buffer = malloc(sizeof(char)
	* (BUFFER_SIZE > 0 ? BUFFER_SIZE + 1 : 1))))
		return (-1);
	res = (ft_get_line2(fd, buffer, line, save));
	free(buffer);
	return (res);
}

int			get_next_line(int fd, char **line, t_params *params)
{
	static char		*masfd[1025];
	int				res;

	if (params->error == 2)
		params->error = 2;
	if (fd < 0 || !line || read(fd, 0, 0) || BUFFER_SIZE < 0 || fd > 1025)
	{
		if (line)
			*line = NULL;
		return (-1);
	}
	if (BUFFER_SIZE == 0)
	{
		*line = NULL;
		return (0);
	}
	res = get_line(fd, line, &(masfd[fd]));
	if (res <= 0 && masfd[fd] != NULL)
	{
		free(masfd[fd]);
		masfd[fd] = NULL;
	}
	return (res);
}
