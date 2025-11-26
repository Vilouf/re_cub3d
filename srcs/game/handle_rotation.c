/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:51:38 by pespana           #+#    #+#             */
/*   Updated: 2025/11/26 12:01:16 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_ray(t_struct *data, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (float)WIN_WIDTH - 1;
	ray->ray_dir_x = data->dir_x + data->plane_x * ray->camera_x;
	ray->ray_dir_y = data->dir_y + data->plane_y * ray->camera_x;
	ray->map_x = (int)data->x_pos;
	ray->map_y = (int)data->y_pos;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	calc_step(t_struct *data, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->x_pos - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->x_pos) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->y_pos - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->y_pos) * ray->delta_dist_y;
	}
}

static void	rotate_player(t_struct *data, float angle)
{
	float	old_dir_x;
	float	old_plane_x;
	float	s;
	float	c;

	old_dir_x = data->dir_x;
	old_plane_x = data->plane_x;
	s = sin(angle);
	c = cos(angle);
	data->dir_x = data->dir_x * c - data->dir_y * s;
	data->dir_y = old_dir_x * s + data->dir_y * c;
	data->plane_x = data->plane_x * c - data->plane_y * s;
	data->plane_y = old_plane_x * s + data->plane_y * c;
}

void	handle_rotation(t_struct *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		rotate_player(data, ROT_SPEED);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		rotate_player(data, -ROT_SPEED);
	}
}

void	draw_floor_and_ceiling(t_struct *data)
{
	int		x;
	int		y;
	int32_t	floor_color;
	int32_t	ceiling_color;

	floor_color = get_rgba(data->color_f[0], data->color_f[1],
			data->color_f[2], 255);
	ceiling_color = get_rgba(data->color_c[0], data->color_c[1],
			data->color_c[2], 255);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx_put_pixel(data->img, x, y, ceiling_color);
			else
				mlx_put_pixel(data->img, x, y, floor_color);
			x++;
		}
		y++;
	}
}
