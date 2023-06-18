/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:08:26 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/18 17:37:48 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H
# include "structs.h"
# define TAU 6.2831853071795864

int			mod(int x, int n);
float		lerp(uint32_t a, uint32_t b, float t);
int			clamp(int a, int min, int max);
float		inv_lerp(uint32_t a, uint32_t b, uint32_t x);
// colors :
uint32_t	f(uint16_t x, uint16_t a);
uint32_t	hue_to_rgb(uint16_t hue);
uint32_t	get_shade(uint32_t col, float shade);
uint32_t	lerp_color(uint32_t c1, uint32_t c2, float t);
// rotation matrices :
void		apply_rot_x(double angle, t_vect3d *p);
void		apply_rot_y(double angle, t_vect3d *p);
void		apply_rot_z(double angle, t_vect3d *p);
// Utils :
void		ft_swap(int16_t *a, int16_t *b);
float		check_zero(float arith);
double		rad_to_deg(double angle);
int			min(int a, int b);

#endif
