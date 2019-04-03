/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 14:43:41 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/03 12:00:22 by yharwyn-         ###   ########.fr       */
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

void	swap_ls(t_ls_item *a, t_ls_item *b)
{
	t_ls_item c;

	c = *a;
	*a = *b;
	*b = c;
}

int 	permission_filler(t_ls *ls)
{
	struct stat fileStat;
	char *name;
	char *full_name;

	name = ls->dir[0]->cont[3]->name;
	full_name = ft_strjoin(ls->dir[0]->path, name);
//	printf("\n'%s'\n", name);
//	printf("\n'%s'\n", full_name);
	if (stat(full_name, &fileStat) < 0)
		return (1);

	printf("Information for %s\n", full_name);
	printf("---------------------------\n");
	printf("File Size: \t\t%lld bytes\n", fileStat.st_size);
	printf("Number of Links: \t%d\n", fileStat.st_nlink);
	printf("File inode: \t\t%lld\n", fileStat.st_ino);

	printf("File Permissions: \t");
	printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");

	printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

	return (0);
}

void print_all_cont(t_ls *ls)
{
	int i;
	int j;

	i = 0;
	while (ls->dir[i] != NULL)
	{
		j = 0;
		while (ls->dir[i]->cont[j] != NULL)
		{
			printf("%s\n", ls->dir[i]->cont[j]->name);
			j++;
		}
		i++;
	}
}