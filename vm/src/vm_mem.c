#include "vm.h"
/*
void check_op(t_op **op, int flag, t_vm *vm)
{
    t_op *tmp;
    t_op *tmp2;

    if (!*op)
        return ;
    tmp = *op;
    tmp2 = NULL;
    while (tmp != NULL)
    {
        tmp->dur--;
        if (tmp->dur <= 0 || flag == 1)
        {
            if (tmp->op_code <= 9 && flag == 0)
                vm->carry = g_op[tmp->op_code - 1](vm, tmp);
            if (!tmp2)
                (*op) = tmp->next;
            else
                tmp2->next = tmp->next;
            ft_opdel(&tmp);
            if (!tmp2)
                tmp = *op;
            else
                tmp = tmp2->next;
        }
        else
        {
            tmp2 = tmp;
            tmp = tmp->next;
        }
    }
}

int mv_mem(int *pos, int move, t_vm *vm, t_op **op)
{
    t_op tmp;
    static int k = 2;

    tmp = **op;
    *pos = *pos + move;
    if (*pos >= MEM_SIZE)
    {
        check_op(op, 0, vm);
        vm->cycle--;
    }
    if (vm->cycle <= 0 && vm->next_cycle_group > 0)
    {
        if ((k = check_alive(vm)) <= 1)
            return (k);
        vm->cycle = vm->next_cycle_group;
        vm->next_cycle_group -= CYCLE_DELTA;
    }
    else if (vm->next_cycle_group <= 0)
        return (-1);
    *pos = *pos % MEM_SIZE;
    return(k);
}

int start_game(t_vm *vm, t_op **op)
{
    int i;
    int alive;
   // t_op *new;

    i = 0;
    while (1)
    {
        if (vm->map[i] == 9 || vm->map[i] == 15 || vm->map[i] == 12 || vm->map[i] == 1)
        {
            if ((alive = save_op_spec(op, &i, vm)) <= 1)
                break;
        }
        else if (vm->map[i] > 1 && vm->map[i] < 16)
        {
            if ((alive = save_op(op, &i, vm)) <= 1)
                break;
        }
        else
            if ((alive = mv_mem(&i, 1, vm, op)) <= 1)
                break ;
    }
    if (alive == 1)
    {
        i = -1;
        while ((unsigned)++i < vm->opts->n_players)
            if (vm->champs[i].alive == 1)
            {
                return(ft_printf("jouer %s a gagne\n", vm->champs[i].name));
            }
    }
    check_op(op, 1, vm);
    return (0);
}*/

void p_turn(t_vm *vm, t_process *process)
{
    int j;

    j = 0;
    if (process->op.dur > 1)
        process->op.dur--;
    else if(process->op.dur == 0)
    {
        if (vm->map[process->pc] > 0 && vm->map[process->pc] < 16)
            process->op = g_optab[vm->map[process->pc] - 1];
        else
            process->pc = (process->pc + 1) % MEM_SIZE;
    }
    else if (process->op.dur == 1)
    {
        if (vm->map[process->pc] == 9 || vm->map[process->pc] == 15 || vm->map[process->pc] == 12 || vm->map[process->pc] == 1)
            j = save_op_spec(process, vm);
        else if (vm->map[process->pc] > 1 && vm->map[process->pc] < 16)
            j = save_op(process, vm);
        if (vm->map[process->pc] > 0 && vm->map[process->pc] <= 11)
            g_op[vm->map[process->pc] - 1](vm, &(process->op), process);
        if (process->op.op_code != 9)
            process->pc = (process->pc + j) % MEM_SIZE;
        process->op.dur--;
    }
}

int start_game(t_vm *vm)
{
    int i;
    t_process *process;

    while (vm->next_cycle_group > 0)
    {
        vm->next_cycle_group -= CYCLE_DELTA;
        while (vm->cycle > 0)
        {
            i = -1;
            process = vm->process;
            while (process)
            {
                if (vm->champs[process->champ].alive >= 0)
                    p_turn(vm, process);
                process = process->next;
            }
            vm->cycle--;
        }
        if ((i = check_alive(vm, 0)) == 1)
        {
            i = -1;
            while ((unsigned)++i < vm->opts->n_players)
                if (vm->champs[i].alive == 1)
                    return(ft_printf("jouer %s a gagne\n", vm->champs[i].name));
        }
        else if (i < 1)
            return(ft_printf("EVERYONE IS DEAD!\n"));
        check_alive(vm, 1);
        vm->cycle = vm->next_cycle_group;
    }
    return (-1);
}

int install_champion(t_champs *champs, t_opts *opts, t_vm *vm)
{
    int i;
    int gap;
    int pos;
    int j;
    t_process *process;

    i = -1;
    gap = MEM_SIZE / opts->n_players;
    while ((unsigned int)++i < opts->n_players)
    {
        j = 0;
        pos = i * gap;
        process = ft_memalloc(sizeof(t_process));
        process->pc = pos;
        process->champ = i;
        process->op = g_optab[16];
        process->next = vm->process;
        vm->process = process;
        j = -1;
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
    vm->opts = opts;
    vm->champs = champs;
    vm->carry = 0;
    vm->process = NULL;
    /*
    if (opts->n_players == 1)
    {
        verbose_zero(champs);
        return (0);
    }*/
    if (!(vm->map = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE)))
        return (-1);
    i = -1;
    while ((unsigned int)++i < opts->n_players)
        ft_printf("%s\n", champs[i].name);
    i = -1;
    while (++i < MEM_SIZE)
        vm->map[i] = 0;
    if (install_champion(champs, opts, vm))
        return (ft_printf("Error, the map is not initilisated\n"));
    //print_vm_mem(vm);
    if (start_game(vm) < 0)
    {
        print_vm_mem(vm);
        return (ft_printf("Error, he doesn't have a game\n"));
    }
    print_vm_mem(vm);
    return (0);
}