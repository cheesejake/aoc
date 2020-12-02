\ Advent of Code, Day 02                              2020-12-01
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)

\ call with eg:
\ gforth day02.fs day02-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day02-input-test"' day02.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: open-input ( c-addr u -- fid )
r/o open-file abort" open failed" ;

: close-input ( fid -- )
close-file abort" close failed" ;

: input>pad ( fid -- u flag ; pad changed )
pad 80 rot read-line abort" read failed" ;

\ Part1: input `u` chars from PAD line by line;
\        output 0 (invalid) or 1 (valid)
: part1 ( u -- 0|1 )
   0 0 rot pad swap >number
   1- >r 1+ >r d>s 0 0 r> r> >number
   1- >r 1+ >r d>s r> r> over c@
   rot 3 + rot 3 - >r >r >r 0 r> r> r> 0 do
      dup i + c@ 2 pick = if rot 1+ rot rot then loop
   drop drop dup >r >= swap r> <= and negate ;

\ Part2: input `u` chars from PAD line by line;
: part2 ( u -- 1 )
   drop 1 ;

variable count1 0 count1 !
variable count2 0 count2 !

: do-lines ( -- )
next-arg open-input
begin dup input>pad while
   dup part1 count1 +! part2 count2 +! repeat
drop close-input ;

do-lines
.( DAY 02, PART 1: ) count1 ? cr
.( DAY 02, PART 2: ) count2 ? cr
bye
