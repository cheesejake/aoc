\ Advent of Code, Day 09                              2020-12-09
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)
\ Assume cells are 64-bits

\ call with eg:
\ gforth -e '5 constant preamble' day09.fs day09-input-test
\                                          ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e '5 constant preamble'  -e 's" day09-input-test"' day09.fs
\                                     ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

( "25 constant preamble" set up on command-line possibly with a different value )
0 value fid
create circ-buffer preamble 1+ cells allot
-1 value solution1

: file>pad ( -- u f ; pad changed )
pad 80 fid read-line abort" read error" ;

: pad>number ( u1 -- u2 )
\ use the first u1 characters in pad to extract the number u2
0 0 rot pad swap >number drop drop d>s ;

: setup ( -- )
next-arg r/o open-file abort" open error" to fid
preamble 0 do file>pad drop pad>number circ-buffer i cells + ! loop
;

: ijsum ( i j -- sum )
circ-buffer swap cells + @ swap circ-buffer swap cells + @ + ;

: lastread ( -- n )
circ-buffer preamble cells + @ ;

: print-buffer
preamble 1+ 0 do circ-buffer i cells + @ . loop ;

: no-match-pairsum ( -- f )
preamble 1- 0 do preamble i 1+ do
   i j ijsum lastread = if unloop unloop 0 exit then
loop loop -1 ;

: work-part1
   no-match-pairsum if circ-buffer preamble cells + @ to solution1 then ;

: work-part2 ;

: work ( -- )
begin file>pad while
   pad>number circ-buffer preamble cells + !
   work-part1 work-part2
   circ-buffer 1 cells + circ-buffer preamble 1+ cells move
repeat drop ;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 9, part 1: " solution1 . cr
." Day 9, part 2: " -1 . cr
;

setup work finish report BYE
