/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:37:27 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/13 22:42:47 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_colors(t_struct *data)
{
	data->color_c[0] = -1;
	data->color_c[1] = -1;
	data->color_c[2] = -1;
	data->color_f[0] = -1;
	data->color_f[1] = -1;
	data->color_f[2] = -1;
}

int	main(int ac, char **av)
{
	t_struct	data;

	if (ac != 2)
		return (ft_putstr_fd("Error\nWrong Args\n", 2), 1);
	ft_memset(&data, 0, sizeof(t_struct));
	init_gc(&(data.gc));
	init_colors(&data);
	parsing(&data, av[1]);
	data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!data.mlx)
		free_exit(data.gc, 1, "Error\nMLX init failed\n");
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.img)
	{
		mlx_close_window(data.mlx);
		free_exit(data.gc, 1, "Error\nMLX image creation failed\n");
	}
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		free_exit(data.gc, 1, "Error\nMLX image to window failed\n");
	}
	mlx_loop_hook(data.mlx, game_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (free_exit(data.gc, 0, NULL), 0);
}
