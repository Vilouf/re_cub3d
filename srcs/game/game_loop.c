/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 22:34:18 by pespana           #+#    #+#             */
/*   Updated: 2025/12/02 20:15:48 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int32_t	get_pixel_color(mlx_texture_t *tex, int x, int y)
{
	int	pos;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= (int)tex->width)
		x = tex->width - 1;
	if (y >= (int)tex->height)
		y = tex->height - 1;
	pos = (y * tex->width + x) * tex->bytes_per_pixel;
	return (get_rgba(tex->pixels[pos],
			tex->pixels[pos + 1],
			tex->pixels[pos + 2],
			tex->pixels[pos + 3]));
}

mlx_texture_t	*select_texture(t_struct *data, t_ray *ray)
{
	if (ray->side == 1)
	{
		if (ray->ray_dir_y > 0)
			return (data->tex_so);
		else
			return (data->tex_no);
	}
	else
	{
		if (ray->ray_dir_x > 0)
			return (data->tex_ea);
		else
			return (data->tex_we);
	}
}

void	game_hook(void *param)
{
	t_struct	*data;

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
