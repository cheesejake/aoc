\ call with
\ gforth-fast -d 100K input one.fs
\             ^^^^^^^ data stack size

create map 1010 1010 * chars allot

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
      do
         2dup do
            map i 1010 * j + chars + c@
            1 + dup 120 > if drop 2 then
            map i 1010 * j + chars + c!
         loop
      loop 2drop
      ." after mapcount loops" space .s cr
   depth 4 < until
;

: zeromap ( -- )
   1010 0 do 1010 0 do
      0 map i 1010 * j + chars + c!
   loop loop
;

: counttwos ( -- n )
   0                     \ starting count
   1010 0 do 1010 0 do
      map i 1010 * j + chars + c@
      dup 1 > if swap 1 + swap i . j . then
      drop
   loop loop
;

zeromap ." zeromap ok" space cr
mapcount ." mapcount ok" space cr
counttwos
. cr bye
