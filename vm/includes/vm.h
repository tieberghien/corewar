#ifndef VM_H
# define VM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>

# define USAGE		"usage: ./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ..."
# define CORRUPT	"Invalid champion"
# define OPEN_CHAMP	"failed to open .cor"
# define PARSE_CHAMP	"failed to read .cor"
# define MAX_CHAMPS	"Too many champions"
# define SNEAKY		"MAX_PLAYERS not properly defined"
# define VERBOSE	"verbosity level: 0, 1, 2, 4, 8, 16"
# define MAGIC		"File has an invalid header"
# define EMPTY		"Champion without instructions"
# define BIG		"Champion has too large of a code (max 682 bytes)"
# define NAME		"Failed to read champion name"
# define COMMENT	"Failed to read champion comment"
# define INSTR		"Failed to copy instructions"
# define PARAM_C	192
# define PARAM_B	48
# define PARAM_A	12

static unsigned char g_magic[] = {0, 234, 131, 243};

typedef struct		s_opts
{
	unsigned int	aff_mode;
	unsigned int	n_cycles;
	unsigned int	s_cycles;
	unsigned int	n_players;
	unsigned int	verbosity;
}					t_opts;

typedef struct 		s_op
{
	char			*name;
	int				argc;
	int				params[3];	
	int				op_code;
	int				dur;
	char			effect[100];
	int				carry;
	unsigned char	ocp;
}					t_op;

typedef struct		s_champ
{
	int				player_id;
	unsigned int	size;
	char			*name;
	char			*comment;
	char			*file_name;
	int				fd;
	unsigned char	*instructions;
	unsigned int	registre[REG_NUMBER];
	int				alive;
}					t_champs;

typedef struct		s_process
{
	int					number;
	int					pc;
	t_op				op;
	int					mv;
	int					champ;
	int					carry;
	int					live;
	unsigned int		registre[REG_NUMBER];
	int					count;
	struct s_process	*next;
}					t_process;

typedef	struct		s_vm
{
	int 			ping;
	unsigned char	*map;
	char			*last;
	int				*players_map;
	int			 	cycle;
	int				next_cycle_group;
	int				c;
	int				live_num;
	int				last_live;
	t_opts			*opts;
	t_champs		*champs;
	t_process		**process;
}					t_vm;

/*
**we need to change all the operation so that they will take t_processes instead of t_champs;
*/

static t_op			g_optab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, "0", 0, 0}
};

void			init_reg(t_champs *champs, int player, t_process *process);
unsigned int    rest_address(t_process *process, unsigned int num);
void			tointhex(unsigned long int num, unsigned char **tmp);
int				toint(t_vm *vm, int i, int size);
int 			mv_mem(int *pos, int move, t_vm *vm, t_op **op);
void    		ft_opdel(t_op **op);
t_op   			*ft_opdup(t_op op);
//void			parse_args(int ac, char **av, t_opts *opts);
int				display_intro(t_champs *champs, t_opts opts);
void			verbose_zero(t_champs *champs);
void			verbose_one(t_champs champs);
int				oc_file(t_champs *champs, t_opts *opts);
int 			init_vm(t_champs *champs, t_opts *opts, t_vm *vm);
void			print_vm_mem(t_vm *vm);
int				save_op(t_process *process, t_vm *vm);
int				save_op_spec(t_process *process, t_vm *vm);
int 			check_alive(t_process **process, int flag);
int				res_add(unsigned int param, int pc);
int 			live(t_vm *vm, t_op *op, t_process *process);
int				ld(t_vm *vm, t_op *op, t_process *process);
int 			st(t_vm *vm, t_op *op, t_process *process);
int				add(t_vm *vm, t_op *op, t_process *process);
int 			sub(t_vm *vm, t_op *op, t_process *process);
int				op_and(t_vm *vm, t_op *op, t_process *process);
int 			op_or(t_vm *vm, t_op *op, t_process *process);
int 			op_xor(t_vm *vm, t_op *op, t_process *process);
int 			zjmp(t_vm *vm, t_op *op, t_process *process);
int 			ldi(t_vm *vm, t_op *op, t_process *process);
int 			sti(t_vm *vm, t_op *op, t_process *process);
int 			op_fork(t_vm *vm, t_op *op, t_process *process);
int				lld(t_vm *vm, t_op *op, t_process *process);
int				lldi(t_vm *vm, t_op *op, t_process *process);
int				op_lfork(t_vm *vm, t_op *op, t_process *process);
int				aff(t_vm *vm, t_op *op, t_process *process);
void			verb_adv(t_vm *vm, t_process *process, int l);
void			return_failure(char *str, char *op);
void			free_vm(t_vm *vm, t_opts opts);

static int			(*g_op[])(t_vm *,t_op *, t_process *) = {&live, &ld, &st, &add, &sub, &op_and, &op_or, &op_xor, &zjmp, &ldi, &sti, &op_fork, &lld, &lldi, &op_lfork, &aff};

#endif
