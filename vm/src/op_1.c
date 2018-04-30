#include "vm.h"

/*
int tohexint(unsigned int num)
{
    unsigned int total;
    unsigned int cpy;
    int i;
    int somme;

    i = -1;
    total = 256 * 256;
    somme = 0;
    while (++i < 2)
    {
        cpy = num / total;
        somme = somme + (cpy % 256);
        total /= 256;
    }
    return (somme);
}
*/

int	aff(t_vm *vm, t_op *op, t_process *process)
{
    vm->map[0] = vm->map[0];
	ft_printf("%c\n", process->registre[op->params[0] - 1] % 256);
	if (process->registre[op->params[0] - 1] == 0)
		process->carry = 1;
	else
		process->carry = 0;
	return (process->carry);
}


int op_lfork(t_vm *vm, t_op *op, t_process *process)
{
    t_process   *new;

    if (!(new = ft_memalloc(sizeof(t_process))))
        return (-1);
    *new = *process;
    if (process->registre[op->params[0] - 1] == 0)
        new->pc = process->pc;
    else
       new->pc = (process->pc + op->params[0]) % MEM_SIZE;
    new->next = vm->process;
    vm->process = new;
    return (0);
}

int lldi(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    par_b = op->params[1];
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
    vm->map[0] = vm->map[0];
    if (op->params[0] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    if (op->params[1] < REG_NUMBER)
    process->registre[op->params[1] - 1] = op->params[0];
    return (process->carry);
}

int op_fork(t_vm *vm, t_op *op, t_process *process)
{
    t_process   *new;

    if (!(new = ft_memalloc(sizeof(t_process))))
        return (-1);
    *new = *process;
    if (process->registre[op->params[0] - 1] == 0)
        new->pc = process->pc;
    else
       new->pc = (process->pc + (op->params[0] % IDX_MOD)) % MEM_SIZE;
    new->next = vm->process;
    vm->process = new;
    return (0);
}

int sti(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int par_a;
    unsigned int par_b;
    unsigned char *idx_val;
    int k;
    int err;

    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    par_b =op->params[2];
    ft_printf("param -> %d\n", par_a);
    tointhex((unsigned int)process->registre[op->params[0] - 1], &idx_val);
    if ((par_a = process->pc + (par_a + par_b) % IDX_MOD) == 0)
        process->carry = 1;
    else
        process->carry = 0;
    k = -1;
    while (++k < 4)
    {
        ft_printf("%hhx \n", idx_val[k]);
        vm->map[(par_a + k) % MEM_SIZE] = idx_val[k];
    }
    ft_putchar('\n');
    ft_memdel((void**)&idx_val);
    return (process->carry);
}

int ldi(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : process->pc + (op->params[0] % IDX_MOD);
    par_b = process->pc + (op->params[1] % IDX_MOD);
    if (((err == 1 && op->params[0] < REG_NUMBER) || err == 0) && op->params[2] < REG_NUMBER)
    process->registre[op->params[2] - 1] = (par_a + par_b);
    if (op->params[2] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int zjmp(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int i;

    vm->map[0] = vm->map[0];
    i = 0;
    if (process->carry == 1)
    {
        process->pc = (process->pc + op->params[0]) % MEM_SIZE;
        return (process->carry);
    }
    process->pc = (process->pc + 3)  % MEM_SIZE;
    return (process->carry);
}

int op_xor(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (err == 3)
        par_a = process->pc + (par_a % IDX_MOD);
    if (err == 1 && op->params[0] >= REG_NUMBER)
        return (process->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (err == 3)
        par_b = process->pc + (par_b % IDX_MOD);
    if (err == 1 && op->params[1] >= REG_NUMBER)
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
        return (process->carry);
    process->registre[op->params[2] - 1] = (par_a ^ par_b) % IDX_MOD;
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

    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (err == 3)
        par_a = process->pc + (par_a % IDX_MOD);
    if (err == 1 && op->params[0] >= REG_NUMBER)
        return (process->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (err == 3)
        par_b = process->pc + (par_b % IDX_MOD);
    if (err == 1 && op->params[1] >= REG_NUMBER)
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

    vm->map[0] = vm->map[0];
    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? process->registre[op->params[0] - 1] : op->params[0];
    if (err == 3)
        par_a = process->pc + (par_a % IDX_MOD);
    if (err == 1 && op->params[0] >= REG_NUMBER)
        return (process->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? process->registre[op->params[1] - 1] : op->params[1];
    if (err == 3)
        par_b = process->pc + (par_b % IDX_MOD);
    if (err == 1 && op->params[1] >= REG_NUMBER)
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
    vm->map[0] = vm->map[0];
    if (op->params[0] >= REG_NUMBER)
        return (process->carry);
    if (op->params[1] >= REG_NUMBER)
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
        return (process->carry);
    process->registre[op->params[2] - 1] = process->registre[op->params[1] - 1] - process->registre[op->params[0] - 1];
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int add(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int par_a;
    unsigned int par_b;

    vm->map[0] = vm->map[0];
    if (op->params[0] >= REG_NUMBER)
        return (process->carry);
    if (op->params[1] >= REG_NUMBER)
        return (process->carry);
    if (op->params[2] >= REG_NUMBER)
        return (process->carry);
    par_a = process->registre[op->params[1] - 1];
    par_b = process->registre[op->params[0] - 1];
    process->registre[op->params[2] - 1] = par_a + par_b;
    if (process->registre[op->params[2] - 1] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    return (process->carry);
}

int st(t_vm *vm, t_op *op, t_process *process)
{
    unsigned char *idx_val;
    int k;

    vm->map[0] = vm->map[0];
    if (op->params[0] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    if (((op->ocp & PARAM_B) >> 4) == 1)
    process->registre[op->params[1] - 1] = process->registre[op->params[0] - 1];
    else
    {
        op->params[1] = process->pc + (op->params[1] % IDX_MOD);
        tointhex((unsigned int)process->registre[op->params[0] - 1], &idx_val);
        if (!idx_val)
            return (process->carry);
        k = -1;
        while (++k < 4)
            vm->map[(op->params[1] + k) % MEM_SIZE] = idx_val[k];
        ft_memdel((void**)&idx_val);
    }
    return (process->carry);
}

int ld(t_vm *vm, t_op *op, t_process *process)
{
    vm->map[0] = vm->map[0];
    if (op->params[0] == 0)
        process->carry = 1;
    else
        process->carry = 0;
    if (op->params[1] < REG_NUMBER)
    process->registre[op->params[1] - 1] = (((op->ocp & PARAM_C) >> 6) == 2) ? op->params[0] : process->pc + (op->params[0] % IDX_MOD);
    return (process->carry);
}

int live(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int i;

    process->champ = process->champ;
    i = 0;
    ft_printf("joueur : %s, carry : %d, cycle : %d, parametre : %d\n", vm->champs[process->champ].name, process->carry, vm->cycle, op->params[0]);
    while (i < vm->opts->n_players)
    {
        if (op->params[0] == vm->champs[i].player_id)
        {
            vm->champs[i].alive = 1;
            verbose_one(*(vm->champs + i));
            return (process->carry);
        }
        i++;
    }
    return (process->carry);
}
