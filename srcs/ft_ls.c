/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:22:02 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/05 21:47:51 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int				ft_ls(t_file *paths, char flags)
{
	if (flags & 0x80)
		return (ls_color(paths, flags));
	if (N_DIR(paths))
		return (print_first_files(&paths, flags, get_longest(paths, 1)));
	else if (!(flags & 0x2) && !paths->index)
		return (print_contents(paths, flags, 0));
	else if (flags & 0x2 && !paths->index && N_DIR(paths))
		return (recurse(paths, flags));
	else if (paths->index)
		;
	return (0);
}
