/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:00:53 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/05 15:20:46 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	grab_ls(t_ls *ls, int i)
{
	int j;
	DIR				*d;
	struct dirent	*dir;
	j = 0;

	d = opendir(ls->dir[i]->name);
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
		{
			if ((a_FLAG) == 0 && dir->d_name[0] != '.')
			{
				ls->dir[i]->cont[j] = create_ls_item(0);
				f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
				f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
				path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
				j++;
			}
			else if (a_FLAG)
			{
				ls->dir[i]->cont[j] = create_ls_item(0);
				f_strcpy(ls->dir[i]->cont[j]->name, dir->d_name);
				f_strcpy(ls->dir[i]->cont[j]->path, ls->dir[i]->path);
				path_cpy(ls->dir[i]->cont[j]->path, ls->dir[i]->cont[j]->name, ls);
				j++;
			}
		}
		closedir(d);
	}
	ls->dir[i]->cont[j] = 0;
	//free_item_ls     надо последний елемент
}

void 	get_arguments(int argc, char *argv[], t_ls *ls)
{
	int i;
	int j;
	int k;
	char *tmp;

	i = 1;
	tmp = malloc(sizeof(char) * 256);
    if (argc == 1)
    {
        f_strcpy(tmp, ".");
        if (ft_check_open_dir(tmp) == 1)
        {
            ls->dir[(ls->num_dir)] = create_ls_item(1);
            f_strcpy(ls->dir[ls->num_dir]->name, tmp);
            path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
            ++(ls->num_dir);
        }
        return ;
    }
	while (i < argc)
	{
		if (argv[i][0] == '-')
			i++;
		else
		{
			j = 0;
			while(ISSPACE(argv[i][j]))
				j++;
			k = 0;
			if (argv[i][j] == '\0')
            {
                f_strcpy(tmp, ".");
                if (ft_check_open_dir(tmp) == 1)
                {
                    ls->dir[(ls->num_dir)] = create_ls_item(1);
                    f_strcpy(ls->dir[ls->num_dir]->name, tmp);
                    path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
                    ++(ls->num_dir);
                }
                return ;
            }
			while (argv[i][j] != '\0' && argv[i][j] != ' ')
			{
				tmp[k] = argv[i][j];
				j++;
				k++;
			}
			tmp[k] = '\0';
			if (is_dir(tmp) == 1)
			{
				if (ft_check_open_dir(tmp) == 1)
				{
					ls->dir[(ls->num_dir)] = create_ls_item(1);
					f_strcpy(ls->dir[ls->num_dir]->name, tmp);
					path_cpy(ls->dir[ls->num_dir]->path, tmp, ls);
					++(ls->num_dir);
				}
			}
			else
			{
				if (ft_check_open_file(tmp) == 1)
				{
					ls->file[(ls->num_file)] = create_ls_item(0);
					f_strcpy(ls->file[ls->num_file]->name, tmp);
					path_cpy(ls->file[ls->num_file]->path, tmp, ls);
					++(ls->num_file);
				}
			}
			ft_bzero(tmp, (size_t)k);
			i++;
		}
	}
}

void	get_contents(t_ls *ls)
{
	int i;

	i = 0;
	if (ls->dir[0] != NULL)
	{
		while (ls->dir[i] != NULL)
		{
            grab_ls(ls, i);
			i++;
		}
	}
}

int	perm_maker(t_ls *ls)
{
	int i;
	int j;
	struct stat fileStat;

	i = 0;
	while(ls->dir[i] != NULL)
	{
		ls->dir[i]->st_blocks = 0;
		if (lstat(ls->dir[i]->path, &fileStat) < 0)
			return (1);
		perm_getter(ls->dir[i]);
		ls->dir[i]->links = fileStat.st_nlink;
		ls->dir[i]->file_size = fileStat.st_size;
		j = 0;
		while (ls->dir[i]->cont[j] != NULL)
		{
			if (lstat(ls->dir[i]->cont[j]->path, &fileStat) < 0)
				return (1);
			perm_getter(ls->dir[i]->cont[j]);
			ls->dir[i]->cont[j]->links = fileStat.st_nlink;
			ls->dir[i]->cont[j]->file_size = fileStat.st_size;
			time_getter(ls->dir[i]->cont[j]);
			uid_guid_getter(ls->dir[i]->cont[j]);
			if (is_dir(ls->dir[i]->cont[j]->path) == 0)
				ls->dir[i]->st_blocks += total(ls->dir[i]->cont[j]);
			j++;
		}
		i++;
	}
	i = 0;
	while(ls->file[i] != NULL)
	{
		ls->file[i]->st_blocks = 0;
		if (lstat(ls->file[i]->path, &fileStat) < 0)
			return (1);
		perm_getter(ls->file[i]);
		ls->file[i]->links = fileStat.st_nlink;
		ls->file[i]->file_size = fileStat.st_size;
		time_getter(ls->file[i]);
		uid_guid_getter(ls->file[i]);
		ls->file[i]->st_blocks = total(ls->file[i]);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_ls		*ls;

	if (arg_checker(argc, argv) == -1)
	{
			ft_putendl("\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] "
					   "[file ...]\n");
			return (0);
	}
	ls = create_ls_main();
	ls->flag = Ft_Get_Bit(argc, argv);
	get_arguments(argc, argv, ls);
	get_contents(ls);
	if (l_FLAG)
	{
		perm_maker(ls);
	}
	else if (one_FLAG)
	{
		print_ls_one_flag(ls);
	}
	else
	{
        ft_print_anti_l(ls);
	}
}



