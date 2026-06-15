/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:46:53 by dminh             #+#    #+#             */
/*   Updated: 2026/06/13 10:28:33 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		printf("Error\nUsage: ./cub3D <file.cub>\n");
		return (EXIT_FAILURE);
	}
	ft_memset(&game, 0, sizeof(game));
	init_map_struct(&game.map);
	if (!parse_cub(av[1], &game.map)
		|| !build_final_map(&game.map)
		|| !validate_map_walls(&game.map))
	{
		printf("error map\n");
		ft_clean_exit(&game, EXIT_FAILURE);
	}
	ft_starting_orientation(&game);
	ft_game(&game);
	return (0);
}
