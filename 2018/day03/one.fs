\ call with
\ gforth-fast input one.fs

variable @n \ number of claims
create map 1000 1000 * chars allot

: organize-stack ( x l t w h -- w+l+1 l t+h+1 t )
   >r swap                    ( x l w t ) ( R: h )
   dup >r + swap >r >r        ( x l w ) ( R: t t+h )
   over + 1 + swap            ( x w+l+1 l ) ( R: t t+h )
   >r >r drop r> r> r> 1 + r> ( w+l l t+h+1 t )
;

: mapcount ( id1 l1 t1 w1 h1 id2 l2 t2 w2 h2 ... idN lN tN wN hN -- )
   begin
       organize-stack
       do do
       loop loop
   depth 0 = until
;

depth 5 / @n !
\ mapcount
\ cr bye
