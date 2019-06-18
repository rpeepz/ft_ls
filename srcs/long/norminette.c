/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 21:31:00 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/17 22:10:55 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_ls.h"

void			norminette(t_file **apath, char flgs, char *tmp)
{
	char	buf[PAGESIZE];
	t_file	*cur;
	int		*arr;
	int		len;

	cur = *apath;
	tmp = buf;
	arr = get_longest_any(cur, flgs);
	len = ft_sprintf(buf, "\0");
	while (cur)
	{
		IF_THEN_CONTINUE(!(flgs & 0x4) && cur->name[0] == '.',
			cur = cur->next);
		len += ft_sprintf(&buf[len], "%s\n", long_out(arr, cur, "", 0));
		IF_THEN(!(cur = cur->next) || len > PAGESIZE - 255,
			ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	free(arr);
}

void			norminette2(t_file **apath, char *tmp)
{
	char	buf[PAGESIZE];
	t_file	*paths;
	int		*arr;
	int		len;

	paths = *apath;
	tmp = buf;
	arr = get_longest_file(paths);
	len = ft_sprintf(buf, "\0");
	while (paths && N_DIR(paths))
	{
		len += ft_sprintf(&buf[len], "%s\n", long_out(arr, paths, "", 0));
		IF_THEN(!(paths = paths->next) || Y_DIR(paths) || len > PAGESIZE - 255,
			ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
		*apath = paths;
	}
	free(arr);
}
