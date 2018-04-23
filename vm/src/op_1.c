#include "vm.h"

int live(t_vm *vm, t_op *op)
{
    int i;

    i = -1;
    while ((unsigned)++i < vm->opts->n_players)
        if (op->params[0] == vm->champs[i].player_id)
        {
            vm->champs[i].alive = 1;
            ft_printf("le joueur %s est en vie\n", vm->champs[i].name);
            return (vm->carry);
        }
    return (vm->carry);
}

int check_alive(t_vm *vm)
{
    unsigned int i;
    int somme;

    i = 0;
    somme = 0;
    while (i < vm->opts->n_players)
    {
        somme = somme + vm->champs[i].alive;
        i++;
    }
    return (somme);
}