/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 09:25:55 by pespana           #+#    #+#             */
/*   Updated: 2025/10/31 09:41:04 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_keypress(int keycode, t_struct *data)
{
	if (keycode == KEY_ESC)
		free_exit(data->gc, 0, "Closing cub3d.\n");
	return (0);
}

int	handle_close_window(t_struct *data)
{
	free_exit(data->gc, 0, "Closing cub3d.\n");
	return (0);
}
