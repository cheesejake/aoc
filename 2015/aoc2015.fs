\ == global utilities ==========================================

\ system agnostic newline (10 on Un*x, 13 on Windows)
: newline? ( key -- f ) dup 10 = swap 13 = or ;

: sort3asc ( n1 n2 n3 -- min med max )
       2dup < if swap then
   rot 2dup > if swap then
   rot 2dup > if swap then ;
: sort3desc ( n1 n2 n3 -- max med min )
       2dup > if swap then
   rot 2dup < if swap then
   rot 2dup < if swap then ;

: same-coords? ( x1 y1 x2 y2 -- f ) rot = rot rot = and ;
