
#include "minishell.h"

char    **ft_soft_split(char *str, char c)
{
    char    **res;
    char    **tmp;
    int trimlen;

    res = malloc(sizeof(char *) * 3);
    tmp = res;
    trimlen = ft_trim_len(str, c);
    *res = malloc(trimlen + 1);
    ft_strlcpy(*(res++), str, trimlen + 1);
    *(res++) = ft_substr(str, trimlen + 1, ft_strlen(str) - trimlen - 1);
    *res = NULL;
    return (tmp);
}