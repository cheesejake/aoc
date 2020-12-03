\ Advent of Code, Day 03                              2020-12-03
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)

\ call with eg:
\ gforth day03.fs day03-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day03-input-test"' day03.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: DBG ( c-addr u -- ) type ."  ==> " .s cr ;

: open-input ( c-addr u -- fid )
r/o open-file abort" open failed" ;

: close-input ( fid -- )
close-file abort" close failed" ;

: input>pad ( fid -- u flag ; pad changed )
pad 80 rot read-line abort" read failed" ;

\ variables
500 constant maxlines
50 constant maxcolumns                            \ width of map
create mapmod[] maxlines maxcolumns * chars allot

\ Part1:
: part1 ( nlines -- ntrees ) drop 0 ;

\ Part2:
: part2 ( nlines -- 0 ) drop 0 ;

: read-input ( -- n ) \ number of lines read
next-arg open-input 0                 ( fid 0 )
begin over input>pad while            ( fid 0 u )
   pad                                ( fid 0 u <src> )
   rot dup >r 1+ rot rot r>           ( fid 0+1 u <src> 0 )
   maxcolumns * mapmod[] +            ( fid 0+1 u <src> <dst> )
   rot                                ( fid 0+1 <src> <dst> u )
   move repeat                        ( fid 1 )
drop swap close-input ;               ( n )

read-input
.( DAY 03, PART 1: ) dup part1 . cr
.( DAY 03, PART 2: ) part2 . cr
s" end" DBG
bye
