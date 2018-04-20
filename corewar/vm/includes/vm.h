#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>

# define NO_CHAMP	"missing champion"
# define OPEN_CHAMP	"failed to open .cor"
# define PARSE_CHAMP	"failed to read .cor"
# define SIZE_CHAMP	"champion size over max size"
# define MAX_CHAMPS	"too many champions"
# define VERBOSE	"verbosity level: 0, 1, 2, 4, 8, 16"
# define PARAM_C	192
# define PARAM_B	48
# define PARAM_A	12

static unsigned char g_magic[] = {0, 234, 131, 243};

typedef struct		s_opts
{
	unsigned int	aff_mode;
	unsigned int	n_cycles;
	unsigned int	s_cycles;
//	unsigned int	player_id;
	unsigned int	n_players;
	unsigned int	verbosity;
}					t_opts;

typedef struct		s_champ
{
	int				player_id;
	unsigned int	size;
	char			*name;
	char			*comment;
	char			*file_name;
	int				fd;
	unsigned char	*instructions;
}					t_champs;

typedef struct 		s_op
{
	char			*name;
	int				argc;
	int				params[3];	
	int				op_code;
	int				dur;
	char			effect[100];
	int				carry;
	int				ocp;
	struct s_op		*next;
}					t_op;

static t_op			g_optab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0, NULL},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0, NULL},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0, NULL},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0, NULL},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0, NULL},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0, NULL},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0, NULL},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0, NULL},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1, NULL},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1, NULL},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1, NULL},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1, NULL},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0,NULL},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1, NULL},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1, NULL},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0, NULL},
	{0, 0, {0}, 0, 0, "0", 0, 0, NULL}
};

typedef	struct		s_vm
{
	unsigned char			*map;
}					t_vm;

void    		ft_opdel(t_op **op);
t_op   			*ft_opdup(t_op op);
//void			parse_args(int ac, char **av, t_opts *opts);
int				display_intro(t_champs *champs, t_opts opts);
//void			verbose_zero(t_champ *champs);
//void			verbose_one(t_champ *champs);
int				oc_file(t_champs *champs, t_opts *opts);
int 			fun_exit(char *str, t_champs *champs, t_opts *opts);
int 			init_vm(t_champs *champs, t_opts *opts, t_vm *vm);
void			print_vm_mem(t_vm *vm);
#endif
