/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dminh <dminh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:47:31 by dminh             #+#    #+#             */
/*   Updated: 2026/05/21 15:14:58 by dminh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include "mlx.h"
# include "libft.h"

# define TILES

typedef struct s_player
{
	float	pos_x;
	float	pos_y;
	float	dir_x;
	float	dir_y;
	float	plane_x;
	float	plane_y;
}	t_player;

typedef struct s_map
{

}	t_map;

typedef struct s_game
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_player	*player;
	t_map		*map;
}	t_game;

#endif
