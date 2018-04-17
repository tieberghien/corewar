#include "vm.h"

void print_vm_mem(t_vm *vm)
{
    int i;

    i = 0;
    ft_putstr("0x");
    while (i < MEM_SIZE)
    {
        if (i % 64 == 0)
            ft_printf("%#.4x : ", i);
        if (vm->map[i] < 16)
            ft_putchar('0');
        ft_printf("%hhx", vm->map[i]);
        i++;
        if (i % 1 == 0)
            ft_putchar(' ');
        if (i % 64 == 0)
            ft_putchar('\n');
    }
}

int install_champion(t_champs* champs, t_opts *opts, t_vm *vm)
{
    int i;
    int gap;
    int pos;
    int j;

    i = -1;
    gap = MEM_SIZE / opts->n_players;
    while ((unsigned int)++i < opts->n_players)
    {
        j = -1;
        pos = i * gap;
        while (++j < (int)champs[i].size)
            vm->map[j + pos] = champs[i].instructions[j];

    }
    print_vm_mem(vm);
    return (0);
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
    return (0);
}