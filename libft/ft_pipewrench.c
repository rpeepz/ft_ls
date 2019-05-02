/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipewrench.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:27:51 by rpapagna          #+#    #+#             */
/*   Updated: 2019/04/12 15:59:45 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_pipewrench.h"

static int		teflon_tape(va_list ap)
{
	char	**p_string;
	int		i;
	int		freed;

	i = 0;
	freed = 0;
	p_string = va_arg(ap, char **);
	while (p_string[i])
		i++;
	while (freed < i && p_string[freed])
	{
		free(p_string[freed++]);
	}
	free(p_string);
	return (i + 1);
}

static int		plunger(va_list ap, int depth)
{
	if (depth == 2)
		return (teflon_tape(ap));
	if (depth > 2)
		return (1);
	free(va_arg(ap, char*));
	return (depth);
}

static int		pipe_cutter(char **str, va_list ap)
{
	int		pointer_depth;
	int		freed;
	int		x;

	pointer_depth = 0;
	while (**str == KEY)
	{
		(*str)++;
		pointer_depth += 1;
	}
	freed = 0;
	if (ft_isdigit(**str))
	{
		x = ft_atoi(*str);
	}
	if (**str == 's')
	{
		freed += plunger(ap, pointer_depth);
		(*str)++;
	}
	return (freed);
}

int				ft_pipewrench(char *str, ...)
{
	int		freed;
	va_list ap;

	freed = 0;
	va_start(ap, str);
	while (*str && freed >= 0)
	{
		if (*str != KEY)
		{
			freed = -1;
			break ;
		}
		else
		{
			freed += pipe_cutter(&str, ap);
			if (freed == 0)
			{
				write(1, "\nusage: ft_pipewren", 19);
				write(1, "ch(const char * res", 19);
				write(1, "trict format, ...)\n", 19);
			}
		}
	}
	va_end(ap);
	return (freed);
}
