/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:45:57 by pespana           #+#    #+#             */
/*   Updated: 2025/12/02 20:15:46 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	handle_movement_w(t_struct *data)
{
	float	new_x;
	float	new_y;

	new_x = data->x_pos + data->dir_x * MOVE_SPEED;
	new_y = data->y_pos + data->dir_y * MOVE_SPEED;
	if (data->map[(int)new_y][(int)data->x_pos] != '1'
		&& data->map[(int)data->y_pos][(int)new_x] != '1'
		&& data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_pos = new_x;
		data->y_pos = new_y;
	}
}

static void	handle_movement_s(t_struct *data)
{
	float	new_x;
	float	new_y;

	new_x = data->x_pos - data->dir_x * MOVE_SPEED;
	new_y = data->y_pos - data->dir_y * MOVE_SPEED;
	if (data->map[(int)new_y][(int)data->x_pos] != '1'
		&& data->map[(int)data->y_pos][(int)new_x] != '1'
		&& data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_pos = new_x;
		data->y_pos = new_y;
	}
}

static void	handle_movement_d(t_struct *data)
{
	float	new_x;
	float	new_y;

	new_x = data->x_pos + data->plane_x * MOVE_SPEED;
	new_y = data->y_pos + data->plane_y * MOVE_SPEED;
	if (data->map[(int)new_y][(int)data->x_pos] != '1'
		&& data->map[(int)data->y_pos][(int)new_x] != '1'
		&& data->map[(int)new_y][(int)new_x] != '1')
	{
		data->x_pos = new_x;
		data->y_pos = new_y;
	}
}

void	handle_movement(t_struct *data)
{
	float	new_x;
	float	new_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		handle_movement_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		handle_movement_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		handle_movement_d(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		new_x = data->x_pos - data->plane_x * MOVE_SPEED;
		new_y = data->y_pos - data->plane_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)data->x_pos] != '1'
			&& data->map[(int)data->y_pos][(int)new_x] != '1'
			&& data->map[(int)new_y][(int)new_x] != '1')
		{
			data->x_pos = new_x;
			data->y_pos = new_y;
		}
	}
}
