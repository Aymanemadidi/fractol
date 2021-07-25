/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-madi <ael-madi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:31:07 by ael-madi          #+#    #+#             */
/*   Updated: 2021/07/25 21:01:26 by ael-madi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int close_with_red(void *param)
{
    (void)param;
    exit(0);
}

int	key_hook(int keycode, t_mlx *vars)
{	
    (void)vars;
	if (keycode == 53)
		exit(0);
	printf("Hello from key_hook %d\n!\n", keycode);
    return (0);
}

int main()
{   
    int y = 0;
    int x = 0;
    int n = 0;
    int maxIterations = 50;
    int imageHeight = 800;
    int imageWidth = 800;
    double minRe = -2.0;
    double maxRe = 1.0;//decrease here to zoom
    double minIm = -1.2;//decrease here to zoom
    double maxIm = minIm+(maxRe-minRe)*(imageHeight/imageWidth);
    double re_factor = (maxRe-minRe)/(imageWidth-1);
    double im_factor = (maxIm-minIm)/(imageHeight-1);
    double c_im = 0;
    double c_re = 0;
    double z_re = 0;
    double z_im = 0;
    double z_re2 = 0;
    double z_im2 = 0;
    int isInside = 1;

    t_mlx	vars;

    vars.mlx_ptr = mlx_init();
	vars.win = mlx_new_window(vars.mlx_ptr, 800, 800, "fractol");
    vars.img.img_ptr = mlx_new_image(vars.mlx_ptr, imageWidth, imageHeight);
    
    vars.img.data = (int *)mlx_get_data_addr(vars.img.img_ptr, &vars.img.bpp, &vars.img.size_l,
	&vars.img.endian);

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_hook(vars.win, 17, 0, close_with_red, &vars);

    while (y < imageHeight)
    {   
        c_im = maxIm - y*im_factor;
        while (x <imageWidth)
        {   
            c_re = minRe + x*re_factor;
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
                    //vars.img.data[y * imageWidth + x] = 0;
                    break;
                }
                z_im = 2*z_re*z_im + c_im;
                z_re = z_re2 - z_im2 + c_re;
                n++;
            }
            if (n < maxIterations)
            {
                vars.img.data[y * imageWidth + x] = 2555904 - 100000 * n;
            }
            n = 0;
            if(isInside)
            {
                vars.img.data[y * imageWidth + x] = 0;
                //mlx_pixel_put(vars.mlx_ptr, vars.win, x, y, 0XF00FFF);
            }
                
            x++;
        }
        x = 0;
        y++;
    }
    mlx_put_image_to_window(vars.mlx_ptr, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx_ptr);
    return (0);
}