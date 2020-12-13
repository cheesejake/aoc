\ Advent of Code, Day 13                              2020-12-13
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)
\ Assume 64 bits cells

\ call with eg:
\ gforth day13.fs day13-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day13-input-test"' day13.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

0 value fid
0 value mintime
0 value padstart
0 value padend

: setup ( -- )
next-arg r/o open-file abort" open error" to fid
pad 80 fid read-line abort" read error" drop
0 0 rot pad swap >number drop drop d>s to mintime ;

12345 dup * value answer1 \ wait time * bus id
999999 value minwait

: waittime ( start cycle -- time )
2dup / 1+ * swap -
dup minwait min to minwait ;

: step-solve1 ( bus -- )
mintime over waittime dup minwait =
if 2dup * to answer1 then
2drop ;

: solve2 ( -- )
;

: file>ch ( -- ch flag )
pad 1 fid read-file abort" read error" pad c@ swap ;

: isdigit? ( ch -- flag )
dup [char] 0 >= swap [char] 9 <= and ;

-1 value buspos
: file>bus ( -- bus | 0 )
buspos 1+ to buspos
0 begin file>ch while
   dup [char] x = if buspos 1+ to buspos then
   dup isdigit?
      if '0' - swap 10 * +
      else drop dup 0 <> if exit then
   then repeat drop
;

: work ( -- )
begin file>bus dup while
." found bus with id " dup . ." at position " buspos . cr
step-solve1 repeat drop ;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 13, part 1: " answer1 . cr
." Day 13, part 2: " -1 . cr ;

setup work finish report BYE
