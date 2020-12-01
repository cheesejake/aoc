\ Advent of Code, Day 01                              2020-12-01

: open-input                                    ( fname -- fid )
( fname ) r/o open-file abort" open failed" ;

: close-input                                         ( fid -- )
( fid ) close-file abort" close failed" ;

: input>pad                         ( fid -- n f ; pad changed )
pad 80 rot read-line abort" read failed" ;

: pad>number                                     ( n -- number )
0 0 rot pad swap >number drop drop d>s ;

: input>array                                ( addr fname -- n )
open-input 0 rot rot            ( 0 addr fid )
begin                           ( n addr fid )
   dup input>pad while          ( n addr fid ndigits )
   pad>number                   ( n addr fid number )
   2 pick 4 pick cells + !      ( n addr fid )
   rot 1+ rot rot repeat
drop close-input drop ;

create expenses 250 cells allot                \ array for input

\ Part1: brute-force FTW
\ should sort array and limit searching
: part1 ( n -- result )
dup 1- 0 do                               ( n )
   2020 expenses i cells + @ -            ( n 2020-val )
   over i 1+ do                           ( n search )
      dup expenses i cells + @ = if       ( n search )
         unloop unloop swap drop 2020 over - * exit
      then
   loop drop loop drop 0 ;

\ Part2: brute-force with 1 more loop
\ really should sort array and limit searching
: part2 ( n -- result )
dup 2 - 0 do                              ( n )
   expenses i cells + @                   ( n val1 )
   over 1- i 1+ do                        ( n val1 )
      expenses i cells + @                ( n val1 val2 )
      2 pick i 1+ do                      ( n val1 val2 )
         expenses i cells + @             ( n val1 val2 val3 )
         2 pick 2 pick 2 pick + + 2020 = if
            unloop unloop unloop * * swap drop exit
         then
         drop loop
      drop loop
   drop loop 0 * ;

expenses s" .day01-input" input>array          ( n )
.( DAY 01, PART 1: ) dup part1 . cr            ( n )
.( DAY 01, PART 2: ) part2 . cr                ( )
cr .s cr bye
