/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 19:57:58 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mlx/img.h"
#include "libft/mlx/mlx.h"

inline t_ximg	*ft_ximg(t_mlx *mlx, int width, int height)
{
	t_ximg *img;

	if (!(img = ft_vec_push(&mlx->imgs)))
	{
		mlx->err_hdl(mlx, errno);
		return (NULL);
	}
	FT_INIT(img, t_xwin);
	if (!(img->ptr = mlx_new_image(mlx->ptr, width, height)))
	{
		mlx->err_hdl(mlx, MLX_ENIMG);
		return (NULL);
	}
	if (!(img->li = mlx_get_data_addr(img->ptr, &img->bpp, &img->lisz,
		&img->endian)))
	{
		mlx->err_hdl(mlx, MLX_EAIMG);
		return (NULL);
	}
	img->mlx = mlx;
	img->width = width;
	img->height = height;
	return (img);
}

inline void		ft_ximg_dtor(t_ximg *self)
{
	mlx_destroy_image(self->mlx->ptr, self->ptr);
	FT_INIT(self, t_ximg);
}

inline void		ft_ximg_clear(t_ximg *self)
{
	ft_memset(self->li, 0, (self->height * self->lisz) + (self->width * (self->bpp / 8)));
}

inline void		ft_ximg_draw(t_ximg *self, t_xwin *win, int x, int y)
{
	if (!mlx_put_image_to_window(self->mlx->ptr, win->ptr, self->ptr, x, y))
		self->mlx->err_hdl(self->mlx, MLX_EDRAW);
}

inline void		ft_ximg_wdot(t_ximg *self, t_v2 d, int color)
{
	if (d.y >= self->height || d.x >= self->width || d.x < 0 || d.y < 0)
		return ;
	*(int *)(self->li + (d.y * self->lisz) + (d.x * (self->bpp / 8))) = color;
}
