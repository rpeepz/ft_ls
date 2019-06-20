/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 21:31:00 by rpapagna          #+#    #+#             */
/*   Updated: 2019/06/20 02:43:47 by rpapagna         ###   ########.fr       */
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
	arr = get_longest_any(cur, flgs, 0);
	len = ft_sprintf(buf, "\0");
	while (cur)
	{
		IF_THEN_CONTINUE(!(flgs & 0x4) && cur->name[0] == '.',
			cur = cur->next);
		len += ft_sprintf(&buf[len], "%s\n", long_out(arr, cur, "",
			flgs & 0x80 ? 1 : 0));
		IF_THEN(!(cur = cur->next) || len > PAGESIZE - 255,
			ft_printf("%s", buf) && (len = ft_sprintf(buf, "\0")));
	}
	IF_THEN(LEN(buf), ft_putstr(buf));
	free(arr);
}

void			norminette2(t_file **apath, char *tmp, int len, char flags)
{
	char	buf[PAGESIZE];
	t_file	*paths;
	int		*arr;

	paths = *apath;
	tmp = buf;
	arr = get_longest_file(paths);
	IF_THEN(!(len = 0), ft_bzero(buf, 4096));
	while (paths && N_DIR(paths))
	{
		opendir(paths->name);
		if (!(ft_strcmp(strerror(errno), "No such file or directory")))
			ft_printf("ls: %s: %s\n", paths->name, strerror(errno));
		else
			len += ft_sprintf(&buf[len], "%s\n", long_out(arr, paths, "",
				flags & 0x80 ? 1 : 0));
		if (!(paths = paths->next) || Y_DIR(paths) || len > PAGESIZE - 255)
		{
			IF_THEN(ft_printf("%s", tmp), (len = 0));
			ft_bzero(buf, 4096);
		}
		*apath = paths;
	}
	IF_THEN(paths && !(flags & 0x80) && !(flags & 0x2), ft_putchar('\n'));
	free(arr);
}
