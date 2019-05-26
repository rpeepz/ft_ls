/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:18:05 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 02:03:13 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SPRINTF_H
# define FT_SPRINTF_H
# define PAGESIZE 4096

# include "libft.h"
# include "ft_printf.h"
# include <stdarg.h>

# define ADD_ONE_TO_BUFF(buf, c, n) ft_strncpy(buf, c, 1); buf++; n++;
# define ADD_TO_BUFF(buf, src, n, ln) ft_strncpy(buf, src, ln); buf+=ln; n+=ln;

int				ft_sprintf(char *buf, char *str, ...);
/*
**STRUCTURES
*/

typedef struct	s_fl
{
	int			space;
	int			pound;
	int			minus;
	int			fplus;
	int			fzero;
}				t_fl;

typedef struct	s_mod
{
	t_fl		fl;
	int			width;
	int			prcsn;
	int			length;
	int			neg;
}				t_mod;
/*
**GETTING AND SETTING FUNCTIONS
*/

t_mod			get_mod(char **str, va_list ap);

/*
**CONVERSION FUNCTIONS
*/

int				c_to_buf(char *buf, t_mod modifiers, va_list ap);
int				i_to_buf(char *buf, t_mod modifiers, va_list ap);
int				s_to_buf(char *buf, t_mod modifiers, va_list ap);

#endif
