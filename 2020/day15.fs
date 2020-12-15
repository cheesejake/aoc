0 value data

: setup
30000000 cells allocate abort" no memory" to data
data 30000000 cells 0 fill ;
: release data free abort" free error";

\ hi is most recent turn, lo is previous turn
: n>hilo ( n -- hi lo ) dup $100000000 / swap $ffffffff and ;
: hilo>n ( hi lo -- n ) swap $100000000 * + ;

: adddata ( n turn -- )
>r cells data + dup @ n>hilo
drop r> swap hilo>n swap ! ;

0 value lastnumber

: part1
0 dup to lastnumber 1 adddata
3 dup to lastnumber 2 adddata
6 dup to lastnumber 3 adddata
2021 4 do
\ suppose your input is the squares of the 1st 7 integers,
\ delete the above 4 lines and uncomment the next 8
\ 1  dup to lastnumber 1 adddata
\ 4  dup to lastnumber 2 adddata
\ 9  dup to lastnumber 3 adddata
\ 16 dup to lastnumber 4 adddata
\ 25 dup to lastnumber 5 adddata
\ 36 dup to lastnumber 6 adddata
\ 49 dup to lastnumber 7 adddata
\ 2021 8 do
   lastnumber cells data + @
   n>hilo dup 0= if
      drop drop 0 else
      - then
   dup to lastnumber i adddata loop
." day 15, part 1: " lastnumber . cr ;

: part2
30000001 2021 do
   lastnumber cells data + @
   n>hilo dup 0= if
      drop drop 0 else
      - then
   dup to lastnumber i adddata loop
." day 15, part 2: " lastnumber . cr ;

setup part1 part2 release bye
