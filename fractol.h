/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-madi <ael-madi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 17:36:04 by ael-madi          #+#    #+#             */
/*   Updated: 2021/07/24 17:39:11 by ael-madi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win;
	t_img		img;
}				t_mlx;

typedef struct	s_fract
{
	int y;
    int x;
    int n;
    int maxIterations;
    int imageHeight;
    int imageWidth;
    double minRe;
    double maxRe;//decrease here to zoom
    double minIm;//decrease here to zoom
    double maxIm;
    double re_factor;
    double im_factor;
    double c_im;
    double c_re;
    double z_re;
    double z_im;
    double z_re2;
    double z_im2;
    int isInside;	
}				t_fract;



#endif