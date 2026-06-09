/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:46:53 by dminh             #+#    #+#             */
/*   Updated: 2026/06/09 11:03:51 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
