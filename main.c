/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-madi <ael-madi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:31:07 by ael-madi          #+#    #+#             */
/*   Updated: 2021/07/23 19:38:39 by ael-madi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int close_with_red(void *param)
{
    (void)param;
    exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{	
	if (keycode == 53)
		exit(0);
	printf("Hello from key_hook %d\n!\n", keycode);
    return (0);
}

int main()
{   
    double y = 0;
    double x = 0;
    int n = 0;
    int maxIterations = 50;
    double ImageHeight = 1200;
    double ImageWidth = 1200;
    double MinRe = -2.0;
    double MaxRe = 1.0;
    double MinIm = -1.2;
    double MaxIm = MinIm+(MaxRe-MinRe)*(ImageHeight/ImageWidth);
    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
    double c_im = 0;
    double c_re = 0;
    double z_re = 0;
    double z_im = 0;
    double z_re2 = 0;
    double z_im2 = 0;
    int isInside = 1;

    t_vars	vars;

    vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1200, 1200, "Hello world!");

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_hook(vars.win, 17, 0, close_with_red, &vars);

    while (y < ImageHeight)
    {   
        c_im = MaxIm - y*Im_factor;
        while (x <ImageWidth)
        {   
            c_re = MinRe + x*Re_factor;
            z_re = c_re;
            z_im = c_im;
            isInside = 1;
            while (n < maxIterations)
            {
                z_re2 = z_re*z_re;
                z_im2 = z_im*z_im;
                if(z_re2 + z_im2 > 4)
                {
                    isInside = 0;
                    break;
                }
                z_im = 2*z_re*z_im + c_im;
                z_re = z_re2 - z_im2 + c_re;
                n++;
            }
            n = 0;
            if(isInside)
                mlx_pixel_put(vars.mlx, vars.win, x, y, 0XF00FFF);
            x++;
        }
        x = 0;
        y++;
    }
    mlx_loop(vars.mlx);
    return (0);
}