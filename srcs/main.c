/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:37:27 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/29 14:22:08 by vielblin         ###   ########.fr       */
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
		return (ft_putstr_fd("Args Error\n", 2), 1);
	ft_memset(&data, 0, sizeof(t_struct));
	init_gc(&(data.gc));
	init_colors(&data);
	parsing(&data, av[1]);
	return (free_exit(data.gc, 0, NULL), 0);
}