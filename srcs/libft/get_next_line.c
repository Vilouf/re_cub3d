/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:36:32 by vielblin          #+#    #+#             */
/*   Updated: 2025/09/23 17:54:20 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*prepare_next_line(char *str)
{
	int		i;
	char	*next_line;

	i = 0;
	while (str[i] != '\n' && str[i] != 0)
		i++;
	if (str[i] == 0)
		return (free(str), NULL);
	next_line = ft_substr2(str, i + 1, ft_strlen2(str));
	if (!next_line)
		return (free(str), NULL);
	free(str);
	return (next_line);
}

static char	*get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\n' && str[i] != 0)
		i++;
	line = ft_substr2(str, 0, i + 1);
	return (line);
}

static char	*read_line(int fd, char *str)
{
	char	*buf;
	int		check_read;

	buf = ft_calloc2(BUFFER_SIZE + 1, sizeof (char));
	if (!buf)
		return (NULL);
	check_read = 1;
	while (check_read > 0 && !ft_strchr2(buf, '\n'))
	{
		check_read = read(fd, buf, BUFFER_SIZE);
		if (check_read == -1)
		{
			if (str)
				free(str);
			return (free(buf), NULL);
		}
		buf[check_read] = 0;
		if (check_read != 0)
		{
			str = ft_strjoin2(str, buf);
			if (!str)
				return (free(buf), NULL);
		}
	}
	return (free(buf), str);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*ret_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_line(fd, str);
	if (!str)
		return (NULL);
	ret_line = get_line(str);
	if (ret_line == NULL)
		return (NULL);
	str = prepare_next_line(str);
	return (ret_line);
}
