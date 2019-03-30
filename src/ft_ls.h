/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yharwyn- <yharwyn-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:41:22 by yharwyn-          #+#    #+#             */
/*   Updated: 2019/03/30 15:08:10 by yharwyn-         ###   ########.fr       */
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

typedef struct		s_ls
{
	int				flag;
	char			*path;
	struct s_ls		*next;
}					t_ls;


/*
** 		NODE FUNCTIONS
*/




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
