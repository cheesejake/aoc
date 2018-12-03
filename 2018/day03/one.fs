\ call with
\ gforth-fast -d 100K input one.fs
\             ^^^^^^^ data stack size

variable @n \ number of claims
create map 1000 1000 * chars allot

: organize-stack ( ... x l t w h -- ... w+l+1 l h+t+1 t )
   >r >r >r >r drop               ( ... ) ( R: h w t l )
   r> r> r>                       ( ... l t w ) ( R: h )
   swap >r                        ( ... l w ) ( R: h t )
   over 1 + + swap                ( ... w+l+1 l ) ( R: h t )
   r> dup r>                      ( ... w+l+1 l t t h )
   1 + + swap                     ( ... w+l+1 l t+h+1 t )
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
