/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 09:50:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/19 19:16:31 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"

static void	my_mlx_point_put(t_data *data, t_point *pt, int flip)
{
	char		*dst;
	uint16_t	x;
	uint16_t	y;

	x = pt->x;
	y = pt->y;
	if (flip)
	{
		x = pt->y;
		y = pt->x;
	}
	if (!(0 <= x && x < WINDOW_WIDTH))
		return ;
	if (!(0 <= y && y < WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(uint32_t *)dst = pt->color;
}

void	get_direction(t_point *pt1, t_point *pt2, t_point *dir)
{
	dir->x = 1;
	dir->y = 1;
	if (pt2->y < pt1->y)
		dir->y = -1;
	if (pt2->x < pt1->x)
		dir->x = -1;
}

int	handle_y_x(t_point *pt1, t_point *pt2)
{
	int	y_x_flip;

	y_x_flip = 0;
	if (ft_abs(pt2->y - pt1->y) > ft_abs(pt2->x - pt1->x))
	{
		y_x_flip = 1;
		ft_swap(&pt1->x, &pt1->y);
		ft_swap(&pt2->x, &pt2->y);
	}
	return (y_x_flip);
}

void	handle_aa(t_vars *vars, t_point *to_draw, t_point *dir, float percent, int flip)
{
	my_mlx_point_put(vars->img,
		&(t_point){to_draw->x - dir->x, to_draw->y - dir->y,
		get_shade(to_draw->color, percent - 0.2)}, flip);
	my_mlx_point_put(vars->img,
		&(t_point){to_draw->x - dir->x, to_draw->y + dir->y,
		get_shade(to_draw->color, 1 - percent)}, flip);
}

void	draw_line(t_vars *vars, t_point pt1, t_point pt2)
{
	int			y_x_flip;
	t_point		dir;
	t_point		to_draw;
	float		percent;

	y_x_flip = handle_y_x(&pt1, &pt2);
	get_direction(&pt1, &pt2, &dir);
	percent = 1;
	to_draw = pt1;
	while (to_draw.x * dir.x <= pt2.x * dir.x)
	{
		to_draw.color = gradient(&pt1, &pt2, to_draw.x);
		if (vars->is_aa)
			handle_aa(vars, &to_draw, &dir, percent, y_x_flip);
		if (ft_abs(get_error(&to_draw, &pt1, &pt2)) >= 0.5 * ft_abs(pt2.x - pt1.x))
		{
			percent = 1;
			to_draw.y += dir.y;
		}
		percent -= 0.05;
		if (percent < 0)
			percent = 0;
		my_mlx_point_put(vars->img, &to_draw, y_x_flip);
		to_draw.x += dir.x;
	}
}
