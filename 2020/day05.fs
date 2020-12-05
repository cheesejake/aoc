\ Advent of Code, Day 05                              2020-12-05
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)

\ call with eg:
\ gforth day05.fs day05-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day05-input-test"' day05.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

0 value fid

: setup ( -- )
next-arg r/o open-file abort" open error" to fid ;

: fbrl ( -- )
\ change FB in pad to 01;same with RL
pad       c@ 'F' = if '0' pad       c! else '1' pad       c! then
pad 1+    c@ 'F' = if '0' pad 1+    c! else '1' pad 1+    c! then
pad #2 +  c@ 'F' = if '0' pad #2 +  c! else '1' pad #2 +  c! then
pad #3 +  c@ 'F' = if '0' pad #3 +  c! else '1' pad #3 +  c! then
pad #4 +  c@ 'F' = if '0' pad #4 +  c! else '1' pad #4 +  c! then
pad #5 +  c@ 'F' = if '0' pad #5 +  c! else '1' pad #5 +  c! then
pad #6 +  c@ 'F' = if '0' pad #6 +  c! else '1' pad #6 +  c! then
pad #7 +  c@ 'L' = if '0' pad #7 +  c! else '1' pad #7 +  c! then
pad #8 +  c@ 'L' = if '0' pad #8 +  c! else '1' pad #8 +  c! then
pad #9 +  c@ 'L' = if '0' pad #9 +  c! else '1' pad #9 +  c! then ;

: input>binvalues ( fid -- row col ; pad changed )
pad 80 rot read-line abort" read failed" if                ( u2 )
   drop fbrl                                               ( )
   0. pad 7 #2 base ! >number #10 base !  drop drop d>s    ( ? )
   0. pad 7 + 3 #2 base ! >number #10 base ! drop drop d>s ( ? ? )
   else                                                    ( u2 )
   drop -1 -1 then ;                                       ( -1 -1 )

: row/col>seatid ( row col - seatID )
swap 8 * + ;

0 value maxx
: solve1 ( row col -- ; maxx updated )
row/col>seatid maxx max to maxx ;

: solve2 ( row col -- )
drop drop ;

: work ( -- )
begin fid input>binvalues dup -1 <> while ( r s )
   2dup solve1 solve2 repeat              ( )
;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 4, part 1: " maxx . cr
." Day 4, part 2: " -1 . cr ;

setup work finish report BYE
