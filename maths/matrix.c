/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:07:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/16 18:55:37 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/maths.h"

void	apply_rot_x(double angle, t_vect3d *p)
{
	t_vect3d	result;

	result = (t_vect3d){p->x, p->y, p->z};
	result.y = p->y * cos(angle) - p->z * sin(angle);
	result.z = p->y * sin(angle) + p->z * cos(angle);

	p->x = result.x;
	p->y = result.y;
	p->z = result.z;
}

void	apply_rot_y(double angle, t_vect3d *p)
{
	t_vect3d	result;

	result = (t_vect3d){p->x, p->y, p->z};
	result.x = p->x * cos(angle) + p->z * sin(angle);
	result.z = p->x * (-sin(angle)) + p->z * cos(angle);

	p->x = result.x;
	p->y = result.y;
	p->z = result.z;
}

void	apply_rot_z(double angle, t_vect3d *p)
{
	t_vect3d	result;

	result = (t_vect3d){p->x, p->y, p->z};
	result.x = p->x * cos(angle) - p->y * sin(angle);
	result.y = p->x * sin(angle) + p->y * cos(angle);

	p->x = result.x;
	p->y = result.y;
	p->z = result.z;
}

