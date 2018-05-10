#include "vm.h"

int readintr(t_vm *vm)
{
    int i;
    int par;
    int ocp;
    t_op *new;

    i = 0;
    while (i < MEM_SIZE)
    {
        if (vm->map[i] == 9 || vm->map[i] == 15 || vm->map[i] == 12)
        {
            new = ft_opdup(g_optab[vm->map[i] - 1]);
            ft_putstr("\x1B[31m");
            ft_printf("%hhx ", vm->map[i]);
            ft_putstr("\x1B[32m");
            ft_printf("%hhx %hhx\n", vm->map[i + 1], vm->map[i + 2]);
            i += 3;
        }
        else if (vm->map[i] == 1)
        {
            ft_putstr("\x1B[31m");
            ft_printf("%hhx ", vm->map[i]);
            new = ft_opdup(g_optab[vm->map[i] - 1]);
            ft_putstr("\x1B[32m");
            ft_printf("%hhx %hhx %hhx %hhx\n",vm->map[i + 1], vm->map[i + 2], vm->map[i + 3], vm->map[i + 4]);
            i += 5;
        }
        else if (vm->map[i] > 1 && vm->map[i] < 17)
        {
            new = ft_opdup(g_optab[vm->map[i] - 1]);
            ft_putstr("\x1B[31m");
            ft_printf("%hhx ", new->op_code);
            i++;
            ocp = vm->map[i];
            ft_putstr("\x1B[32m");
            ft_printf("%hhx ", vm->map[i]);
            i++;
            ft_putstr("\x1B[33m");
            if (decript_ocp((par = ((ocp & PARAM_C) >> 6)) > 1))
            {
                if (par == 2 && 
                (new->op_code < 9 || new->op_code == 13))
                    ft_printf("%hhx %hhx %hhx %hhx ", vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
                else
                    ft_printf("%hhx %hhx ", vm->map[i], vm->map[i + 1]);
                i += (par == 2 && 
                (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            }
            else if (par == 1)
            {
                ft_printf("%hhx ", vm->map[i]);
                i++;
            }
            ft_putstr("\x1B[34m");
            if (decript_ocp((par =((ocp & PARAM_B) >> 4))) > 1)
            {
                if (par == 2 && 
                (new->op_code < 9 || new->op_code == 13))
                    ft_printf("%hhx %hhx %hhx %hhx ", vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
                else
                    ft_printf("%hhx %hhx ", vm->map[i], vm->map[i + 1]);
                i += (par == 2 && 
                (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            }
            else if (par == 1)
            {
                ft_printf("%hhx ", vm->map[i]);
                i++;
            }
            ft_putstr("\x1B[35m");
            if (decript_ocp((par = ((ocp & PARAM_A)) >> 2 ) > 1))
            {
                if (par == 2 &&
                (new->op_code < 9 || new->op_code == 13))
                    ft_printf("%hhx %hhx %hhx %hhx ", vm->map[i], vm->map[i + 1], vm->map[i + 2], vm->map[i + 3]);
                else
                    ft_printf("%hhx %hhx ", vm->map[i], vm->map[i + 1]);
                i += (par == 2 && 
                (new->op_code < 9 || new->op_code == 13)) ? 4 : 2;
            }
            else if (par == 1)
            {
                ft_printf("%hhx ", vm->map[i]);
                i++;
            }
            ft_putstr("\x1B[0m");
            ft_printf("\n");
        }
        else
            i++;
    }
    ft_putchar('\n');
    return (0);
}
