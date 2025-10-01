/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:11:42 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/01 17:35:18 by vielblin         ###   ########.fr       */
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
}

int	check_id(t_struct *data, char **words)
{
	if (!words)
		return (0);
	if (ft_strcmp(words[0], "NO"))
		data->txt_no = words[1];
	else if (ft_strcmp(words[0], "SO"))
		data->txt_so = words[1];
	else if (ft_strcmp(words[0], "WE"))
		data->txt_we = words[1];
	else if (ft_strcmp(words[0], "EA"))
		data->txt_ea = words[1];
	else if (ft_strcmp(words[0], "F"))
		return (get_color(data, words[1]), 1);
	else if (ft_strcmp(words[0], "C"))
		return (get_color(data, words[1]), 2);
	else
		return (0);
	return (1)
}

void	parsing(t_struct *data, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	// gc_addback(&(data->gc->leaf), gc_lstnew((void *) line));
	while (line)
	{
		check_id(data, ft_split(line, ' ', data->gc))
		line = get_next_line(fd);
		// gc_addback(&(data->gc->leaf), gc_lstnew((void *) line));
	}
	close(fd);
}