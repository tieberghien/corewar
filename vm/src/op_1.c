#include "vm.h"

int find_champ(int pc, t_vm *vm)
{
    int player;
    int i;

    player = vm->players_map[pc];
    i = -1;
    while ((unsigned)++i < vm->opts->n_players)
        if (vm->champs[i].player_id == player)
            return (i);
    return (-1);
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

int st(t_vm *vm, t_op *op)
{
    int player;
    unsigned char *idx_val;
    int k;

    player = find_champ(op->pc, vm);
    if (op->params[0] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    if (((op->ocp & PARAM_B) >> 4) == 1)
        vm->champs[player].registre[op->params[1] - 1] = vm->champs[player].registre[op->params[0] - 1];
    else
    {
        tointhex((unsigned int)vm->champs[player].registre[op->params[0] - 1], &idx_val);
        if (!idx_val)
            return (vm->carry);
        k = -1;
        while (++k < 4)
        {
            vm->map[op->pc + op->params[1] + k] = idx_val[k];
            vm->players_map[op->pc + op->params[1] + k] = vm->champs[player].player_id;
        }
        ft_memdel((void**)&idx_val);
    }
    return (vm->carry);
}

int ld(t_vm *vm, t_op *op)
{
    int player ;

    player = find_champ(op->pc, vm);
    if (op->params[0] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    if (op->params[1] < REG_NUMBER)
        vm->champs[player].registre[op->params[1] - 1] = op->params[0];
    return (0);
}

int live(t_vm *vm, t_op *op)
{
    int i;

    i = -1;
    while ((unsigned)++i < vm->opts->n_players)
        if (op->params[0] == vm->champs[i].player_id)
        {
            vm->champs[i].alive = 1;
            //ft_printf("le joueur %s est en vie\n", vm->champs[i].name);
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

