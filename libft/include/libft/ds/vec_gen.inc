/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_gen.inc                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alucas- <alucas-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 16:25:13 by alucas-           #+#    #+#             */
/*   Updated: 2017/12/08 16:25:13 by alucas-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../mem.h"
# include "../str.h"
# include "../math.h"

#define V_JOIN_NX(A, B) A ## B
#define V_JOIN(A, B) V_JOIN_NX(A, B)
#define V_STY V_JOIN(s_, TY)
#define V_TTY V_JOIN(t_, TY)
#ifndef SZ_TY
# define SZ_TY size_t
#endif
#define V_METH(N) V_JOIN(ft_, V_JOIN(TY, V_JOIN(_, N)))

typedef struct	V_STY
{
	T			*buf;
	SZ_TY		cap;
	SZ_TY		len;
}				V_TTY;

#ifndef IMPL
# define SCOPE extern
#else
# define SCOPE static
#endif

SCOPE void		V_METH(ctor)(V_TTY *s);
SCOPE void		V_METH(dtor)(V_TTY *s, void (*idtor)(void *i, ...));
SCOPE void		V_METH(clear)(V_TTY *s, void (*idtor)(void *i, ...));
SCOPE size_t	V_METH(clean)(V_TTY *s, size_t n, void (*idtor)(void *i, ...));
SCOPE size_t	V_METH(size)(V_TTY *s);
SCOPE int8_t	*V_METH(begin)(V_TTY *s);
SCOPE int8_t	*V_METH(end)(V_TTY *s);
SCOPE int8_t	*V_METH(at)(V_TTY *s, size_t i);
SCOPE _Bool		V_METH(realloc)(V_TTY *s, size_t n);
SCOPE _Bool		V_METH(grow)(V_TTY *s, size_t n);
SCOPE _Bool		V_METH(ensure)(V_TTY *s, size_t n);
SCOPE int8_t	*V_METH(pushn)(V_TTY *s, size_t n);
SCOPE int8_t	*V_METH(pushnc)(V_TTY *s, int8_t const *b, size_t n);
SCOPE int8_t	*V_METH(push)(V_TTY *s);
SCOPE int8_t	*V_METH(pushc)(V_TTY *s, int8_t item);
SCOPE int8_t	*V_METH(unshiftn)(V_TTY *s, size_t n);
SCOPE int8_t	*V_METH(unshiftnc)(V_TTY *s, int8_t const *b, size_t n);
SCOPE int8_t	*V_METH(unshift)(V_TTY *s);
SCOPE int8_t	*V_METH(unshiftc)(V_TTY *s, int8_t item);
SCOPE int8_t	*V_METH(putn)(V_TTY *s, size_t i, size_t n);
SCOPE int8_t	*V_METH(putnc)(V_TTY *s, size_t i, int8_t const *b, size_t n);
SCOPE int8_t	*V_METH(put)(V_TTY *s, size_t i);
SCOPE int8_t	*V_METH(putc)(V_TTY *s, size_t i, int8_t item);
SCOPE size_t	V_METH(popn)(V_TTY *s, size_t n, int8_t *out);
SCOPE _Bool		V_METH(pop)(V_TTY *s, int8_t *out);
SCOPE size_t	V_METH(shiftn)(V_TTY *s, size_t n, int8_t *out);
SCOPE _Bool		V_METH(shift)(V_TTY *s, int8_t *out);
SCOPE size_t	V_METH(removen)(V_TTY *s, size_t i, size_t n, int8_t *out);
SCOPE _Bool		V_METH(remove)(V_TTY *s, size_t i, int8_t *out);

#ifdef IMPL

#ifdef STATIC
# define SCOPE static
#else
# define SCOPE
#endif

SCOPE inline void	V_METH(ctor)(V_TTY *self)
{
	ft_memset(self, 0, sizeof(V_TTY));
}

#endif
