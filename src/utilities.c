/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:43:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/02 14:07:29 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_ls_item	*create_ls_item(int flag)
{
	t_ls_item	*tmp;

	tmp = (t_ls_item*)malloc(sizeof(t_ls_item) + 1);
	tmp->cont = NULL;
	flag == 1 ? tmp->cont = malloc(sizeof(t_ls_item*) * 1000) : 0;
	tmp->next = NULL;
	return (tmp);
}

t_ls	*create_ls_main(void)
{
	t_ls	*tmp;

	tmp = malloc(sizeof(t_ls) * 1000 + 1);
	tmp->num_dir = 0;
	tmp->num_file = 0;
	tmp->flag = 0;
	tmp->dir = malloc(sizeof(t_ls_item*) * 1000);
	tmp->file = malloc(sizeof(t_ls_item*) * 1000);
	return (tmp);
}


int is_dir(char *path)
{
	if (path == NULL)
		return (-1);
	struct stat fileStat;
	if (stat(path,&fileStat) < 0)
		return (-1);
	return ((S_ISDIR(fileStat.st_mode)) ? 1 : 0);
}

void free_ls_item(t_ls_item	*ls)
{
	int i;

	i = 0;
	if (ls->cont != NULL)
	{
		while (ls->cont[i])
			free(ls->cont[i++]);
	}
	free(ls->cont);
}
