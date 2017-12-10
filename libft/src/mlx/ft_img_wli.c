/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_img_wli.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:59:08 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 14:52:42 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/mlx/img.h"

static inline void	ximg_wli_yl(t_ximg *self, int const *lens, t_v3 a,
	int color)
{
	int	inc;
	int	len;
	int	j;

	inc = !lens[0] ? 0 : (lens[1] << 16) / lens[0];
	if ((len = lens[0]) > 0)
	{
		len += a.y;
		j = 0x8000 + ((int)a.x << 16);
		while (a.y <= len)
		{
			ft_ximg_wdot(self, ft_v3(j >> 16, a.y, 0), color);
			j += inc;
			++a.y;
		}
		return ;
	}
	len += a.y;
	j = 0x8000 + ((int)a.x << 16);
	while (a.y >= len)
	{
		ft_ximg_wdot(self, ft_v3(j >> 16, a.y, 0), color);
		j -= inc;
		--a.y;
	}
}

static inline void	ximg_wli_xl(t_ximg *self, int const *lens, t_v3 a,
	int color)
{
	int	inc;
	int	len;
	int	j;

	inc = !lens[0] ? 0 : (lens[1] << 16) / lens[0];
	if ((len = lens[0]) > 0)
	{
		len += a.x;
		j = 0x8000 + ((int)a.y << 16);
		while (a.x <= len)
		{
			ft_ximg_wdot(self, ft_v3(a.x, j >> 16, 0), color);
			j += inc;
			++a.x;
		}
		return ;
	}
	len += a.x;
	j = 0x8000 + ((int)a.y << 16);
	while (a.x >= len)
	{
		ft_ximg_wdot(self, ft_v3(a.x, j >> 16, 0), color);
		j -= inc;
		--a.x;
	}
}

inline void			ft_ximg_wli(t_ximg *self, t_v3 o, t_v3 t, int color)
{
	int	slen;
	int	llen;

	slen = (int)(t.y - o.y);
	llen = (int)(t.x - o.x);
	if (ABS(slen) > ABS(llen))
		ximg_wli_yl(self, (int [2]){slen, llen}, o, color);
	else
		ximg_wli_xl(self, (int [2]){llen, slen}, o, color);
}
