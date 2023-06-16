/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:24:41 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/16 18:26:40 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_point {
	int			x;
	int			y;
	uint32_t	color;
}				t_point;

typedef struct s_vect3d
{
	double x;
	double y;
	double z;
}				t_vect3d;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_color;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_data		*img;
	t_point		line[2];
	t_vect3d	points[8];
	t_vect3d	**pts;
	int			rows;
	int			cols;
	double		distance; // z distance
	// rotation angles
	double	alpha;
	double	beta;
	double	gamma;
	// Weak prespective
	double	fov;
	// Scale
	int scale;
}				t_vars;

#endif
