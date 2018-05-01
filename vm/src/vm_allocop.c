#include "vm.h"

unsigned int toint(t_vm *vm, int i, int size)
{
    int multiplicateur;
    unsigned int total;
    int k;

    k = 0;
    total = 0;
    multiplicateur = 1;
    size =  size + i - 1;
    while (size >= i)
    {
        total += vm->map[size] * multiplicateur;
        multiplicateur *= 256;
        size--;
        k++;
    }
    return (total);
}

int main_decript(int par, unsigned char *vm, int j, t_op *new)
{
    int k;
    t_vm map;

    k = 0;
    map.map = vm;
    if (par > 1)
    {
        k = (par == 2 && (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
        new->params[j] = toint(&map , 0, k);
        return (k);
    }
    else if (par == 1)
    {
        new->params[j] = toint(&map, 0, 1);
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

int save_op_spec(t_process *process, t_vm *vm)
{
    int     k;
    int     j;
    int     alive;
 
    k = process->pc;
    j = 0;
    alive = (vm->map[k] == 1) ? 4 : 2;
    k = (k + 1) % MEM_SIZE;
    j++;
    process->op.params[0] = toint(vm, k, alive);
    k = (k + alive) % MEM_SIZE;
    j += alive;
    return (j);
}

int save_op(t_process *process, t_vm *vm)
{
    int     k;
    int     j;
    int     alive; 

    k = process->pc;
    j = 0;
    k = (k + 1) % MEM_SIZE;
    j++;
    process->op.ocp = vm->map[k];
    k = (k + 1) % MEM_SIZE;
    j++;
    alive = main_decript(decript_ocp((process->op.ocp & PARAM_C) >> 6), vm->map + k, 0, &(process->op));
    k = (k + alive) % MEM_SIZE;
    j += alive;
    alive = main_decript(decript_ocp((process->op.ocp & PARAM_B) >> 4), vm->map + k, 1, &(process->op));
    k = (k + alive) % MEM_SIZE;
    j += alive;
    alive = main_decript(decript_ocp((process->op.ocp & PARAM_A) >> 2), vm->map + k, 2, &(process->op));
    k = (k + alive) % MEM_SIZE;
    j += alive;
    return (j);
}