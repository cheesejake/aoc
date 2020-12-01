\ Advent of Code, Day 01                              2020-12-01
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated, ...
\ Assume lines have 80 characters or fewer

: open-input ( c-addr u -- fid )
r/o open-file abort" open failed" ;

: close-input ( fid -- )
close-file abort" close failed" ;

: input>pad ( fid -- u flag ; pad changed )
\ According to Forth Standard, size of the scratch area whose
\ address is returned by PAD shall be at least 84 characters.
\ reads up to 80 characters from file to pad
\ stack holds quantity read and flag (0 means no input)
pad 80 rot read-line abort" read failed" ;

: pad>number ( u -- n )
\ converts the first n digits in pad to number
0 0 rot pad swap >number drop drop d>s ;

\ leave number of elements read on TOS
: input>array ( addr c-addr u1 -- u2 )
open-input 0 rot rot
begin
   dup input>pad while
   pad>number
   2 pick 4 pick cells + !
   rot 1+ rot rot repeat
drop close-input drop ;

create expenses 250 cells allot                \ array for input

\ Part1: brute-force FTW
\ should sort array and limit searching
: part1 ( u -- n )
dup 1- 0 do 2020 expenses i cells + @ -
   over i 1+ do dup expenses i cells + @ = if
      unloop unloop swap drop 2020 over - * exit
   then loop drop loop drop 0 ;

\ Part2: brute-force with 1 more loop
\ really should sort array and limit searching
: part2 ( u -- n )
dup 2 - 0 do expenses i cells + @
   over 1- i 1+ do expenses i cells + @
      2 pick i 1+ do expenses i cells + @
         2 pick 2 pick 2 pick + + 2020 = if
            unloop unloop unloop * * swap drop exit then
   drop loop drop loop drop loop 0 * ;

expenses s" .day01-input" input>array
.( DAY 01, PART 1: ) dup part1 . cr
.( DAY 01, PART 2: ) part2 . cr
bye
