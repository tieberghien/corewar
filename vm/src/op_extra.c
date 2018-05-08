#include "vm.h"

int res_add(unsigned int param, int pc)
{
    int hello;

    hello = (short)param;
    hello = (hello >= 0) ? hello % IDX_MOD : - (-hello % IDX_MOD);
    hello = pc + hello;
    hello = (hello >= 0) ? hello % MEM_SIZE : MEM_SIZE - (-hello % MEM_SIZE);
    //ft_printf("%d\n", hello);
    return (hello);
}

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
    int fexit;

    i = 0;
    if (!*process)
        return (-1);
    tmp = *process;
    tmp2 = NULL;
    fexit = 0;
    while (tmp != NULL)
    {
        if (tmp->live == 0 || flag == 1)
        {
            //fexit = 1;
            //ft_printf("%d ", tmp->number);
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
            //ft_printf("%d ", tmp->number);
            tmp->live = 0;
            tmp2 = tmp;
            tmp = tmp->next;
            i++;
        }
    }
    //ft_putchar('\n');
    //ft_putchar('\n');
 //   if (fexit)
 //       exit(1);
    if (i > 0)
        return (1);
    else 
        return (-1);
}

void    tointhex(unsigned long int num, unsigned char **tmp, t_vm *vm)
{
    unsigned int total;
    unsigned int cpy;
    unsigned char *new;
    int i;

    i = -1;
    if (!(new = (unsigned char*)malloc(sizeof(unsigned char) * 4)))
        return ;
    total = 256 * 256 * 256;
    while (++i < 4)
    {
        cpy = num / total;
        new[i] = (unsigned char)(cpy % 256);
        total /= 256;
    }
    if (vm->c == 22679)
    {
        i = -1;
        //while (++i < 4)
          //  ft_printf("%hhx ", new[i]);
        //ft_printf("\n");
    }
    *tmp = new;
}