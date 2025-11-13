/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:34:18 by pespana           #+#    #+#             */
/*   Updated: 2025/11/13 23:22:25 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	init_ray(t_struct *data, t_ray *ray, int x)
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

static void	calc_step(t_struct *data, t_ray *ray)
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

static void	perform_dda(t_struct *data, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

static void	calc_wall(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

static void	draw_slice(t_struct *data, t_ray *ray, int x)
{
	int	y;

	if (ray->side == 1)
		ray->color = get_rgba(0, 200, 0, 255);
	else
		ray->color = get_rgba(200, 0, 0, 255);

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		mlx_put_pixel(data->img, x, y, ray->color);
		y++;
	}
}

static void	raycast_walls(t_struct *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		calc_step(data, &ray);
		perform_dda(data, &ray);
		calc_wall(&ray);
		draw_slice(data, &ray, x);
		x++;
	}
}

static void	handle_movement(t_struct *data)
{
	float	new_x;
	float	new_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		new_x = data->x_pos + data->dir_x * MOVE_SPEED;
		new_y = data->y_pos + data->dir_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)new_x] != '1')
		{
			data->x_pos = new_x;
			data->y_pos = new_y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = data->x_pos - data->dir_x * MOVE_SPEED;
		new_y = data->y_pos - data->dir_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)new_x] != '1')
		{
			data->x_pos = new_x;
			data->y_pos = new_y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		new_x = data->x_pos + data->plane_x * MOVE_SPEED;
		new_y = data->y_pos + data->plane_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)new_x] != '1')
		{
			data->x_pos = new_x;
			data->y_pos = new_y;
		}
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		new_x = data->x_pos - data->plane_x * MOVE_SPEED;
		new_y = data->y_pos - data->plane_y * MOVE_SPEED;
		if (data->map[(int)new_y][(int)new_x] != '1')
		{
			data->x_pos = new_x;
			data->y_pos = new_y;
		}
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

static void	handle_rotation(t_struct *data)
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

static void	draw_floor_and_ceiling(t_struct *data)
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

void	game_hook(void *param)
{
	t_struct *data;

	data = (t_struct *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(data->mlx);
		return ;
	}
	handle_movement(data);
	handle_rotation(data);
	draw_floor_and_ceiling(data);
	raycast_walls(data);
}
