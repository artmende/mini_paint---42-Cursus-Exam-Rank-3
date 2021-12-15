/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:07:27 by artmende          #+#    #+#             */
/*   Updated: 2021/12/15 17:09:01 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MICRO_PAINT_H
# define MICRO_PAINT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <math.h>

# define ERROR_ARG "Error: argument\n"
# define ERROR_CORRUPTED "Error: Operation file corrupted\n"

typedef struct s_rect
{
	char	type;
	char	symb;
	float	width;
	float	height;
	float	top_left_x;
	float	top_left_y;
}	t_rect;

typedef struct s_background
{
	int		x;
	int		y;
	char	symb;
}	t_background;

#endif