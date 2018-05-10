#include "vm.h"

void	verb_adv(t_vm *vm, t_process *process, int l)
{
	int		len;
	int		i;

	len = l;
	i = 0;
	ft_printf("ADV %d (", len);
	if (process->pc == 0)
		ft_putstr("0x");
	ft_printf("%#.4x -> ", process->pc);
	if (process->pc + len == 0)
		ft_putstr("0x");
	ft_printf("%#.4x) ", process->pc + len);
	while (i < len)
	{
        //vm->map[0] = vm->map[0];
        //process->number = process->number;
		ft_printf("%.2hhx ", vm->map[(process->pc + i) % MEM_SIZE]);
		i++;
	}
	ft_putchar('\n');
}

int	aff(t_vm *vm, t_op *op, t_process *process)
{
    if (((op->ocp & PARAM_C) >> 6) != 1 || ((op->ocp & PARAM_B) >> 4) != 0 || ((op->ocp & PARAM_A) >> 2) != 0)
       return (0);
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
	if (process->registre[op->params[0] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}


int op_lfork(t_vm *vm, t_op *op, t_process *process)
{
    t_process   *new;

    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    if (!(new = ft_memalloc(sizeof(t_process))))
        return (-1);
    *new = *process;
    //verb_adv(vm, process, 3);
    if (op->params[0] == 0)
        new->pc = (process->pc + 3) % MEM_SIZE;
    else
        new->pc = (op->params[0] + process->pc) % MEM_SIZE;
    new->next = *(vm->process); 
    *(vm->process) = new;
    vm->ping++;
    new->number = vm->ping;
    return (0);
}

int lldi(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int k;

    //ft_printf("hello 7\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    //verb_adv(vm, process, 7);
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0 
    || ((op->ocp & PARAM_B) >> 4) == 3 || ((op->ocp & PARAM_A) >> 2) != 1)
       return (0);
    if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
        return (0);
    if ((k = (((op->ocp & PARAM_C)) >> 6) == 1) && (op->params[0] > REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    if (k == 3)
        par_a = (short)op->params[0];
    else
        par_a = (k == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if ((k = (((op->ocp & PARAM_B)) >> 4) == 1) && (op->params[1] > REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    par_b = (k == 1) ? process->registre[op->params[1] - 1] : (short)op->params[1];
    process->registre[op->params[2] - 1] = toint(vm ,par_a + par_b, 4);
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int lld(t_vm *vm, t_op *op, t_process *process)
{
    if (((op->ocp & PARAM_C) >> 6) < 2 || ((op->ocp & PARAM_B) >> 4) > 1 || ((op->ocp & PARAM_A) >> 2) != 0)
       return (0);
    vm->map[0] = vm->map[0];
    if (op->params[1] > 0 && op->params[1] <= REG_NUMBER)
        process->registre[op->params[1] - 1] = op->params[0];
    else
        return (0);
    if (op->params[0] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int ldi(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int k;

    //ft_printf("hello 7\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    //verb_adv(vm, process, 7);
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0 
    || ((op->ocp & PARAM_B) >> 4) == 3 || ((op->ocp & PARAM_A) >> 2) != 1)
       return (0);
    if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
        return (0);
    if ((k = (((op->ocp & PARAM_C)) >> 6) == 1) && (op->params[0] > REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    if (k == 3)
        par_a = (short)op->params[0];
    else
        par_a = (k == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if ((k = (((op->ocp & PARAM_B)) >> 4) == 1) && (op->params[1] > REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    par_b = (k == 1) ? process->registre[op->params[1] - 1] : (short)op->params[1];
    process->registre[op->params[2] - 1] = toint(vm , res_add(par_a + par_b, process->pc), 4);
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int op_xor(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    //ft_printf("hello 3\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0 || ((op->ocp & PARAM_A) >> 2) != 1)
        return (0);
    if ((err = (((op->ocp & PARAM_C)) >> 6) == 1) && (op->params[0] > REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    if (err == 3)
        par_a = res_add(op->params[0] , process->pc);
    else
        par_a = (err == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (((err = ((op->ocp & PARAM_B) >> 4)) == 1) && (op->params[1] > REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (err == 3)
        par_b = res_add(op->params[1] , process->pc);
    else
        par_b = (err == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (op->params[2] > REG_NUMBER || op->params[2] < 1)
        return (process->carry);
    process->registre[op->params[2] - 1] = par_a ^ par_b;
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int op_or(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    //ft_printf("hello 3\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0 || ((op->ocp & PARAM_A) >> 2) != 1)
        return (0);
    if ((err = (((op->ocp & PARAM_C)) >> 6) == 1) && (op->params[0] > REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    if (err == 3)
        par_a = res_add(op->params[0] , process->pc);
    else
        par_a = (err == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (((err = ((op->ocp & PARAM_B) >> 4)) == 1) && (op->params[1] > REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (err == 3)
        par_b = res_add(op->params[1] , process->pc);
    else
        par_b = (err == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (op->params[2] > REG_NUMBER || op->params[2] < 1)
        return (process->carry);
    process->registre[op->params[2] - 1] = par_a | par_b;
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int op_and(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    //ft_printf("hello 3\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0 || ((op->ocp & PARAM_A) >> 2) != 1)
        return (0);
    if ((err = (((op->ocp & PARAM_C)) >> 6) == 1) && (op->params[0] > REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    if (err == 3)
        par_a = res_add(op->params[0] , process->pc);
    else
        par_a = (err == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (((err = ((op->ocp & PARAM_B) >> 4)) == 1) && (op->params[1] > REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (err == 3)
        par_b = res_add(op->params[1] , process->pc);
    else
        par_b = (err == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (op->params[2] > REG_NUMBER || op->params[2] < 1)
        return (process->carry);
    process->registre[op->params[2] - 1] = par_a & par_b;
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int sub(t_vm *vm, t_op *op, t_process *process)
{
    //ft_printf("hello 2\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    if (((op->ocp & PARAM_C) >> 6) != 1 || ((op->ocp & PARAM_B) >> 4) != 1 || ((op->ocp & PARAM_A) >> 2) != 1)
       return (0);
    if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
        return (0);
    if (op->params[1] <= 0 || op->params[1] > REG_NUMBER)
        return (0);
    if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
        return (0);
    process->registre[op->params[2] - 1] = process->registre[op->params[0] - 1] - process->registre[op->params[1] - 1];
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int add(t_vm *vm, t_op *op, t_process *process)
{
    //ft_printf("hello 1\n");
    unsigned int par_a;
    unsigned int par_b;


    vm->map[0] = vm->map[0];
    if (((op->ocp & PARAM_C) >> 6) != 1 || ((op->ocp & PARAM_B) >> 4) != 1 || ((op->ocp & PARAM_A) >> 2) != 1)
       return (0);
    if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
        return (0);
    if (op->params[1] <= 0 || op->params[1] > REG_NUMBER)
        return (0);
    if (op->params[2] <= 0 || op->params[2] > REG_NUMBER)
        return (0);
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    par_a = process->registre[op->params[1] - 1];
    par_b = process->registre[op->params[0] - 1];
    process->registre[op->params[2] - 1] = par_a + par_b;
    //ft_printf("%zu\n", process->registre[op->params[2] -]);
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int op_fork(t_vm *vm, t_op *op, t_process *process)
{
    t_process   *new;

    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    if (!(new = ft_memalloc(sizeof(t_process))))
        return (-1);
    *new = *process;
    //verb_adv(vm, process, 3);
    if (op->params[0] == 0)
        new->pc = (process->pc + 3) % MEM_SIZE;
    else
        new->pc = res_add(op->params[0], process->pc) % MEM_SIZE;
    new->next = *(vm->process); 
    *(vm->process) = new;
    vm->ping++;
    new->number = vm->ping;
    return (0);
}

int sti(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int par_a;
    unsigned int par_b;
    unsigned char *idx_val;
    int k;


    if (((op->ocp & PARAM_C) >> 6) != 1 || ((op->ocp & PARAM_B) >> 4) == 0 || ((op->ocp & PARAM_A) >> 2) == 0 || ((op->ocp & PARAM_A) >> 2) == 3)
       return (0);
    if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
        return (0);
    vm->map[0] = vm->map[0];
    if ((k = (((op->ocp & PARAM_B)) >> 4) == 1) && (op->params[1] > REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (k == 3)
        par_a = (short)op->params[1];
    else
        par_a = (k == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (((k = ((op->ocp & PARAM_A) >> 2)) == 1) && (op->params[2] > REG_NUMBER || op->params[2] < 1))
        return (process->carry);
    par_b = (k == 1) ? process->registre[op->params[2] - 1] : op->params[2];
    tointhex((unsigned int)process->registre[op->params[0] - 1], &idx_val, vm);
    par_a = res_add(par_a + par_b, process->pc);
    //if (vm->c + 1 == 11245)
    //    ft_printf("op : %s - ocp : %d params : %d_%d_%d - pc : %d   par_a : %d\n", op->name, op->ocp, op->params[0], op->params[1], process->registre[op->params[2] - 1], process->pc, par_a);
    if (!idx_val)
        return (process->carry);
    k = -1;
    while (++k < 4)
    {
        vm->map[(par_a + k) % MEM_SIZE] = idx_val[k];
    }    
    ft_memdel((void**)&idx_val);
    return (process->carry);
}

int zjmp(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int i;
    
    //ft_printf("op : %s - params : %x_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    i = 0;
    if (process->carry == 1)
    {
        //ft_printf("| zjmp %d OK\n", (short)op->params[0]);
        process->pc = res_add(op->params[0], process->pc);// (process->pc + res_add(op->params[0])) % MEM_SIZE;
        return (process->carry);
    }
    verb_adv(vm, process, 3);
    process->pc = (process->pc + 3)  % MEM_SIZE;
    return (process->carry);
}

int st(t_vm *vm, t_op *op, t_process *process)
{
    unsigned char *idx_val;
    int k;

    //ft_printf("op : %s - params : %d_%d- pc : %d\n", op->name, process->registre[op->params[0] - 1], op->params[1], process->pc);
    if (((op->ocp & PARAM_C) >> 6) != 1 || ((op->ocp & PARAM_B) >> 4) == 2 || ((op->ocp & PARAM_A) >> 2) != 0)
       return (0);
    if (((op->ocp & PARAM_B) >> 4) == 1)
    {
        if ((op->params[1] <= 0 || op->params[1] > REG_NUMBER) || (op->params[0] <= 0 || op->params[0] > REG_NUMBER))
        {
            return (0);
        }
        process->registre[op->params[1] - 1] = process->registre[op->params[0] - 1];
    }
    else
    {
        
        if ((op->params[0] <= 0 || op->params[0] > REG_NUMBER))
        {
            //verb_adv(vm, process, 5);
            return (0);
        }
        //ft_printf("| %s r%d %d\n", op->name, op->params[0], (short)op->params[1]);
        op->params[1] = res_add(op->params[1], process->pc);
        tointhex(process->registre[op->params[0] - 1], &idx_val, vm);
        if (!idx_val)
            return (process->carry);
        k = -1;
        while (++k < 4)
        {
            vm->map[(op->params[1] + k) % MEM_SIZE] = idx_val[k];
            //ft_printf("%hhx ", idx_val[k]);
        }
        ft_memdel((void**)&idx_val);
        //if (((op->ocp & PARAM_C) >> 6) == 3)
            //verb_adv(vm, process, 6);
        //else 
            //verb_adv(vm, process, 5);
    }
    return (process->carry);
}

int ld(t_vm *vm, t_op *op, t_process *process)
{
    //ft_printf("op : %s - params : %d_%d- pc : %d\n", op->name, op->params[0], process->registre[op->params[1] - 1], process->pc);
    //exit(1);
    if (((op->ocp & PARAM_C) >> 6) < 2 || ((op->ocp & PARAM_B) >> 4) > 1 || ((op->ocp & PARAM_A) >> 2) != 0)
       return (0);
    vm->map[0] = vm->map[0];
    if (op->params[1] > 0 && op->params[1] <= REG_NUMBER)
        process->registre[op->params[1] - 1] = (((op->ocp & PARAM_C) >> 6) == 2) ? op->params[0] : res_add(op->params[0], process->pc);
    else
        return (0);
    
    if (op->params[0] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}



int live(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int i;

    //ft_printf("op : %s - params : %d - pc : %d\n", op->name, op->params[0], process->pc);
    process->champ = process->champ;
    i = 0;
    vm->live_num++;
    //verb_adv(vm, process, 5);
    while (i < vm->opts->n_players)
    {
        if (op->params[0] == vm->champs[i].player_id)
        {
            //verbose_one(*(vm->champs + i));
            vm->last_live = vm->champs[i].player_id;
            return (process->carry);
        }
        i++;
    }
    return (process->carry);
}