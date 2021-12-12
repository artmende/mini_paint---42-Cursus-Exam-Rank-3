/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:28:05 by artmende          #+#    #+#             */
/*   Updated: 2021/12/12 01:03:23 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_PAINT_H
# define MINI_PAINT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#define ERROR_ARG "Error: argument\n"
#define ERROR_CORRUPTED "Error: Operation file corrupted\n"

typedef struct s_circle
{
	char	type;
	char	symb;
	float	radius;
	float	cx;
	float	cy;

}	t_circle;

typedef struct s_size
{
	int	x;
	int	y;
}	t_size;

#endif
