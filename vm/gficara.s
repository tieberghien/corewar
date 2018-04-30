.name "gficara"
.comment "i don't really know what i'm doing"

alive:    aff r1
  sti r1,%:live,%1
  sti r1,%:live,%10
  sti r1,%:live,%20
  and r1,%0,r1

live: live %1
    live %10
    live %20
    zjmp %:live
