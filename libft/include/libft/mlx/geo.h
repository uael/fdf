/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/mlx/geo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:40:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/10 10:18:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MLX_GEO_H
# define LIBFT_MLX_GEO_H

# include "../math.h"

typedef struct	s_v2
{
	int 		x;
	int 		y;
}				t_v2;

typedef struct	s_v3
{
	int 		x;
	int 		y;
	int 		z;
}				t_v3;

typedef struct	s_xli
{
	t_v2		a;
	t_v2		b;
}				t_xli;

extern t_v2		ft_v2(int x, int y);
extern t_v3		ft_v3(int x, int y, int z);
extern t_v2		ft_v3iso(int x, int y, int z);
extern t_xli	ft_xli(t_v2 origin, t_v2 target);

#endif
