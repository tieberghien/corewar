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
		ft_printf("%.2hhx ", vm->map[(process->pc + i) % MEM_SIZE]);
		i++;
	}
	ft_putchar('\n');
}

int	aff(t_vm *vm, t_op *op, t_process *process)
{
    //ft_printf("hello 11\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    verb_adv(vm, process, 7);
	//ft_printf("%c\n", process->registre[op->params[0] - 1] % 256);
	if (process->registre[op->params[0] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}


int op_lfork(t_vm *vm, t_op *op, t_process *process)
{
    t_process   *new;

    //ft_printf("hello cycles %d\n", vm->c);
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    if (!(new = ft_memalloc(sizeof(t_process))))
        return (-1);
    verb_adv(vm, process, 7);
    *new = *process;
    if (op->params[0] == 0)
        new->pc = (process->pc + 3) % MEM_SIZE;
    else
        new->pc = (process->pc + op->params[0]) % MEM_SIZE;
    new->op.dur = 0;
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
    int err;

    //ft_printf("hello 9\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    par_b = op->params[1];
    verb_adv(vm, process, 7);
    if (((err == 1 && op->params[0] < REG_NUMBER) || err == 0) && op->params[2] < REG_NUMBER)
        process->registre[op->params[2] - 1] = (par_a + par_b);
    if (op->params[2] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int lld(t_vm *vm, t_op *op, t_process *process)
{
    //ft_printf("hello 8\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    verb_adv(vm, process, 7);
    if (op->params[0] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    if (op->params[1] < REG_NUMBER)
        process->registre[op->params[1] - 1] = (((op->ocp & PARAM_C) >> 6) == 2) ? op->params[0] : process->pc + op->params[0];
    return (process->carry);
}

int ldi(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    //ft_printf("hello 7\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    verb_adv(vm, process, 7);
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : res_add(op->params[0], process->pc);
    par_b = res_add(op->params[1], process->pc);
    if (((err == 1 && op->params[0] < REG_NUMBER) || err == 0) && op->params[2] < REG_NUMBER)
    process->registre[op->params[2] - 1] = (par_a + par_b);
    if (op->params[2] == 0)
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

    //ft_printf("hello 6\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    verb_adv(vm, process, 7);
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (err == 3)
        par_a = res_add(par_a, process->pc);
    if (err == 1 && (op->params[0] >= REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (err == 3)
        par_b = res_add(par_b, process->pc);
    if (err == 1 && (op->params[1] >= REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
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

//ft_printf("hello 5\n");
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (err == 3)
        par_a = res_add(par_a, process->pc);
    if (err == 1 && (op->params[0] >= REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    verb_adv(vm, process, 5);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (err == 3)
        par_b = res_add(par_b, process->pc);
    if (err == 1 && (op->params[1] >= REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
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
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (err == 3)
        par_a = res_add(par_a, process->pc);
    if (err == 1 && (op->params[0] >= REG_NUMBER || op->params[0] < 1))
        return (process->carry);
    verb_adv(vm, process, 5);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (err == 3)
        par_b = res_add(par_b, process->pc);
    if (err == 1 && (op->params[1] >= REG_NUMBER || op->params[1] < 1))
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
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
    if (op->params[0] >= REG_NUMBER)
        return (process->carry);
    if (op->params[1] >= REG_NUMBER)
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
        return (process->carry);
    verb_adv(vm, process, 5);
    process->registre[op->params[2] - 1] = process->registre[op->params[1] - 1] - process->registre[op->params[0] - 1];
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

    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    if (op->params[0] >= REG_NUMBER)
        return (process->carry);
    if (op->params[1] >= REG_NUMBER)
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
        return (process->carry);
    verb_adv(vm, process, 5);
    par_a = process->registre[op->params[1] - 1];
    par_b = process->registre[op->params[0] - 1];
    process->registre[op->params[2] - 1] = par_a + par_b;
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
    //new->live = 0;
    verb_adv(vm, process, 3);
    if (op->params[0] == 0)
        new->pc = (process->pc + 3) % MEM_SIZE;
    else
        new->pc = res_add(op->params[0], process->pc) % MEM_SIZE;
    new->op.dur = 0;
    new->next = *(vm->process); 
    *(vm->process) = new;
    vm->ping++;
    new->number = vm->ping;
    //ft_printf("pc -> %d\n", new->pc);
    return (0);
}

int sti(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int par_a;
    unsigned int par_b;
    unsigned char *idx_val;
    int k;

    if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
        return (-1);
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    k = 3;
    if (((op->ocp & PARAM_B) >> 4) == 1)
        k++;
    if (((op->ocp & PARAM_B) >> 4) != 1)
        k += 2;
    if (((op->ocp & PARAM_A) >> 2) == 1)
        k += 1;
    if (((op->ocp & PARAM_A) >> 2) != 1)
        k += 2;
    verb_adv(vm, process, k++);
    par_a = (((op->ocp & PARAM_B) >> 4) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    par_b = (((op->ocp & PARAM_A) >> 2) == 1) ? process->registre[op->params[2] - 1] : op->params[2];
    tointhex((unsigned int)process->registre[op->params[0] - 1], &idx_val, vm);
    par_a = res_add(par_a + par_b, process->pc);
    if (!idx_val)
        return (process->carry);
    k = -1;
    while (++k < 4)
    {
        vm->map[(par_a + k) % MEM_SIZE] = idx_val[k];
        vm->color[(par_a + k) % MEM_SIZE] = process->champ + 1;
    }
    //
    //ft_printf("op : %s - params : %d_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], par_a);    
    ft_memdel((void**)&idx_val);
    return (process->carry);
}

int zjmp(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int i;
    //verb_adv(vm, process, 3);
    //ft_printf("op : %s - params : %x_%d_%d - pc : %d\n", op->name, op->params[0], op->params[1], op->params[2], process->pc);
    vm->map[0] = vm->map[0];
    i = 0;
    if (process->carry == 1)
    {
        //ft_printf("| zjmp %d OK\n", (short)op->params[0]);
        process->pc = res_add(op->params[0], process->pc);// (process->pc + res_add(op->params[0])) % MEM_SIZE;
        return (process->carry);
    }
    process->pc = (process->pc + 3)  % MEM_SIZE;
    //ft_printf("op : %s - params : %d - pc : %d\n", op->name, op->params[0], process->pc);
    return (process->carry);
}

int st(t_vm *vm, t_op *op, t_process *process)
{
    unsigned char *idx_val;
    int k;

    //ft_printf("op : %s - params : %d_%d- pc : %d\n", op->name, op->params[0], op->params[1], process->pc);
    if (((op->ocp & PARAM_C) >> 6) > 1 || ((op->ocp & PARAM_B) >> 4) == 2 || ((op->ocp & PARAM_A) >> 2) != 0)
        return (-1);
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0)
        return (-1);
    if (((op->ocp & PARAM_B) >> 4) == 1)
    {
        verb_adv(vm, process, 4);
        process->registre[op->params[1] - 1] = process->registre[op->params[0] - 1];
    }
    else
    {
        
        if (op->params[0] <= 0 || op->params[0] > REG_NUMBER)
        {
            verb_adv(vm, process, 5);
            return (-1);
        }
        //ft_printf("| %s r%d %d\n", op->name, op->params[0], (short)op->params[1]);
        op->params[1] = res_add(op->params[1], process->pc);
        tointhex(process->registre[op->params[0] - 1], &idx_val, vm);
        k = -1;
        if (!idx_val)
            return (process->carry);
        k = -1;
        while (++k < 4)
        {
            vm->map[(op->params[1] + k) % MEM_SIZE] = idx_val[k];
            vm->color[(op->params[1] + k) % MEM_SIZE] = process->champ + 1;
            //ft_printf("%hhx ", idx_val[k]);
        }
        ft_memdel((void**)&idx_val);
        verb_adv(vm, process, 5);
    }
    return (process->carry);
}

int ld(t_vm *vm, t_op *op, t_process *process)
{
    //ft_printf("op : %s - params : %d_%d - pc : %d\n", op->name, op->params[0], op->params[1], process->pc);
    vm->map[0] = vm->map[0];
    //ft_printf("register : %d       avamt : %ld       ", op->params[1], process->registre[op->params[1] - 1]);    
    //ft_printf("| ld %d r%d\n", op->params[0], op->params[1]);
    if ((((op->ocp & PARAM_C) >> 6) == 2))
        verb_adv(vm, process, 7);
    else
        verb_adv(vm, process, 5);
    if (((op->ocp & PARAM_C) >> 6) == 1 || ((op->ocp & PARAM_B) >> 4) > 1 || ((op->ocp & PARAM_A) >> 2) != 0)
        return (-1);
    if (((op->ocp & PARAM_C) >> 6) == 0 || ((op->ocp & PARAM_B) >> 4) == 0)
        return (-1);

    if (op->params[1] > 0 && op->params[1] < REG_NUMBER)
        process->registre[op->params[1] - 1] = (((op->ocp & PARAM_C) >> 6) == 2) ? op->params[0] : res_add(op->params[0], process->pc);
    else
        return (-1);
    if (process->registre[op->params[1] - 1] == 0)
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
    verb_adv(vm, process, 5);
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