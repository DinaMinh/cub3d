/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:46:53 by dminh             #+#    #+#             */
/*   Updated: 2026/06/08 16:28:03 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_click_cross(t_game *game)
{
	int	i;

	i = 0;
	if (game->map.grid)
	{
		while (game->map.grid[i])
			free(game->map.grid[i++]);
		free(game->map.grid);
	}
	if (game->map.no_tex_path)
		free(game->map.no_tex_path);
	if (game->map.so_tex_path)
		free(game->map.so_tex_path);
	if (game->map.we_tex_path)
		free(game->map.we_tex_path);
	if (game->map.ea_tex_path)
		free(game->map.ea_tex_path);
	if (game->map.raw_map)
		ft_lstclear(&game->map.raw_map, free);
	mlx_destroy_image(game->mlx_ptr, game->img);
	mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	mlx_destroy_display(game->mlx_ptr);
	free(game->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

long long	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void	ft_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > W_HEIGHT || x < 0 || x > W_WIDTH)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_pixel_put_map(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (y < 0 || y > 250 || x < 0 || x > 250)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw_square(t_game *game, int x, int y, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			ft_pixel_put(game, x + j, y + i, YELLOW);
			j++;
		}
		i++;
	}
}

void	ft_draw_square_map(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < M_TILES)
	{
		j = 0;
		while (j < M_TILES)
		{
			if (j == M_TILES - 1 || i == M_TILES - 1)
				ft_pixel_put_map(game, x + j, y + i, 0x00000000);
			else
				ft_pixel_put_map(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_game *game)
{
	float	delta_x;
	float	delta_y;
	int	x;
	int	y;
	int	color;

	y = 0;
	while (game->map.grid[y])
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			delta_x = x * TILES - game->player.pos_x;
			delta_y = y * TILES - game->player.pos_y;
			game->screen_x = CENTER_X + (delta_x / M_SCALE);
			game->screen_y = CENTER_Y + (delta_y / M_SCALE);
			if (game->map.grid[y][x] == '1')
				color = WHITE;
			else if (game->map.grid[y][x] == '0')
				color = PURPLE;
			if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == '0')
				ft_draw_square_map(game, game->screen_x, game->screen_y, color);
			x++;
		}
		y++;
	}
	ft_draw_square(game, CENTER_X - (PLAYER_W / 2), CENTER_Y - (PLAYER_W / 2), PLAYER_W);
	ft_draw_minimap_rays(game);
}

int	ft_game_hook(t_game *game)
{
	static long long	last_frame = 0;
	long long			current_frame;

	current_frame = ft_get_time();
	if (current_frame - last_frame >= MS / FPS)
	{
		last_frame = current_frame;
		ft_memset(game->addr, 0, W_HEIGHT * game->line_length);
		ft_movements(game);
	}
	ft_draw_rays(game);
	ft_draw_map(game);
	mlx_put_image_to_window(game->mlx_ptr, game->win_ptr, game->img, 0, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3D <file.cub>\n");
		return (1);
	}
	ft_memset(&game, 0, sizeof(game));
	init_map_struct(&game.map);
	if (!parse_cub(av[1], &game.map)
			|| !build_final_map(&game.map)
			|| !validate_map_walls(&game.map))
	{
		printf("error map\n");
		return (1);
	}
	print_map_struct(&game.map, "Après Initialisation");
	ft_starting_orientation(&game);
	ft_game(&game);
	return (0);
}
