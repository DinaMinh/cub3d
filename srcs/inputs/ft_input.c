/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/26 10:13:19 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 09:50:46 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_key_press(int keysym, t_game *game)
{
	if (keysym == XK_W || keysym == XK_w)
		game->key[UP] = 1;
	else if (keysym == XK_S || keysym == XK_s)
		game->key[DOWN] = 1;
	else if (keysym == XK_A || keysym == XK_a)
		game->key[LEFT] = 1;
	else if (keysym == XK_D || keysym == XK_d)
		game->key[RIGHT] = 1;
	else if (keysym == XK_Left)
		game->key[L_ARROW] = 1;
	else if (keysym == XK_Right)
		game->key[R_ARROW] = 1;
}

void	ft_key_release(int keysym, t_game *game)
{
	if (keysym == XK_W || keysym == XK_w)
		game->key[UP] = 0;
	else if (keysym == XK_S || keysym == XK_s)
		game->key[DOWN] = 0;
	else if (keysym == XK_A || keysym == XK_a)
		game->key[LEFT] = 0;
	else if (keysym == XK_D || keysym == XK_d)
		game->key[RIGHT] = 0;
	else if (keysym == XK_Left)
		game->key[L_ARROW] = 0;
	else if (keysym == XK_Right)
		game->key[R_ARROW] = 0;
}

int	ft_input(int keysym, t_game *game)
{
	int	offset;
	int	d_x;
	int	d_y;

	offset = TILES;
	d_x = (int)(game->player.pos_x + (game->player.dir_x * offset)) / TILES;
	d_y = (int)(game->player.pos_y + (game->player.dir_y * offset)) / TILES;
	if (keysym == XK_Escape)
		ft_clean_exit(game);
	if (keysym == XK_S || keysym == XK_s || keysym == XK_W || keysym == XK_w
		|| keysym == XK_A || keysym == XK_a || keysym == XK_D
		|| keysym == XK_d || keysym == XK_Left || keysym == XK_Right)
		ft_key_press(keysym, game);
	if (keysym == XK_E || keysym == XK_e)
	{
		if (game->map.grid[d_y][d_x] == 'D')
		{
			game->d_anim.open_x = d_x;
			game->d_anim.open_y = d_y;
			game->d_anim.opening = true;
			game->d_anim.start_time = ft_get_time();
		}
		game->key[E] = 1;
	}
	return (EXIT_SUCCESS);
}

int	ft_release(int keysym, t_game *game)
{
	if (keysym == XK_S || keysym == XK_s || keysym == XK_W || keysym == XK_w
		|| keysym == XK_A || keysym == XK_a || keysym == XK_D
		|| keysym == XK_d || keysym == XK_Left || keysym == XK_Right)
		ft_key_release(keysym, game);
	return (EXIT_SUCCESS);
}
