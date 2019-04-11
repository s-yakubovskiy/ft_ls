//
// Created by Yoshiko Harwyn hoare on 2019-04-08.
//

#include "ft_ls.h"

int	Ft_Bitwise_Shift(unsigned int flag, unsigned int a)
{
    flag = flag >> a;
    flag = flag + 1;
    flag = flag << a;
    return (flag);
}

int	Ft_Get_Bit(int argc, char **argv)
{
    int		flag;
    char    *str;

    flag = 0;
    str = Ft_Get_Str_Options(argc, argv);
    if (Check_On_Consist(str, '1') == 1)
        flag = Ft_Bitwise_Shift(flag, 5);
    if (Check_On_Consist(str, 't') == 1)
        flag = Ft_Bitwise_Shift(flag, 4);
    if (Check_On_Consist(str, 'r') == 1)
        flag = Ft_Bitwise_Shift(flag, 3);
    if (Check_On_Consist(str, 'a') == 1)
        flag = Ft_Bitwise_Shift(flag, 2);
    if (Check_On_Consist(str, 'R') == 1)
        flag = Ft_Bitwise_Shift(flag, 1);
    if (Check_On_Consist(str, 'l') == 1)
        flag = Ft_Bitwise_Shift(flag, 0);
    ft_memdel((void **)&str);
    return (flag);
}

void	f_strcpy(char *dst, const char *src)
{
    int		i;
    int     j;

    i = -1;
    j = 0;
    while(dst[j] != '\0')
        j++;
    while (src[++i])
        dst[j++] = src[i];
    dst[j] = '\0';
}

void	path_cpy(char *dst, const char *src, t_ls *ls)
{
    int		i;
    int 	j;

    i = -1;
    j = 0;
    while (dst[j] != '\0')
        j++;
    while (src[++i])
        dst[j++] = src[i];
    dst[j] = '\0';
    if (is_dir(dst) && dst[j - 1] != '/')
    {
        dst[j] = '/';
        dst[j + 1] = '\0';
    }
}