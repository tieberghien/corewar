#include "vm.h"

int mv_mem(int *pos, int move, t_vm *vm)
{
    *pos = *pos + move;
    if (*pos >= MEM_SIZE)
        vm->cycle--;
    if (vm->cycle == 0 && vm->next_cycle_group > 0)
        vm->cycle = vm->next_cycle_group;
    else if (vm->next_cycle_group == 0)
        return (-1);
    *pos = *pos % MEM_SIZE;
    return(1);
}

int start_game(t_vm *vm, t_op **op)
{
    int i;
    t_op *new;

    i = 0;
    while (i < MEM_SIZE)
    {
        if (vm->map[i] == 9 || vm->map[i] == 15 || vm->map[i] == 12 || vm->map[i] == 1)
            save_op(op, &i, vm, 0);
        else if (vm->map[i] > 1 && vm->map[i] < 17)
            save_op(op, &i, vm, 1);
        else
            i++;
    }
    new = *op;
    while (new)
    {
        i = 0;
        ft_printf("%s  ", new->name);
        while (i < new->argc)
        {
            ft_printf("%x ", new->params[i]);
            i++;
        }
        ft_printf("\n");
        new = new->next;
    }
    return (0);
}

int install_champion(t_champs *champs, t_opts *opts, t_vm *vm)
{
    int i;
    int gap;
    int pos;
    int j;
    t_op *op;

    op = NULL;
    i = -1;
    gap = MEM_SIZE / opts->n_players;
    while ((unsigned int)++i < opts->n_players)
    {
        j = -1;
        pos = i * gap;
        while (++j < (int)champs[i].size)
            vm->map[j + pos] = champs[i].instructions[j];
    }
    return (0);
}

int init_vm(t_champs *champs, t_opts *opts, t_vm *vm)
{
    int i;
    t_op *op;

    op = NULL;
    vm->cycle = CYCLE_TO_DIE;
    vm->next_cycle_group = CYCLE_TO_DIE - CYCLE_DELTA;
    if (!(vm->map = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE)))
        return (-1);
    i = -1;
    while (++i < MEM_SIZE)
        vm->map[i] = 0;
    if (install_champion(champs, opts, vm))
        return (ft_printf("Error, the map is not initilisated\n"));
    if (start_game(vm, &op))
        return (ft_printf("Error, he doesn't have a game\n"));
    return (0);
}