\ call with
\ gforth-fast input two.fs -e bye

variable @nboxes 0 @nboxes ! \ number of boxes
variable @idlen              \ length of id of first box
variable @boxids             \ space for ids of N boxes
variable @tmp                \ multi use local variable
variable @tmp1               \ multi use local variable
variable @tmp2               \ multi use local variable

: 4dup ( a b c d -- a b c d a b c d )
    >r >r 2dup
    r@ r@
    2over r> r> ;

: save-words ( w1 w2 w3 ... wN -- )
   0 @tmp !
   begin
      @idlen @ = invert if . ." is bad length" cr bye then
      @boxids @ @idlen @ @tmp @ * chars + @idlen @ move
      @tmp @ 1 + @tmp !
   depth 0 = until ;

: printboxid ( n -- )
   @boxids @ swap @idlen @ * chars + @idlen @ type cr
;

: boxchar ( cindex windex -- c )
   @idlen @ * + @boxids @ swap chars + c@
;

: bubblecompare ( -- wi wj )
   -1 dup @tmp1 ! @tmp2 !
   @nboxes @ 1 - 0 do          \ k
      @nboxes @ i 1 + do       \ j
         0 @tmp !
         @idlen @ 0 do         \ i
            i k boxchar i j boxchar
            = invert if @tmp @ 1 + @tmp ! then
         loop
         @tmp @ 1 = if i @tmp1 ! j @tmp2 ! then
      loop
   loop
   @tmp1 @ @tmp2 @
;

: seewords ( -- )
   @nboxes @ 0 do
       @boxids @ @idlen @ i * chars + @idlen @ type cr
   loop
;

: printequalchars ( id1 id2 -- )
   @tmp2 ! @tmp1 !
   @idlen @ 0 do
      i @tmp1 @ boxchar
      i @tmp2 @ boxchar
      over = if emit 0 then
      drop \ drop 0 if they were equal, drop whatever if they were different
   loop
   cr
;

depth 2 / @nboxes !
dup @idlen !
here @boxids ! @idlen @ @nboxes @ * chars allot
save-words
\ seewords
bubblecompare
\ printboxid printboxid
printequalchars
bye
