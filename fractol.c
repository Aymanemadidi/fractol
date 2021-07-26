/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-madi <ael-madi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 17:31:07 by ael-madi          #+#    #+#             */
/*   Updated: 2021/07/26 20:19:18 by ael-madi         ###   ########.fr       */
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
    if (keycode == 6)
        printf("you need to zoom\n");  
	printf("Hello from key_hook %d\n!\n", keycode);
    return (0);
}

void init_fract(t_fract *fract)
{
    fract->y = 0;
    fract->x = 0;
    fract->n = 0;
    fract->maxIterations = 5000;
    fract->imageHeight = 800;
    fract->imageWidth = 800;
    fract->minRe = -2.0;
    fract->maxRe = 1.0;//decrease here to zoom
    fract->minIm = -1.2;//decrease here to zoom
    fract->maxIm = fract->minIm+(fract->maxRe-fract->minRe)*(fract->imageHeight/fract->imageWidth);
    fract->re_factor = (fract->maxRe-fract->minRe)/(fract->imageWidth-1);
    fract->im_factor = (fract->maxIm-fract->minIm)/(fract->imageHeight-1);
    fract->c_im = 0;
    fract->c_re = 0;
    fract->z_re = 0;
    fract->z_im = 0;
    fract->z_re2 = 0;
    fract->z_im2 = 0;
    fract->isInside = 1;
}

int main()
{   
    /*int y = 0;
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
    int isInside = 1;*/
    t_fract fract;

    init_fract(&fract);

    t_mlx	vars;

    vars.mlx_ptr = mlx_init();
	vars.win = mlx_new_window(vars.mlx_ptr, 800, 800, "fractol");
    vars.img.img_ptr = mlx_new_image(vars.mlx_ptr, fract.imageWidth, fract.imageHeight);
    
    vars.img.data = (int *)mlx_get_data_addr(vars.img.img_ptr, &vars.img.bpp, &vars.img.size_l,
	&vars.img.endian);

    mlx_key_hook(vars.win, key_hook, &vars);
    mlx_hook(vars.win, 17, 0, close_with_red, &vars);

    while (fract.y< fract.imageHeight)
    {   
        fract.c_im = fract.maxIm - fract.y*fract.im_factor;
        while (fract.x<fract.imageWidth)
        {   
            fract.c_re = fract.minRe + fract.x*fract.re_factor;
            fract.z_re = fract.c_re;
            fract.z_im = fract.c_im;
            fract.isInside = 1;
            while (fract.n <fract. maxIterations)
            {
                fract.z_re2 = fract.z_re*fract.z_re;
                fract.z_im2 = fract.z_im*fract.z_im;
                if(fract.z_re2 + fract.z_im2 > 4)
                {
                    fract.isInside = 0;
                    //vars.img.data[y * imageWidth + x] = 0;
                    break;
                }
                fract.z_im = 2*fract.z_re*fract.z_im + fract.c_im;
                fract.z_re = fract.z_re2 - fract.z_im2 + fract.c_re;
                fract.n++;
            }
            if (fract.n < fract.maxIterations)
            {
                vars.img.data[fract.y * fract.imageWidth + fract.x] = 2555904 - 10000 * fract.n;
                //mlx_pixel_put(vars.mlx_ptr, vars.win, fract.x, fract.y, 2555904 - 10000 * fract.n);
            }
            fract.n = 0;
            if(fract.isInside)
            {
                vars.img.data[fract.y * fract.imageWidth + fract.x] = 0;
                //mlx_pixel_put(vars.mlx_ptr, vars.win, fract.x, fract.y, 0XF00FFF);
            }
                
            fract.x++;
        }
        fract.x = 0;
        fract.y++;
    }
    mlx_put_image_to_window(vars.mlx_ptr, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx_ptr);
    return (0);
}