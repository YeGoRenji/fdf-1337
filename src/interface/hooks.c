/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:54:56 by ylyoussf          #+#    #+#             */
/*   Updated: 2024/05/09 13:14:29 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"
#include "../../include/keys.h"

int	close_win(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->img->img);
	mlx_destroy_window(vars->mlx, vars->win);
	while (vars->rows--)
		free(vars->pts[vars->rows]);
	exit(0);
}

int	hook_rot_dist(t_vars *vars, int keycode)
{
	if (keycode == KEY_Q)
		vars->alpha += ROT_SPEED;
	else if (keycode == KEY_A)
		vars->alpha -= ROT_SPEED;
	else if (keycode == KEY_W)
		vars->beta += ROT_SPEED;
	else if (keycode == KEY_S)
		vars->beta -= ROT_SPEED;
	else if (keycode == KEY_E)
		vars->gamma += ROT_SPEED;
	else if (keycode == KEY_D)
		vars->gamma -= ROT_SPEED;
	else if (keycode == KEY_Y)
		vars->dist += DIST_SPEED;
	else if (keycode == KEY_H)
		vars->dist -= DIST_SPEED;
	else if (keycode == KEY_T)
		vars->fov += FOV_SPEED;
	else if (keycode == KEY_G)
		vars->fov -= FOV_SPEED;
	else
		return (0);
	return (1);
}

int	hook_bonus_trans(t_vars *vars, int keycode)
{
	if (keycode == KEY_F)
		vars->is_color_gradient = !vars->is_color_gradient;
	else if (keycode == KEY_O)
		vars->is_pres = !vars->is_pres;
	else if (keycode == KEY_P)
		vars->is_aa = !vars->is_aa;
	else if (keycode == KEY_UP)
		vars->y += 1;
	else if (keycode == KEY_DOWN)
		vars->y -= 1;
	else if (keycode == KEY_RIGHT)
		vars->x += 1;
	else if (keycode == KEY_LEFT)
		vars->x -= 1;
	else if (keycode == KEY_ESC)
		return (close_win(vars));
	else if (keycode == KEY_R)
	{
		vars->alpha = 0;
		vars->beta = 0;
		vars->gamma = 0;
	}
	else
		return (0);
	return (1);
}

int	rotation_handler(int keycode, t_vars *vars)
{
	if (!hook_rot_dist(vars, keycode) && !hook_bonus_trans(vars, keycode))
		return (0);
	if (vars->fov < 0)
		vars->fov = 0;
	redraw(vars);
	return (0);
}

int	zoom_handler(int keycode, int x, int y, t_vars *vars)
{
	if (keycode == SCROLL_UP)
		vars->scale += 5;
	else if (keycode == SCROLL_DOWN)
		vars->scale -= 5;
	(void)x;
	(void)y;
	if (vars->scale < 1)
		vars->scale = 1;
	redraw(vars);
	return (0);
}
