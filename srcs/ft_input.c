/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:13:19 by dminh             #+#    #+#             */
/*   Updated: 2026/05/26 11:00:34 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_input(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(game->mlx_ptr, game->img);
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
		mlx_destroy_display(game->mlx_ptr);
		free(game->mlx_ptr);
		exit(EXIT_SUCCESS);
	}
	if (keysym == XK_S || keysym == XK_s || keysym == XK_W || keysym == XK_w
			|| keysym == XK_A || keysym == XK_a || keysym == XK_D
			|| keysym == XK_d || keysym == XK_Left || keysym == XK_Right)
		ft_movements(keysym, game);
	return (EXIT_SUCCESS);
}
