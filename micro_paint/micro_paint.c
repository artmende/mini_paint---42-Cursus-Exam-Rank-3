/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artmende <artmende@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:07:30 by artmende          #+#    #+#             */
/*   Updated: 2021/12/15 17:27:37 by artmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "micro_paint.h"

int	error = 0;

int	ft_strlen(char *str)
{
	int	i;

	i=0;
	while (str && str[i])
		i++;
	return (i);
}

int	display_error_msg(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

void	display_result(char *result, t_background background)
{
	int	x = 0;
	int	y = 0;
	int	i = 0;

	while (y < background.y)
	{
		x = 0;
		while (x < background.x)
		{
			write(1, &result[i], 1);
			x++;
			i++;
		}
		write(1, "\n", 1);
		y++;
	}
}

int	get_index_from_coordinate(int x, int y, t_background background)
{
	return (y * background.x + x);
}

void	reset_rect(t_rect *rect)
{
	rect->height = -1;
	rect->width = -1;
	rect->top_left_x = -1;
	rect->top_left_x = -1;
	rect->symb = -1;
	rect->type = -1;
}

int	pixel_need_to_be_filled(int x, int y, t_rect rect, float bottom_right_x, float bottom_right_y)
{
	if (rect.type == 'r')
	{
		if (x >= rect.top_left_x && x < rect.top_left_x + 1 && y >= rect.top_left_y && y <= bottom_right_y) // bord gauche
			return (1);
		if (x <= bottom_right_x && x > bottom_right_x - 1 && y >= rect.top_left_y && y <= bottom_right_y) // bord droit
			return (1);
		if (y >= rect.top_left_y && y < rect.top_left_y + 1 && x >= rect.top_left_x && x <= bottom_right_x) // bord du haut
			return (1);
		if (y <= bottom_right_y && y > bottom_right_y - 1 && x >= rect.top_left_x && x <= bottom_right_x) // bord du bas
			return (1);
		return (0);
	}
	else // rect.type == 'R'
	{
		if (x >= rect.top_left_x && x <= bottom_right_x && y >= rect.top_left_y && y <= bottom_right_y)
			return (1);
		else
			return (0);
	}
}

void	draw_rect(t_rect rect, char *result, t_background background)
{
	int		x = 0;
	int		y = 0;
	float	bottom_right_x;
	float	bottom_right_y;

	if (rect.width <= 0 || rect.height <= 0 || rect.symb < 0 || (rect.type != 'r' && rect.type != 'R'))
	{
		error = 1;
		return ;
	}
	bottom_right_x = rect.top_left_x + rect.width;
	bottom_right_y = rect.top_left_y + rect.height;
	while (y < background.y)
	{
		x = 0;
		while (x < background.x)
		{
			if (pixel_need_to_be_filled(x, y, rect, bottom_right_x, bottom_right_y))
				result[get_index_from_coordinate(x, y, background)] = rect.symb;
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	FILE			*op_file;
	t_background	background;
	t_rect			rect;
	int				ret_of_fscanf;
	char			result[100000];

	if (argc != 2)
		return (display_error_msg(ERROR_ARG));
	if (!(op_file = fopen(argv[1], "r")))
		return (display_error_msg(ERROR_CORRUPTED));
	if (3 != fscanf(op_file, " %d %d %c \n", &background.x, &background.y, &background.symb) || background.x > 300 || background.x < 1 || background.y > 300 || background.y < 1)
	{
		fclose(op_file);
		return (display_error_msg(ERROR_CORRUPTED));
	}
	memset(result, background.symb, background.x * background.y);
	reset_rect(&rect);
	while (-1 != (ret_of_fscanf = fscanf(op_file, " %c %f %f %f %f %c \n", &rect.type, &rect.top_left_x, &rect.top_left_y, &rect.width, &rect.height, &rect.symb)))
	{
		if (ret_of_fscanf != 6)
			error = 1;
		draw_rect(rect, result, background);
		reset_rect(&rect);
		if (error == 1)
			break ;
	}
	if (error)
	{
		fclose(op_file);
		return (display_error_msg(ERROR_CORRUPTED));
	}
	display_result(result, background);
	fclose(op_file);
	return (0);
}
