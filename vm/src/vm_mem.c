#include "vm.h"

void	init_reg(t_champs *champs, int player, t_process *process)
{
	int i;

	i = 0;
	process->registre[0] = champs[player].player_id;
	while (++i < REG_NUMBER)
		process->registre[i] = 0;
}

void p_turn(t_vm *vm, t_process *process)
{
    int j;

    j = 0;
    if (process->op.dur > 1)
        process->op.dur--;
    else if(process->op.dur == 0)
    {
        if (vm->map[process->pc] > 0 && vm->map[process->pc] <= 16)
        {
            process->op = g_optab[vm->map[process->pc] - 1];
            process->op.dur--;
        }
        else
            process->pc = (process->pc + 1) % MEM_SIZE;
    }
    else if (process->op.dur == 1)
    {
        if (vm->map[process->pc] == 9 || vm->map[process->pc] == 15 || vm->map[process->pc] == 12 || vm->map[process->pc] == 1)
        {
            if (vm->map[process->pc] == 1)
                process->live++;
            j = save_op_spec(process, vm);
        }
        else if (vm->map[process->pc] > 1 && vm->map[process->pc] <= 16)
            j = save_op(process, vm);
        if (vm->map[process->pc] > 0 && vm->map[process->pc] <= 16)
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
    int check;
    unsigned int tot_cycle;

    check = 0;
    vm->live_num = 0;
    tot_cycle = 0;
    while (1)
    {
        vm->cycle = vm->next_cycle_group;
//        ft_printf("cycle to die -> %d\n", vm->next_cycle_group);
        while (vm->cycle > 0)
        {
            i = -1;
            process = vm->process;
            while (process)
            {
           //	ft_printf("process_id - %d\n", process->champ);
                if (process->live >= 0)
                    p_turn(vm, process);
                process = process->next;
		//		print_vm_mem(vm);
            }
//          ft_printf("\n");
            tot_cycle++;
            if (vm->opts->s_cycles != 0 && tot_cycle >= vm->opts->s_cycles)
                return (-6);
  //          ft_printf("cycle -> %d\n", tot_cycle);
            vm->cycle--;
        }
	//	print_vm_mem(vm);
        if (check_alive(&(vm->process), 0) < 0)
            return (-1);
        check++;
        if (check >= MAX_CHECKS || vm->live_num >= NBR_LIVE)
        {
            vm->next_cycle_group -= CYCLE_DELTA;
            check = 0;
        }
        if (vm->next_cycle_group < 0)
            return (1);
    //    ft_printf("live for cycle   %d\n", vm->live_num);
        vm->live_num = 0;
    }
}

int install_champion(t_champs *champs, t_opts *opts, t_vm *vm)
{
    int i;
    int gap;
    int pos;
    int j;
    t_process *process;

    i = -1;
    gap = (MEM_SIZE / opts->n_players);
    while ((unsigned int)++i < opts->n_players)
    {
        j = 0;
        pos = i * gap;
        process = ft_memalloc(sizeof(t_process));
        process->pc = pos;
        process->carry = 0;
        process->live = 0;
        process->champ = i;
        init_reg(champs, i, process);
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
    vm->next_cycle_group = CYCLE_TO_DIE;
    vm->opts = opts;
    vm->champs = champs;
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
    //while ((unsigned int)++i < opts->n_players)
      //  ft_printf("%s\n", champs[i].name);
    i = -1;
    while (++i < MEM_SIZE)
        vm->map[i] = 0;
    if (install_champion(champs, opts, vm))
        return (ft_printf("Error, the map is not initilisated\n"));
    //print_vm_mem(vm);
    if (start_game(vm) < -5)
    {
        print_vm_mem(vm);
        return (1000);

    }
    else
    {
        i = 0;
        while (champs[i].player_id != vm->last_live)
            i++;
        verbose_zero(champs + i);
        check_alive(&(vm->process), 1);
    }
    //print_vm_mem(vm);
    return (0);
}
