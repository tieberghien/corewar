.name "zork"
.comment "just a basic living prog"
		
live:	sti	r2,%:pouet,%0
	and	r1,%0,r1
mais:
ohlala:
pouet:	live	%1
	zjmp	%:live
