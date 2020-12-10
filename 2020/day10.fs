\ Advent of Code, Day 10                              2020-12-10
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)
\ Assume 64 bits cells

\ call with eg:
\ gforth day10.fs day10-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day10-input-test"' day10.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

0 value fid
variable adapters 120 cells allot \ more than enough for my input
0 value n                         \ number of adapters

: file>array ( -- )
begin pad 80 fid read-line throw
   while >r 0 0 pad r> >number drop drop d>s
   adapters n cells + ! n 1+ to n
   repeat drop ;

: nth ( u -- n )
cells adapters + @ ;

: print-array ( -- )
n 0 do i nth . loop cr ;

: ijswap ( j i -- )
2dup nth swap nth 2>r
cells adapters + r> swap !
cells adapters + r> swap ! ;

: bubble-sort ( -- )
1 n 1 - do i 0 do
   i nth i 1+ nth > if
   i i 1+ ijswap then
loop -1 +loop ;

: setup ( -- )
next-arg r/o open-file abort" open error" to fid
1 to n 0 adapters ! \ add 0 to the array
file>array bubble-sort
\ add device joltage to array
n 1- nth 3 +   n cells adapters + !   n 1+ to n ;

0 value count1
0 value count2
0 value count3

: solve1 ( -- ; count1 and count3 updated ) \ and count2
n 1 do i nth i 1- nth -
   dup 1 = if count1 1+ to count1 then
   dup 3 = if count3 1+ to count3 then
       2 = if count3 1+ to count3 then loop
;

: fact ( n1 -- n2 )
dup 2 < if drop 1 exit then dup 1- recurse * ;

: tribonacci ( n -- tribonacci )
dup 0 = if drop 1 exit then
dup 1 = if        exit then
dup 2 = if        exit then
dup dup 1- recurse rot 2 - recurse rot 3 - recurse + + ;

: seq1's ( index -- index3 n )
0 begin
   over dup 1+ nth swap nth - 1 = while
   1+ swap 1+ swap repeat
swap 1+ swap ;

1 value product
: solve2 ( -- )
1 0 begin seq1's tribonacci rot * swap dup n = until
drop product * to product ;

: work ( -- )
solve1 solve2 ;

: finish ( -- )
fid close-file abort" close error" ;

: report ( -- )
." Day 10, part 1: " count1 count3 * . cr
." Day 10, part 2: " product . cr ;

setup work finish report BYE
