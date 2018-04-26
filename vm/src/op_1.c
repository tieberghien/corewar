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

int ldi(t_vm *vm, t_op *op)
{

    if (params[2] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
}
*/

int sti(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int par_a;
    unsigned int par_b;
    unsigned char *idx_val;
    int k;
    int err;

    par_a = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? champ->registre[op->params[1] - 1] : op->params[1];
    par_b = op->params[2];
    tointhex((unsigned int)champ->registre[op->params[0] - 1], &idx_val);
    if ((par_a = rest_address(champ, par_a + par_b)) == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    k = -1;
    while (++k < 4)
        vm->map[(par_a + k) % MEM_SIZE] = idx_val[k];
    ft_memdel((void**)&idx_val);
    return (vm->carry);
}

int ldi(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? champ->registre[op->params[0] - 1] : rest_address(champ, op->params[0]);
    par_b = rest_address(champ, op->params[1]);
    if (((err == 1 && op->params[0] < REG_NUMBER) || err == 0) && op->params[2] < REG_NUMBER)
        champ->registre[op->params[2] - 1] = (par_a + par_b);
    if (op->params[2] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    return (vm->carry);
}

int zjmp(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int i;

    i = 0;
    if (vm->carry == 1)
    {
        champ->pc = (champ->pc + op->params[0]) % MEM_SIZE;
        return (vm->carry);
    }
    champ->pc = (champ->pc + 3)  % MEM_SIZE;
    return (vm->carry);
}

int op_xor(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? champ->registre[op->params[0] - 1] : op->params[0];
    if (err == 1 && op->params[0] >= REG_NUMBER)
        return (vm->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? champ->registre[op->params[1] - 1] : op->params[1];
    if (err == 1 && op->params[1] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[2] >= REG_NUMBER)
        return (vm->carry);
    champ->registre[op->params[2] - 1] = par_a ^ par_b;
    if (champ->registre[op->params[2] - 1] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    return (vm->carry);
}

int op_or(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? champ->registre[op->params[0] - 1] : op->params[0];
    if (err == 1 && op->params[0] >= REG_NUMBER)
        return (vm->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? champ->registre[op->params[1] - 1] : op->params[1];
    if (err == 1 && op->params[1] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[2] >= REG_NUMBER)
        return (vm->carry);
    champ->registre[op->params[2] - 1] = par_a | par_b;
    if (champ->registre[op->params[2] - 1] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    return (vm->carry);
}

int op_and(t_vm *vm, t_op *op, t_process *process)
{
    int par_a;
    int par_b;
    int err;

    par_a = ((err = ((op->ocp & PARAM_C) >> 6)) == 1) ? champ->registre[op->params[0] - 1] : op->params[0];
    if (err == 1 && op->params[0] >= REG_NUMBER)
        return (vm->carry);
    err = 0;
    par_b = ((err = ((op->ocp & PARAM_B) >> 4)) == 1) ? champ->registre[op->params[1] - 1] : op->params[1];
    if (err == 1 && op->params[1] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[2] >= REG_NUMBER)
        return (vm->carry);
    champ->registre[op->params[2] - 1] = par_a & par_b;
    if (champ->registre[op->params[2] - 1] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    return (vm->carry);
}

int sub(t_vm *vm, t_op *op, t_process *process)
{
    if (op->params[0] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[1] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[2] >= REG_NUMBER)
        return (vm->carry);
    champ->registre[op->params[2] - 1] = champ->registre[op->params[1] - 1] - champ->registre[op->params[0] - 1];
    if (champ->registre[op->params[2] - 1] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    return (vm->carry);
}

int add(t_vm *vm, t_op *op, t_process *process)
{
    unsigned int par_a;
    unsigned int par_b;

    if (op->params[0] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[1] >= REG_NUMBER)
        return (vm->carry);
    if (op->params[2] >= REG_NUMBER)
        return (vm->carry);
    par_a = champ->registre[op->params[1] - 1];
    par_b = champ->registre[op->params[0] - 1];
    champ->registre[op->params[2] - 1] = par_a + par_b;
    if (champ->registre[op->params[2] - 1] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    return (vm->carry);
}

int st(t_vm *vm, t_op *op, t_process *process)
{
    unsigned char *idx_val;
    int k;

    if (op->params[0] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    if (((op->ocp & PARAM_B) >> 4) == 1)
        champ->registre[op->params[1] - 1] = champ->registre[op->params[0] - 1];
    else
    {
        op->params[1] = rest_address(champ, op->params[1]);
        tointhex((unsigned int)champ->registre[op->params[0] - 1], &idx_val);
        if (!idx_val)
            return (vm->carry);
        k = -1;
        while (++k < 4)
            vm->map[(op->params[1] + k) % MEM_SIZE] = idx_val[k];
        ft_memdel((void**)&idx_val);
    }
    return (vm->carry);
}

int ld(t_vm *vm, t_op *op, t_process *process)
{
    if (op->params[0] == 0)
        vm->carry = 1;
    else
        vm->carry = 0;
    if (op->params[1] < REG_NUMBER)
        champ->registre[op->params[1] - 1] = rest_address(champ, op->params[0]);
    return (vm->carry);
}

int live(t_vm *vm, t_op *op, t_process *process)
{
    int i;

    process->champ = process->champ;
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