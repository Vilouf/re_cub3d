/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:49:30 by pespana           #+#    #+#             */
/*   Updated: 2025/11/26 12:01:20 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static void	calc_wall(t_struct *data, t_ray *ray)
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
	if (ray->side == 0)
		ray->wall_x = data->y_pos + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = data->x_pos + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
}

static void	init_draw_vars(t_struct *data, t_ray *ray, t_draw *draw)
{
	draw->tex = select_texture(data, ray);
	draw->tex_x = (int)(ray->wall_x * (float)draw->tex->width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		draw->tex_x = draw->tex->width - draw->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		draw->tex_x = draw->tex->width - draw->tex_x - 1;
	draw->tex_step = 1.0 * draw->tex->height / ray->line_height;
	draw->tex_pos = (ray->draw_start - WIN_HEIGHT / 2
			+ ray->line_height / 2) * draw->tex_step;
}

static void	draw_slice(t_struct *data, t_ray *ray, int x)
{
	t_draw	draw;
	int		y;
	int32_t	color;

	init_draw_vars(data, ray, &draw);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw.tex_y = (int)draw.tex_pos;
		draw.tex_pos += draw.tex_step;
		color = get_pixel_color(draw.tex, draw.tex_x, draw.tex_y);
		mlx_put_pixel(data->img, x, y, color);
		y++;
	}
}

void	raycast_walls(t_struct *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(data, &ray, x);
		calc_step(data, &ray);
		perform_dda(data, &ray);
		calc_wall(data, &ray);
		draw_slice(data, &ray, x);
		x++;
	}
}
