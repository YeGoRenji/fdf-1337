/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 09:50:00 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 03:54:10 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"

void	clear_img(t_data *img)
{
	void	*dst;
	int		y;
	int		x;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			dst = img->addr + (y * img->line_length
					+ x * (img->bits_per_pixel / 8));
			*(unsigned int *)dst = 0x000000;
			++x;
		}
		++y;
	}
}

void	my_mlx_point_put(t_data *data, t_point *pt, int flip)
{
	char		*dst;
	int64_t		x;
	int64_t		y;

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

t_point	*f3d_to_2d(t_vars *vars, t_vect3d point3d)
{
	t_point		*p;
	t_vect3d	result_pt;
	double		pres;

	result_pt = (t_vect3d){point3d.x, point3d.y, point3d.z, point3d.color};
	apply_rot_x(vars->alpha, &result_pt);
	apply_rot_y(vars->beta, &result_pt);
	apply_rot_z(vars->gamma, &result_pt);
	pres = check_zero(vars->is_pres * (vars->dist - vars->fov * result_pt.z));
	if (pres <= 0)
		return (NULL);
	p = ft_malloc_exit(sizeof(t_point));
	p->x = (WINDOW_WIDTH / 2) + vars->scale * (result_pt.x + vars->x) / pres;
	p->y = (WINDOW_HEIGHT / 2) + vars->scale * (result_pt.y - vars->y) / pres;
	if (p->x < INT16_MIN || p->x > INT16_MAX
		|| p->y < INT16_MIN || p->y > INT16_MAX)
	{
		return (free(p), NULL);
	}
	p->color = point3d.color;
	if (vars->is_color_gradient)
		p->color = hue_to_rgb(320 * inv_lerp(vars->min, vars->max, point3d.z));
	return (p);
}

void	redraw(t_vars *vars)
{
	int			i;
	int			j;
	t_point		*p[3];

	clear_img(vars->img);
	clear_console();
	print_info(vars);
	i = 0;
	while (i < vars->rows)
	{
		j = 0;
		while (j < vars->cols)
		{
			p[0] = f3d_to_2d(vars, vars->pts[i][j]);
			p[1] = f3d_to_2d(vars, vars->pts[(i + 1) % vars->rows][j]);
			p[2] = f3d_to_2d(vars, vars->pts[i][(j + 1) % vars->cols]);
			if (!p[0] || !p[1] || !p[2])
			{
				free(p[0]);
				free(p[1]);
				free(p[2]);
				++j;
				continue ;
			}
			if (i < vars->rows - 1)
				draw_line(vars, *p[0], *p[1]);
			if (j < vars->cols - 1)
				draw_line(vars, *p[0], *p[2]);
			free(p[0]);
			free(p[1]);
			free(p[2]);
			++j;
		}
		++i;
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
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
