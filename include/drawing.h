/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:38:33 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 16:50:58 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_H
# define DRAWING_H

# include "structs.h"
# include "maths.h"
# include "consts.h"
# include "parser.h"

void	draw_line(t_vars *vars, t_point pt1, t_point pt2);
void	my_mlx_point_put(t_data *data, t_point *pt, int flip);
t_point	*f3d_to_2d(t_vars *vars, t_vect3d point3d);
void	redraw(t_vars *vars);
// utils
void	get_direction(t_point *pt1, t_point *pt2, t_dir *dir);
int		handle_y_x(t_point *pt1, t_point *pt2);
void	handle_aa(t_vars *vars, t_point *to_draw, t_dir *dir, float percent);
void	angle_points(t_vars *vars, t_point *p[3], int i, int j);
// hooks
int		close_win(t_vars *vars);
int		rotation_handler(int keycode, t_vars *vars);
int		zoom_handler(int keycode, int x, int y, t_vars *vars);
// debug
void	clear_console(void);
void	print_info(t_vars *vars);

#endif
