/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 18:30:36 by artmende          #+#    #+#             */
/*   Updated: 2021/12/12 01:52:32 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_paint.h"

int	error = 0;

int	ft_strlen(char *str)
{
	int	i;

	i=0;
	while(str && str[i])
		i++;
	return (i);
}

int	display_error_msg(char *str)
{
	(void)str;
	write(1, str, ft_strlen(str));
	return (1);
}

void	display_result(char *result, t_size size)
{
	int	x = 0;
	int	y = 0;
	int	i = 0;

	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			write(1, &result[i], 1);
			x++;
			i++;
		}
		write(1, "\n", 1);
		y++;
	}
}

int	get_index_from_coordinate(int x, int y, t_size size)
{
	return (y * size.x + x);
}

void	reset_circle(t_circle *circle)
{
	circle->cx = -1;
	circle->cy = -1;
	circle->radius = -1;
	circle->symb = -1;
	circle->type = -1;
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

int	pixel_need_to_be_filled(int x, int y, t_circle circle)
{
	float	distance;

	distance = get_distance(x, y, circle.cx, circle.cy);
	if (circle.type == 'c')
	{
		if (distance > circle.radius || distance <= circle.radius - 1)
			return (0);
		else
			return (1);
	}
	else if (circle.type == 'C')
	{
		if (distance > circle.radius)
			return (0);
		else
			return (1);
	}
	else
	{
		error = 1;
		return (0);
	}
}

void	draw_circle(t_circle circle, char *result, t_size size)
{
	int	x = 0;
	int	y = 0;

	if (circle.radius < 0 || circle.symb < 0 || circle.radius <= 0)
	{
		error = 1;
		return ;
	}
	while (y < size.y)
	{
		x = 0;
		while (x < size.x)
		{
			if (pixel_need_to_be_filled(x, y, circle))
				result[get_index_from_coordinate(x, y, size)] = circle.symb;
			x++;
		}
		y++;
	}
}


int	main(int argc, char **argv)
{
	FILE		*op_file;
	t_size		size;
	t_circle	circle;
	char		c_bckgrnd;
	int			ret_of_fscanf;
	char		result[100000];

	if (argc != 2)
		return (display_error_msg(ERROR_ARG));
	if (!(op_file = fopen(argv[1], "r")))
		return (display_error_msg(ERROR_CORRUPTED));
	if (3 != fscanf(op_file, " %d %d %c \n", &size.x, &size.y, &c_bckgrnd) || size.x > 300 || size.x < 1 || size.y > 300 || size.y < 1)
	{
		fclose(op_file);
		return (display_error_msg(ERROR_CORRUPTED));
	}
	memset(result, c_bckgrnd, size.x * size.y);
	reset_circle(&circle);
	while (-1 != (ret_of_fscanf = fscanf(op_file, " %c %f %f %f %c \n", &circle.type, &circle.cx, &circle.cy, &circle.radius, &circle.symb)))
	{
		if (ret_of_fscanf != 5)
			error = 1;
		draw_circle(circle, result, size);
		reset_circle(&circle);
		if (error == 1)
			break ;
	}
	if (-1 != fscanf(op_file, " %c ", &c_bckgrnd))
		error = 1;
	if (error)
	{
		fclose(op_file);
		return(display_error_msg(ERROR_CORRUPTED));
	}
	display_result(result, size);
	fclose(op_file);
	return (0);
}
