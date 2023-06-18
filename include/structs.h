/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:24:41 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/18 17:56:58 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_point {
	int16_t		x;
	int16_t		y;
	uint32_t	color;
}				t_point;

typedef struct s_vect3d
{
	double x;
	double y;
	double z;
	uint32_t	color;
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
	t_vect3d	**pts;
	int			rows;
	int			cols;
	// Translation
	double		x;
	double		y;
	double		dist; // z distance
	// Rotation
	double		alpha;
	double		beta;
	double		gamma;
	// Weak prespective
	double		fov;
	// Scale
	int			scale;
	// feature
	int			is_color_gradient;
	int			max;
	int			min;
	int			is_pres;
}				t_vars;

#endif
