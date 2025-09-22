/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:37:27 by vielblin          #+#    #+#             */
/*   Updated: 2025/09/22 14:01:00 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_struct	data;
	char		**test;

	(void)ac;
	(void)av;
	ft_memset(&data, 0, sizeof(t_struct));
	init_gc(&(data.gc));
	test = gc_malloc(data.gc, 10 * sizeof(char *));
	for (int i = 0; i < 10; i++)
	{
		test[i] = gc_malloc(data.gc, 1);
	}
	free_exit(data.gc, 0);
	return (0);
}