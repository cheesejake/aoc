\ Advent of Code, Day 12                              2020-12-12
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)
\ Assume 64 bits cells

\ call with eg:
\ gforth day12.fs day12-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day12-input-test"' day12.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

0 value fid

: setup ( -- )
next-arg r/o open-file abort" open error" to fid ;

0 value x
0 value y
0 value direction \ 0 east, 1 north, 2 west, 3 south

: fid>pad ( -- )
pad 80 fid read-line abort" read error" ;

: turnright ( n -- )
begin dup while direction 1- to direction 90 - repeat drop
direction 0 < if direction 4 + to direction then ;

: turnleft ( n -- )
begin dup while direction 1+ to direction 90 - repeat drop
direction 3 > if direction 4 - to direction then ;

: movedir ( n -- )
direction case
   0 of x + to x endof
   1 of y + to y endof
   2 of x swap - to x endof
   3 of y swap - to y endof
   endcase ;

: movenorth ( n -- ) y + to y ;
: movesouth ( n -- ) y swap - to y ;
: moveeast ( n -- ) x + to x ;
: movewest ( n -- ) x swap - to x ;

: solve1 ( n -- )
0 0 rot pad 1 + swap 1- >number drop drop d>s
pad c@ case
   'R' of turnright endof
   'L' of turnleft endof
   'F' of movedir endof
   'N' of movenorth endof
   'S' of movesouth endof
   'E' of moveeast endof
   'W' of movewest endof
   endcase
;

0 value x2
0 value y2
10 value wpx
1 value wpy

: wpturnback (  ) wpx -1 * to wpx wpy -1 * to wpy ;

: wpturnright ( n -- )
dup 180 = if drop wpturnback exit then
    270 = if wpturnback then
    wpx wpy to wpx negate to wpy ;

: wpturnleft ( n -- )
dup 180 = if drop wpturnback exit then
    270 = if wpturnback then
    wpx wpy negate to wpx to wpy ;

: wpmovedir ( n -- ) dup wpx * x2 + to x2 wpy * y2 + to y2 ;
: wpmovenorth ( n -- ) wpy + to wpy ;
: wpmovesouth ( n -- ) wpy swap - to wpy ;
: wpmoveeast ( n -- ) wpx + to wpx ;
: wpmovewest ( n -- ) wpx swap - to wpx ;

: solve2 ( n -- )
0 0 rot pad 1 + swap 1- >number drop drop d>s
pad c@ case
   'R' of wpturnright endof
   'L' of wpturnleft endof
   'F' of wpmovedir endof
   'N' of wpmovenorth endof
   'S' of wpmovesouth endof
   'E' of wpmoveeast endof
   'W' of wpmovewest endof
   endcase
;

: work ( -- )
begin fid>pad while dup solve1 solve2 repeat drop ;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 12, part 1: " x abs y abs + . cr
." Day 12, part 2: " x2 abs y2 abs + . cr ;

setup work finish report BYE
