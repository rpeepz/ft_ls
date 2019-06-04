/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:22:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/03 19:34:14 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_ls(t_file *paths, char flags)
{
	if (!(flags & 0x2) && paths->index == 0)
	{
		if (print_contents(paths, flags))
			return (1);
	}
	else if (N_DIR(paths))
		print_first_files(&paths, flags, get_longest(paths, 1));
	return (0);
}
