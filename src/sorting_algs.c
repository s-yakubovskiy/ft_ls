//
// Created by Yoshiko Harwyn hoare on 2019-04-08.
//

#include "ft_ls.h"

void    bubble_sort_ls(t_ls_item *ls)
{
    int sw;
    int i;

    sw = 0;
    i = 0;
    if (ls == NULL)
        return ;
    while (ls->cont[i + 1] != NULL)
    {
        if (ft_strcmp(ls->cont[i]->name, ls->cont[i + 1]->name) > 0)
        {
            swap_ls_item(ls->cont[i], ls->cont[i + 1]);
            sw++;
        }
        i++;
        if (ls->cont[i + 1] == NULL && sw != 0)
        {
            sw = 0;
            i = 0;
        }
    }
}


//void    bubble_sort_ls(t_ls_item *ls)
//{
//    int sw;
//    int i;
//    int j;
//
//    sw = 0;
//    i = 0;
//    while (ls->cont[i] != NULL)
//    {
//        j = 0;
//        while (ls->cont[j] != NULL)
//        {
//            if (ft_strcmp(ls->cont[j]->name, ls->cont[j + 1]->name) > 0)
//            {
//                swap_ls_item(ls->cont[j], ls->cont[i + 1]);
//                sw++;
//            }
//        }
//    }
//}