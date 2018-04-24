#include "vm.h"

unsigned int toint(t_vm *vm, int i, int size)
{
    int multiplicateur;
    unsigned int total;

    total = 0;
    multiplicateur = 1;
    size =  size + i - 1;
    while (size >= i)
    {
        total += vm->map[size] * multiplicateur;
        multiplicateur *= 256;
        size--;
    }
    return (total);
}

int main_decript(int par, unsigned char *vm, int j, t_op **new)
{
    int k;
    t_vm map;

    k = 0;
    map.map = vm;
    if (par > 1)
    {
        k = (par == 2 && ((*new)->op_code < 9 || (*new)->op_code == 13)) ? 4 : 2;
        (*new)->params[j] = toint(&map , 0, k);
        return (k);
    }
    else if (par == 1)
    {
        (*new)->params[j] = toint(&map, 0, 1);
        return (1);
    }
    return (0);
}

int decript_ocp(unsigned char opc)
{
    if (opc == 1)
        return (1);
    else if (opc == 2)
        return (2);
    else if (opc == 3)
        return (3);
    return (0);
}

int save_op_spec(t_op **op, int *i, t_vm *vm)
{
    int     k;
    int     alive;
    t_op    *new;

    new = ft_opdup(g_optab[vm->map[*i] - 1]);
    new->next = *op;
    *op = new;
    (*op)->pc = *i;
    k = (vm->map[*i] == 1) ? 4 : 2;
    if ((alive = mv_mem(i, 1, vm, op)) <= 1)
        return (alive);
    (*op)->params[0] = toint(vm, *i, k);
    if ((alive = mv_mem(i, k, vm, op)) <= 1)
        return (alive);
    return(alive);
}

int save_op(t_op **op, int *i, t_vm *vm)
{
    int     k;
    int     alive;
    t_op    *new;

    new = ft_opdup(g_optab[vm->map[*i] - 1]);
    new->next = *op;
    *op = new;
    (*op)->pc = *i;
    if ((alive = mv_mem(i, 1, vm, op)) <= 1)
        return (alive);
    k = vm->map[*i];
    (*op)->ocp = k;
    if ((alive = mv_mem(i, 1, vm, op)) <= 1)
        return (alive);
    if ((alive = mv_mem(i, main_decript(decript_ocp((k & PARAM_C) >> 6), vm->map + *i, 0, op), vm, op)) <= 1)
        return (alive);
    if ((alive = mv_mem(i, main_decript(decript_ocp((k & PARAM_B) >> 4), vm->map + *i, 1, op), vm, op)) <= 1)
        return (alive);
    if ((alive = mv_mem(i, main_decript(decript_ocp((k & PARAM_A) >> 2), vm->map + *i, 2, op), vm, op)) <= 1)
        return (alive);
    return (alive);
}