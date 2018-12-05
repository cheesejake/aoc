\ call with
\ gforth-fast -m 9M -d 100k .justnumbers-input.txt one.fs
\             ^^^^^ dictionary size
\                   ^^^^^^^ data stack size

variable tmp
create inputs 1500 5 * cells allot
variable ninputs 0 ninputs !
create map 1010 1010 * cells allot

: organize-stack ( ... x l t w h -- ... w+l l h+t t x )
   ." before organize" space .s cr
   >r swap >r >r >r tmp !         ( ... ) ( R: h t w l ) \ x in tmp
   r> dup r>                      ( ... l l w ) ( R: h t ) \ x in tmp
   + swap                         ( ... w+l l ) ( R: h t ) \ x in tmp
   r> dup r>                      ( ... w+l l t t h ) \ x in tmp
   + swap tmp @                   ( ... w+l l h+t t x )
   ." after organize" space .s cr
;

: saveinputs ( id1 l1 t1 w1 h1 id2 l2 t2 w2 h2 ... idN lN tN wN hN -- )
   begin
       organize-stack
       drop \ inputs[ninputs][0] ! \ id
       drop \ inputs[ninputs][1] ! \ t
       drop \ inputs[ninputs][2] ! \ h+t
       drop \ inputs[ninputs][3] ! \ l
       drop \ inputs[ninputs][4] ! \ w+l
       ninputs dup @ 1 + !
   depth 0 = until
;

: mapareas1 ( -- )
   begin
      organize-stack
      tmp !
      do
         2dup do
            map i 1010 * j + cells + @
            dup 0 < if drop -1 then
            dup 0 > if drop -1 then
            dup 0 = if drop tmp @ then
            map i 1010 * j + cells + !
         loop
      loop 2drop
   depth 0 = until
;

: mapareas2 ( -- )
   1010 0 do 1010 0 do
      map i 1010 * j + cells + @
      dup 0 < if drop -1 then
      dup 0 > if drop -1 then
      dup 0 = if drop tmp @ then
      map i 1010 * j + cells + !
   loop loop
;

: zeromap ( -- )
   1010 0 do 1010 0 do
      0 map i 1010 * j + cells + !
   loop loop
;

\ show the n by n top left corner of the map
: showmap ( n -- )
   ." ==> showmap start" space .s cr
   dup 0 do
      dup 0 do
          map i 1010 * j + cells + @ .
      loop
      cr
   loop
   ." ==> showmap finished" space .s cr
;

: counttwos ( -- n )
   0                     \ starting count
   1010 0 do 1010 0 do
      map i 1010 * j + cells + @
      dup 1 > if swap 1 + swap then
      drop
   loop loop
;

zeromap ." zeromap ok" space cr
mapareas1 ." mapareas1 ok" space cr
mapareas2 ." mapareas2 ok" space cr
8 showmap
\ counttwos
. cr bye
