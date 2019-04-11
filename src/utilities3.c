//
// Created by Yoshiko Harwyn hoare on 2019-04-10.
//

#include "ft_ls.h"

static int perm_maker_ext (t_ls *ls, int i, struct stat fileStat)
{
    int j;

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
    return (0);
}

static int perm_maker_ext2(t_ls *ls, int i, struct stat fileStat)
{
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

int	perm_maker(t_ls *ls)
{
    int i;
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
        if (perm_maker_ext(ls, i, fileStat) == 1)
            return (1);
        i++;
    }
    i = 0;
    return (perm_maker_ext2(ls, i, fileStat));
}

t_ls_item	*create_ls_item(int flag)
{
    t_ls_item	*tmp;

    tmp = ft_memalloc(sizeof(t_ls_item));
    tmp->cont = NULL;
    flag == 1 ? tmp->cont = ft_memalloc(sizeof(t_ls_item*) * 16384) : 0;
    tmp->next = NULL;
    return (tmp);
}

t_ls	*create_ls_main(void)
{
    t_ls	*tmp;

    tmp = ft_memalloc(sizeof(t_ls));
    tmp->num_dir = 0;
    tmp->num_file = 0;
    tmp->flag = 0;
    tmp->dir = ft_memalloc(sizeof(t_ls_item*) * 16384);
    tmp->file = ft_memalloc(sizeof(t_ls_item*) * 16384);
    return (tmp);
}