//
// Created by Yoshiko Harwyn hoare on 2019-04-04.
//

#include "ft_ls.h"

void	print_ls_one_flag(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (ls->dir[i] != NULL)
	{
		j = 0;
		while (ls->dir[i]->cont[j] != NULL)
		{
			ft_putendl(ls->dir[i]->cont[j]->name);
			j++;
		}
		i++;
	}
	i = 0;
	while (ls->file[i] != NULL)
	{
		ft_putendl(ls->file[i]->name);
		i++;
	}
}