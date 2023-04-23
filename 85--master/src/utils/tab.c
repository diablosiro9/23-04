# include "../../include/include.h"

int     ft_tablen(char **tab)
{
    int   i = 0;
    
	if (tab == NULL)
		return 0;
    while (tab[i])
        i += 1;
    return i;
}