#include "vm.h"


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
/*
t_op     *extract_good_instruc(int instruction)
{
    int i;

    i = -1;
    while (g_optab[++i][0])
        if (instruction == g_optab[i][3])
            return (g_optab + i);
    return (NULL);
}
*/

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
    ft_printf("%d\n", total);
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
        //ft_printf(new->params[j]);
        return (k);
    }
    else if (par == 1)
    {
        (*new)->params[j] = toint(&map, 0, 1);
        return (1);
    }
    return (0);
}
 
int start_game(t_vm *vm, t_op **op)
{
    int i;
    int ocp;
    int k;
    t_op *new;

    i = 0;
    while (i < MEM_SIZE)
    {
        if (vm->map[i] == 9 || vm->map[i] == 15 || vm->map[i] == 12 || vm->map[i] == 1)
        {
            new = ft_opdup(g_optab[vm->map[i] - 1]);
            new->next = *op;
            *op = new;
            k = (vm->map[i] == 1) ? 4 : 2;
            i++;
            (*op)->params[0] = toint(vm, i, k);
            i += k;
        }
        else if (vm->map[i] > 1 && vm->map[i] < 17)
        {
            new = ft_opdup(g_optab[vm->map[i] - 1]);
            new->next = *op;
            *op = new;
            i++;
            ocp = vm->map[i++];
            i += main_decript(decript_ocp((ocp & PARAM_C) >> 6), vm->map + i, 0, op);
            i += main_decript(decript_ocp((ocp & PARAM_B) >> 4), vm->map + i, 1, op);
            i += main_decript(decript_ocp((ocp & PARAM_A) >> 2), vm->map + i, 2, op);
        }
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

int mv_mem(int pos, int move)
{
    pos = pos + move;
    return (pos % MEM_SIZE);
}

int init_vm(t_champs *champs, t_opts *opts, t_vm *vm)
{
    int i;
    t_op *op;

    op = NULL;
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