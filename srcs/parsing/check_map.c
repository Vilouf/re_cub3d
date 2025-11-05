/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:34:34 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/05 14:46:12 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_spawn_point(char c)
{
	return ((c == 'N') || (c == 'S') || (c == 'W') || (c == 'E'));
}

static int	check_walls(t_struct *data, int x, int y)
{
	if (x == 0 || y == 0)
		return (0);
	if (!(data->map[y + 1]))
		return (0);
	if (!(data->map[y + 1][x] == '1' || data->map[y + 1][x] == '0'
			|| is_spawn_point(data->map[y + 1][x])))
		return (0);
	if (!(data->map[y - 1][x] == '1' || data->map[y - 1][x] == '0'
			|| is_spawn_point(data->map[y - 1][x])))
		return (0);
	if (!(data->map[y][x + 1] == '1' || data->map[y][x + 1] == '0'
			|| is_spawn_point(data->map[y][x + 1])))
		return (0);
	if (!(data->map[y][x - 1] == '1' || data->map[y][x - 1] == '0'
			|| is_spawn_point(data->map[y][x - 1])))
		return (0);
	return (1);
}

static int	set_player_data(t_struct *data, int x, int y)
{
	if (!check_walls(data, x, y))
		return (0);
	if (data->x_pos != 0 || data->y_pos != 0)
		free_exit(data->gc, 2, "Error\nMore than one spawn point\n");
	data->x_pos = (float) x;
	data->y_pos = (float) y;
	if (data->map[y][x] == 'N')
		data->angle = (float) 90;
	else if (data->map[y][x] == 'S')
		data->angle = (float) 270;
	else if (data->map[y][x] == 'W')
		data->angle = (float) 180;
	else if (data->map[y][x] == 'E')
		data->angle = (float) 0;
	return (1);
}

int	is_map_valid(t_struct *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (is_spawn_point(data->map[y][x]))
			{
				if (!set_player_data(data, x, y))
					return (0);
			}
			else if (data->map[y][x] == '0')
			{
				if (!check_walls(data, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
