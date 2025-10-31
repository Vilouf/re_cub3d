/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 07:21:27 by pespana           #+#    #+#             */
/*   Updated: 2025/10/31 09:22:48 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_struct *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		free_exit(data->gc, 1, "Error\nmlx_init()\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (data->win_ptr == NULL)
		free_exit(data->gc, 1, "Error\nmlx_new_window()\n");
	data->img_ptr = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (data->img_ptr == NULL)
		free_exit(data->gc, 1, "Error\nmlx_new_image()\n");
	data->img_addr = mlx_get_data_addr(data->img_ptr, &(data->bits_per_pixel),
									&(data->line_length), &(data->endian));
									
	if (data->img_addr == NULL)
		free_exit(data->gc, 1, "Error\nmlx_get_data_addr()\n");
}
