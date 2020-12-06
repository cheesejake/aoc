\ Advent of Code, Day 06                              2020-12-06
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)

\ call with eg:
\ gforth day06.fs day06-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day06-input-test"' day06.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

variable answers 26 chars allot

0 value fid
0 value count1
0 value count2

: setup ( -- )
next-arg r/o open-file abort" open error" to fid ;

: solve1 ( -- )
;

: solve2 ( -- )
;

: addtogroup ( -- )
;

: readline ( -- flag )
;

: readgroup ( -- flag )
begin readline while addtogroup repeat ;
;

: work ( -- )
begin readgroup while solve1 solve2 repeat ;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 6, part 1: " count1 . cr
." Day 6, part 2: " count2 . cr ;

setup work finish report BYE
