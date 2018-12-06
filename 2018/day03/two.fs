\ call with
\ gforth-fast -m 9M -d 100k .justnumbers-input.txt two.fs
\             ^^^^^ dictionary size
\                   ^^^^^^^ data stack size
\ thyen execute doit and bye

variable tmp
variable ninputs 0 ninputs !
create inputs 1500 6 * cells allot
create map 1010 1010 * cells allot

: organize-stack ( ... x l t w h -- ... x w+l l t h+t )
   >r swap >r                     ( ... x l w ) ( R: h t )
   over +                         ( ... x l w+l ) ( R: h t )
   r> dup r> +                    ( ... x l w+l t h+t )
;

: saveinputs ( id1 l1 t1 w1 h1 id2 l2 t2 w2 h2 ... idN lN tN wN hN -- )
   begin
      organize-stack
      inputs ninputs @ 6 * cells + >r \ base address
      r@ 4 cells + ! \ inputs[ninputs][4] = h+t
      r@ 3 cells + ! \ inputs[ninputs][3] = t
      r@ 2 cells + ! \ inputs[ninputs][1] = w+l
      r@ 1 cells + ! \ inputs[ninputs][2] = l
      r@ 0 cells + ! \ inputs[ninputs][0] = id
      0 r> 5 cells + ! \ inputs[ninputs][6] = 0
      ninputs dup @ 1 + swap !
   depth 0 = until
;

: mapareas1 ( -- )
   ninputs @ 0 do
      inputs i 6 * cells + tmp ! \ base address
      tmp @ 2 cells + @ tmp @ 1 cells + @ do
         tmp @ 4 cells + @ tmp @ 3 cells + @ do
            map i 1010 * j + cells + @
            dup 0 > if drop -1 then                \ if used fill with -1
            dup 0 = if drop tmp @ 0 cells + @ then \ if empty fill with this ID
            map i 1010 * j + cells + !
         loop
      loop
   loop
;

: mapareas2 ( -- )
   ninputs @ 0 do
      inputs i 6 * cells + tmp ! \ base address
      tmp @ 2 cells + @ tmp @ 1 cells + @ do
         tmp @ 4 cells + @ tmp @ 3 cells + @ do
            map i 1010 * j + cells + @             \ value on map
            tmp @ 0 cells + @                      \ this ID
            = invert if -1 tmp @ 5 cells + ! then  \ flag this input
         loop
      loop
   loop
;

: zeromap ( -- )
   1010 0 do 1010 0 do
      0 map i 1010 * j + cells + !
   loop loop
;

: pushunflagged ( -- n ...) \ hopefully pushes exactly 1 n
   ninputs @ 0 do
      inputs i 6 * cells + tmp ! \ base address
      tmp @ 5 cells + @ 0 = if tmp @ 0 cells + @ then
   loop
;

: doit
   saveinputs
   zeromap ." zeromap ok" space cr
   mapareas1 ." mapareas1 ok" space cr
   mapareas2 ." mapareas2 ok" space cr
   pushunflagged
   .s cr
;
