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

int toint(unsigned int vm, int size)
{

}

int start_game(t_vm *vm, t_op **op)
{
    int i;
    int par;
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
            i++;
            k = (vm->map[i] == 1) ? 5 : 3;

            i += k;
        }
        else if (vm->map[i] > 1 && vm->map[i] < 17)
        {
            new = ft_opdup(g_optab[vm->map[i] - 1]);
            new->next = *op;
            *op = new;
            i++;
            ocp = vm->map[i];
            i++;
            if (decript_ocp((par = ((ocp & PARAM_C) >> 6)) > 1))
                i += (par == 2 && (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            else if (par == 1)
                i++;
            if (decript_ocp((par =((ocp & PARAM_B) >> 4))) > 1)
                i += (par == 2 && (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            else if (par == 1)
                i++;
            if (decript_ocp((par = ((ocp & PARAM_A)) >> 2 ) > 1))
                i += (par == 2 && (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            else if (par == 1)
                i++;
        }
        else
            i++;
    }
    new = *op;
    while (new)
    {
        ft_printf("%s\n", new->name);
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