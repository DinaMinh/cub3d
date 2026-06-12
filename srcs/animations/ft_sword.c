/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sword.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:28:45 by dminh             #+#    #+#             */
/*   Updated: 2026/06/12 11:45:21 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static unsigned int	ft_weapon_color(t_textures *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_length
			+ x * (texture->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	ft_draw_weapon(t_game *game, t_textures *sword)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;

	game->sword_anim.start_x = W_WIDTH - (game->sword_anim.size * SWORD_SCALE)
		- SWORD_PADDING;
	game->sword_anim.start_y = W_HEIGHT - (game->sword_anim.size * SWORD_SCALE);
	y = 0;
	while (y < game->sword_anim.size * SWORD_SCALE)
	{
		x = 0;
		while (x < game->sword_anim.size * SWORD_SCALE)
		{
			tex_x = x / SWORD_SCALE;
			tex_y = y / SWORD_SCALE;
			game->sword_anim.color = ft_weapon_color(sword, tex_x, tex_y);
			if (game->sword_anim.color != FBLACK
				&& game->sword_anim.color != BLACK)
				ft_pixel_put(game, game->sword_anim.start_x + x,
					game->sword_anim.start_y + y, game->sword_anim.color);
			x++;
		}
		y++;
	}
}

void	ft_sword_animation(t_game *game, long long current_frame)
{
	if (game->key[E] == 1)
	{
		if (game->sword_anim.start_time == 0)
			game->sword_anim.start_time = ft_get_time();
		if (current_frame - game->sword_anim.start_time <= 100)
			ft_draw_weapon(game, &game->sword_anim.frame1);
		else if (current_frame - game->sword_anim.start_time > 100
			&& current_frame - game->sword_anim.start_time <= 200)
			ft_draw_weapon(game, &game->sword_anim.frame2);
		else
		{
			game->sword_anim.start_time = 0;
			game->key[E] = 0;
		}
	}
	else
		ft_draw_weapon(game, &game->sword);
}
