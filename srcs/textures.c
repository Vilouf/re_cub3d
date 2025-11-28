/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 23:46:14 by pespana           #+#    #+#             */
/*   Updated: 2025/11/28 19:53:18 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_textures(t_struct *data)
{
	if (data->tex_no)
		mlx_delete_texture(data->tex_no);
	if (data->tex_so)
		mlx_delete_texture(data->tex_so);
	if (data->tex_we)
		mlx_delete_texture(data->tex_we);
	if (data->tex_ea)
		mlx_delete_texture(data->tex_ea);
}

void	load_textures(t_struct *data)
{
	data->tex_no = mlx_load_png(data->txt_no);
	if (!data->tex_no)
	{
		cleanup_textures(data);
		free_exit(data->gc, 1, "Error\nFailed to load NO texture\n");
	}
	data->tex_so = mlx_load_png(data->txt_so);
	if (!data->tex_so)
	{
		cleanup_textures(data);
		free_exit(data->gc, 1, "Error\nFailed to load SO texture\n");
	}
	data->tex_we = mlx_load_png(data->txt_we);
	if (!data->tex_we)
	{
		cleanup_textures(data);
		free_exit(data->gc, 1, "Error\nFailed to load WE texture\n");
	}
	data->tex_ea = mlx_load_png(data->txt_ea);
	if (!data->tex_ea)
	{
		cleanup_textures(data);
		free_exit(data->gc, 1, "Error\nFailed to load EA texture\n");
	}
}
