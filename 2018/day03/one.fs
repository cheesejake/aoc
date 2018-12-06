\ call with
\ gforth-fast -d 100k .justnumbers-input.txt one.fs
\             ^^^^^^^ data stack size
\ then execute doit and bye

variable areas
create map 1010 1010 * chars allot

: organize-stack ( ... x l t w h -- ... w+l l h+t t )
   >r >r >r >r drop               ( ... ) ( R: h w t l )
   r> r> r>                       ( ... l t w ) ( R: h )
   swap >r                        ( ... l w ) ( R: h t )
   over + swap                    ( ... w+l l ) ( R: h t )
   r> dup r>                      ( ... w+l l t t h )
   + swap                         ( ... w+l l t+h t )
;

: mapareas ( id1 l1 t1 w1 h1 id2 l2 t2 w2 h2 ... idN lN tN wN hN -- )
   begin
\      ." before mapareas loops" space .s cr
      organize-stack
      do
         2dup do
            map i 1010 * j + chars + c@
\            ." marking" space i . j . cr
            1 + dup 120 > if drop 2 then
            map i 1010 * j + chars + c!
         loop
      loop 2drop
\      ." after mapareas loops" space .s cr
   depth 0 = until
;

: zeromap ( -- )
   1010 0 do 1010 0 do
      0 map i 1010 * j + chars + c!
   loop loop
;

\ show the n by n top left corner of the map
: showmap ( n -- )
   ." ==> showmap start" space .s cr
   dup 0 do
      dup 0 do
          map i 1010 * j + chars + c@ .
      loop
      cr
   loop
   ." ==> showmap finished" space .s cr
;

: counttwos ( -- n )
   0                     \ starting count
   1010 0 do 1010 0 do
      map i 1010 * j + chars + c@
      dup 1 > if swap 1 + swap then
      drop
   loop loop
;

: doit
   zeromap ." zeromap ok" space cr
   mapareas ." mapareas ok" space cr
   \ 8 showmap
   counttwos
   . cr
;
