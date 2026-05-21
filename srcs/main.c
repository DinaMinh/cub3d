/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:46:53 by dminh             #+#    #+#             */
/*   Updated: 2026/05/21 15:20:02 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	ft_click_cross(t_game game)
{
	mlx_destroy_window(game.mlx_ptr, game.win_ptr);
	mlx_destroy_display(game.mlx_ptr);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int	main(void)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(game));
	game.mlx_ptr = mlx_init();
	if (!game.mlx_ptr)
		return (EXIT_FAILURE);
	game.win_ptr = mlx_new_window(game.mlx_ptr, 1920, 1080, "cub3D");
	if (!game.win_ptr)
	{
		mlx_destroy_display(game.mlx_ptr);
		return (EXIT_FAILURE);
	}
	mlx_hook(game.win_ptr, DestroyNotify, StructureNotifyMask, &ft_click_cross, &game)
	mlx_loop(game.mlx_ptr);
	return (0);
}
