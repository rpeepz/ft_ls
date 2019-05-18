/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 21:48:57 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/18 02:09:15 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				main(int ac, char **av)
{
	char	flags;
//	t_file	file;

	if (ac > 1)
	{
		flags = get_flags(av, 0, 0, 0);
		if (flags & 1UL << 6)
		{
			ft_putstr("usage: ./ft_ls [-Ralrt] [file ...]\n");
			return (0);
		}
	}
	else
		flags = 0;
	if (get_dirs(av, flags, 1, 0))
		ft_putstr("bad path\n");
	return (0);
	ft_printf("flags found :{%#15.8b}\n", flags);
}
