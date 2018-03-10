{\rtf1\ansi\ansicpg1252\cocoartf1504\cocoasubrtf830
{\fonttbl\f0\fswiss\fcharset0 Helvetica;}
{\colortbl;\red255\green255\blue255;}
{\*\expandedcolortbl;;}
\margl1440\margr1440\vieww10800\viewh19440\viewkind0
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0

\f0\fs24 \cf0 typedef struct 		s_op\
\{\
	char	*name;\
	char	*data;\
	int	ac;\
	int	total_pc;\
	char	**addr;\
	int	addr_index[3];\
\}				t_op;\
\
0bxx01xxxx0001\
\
ac = 1;\
*addr[0] = \'93live\'94\
addr_index[0] = 6\
\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 While (i < ac)\
Get address of (addr[I])\
put_it_at(data[addr_index[I]]);\
\
If (name is special name that has mysteryunknownnumber)\
Calculate speecialunknownmysterynumber\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 \
\
typedef struct 		s_opset\
\{\
	char		*name;\
	int		oc;\
	int		address;\
	t_op		*ops;\
	s_opset	*nxt;\
\}				t_opset;\
\
typedef struct		s_oplen\
\{\
	char	*name;\
	int	bytes;\
\}		t_oplen\
\
t_oplen g_oplen[]=\
\{\
	\{\'93live\'94, 5\};\
	\{\'93ld\'94, 6\};\
	\{\'93zjmp\'94, 3\};\
	\{\'93sti\'94, 7\};\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
	\{\'93and\'94, 8\};\
\pard\tx720\tx1440\tx2160\tx2880\tx3600\tx4320\tx5040\tx5760\tx6480\tx7200\tx7920\tx8640\pardirnatural\partightenfactor0
\cf0 	\
\}\
\
 (L2)                                     (live)\
opset               -                  opset                  -\
   |                                          |\
Op1 (sti)                           op1(live)\
op2(and)                          op2(zjmp)\
\
\
}