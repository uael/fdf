/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft/mlx/geo.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 06:40:19 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/09 08:23:01 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_MLX_GEO_H
# define LIBFT_MLX_GEO_H

# include "../math.h"

typedef struct	s_xdot
{
	int 		x;
	int 		y;
}				t_xdot;

typedef struct	s_xli
{
	t_xdot		a;
	t_xdot		b;
}				t_xli;

extern t_xdot	ft_xdot(int x, int y);
extern t_xli	ft_xli(t_xdot origin, t_xdot target);

#endif
