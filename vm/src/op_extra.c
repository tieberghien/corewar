#include "vm.h"

int check_alive(t_vm *vm, int flag)
{
    unsigned int i;
    int somme;

    i = 0;
    somme = 0;
    while (i < vm->opts->n_players)
    {
        if (vm->champs[i].alive > 0)
        {
            somme = somme + vm->champs[i].alive;
            ft_printf("alive : %d joueur : %s\n", somme, vm->champs[i].name);
            if (flag == 1)
                vm->champs[i].alive = 0;
        }
        else
            if (flag == 1)
                vm->champs[i].alive = -1;
        i++;
    }
    return (somme);
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