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

: gcd ( n1 n2 -- gcd )
\ assume n1 and n2 are co-prime :)
\ drop drop 1 ;
begin 2dup dup while mod rot drop repeat drop drop drop ;

: lcm ( n1 n2 -- lcm )
2dup * rot rot gcd / ;

0 value divisor
0 value remainder
0 value multiplier
1 value basis
0 value delta
: step-solve2 ( id pos -- )
2dup - begin dup 0< while 2 pick + repeat to remainder
drop to divisor
0 to multiplier
remainder divisor >= if remainder divisor - to remainder then
begin
   multiplier basis * delta + divisor
   mod remainder
   <> while
   multiplier 1+ to multiplier repeat
basis dup divisor lcm to basis
multiplier * delta + to delta ;

: file>ch ( -- ch flag )
pad 1 fid read-file abort" read error" pad c@ swap ;

: isdigit? ( ch -- flag )
dup [char] 0 >= swap [char] 9 <= and ;

-1 value buspos
: file>bus ( -- bus | 0 ; update buspos )
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
dup step-solve1 buspos step-solve2 repeat drop ;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 13, part 1: " answer1 . cr
." Day 13, part 2: " delta . cr ;

setup work finish report BYE
