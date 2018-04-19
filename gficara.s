.name "gficara"
.comment "i don't really know what i'm doing"

alive:  sti r1,%:live,%1
  sti r2,%:live,%10
  sti r3,%:live,%20
  and r1,%0,r1
  and r2,%5,r2
  and r3,%15,r3

live: live %1
    live %10
    live %20
    zjmp %:live
