#include "vm.h"

void    ft_procdel(t_process **op)
{
    if (!*op)
        return ;
    //if ((*op)->op)
      //  free(&(*op)->op);
    free(*op);
    *op = NULL;
}

int check_alive(t_process **process, int flag)
{
    unsigned int i;
    t_process *tmp;
    t_process *tmp2;

    i = 0;
    if (!*process)
        return (-1);
    tmp = *process;
    tmp2 = NULL;
    while (tmp != NULL)
    {
        
        if ((*process)->live == 0 || flag == 1)
        {
            if (!tmp2)
                (*process) = tmp->next;
            else
                tmp2->next = tmp->next;
            ft_procdel(&tmp);
            if (!tmp2)
                tmp = *process;
            else
                tmp = tmp2->next;
        }
        else
        {
            tmp2 = tmp;
            tmp = tmp->next;
            i++;
        }
    }
    if (i > 0)
        return (1);
    else 
        return (-1);
}

unsigned int     rest_address(t_process *process, unsigned int num)
{
    int somme;

    somme = process->pc + num;
    somme = somme - process->pc;
    somme = somme % IDX_MOD;
    return (process->pc + somme);
}

void    tointhex(unsigned int num, unsigned char **tmp)
{
    unsigned int total;
    unsigned int cpy;
    int i;

    i = -1;
    if (!(*tmp = (unsigned char*)malloc(sizeof(unsigned char) * 4)))
        return ;
    total = 256 * 256 * 256;
    while (++i < 4)
    {
        cpy = num / total;
        (*tmp)[i] = (unsigned char)(cpy % 256);
        total /= 256;
    }
}