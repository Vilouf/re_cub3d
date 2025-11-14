/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:07:15 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/14 02:11:28 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_extention(t_struct *data, char *file)
{
	int	len;

	len = ft_strlen(file);
	if (ft_strcmp(&file[len - 4], ".cub") != 0)
		free_exit(data->gc, 1, "Error\nWrong file extention\n");
}

static int	check_map(t_struct *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' '
			&& !is_spawn_point(line[i]) && line[i] != '\n')
			return (0);
		i++;
	}
	ft_lstadd_back(&(data->lst_map),
		ft_lstnew(data->gc, ft_strdup(data->gc, line)));
	return (1);
}

static void	read_map(t_struct *data, char *line, int fd)
{
	while (line)
	{
		if (!check_map(data, line))
		{
			ft_free(line);
			free_exit(data->gc, 2, "Error\nInvalid Map\n");
		}
		ft_free(line);
		line = get_next_line(fd);
		if (!line || !ft_strcmp(line, "\n"))
			break ;
	}
	while (line)
	{
		if (ft_strcmp(line, "\n"))
		{
			ft_free(line);
			free_exit(data->gc, 2, "Error\nMap is not last element!\n");
		}
		ft_free(line);
		line = get_next_line(fd);
	}
	ft_free(line);
}

static void	read_data(t_struct *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (!check_id(data, ft_split(line, ' ', data->gc)))
			break ;
		ft_free(line);
		line = get_next_line(fd);
	}
	if (!check_data(data))
	{
		ft_free(line);
		free_exit(data->gc, 2, "Error\nInvalid Data\n");
	}
	read_map(data, line, fd);
}

// //TEST FUNCTION
// void	ft_print_elements(t_struct *data)
// {
// 	printf("NO: %s\n", data->txt_no);
// 	printf("SO: %s\n", data->txt_so);
// 	printf("WE: %s\n", data->txt_we);
// 	printf("EA: %s\n", data->txt_ea);
// 	printf("F: %d,%d,%d\n", data->color_f[0], data->color_f[1], data->color_f[2]);
// 	printf("C: %d,%d,%d\n", data->color_c[0], data->color_c[1], data->color_c[2]);

// 	for(int i = 0; data->map[i]; i++)
// 	{
// 		for(int j = 0; data->map[i][j]; j++)
// 		{
// 			write(1, &data->map[i][j], 1);
// 		}
// 		write(1, "\n", 1);
// 	}
// 	printf("x_pos = %f\ny_pos = %f\n", data->x_pos, data->y_pos);
// }

void	parsing(t_struct *data, char *file)
{

	check_map_extention(data, file);
	data->fd = open(file, O_RDONLY);
	if (data->fd == -1)
		free_exit(data->gc, 2, "Error\nInvalid file name\n");
	read_data(data, data->fd);
	parse_map(data);
	if (!is_map_valid(data))
		free_exit(data->gc, 2, "Error\nEmpty space not surrounded by walls\n");
	if (data->x_pos == 0 || data->y_pos == 0)
		free_exit(data->gc, 2, "Error\nMust have spawn point\n");
	// ft_print_elements(data);
	close(data->fd);
}
