#include "vm.h"

void    ft_opdel(t_op **op)
{
    t_op *tmp;

    if (!*op)
        return ;
    tmp = *op;
    *op = (*op)->next;
    free (tmp);
}

t_op   *ft_opdup(t_op op)
{
    t_op    *new;

    new = (t_op*)malloc(sizeof(t_op));
    if (!new)
        return (NULL);
    *new = op;
    return (new);
}