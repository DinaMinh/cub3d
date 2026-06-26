/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebourdet <ebourdet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 13:13:28 by ebourdet          #+#    #+#             */
/*   Updated: 2026/06/26 08:46:29 by ebourdet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_texture(char *str)
{
	if (!ft_strncmp(str, "NO ", 3) || !ft_strncmp(str, "SO ", 3)
		|| !ft_strncmp(str, "WE ", 3) || !ft_strncmp(str, "EA ", 3))
		return (1);
	return (0);
}

int	is_color(char *str)
{
	if (!ft_strncmp(str, "F ", 2) || !ft_strncmp(str, "C ", 2))
		return (1);
	return (0);
}

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	is_empty_or_whitespace(char *str)
{
	int	i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == '\0' || str[i] == '\n')
		return (1);
	return (0);
}

int	msg_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd(msg, 2);
	return (0);
}
