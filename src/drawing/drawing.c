/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 09:50:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/19 15:25:47 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (!(0 <= x && x < WINDOW_WIDTH))
		return ;
	if (!(0 <= y && y < WINDOW_HEIGHT))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_vars *vars, t_point pt1, t_point pt2)
{
	int			y_x_flip = 0;
	uint32_t	color;

	// This is where a line shall be born !
	if (ft_abs(pt2.y - pt1.y) > ft_abs(pt2.x - pt1.x))
	{
		y_x_flip = 1;
		ft_swap(&pt1.x, &pt1.y);
		ft_swap(&pt2.x, &pt2.y);
	}
	int	dir_y = (pt2.y - pt1.y > 0) ? 1 : -1;
	int	dir_x = (pt2.x - pt1.x > 0) ? 1 : -1;
	int	y_put = pt1.y;

	float percent = 1;
	int x = pt1.x;
	for (; x * dir_x <= pt2.x * dir_x; x += dir_x)
	{
		int err = (pt2.y * (x - pt1.x) - pt1.y * (x - pt2.x)) - y_put * (pt2.x - pt1.x);
		color = lerp_color(pt1.color, pt2.color, inv_lerp(pt1.x, pt2.x, x));
		if (vars->is_aa)
		{
			// ! You can make this better
			if (y_x_flip)
			{
				my_mlx_pixel_put(vars->img, y_put - dir_y, x - dir_x, get_shade(color, percent - 0.2));
				my_mlx_pixel_put(vars->img, y_put + dir_y, x - dir_x, get_shade(color, 1 - percent));
			}
			else
			{
				my_mlx_pixel_put(vars->img, x - dir_x, y_put - dir_y, get_shade(color, percent - 0.2));
				my_mlx_pixel_put(vars->img, x - dir_x, y_put + dir_y, get_shade(color, 1 - percent));
			}
		}
		if (ft_abs(err) >= 0.5 * ft_abs(pt2.x - pt1.x))
		{
			percent = 1;
			y_put += dir_y;
		}
		percent -= 0.05;
		if (percent < 0) percent = 0;
		if (y_x_flip)
			my_mlx_pixel_put(vars->img, y_put, x, color);
		else
			my_mlx_pixel_put(vars->img, x, y_put, color);
	}
}
