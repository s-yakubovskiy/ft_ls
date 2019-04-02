/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:41:22 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/04/02 14:07:19 by yharwyn-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/printf/ft_printf.h"
# include "../lib/printf/libft/get_next_line.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>

/*
** 		MACROS
*/

# define l_FLAG ((ls->flag >> 0) & 1)
# define R_FLAG ((ls->flag >> 1) & 1)
# define a_FLAG ((ls->flag >> 2) & 1)
# define r_FLAG ((ls->flag >> 3) & 1)
# define t_FLAG ((ls->flag >> 4) & 1)



# define ISNUM(x) (x >= '0' && x <= '9')
# define ISSPACE(x) (x == ' ' || x == '\n')
# define _MIN(a,b) (((a)<(b))?(a):(b))
# define _MAX(a,b) (((a)>(b))?(a):(b))
# define EVEN(a) (((a)%(2) == 0) ? (1):(0))

/*
** 		COLOURS
*/

# define _C_ "\033[1;96m"
# define _G_ "\033[1;92m"
# define _R_ "\x1b[0m"
# define _RD_ "\033[0;105m"
# define _M_ "\033[1;33m"

/*
** 		STRUCTS
*/

typedef struct			s_ls
{
	int					flag;
	int 				num_dir;
	int 				num_file;
	char				path[256];
	struct s_ls_item	**dir;
	struct s_ls_item	**file;
}						t_ls;



typedef struct			s_ls_item
{
	char				path[256];
	char				stat[11];
	struct s_ls_item	*next;
	struct s_ls_item	**cont;
}						t_ls_item;



/*
** 		NODE FUNCTIONS
*/

t_ls		*create_ls_dir(void);
int			is_dir(char *path);
void		print_ls_list(t_ls *ls_list);
t_ls_item	*create_ls_item(int flag);
t_ls		*create_ls_main(void);
void		free_ls_item(t_ls_item	*ls);

/*
** 		VALIDATE_FUNCS
*/



/*
** 		ALGORITHM_FUNCS
*/



/*
** 		AUX FUNCS
*/



/*
** 		SPLITS_CHECK_FUNCS
*/



#endif

/*
 * L is >> 0
 */