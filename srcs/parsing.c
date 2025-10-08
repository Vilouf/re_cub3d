/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:11:42 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/08 15:08:10 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_color_nums(char **nums)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!nums)
		return (0);
	while (nums[i])
	{
		if (i == 3)
			return (0);
		while (nums[i][j])
		{
			if (nums[i][j] < '0' || nums[i][j] > '9' || j > 2)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	get_color(t_struct *data, char* color, int type)
{
	char	**nums;
	int	i;

	nums = ft_split(color, ',', data->gc);
	if (check_color_nums(nums))
		return (0);
	i = 0;
	while (i < 3)
	{
		if (type == 1)
			data->color_f[i] = ft_atoi(nums[i]);
		else
			data->color_c[i] = ft_atoi(nums[i]);
		i++;
	}
	return (1);
}

int	check_id(t_struct *data, char **words)
{
	if (!words || !ft_strcmp(words[0], "\n"))
		return (1);
	if (!ft_strcmp(words[0], "NO"))
	{
		data->txt_no = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "SO"))
	{
		data->txt_so = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "WE"))
	{
		data->txt_we = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "EA"))
	{
		data->txt_ea = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "F"))
		return (get_color(data, words[1], 1));
	else if (!ft_strcmp(words[0], "C"))
		return (get_color(data, words[1], 2));
	else
		return (0);
	return (1);
}

int	set_map(t_struct *data, char *line)
{
	int	i;

	i = 0;
	(void) data;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
	//ici il faudra mettre un prototype de la map qu'on mettra en carre juste apres
	//faut il read plusieurs fois map.cub pour determiner le nombre de lignes?
}

void	ft_print_elements(t_struct *data)
{
	printf("NO: %s\n", data->txt_no);
	printf("SO: %s\n", data->txt_so);
	printf("WE: %s\n", data->txt_we);
	printf("EA: %s\n", data->txt_ea);
	printf("F: %d,%d,%d\n", data->color_f[0], data->color_f[1], data->color_f[2]);
	printf("C: %d,%d,%d\n", data->color_c[0], data->color_c[1], data->color_c[2]);
}

void	parsing(t_struct *data, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!check_id(data, ft_split(line, ' ', data->gc)))
			break ;
		ft_free(line);
		line = get_next_line(fd);
	}
	ft_free(line);
	ft_print_elements(data);
	line = get_next_line(fd);
	while (line)
	{
		set_map(data, line);
		ft_free(line);
		line = get_next_line(fd);
	}
	ft_free(line);
	close(fd);
}
