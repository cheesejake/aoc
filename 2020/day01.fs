\ template for FORTH puzzles                          2020-12-01

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

: part1 ( n -- result )
dup 1- 0 do                               ( n )
   2020 expenses i cells + @ -            ( n 2020-val )
   over i 1+ do                           ( n search )
      dup expenses i cells + @ = if       ( n search )
         unloop unloop swap drop 2020 over - * exit
      then
   loop drop loop drop 0 ;
: part2 ( n -- result )  dup - ;

expenses s" .day01-input" input>array          ( n )
.( DAY 01, PART 1: ) dup part1 . cr            ( n )
.( DAY 01, PART 2: ) part2 . cr                ( )
cr cr .s bye
