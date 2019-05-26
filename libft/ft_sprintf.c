/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:28:19 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 02:02:04 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sprintf.h"

/*
**	Produces a string of text stored in a buffer with variable size according
**	to a formatted string that is passed in the funciton. Parses and converts
**	variables for output to the buffer based on conversion symbols as standard
**	logic for sprintf.
*/

static int		parse_string(char *buf, char **str, va_list ap)
{
	int		i;
	t_mod	modifier;

	(*str)++;
	if (**str)
		modifier = get_mod(str, ap);
	if (!(i = get_type_specifier(**str)))
	{
		ft_strncpy(buf, *str, 1);
		(*str)++;
		(*buf)++;
		return (1);
	}
	IF_RETURN((i == 2 || i == 12) && (*str)++, i_to_buf(buf, modifier, ap));
	IF_RETURN(i == 3 && (*str)++, c_to_buf(buf, modifier, ap));
	IF_RETURN(i == 4 && (*str)++, s_to_buf(buf, modifier, ap));
	return (42);
}

int				ft_sprintf(char *buf, char *str, ...)
{
	int		nbyte;
	int		i;
	va_list	ap;

	nbyte = 0;
	va_start(ap, str);
	while (*str && nbyte < PAGESIZE)
	{
		if (*str != '%')
		{
			ADD_ONE_TO_BUFF(buf, str, nbyte);
			str++;
		}
		else
		{
			i = parse_string(buf, &str, ap);
			buf += i;
			nbyte += i;
		}
	}
	IF_THEN(nbyte < PAGESIZE, *buf = '\0');
	va_end(ap);
	return (nbyte);
}
