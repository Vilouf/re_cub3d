/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 15:11:42 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/21 02:41:34 by vielblin         ###   ########.fr       */
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

int	check_map(t_struct *data, char *line)
{
	int	i;

	i = 0;
	(void) data;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'W' 
			&& line[i] != 'E' && line[i] != '\n')
			return (0);
		i++;
	}
	ft_lstadd_back(&(data->lst_map), \
		ft_lstnew(data->gc, ft_strdup(data->gc, line)));
	return (1);
}

int	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*set_map_line(char *line, int x, t_gc *gc)
{
	char	*ret;
	int		i;

	i = 0;
	ret = gc_malloc(gc, (x + 1) * sizeof(char));
	while  (i < x)
	{
		if (i < ft_strlen(line))
		{
			if (line[i] != ' ')
				ret[i] = line[i];
			else
				ret[i] = '2';
		}
		else
			ret[i] = '2';
		i++;
	}
	ret[i] = 0;
	return (ret);
}

void	set_map(t_struct *data, int x)
{
	t_list	*tmp;
	int		i;

	tmp = data->lst_map;
	i = 0;
	while (tmp)
	{
		data->map[i] = set_map_line(tmp->data, x, data->gc);
		i++;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
}

void	parse_map(t_struct *data)
{
	int		i;
	int		x;
	int		y;
	t_list	*tmp;

	tmp = data->lst_map;
	x = 0;
	y = 0;
	i = 0;
	while (tmp)
	{
		while (tmp->data[i])
			i++;
		if (i > x)
			x = i;
		i = 0;
		y++;
		tmp = tmp->next;
	}
	data->map = gc_malloc(data->gc, (y + 1) * sizeof(char *));
	set_map(data, x);
}

void	ft_print_elements(t_struct *data)
{
	printf("NO: %s\n", data->txt_no);
	printf("SO: %s\n", data->txt_so);
	printf("WE: %s\n", data->txt_we);
	printf("EA: %s\n", data->txt_ea);
	printf("F: %d,%d,%d\n", data->color_f[0], data->color_f[1], data->color_f[2]);
	printf("C: %d,%d,%d\n", data->color_c[0], data->color_c[1], data->color_c[2]);

	// t_list	*test = data->lst_map;

	// while (test)
	// {
	// 	printf("%s\n", test->data);
	// 	test = test->next;
	// }
	for(int i = 0; data->map[i]; i++)
	{
		for(int j = 0; data->map[i][j]; j++)
		{
			write(1, &data->map[i][j], 1);
		}
		write(1, "\n", 1);
	}
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
	while (line)
	{
		check_map(data, line);
		ft_free(line);
		line = get_next_line(fd);
	}
	ft_free(line);
	parse_map(data);
	ft_print_elements(data);
	close(fd);
}
