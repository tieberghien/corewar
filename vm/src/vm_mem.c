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

int start_game(t_vm *vm)
{
    int i;
    int j;
    int ocp;
    t_op *new;
    int k = 1;

    i = 0;
    while (i < MEM_SIZE)
    {
        if (vm->map[i] == 9)
        {
            k = 32;
            ft_printf("\x1B[3%dm \n %hhx %hhx \n", k, vm->map[i], vm->map[i + 1]);
            i += 2;
        }
        else if (vm->map[i] == 1)
        {
            j = 0;
            k = 31;
            ft_printf("\x1B[3%dm %hhx %hhx %hhc %hhx \n", k, vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
            i += 4;
        }
        else if (vm->map[i] > 1 && i < 17)
        {
            k = 33;
            new = ft_opdup(g_optab[i]);
            ft_printf("\x1B[3%dm %hhx ", k, vm->map[i]);
            i++;
            ocp = vm->map[i];
            ft_printf("\x1B[3%dm %hhx ", k, vm->map[i]);
            i++;
            if (decript_ocp(((ocp & PARAM_C) >> 6) > 1))
            {
                if (/*((ocp & PARAM_C) >> 6) == 2 &&*/ 
                (new->op_code < 9 || new->op_code == 13))
                    ft_printf("\x1B[3%dm %hhx %hhx %hhc %hhx", k, vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
                else
                    ft_printf("\x1B[3%dm %hhx %hhx ", k, vm->map[i], vm->map[i + 1]);
                i += (/*((ocp & PARAM_C) >> 6) == 2 &&*/ 
                (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            }
            else 
            {
                ft_printf("\x1B[3%dm %hhx ", k, vm->map[i]);
                i++;
            }
            if (decript_ocp(((ocp & PARAM_B) >> 4) > 1))
            {
                if (/*((ocp & PARAM_B) >> 4) == 2 &&*/ 
                (new->op_code < 9 || new->op_code == 13))
                    ft_printf("\x1B[3%dm %hhx %hhx %hhc %hhx ", k, vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
                else
                    ft_printf("\x1B[3%dm %hhx %hhx ", k, vm->map[i], vm->map[i + 1]);
                i += (/*((ocp & PARAM_B) >> 4) == 2 &&*/ 
                (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            }
            else
            {
                ft_printf("\x1B[3%dm %hhx ", k, vm->map[i]);
                i++;
            }
            if (decript_ocp(((ocp & PARAM_A) >> 2 ) > 1))
            {
                if (/*((ocp & PARAM_A) >> 2) == 2 &&*/ 
                (new->op_code < 9 || new->op_code == 13))
                    ft_printf("\x1B[3%dm %hhx %hhx %hhc %hhx", k, vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
                else
                    ft_printf("\x1B[3%dm %hhx %hhx ", k, vm->map[i], vm->map[i + 1]);
                i += (/*((ocp & PARAM_A) >> 2) == 2 &&*/ 
                (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            }
            else 
            {
                ft_printf("\x1B[3%dm %hhx ", k, vm->map[i]);
                i++;
            }
            ft_printf("\n");
        }
        else
            i++;
        k = 0;
    }
    ft_putchar('\n');
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

    if (!(vm->map = (unsigned char*)malloc(sizeof(unsigned char) * MEM_SIZE)))
        return (-1);
    i = -1;
    while (++i < MEM_SIZE)
        vm->map[i] = 0;
    if (install_champion(champs, opts, vm))
        return (ft_printf("Error, the map is not initilisated\n"));
    if (start_game(vm))
        return (ft_printf("Error, he doesn't have a game\n"));
    return (0);
}