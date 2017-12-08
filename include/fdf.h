/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 17:19:37 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 17:55:52 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <libft.h>
# include <mlx.h>

# include "fdf/keys.h"

#define FDF_WGT 1000
#define FDF_HGT 1000

typedef struct	s_fdf
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*li;
	int			bpp;
	int			lisz;
	int			endian;
}				t_fdf;

#endif
