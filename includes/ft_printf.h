/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 22:47:33 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/03 03:31:08 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>

# define LEN(X) (int)ft_strlen(X)
# define IF_THEN(X, Y) if(X) {(Y);}
# define IF_RETURN(X, Y) if(X) {return (Y);}

int				ft_printf(char *str, ...);
/*
**STRUCTURES
*/

typedef struct	s_flag
{
	int			space;
	int			pound;
	int			minus;
	int			fplus;
	int			fzero;
}				t_flag;

typedef struct	s_mods
{
	t_flag		fl;
	int			width;
	int			prcsn;
	int			length;
}				t_mods;

typedef struct	s_dispatch_specifier
{
	char		specifier;
	int			(*f)(t_mods, va_list);
}				t_dispatch_specifier;
/*
**GETTING AND SETTING FUNCTIONS
*/

void			set_flags(t_flag *fl, char c);
void			print_one(char **str);
int				get_pre_float(long double number, int ret);
char			*num_string_base(long long num, int base);
char			*num_string_u_base(unsigned long long num, int base);
t_mods			get_mods(char **str, va_list ap);
int				is_flag(char x);
int				get_type_specifier(char x);
int				get_undef_length(char x);

/*
**CONVERSION FUNCTIONS
*/

int				convert_percent(t_mods modifiers);
int				convert_i(t_mods modifiers, va_list ap);
int				convert_c(t_mods modifiers, va_list ap);
int				convert_s(t_mods modifiers, va_list ap);
int				convert_p(t_mods modifiers, va_list ap);
int				convert_o(t_mods modifiers, va_list ap, int i);
int				convert_u(t_mods modifiers, va_list ap, int i);
int				convert_x(t_mods modifiers, va_list ap, int i);
int				convert_f(t_mods modifiers, va_list ap, int i);
int				convert_b(t_mods modifiers, va_list ap, int i);

#endif
