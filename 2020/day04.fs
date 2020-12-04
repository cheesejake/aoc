\ Advent of Code, Day 04                              2020-12-04
\ Assume everything works :)
\ Assume no bad input, no overflows, enough space allocated
\ Assume lines have 80 characters or fewer ( PAD size >= 84)

\ call with eg:
\ gforth day04.fs day04-input-test
\                 ^^^^^^^^^^^^^^^^
\ uses gforth's "next-arg" word to identify the input file
\
\ Or you can change the code to work with
\ gforth -e 's" day04-input-test"' day04.fs
\        ^^^^^^^^^^^^^^^^^^^^^^^^^
\ add the string to the stack before running

: >>>debug<<< ( c-addr u -- ) type ."  ==> " .s cr ;

variable $kv-byr 30 chars allot
variable $kv-iyr 30 chars allot
variable $kv-eyr 30 chars allot
variable $kv-hgt 30 chars allot
variable $kv-hcl 30 chars allot
variable $kv-ecl 30 chars allot
variable $kv-pid 30 chars allot
variable $kv-cid 30 chars allot
variable @input-data 200 chars allot

variable %file-handle
variable %count1 0 %count1 !
variable %count2 0 %count2 !

: setup ( -- )
next-arg r/o open-file abort" open error" %file-handle ! ;

: solve1 ( -- )
;

: solve2 ( -- )
;

: parse-data ( -- )
;

: get-data ( -- flag )
0 ;

: work ( -- )
begin get-data while parse-data solve1 solve2 repeat ;

: finish ( -- )
%file-handle @ close-file abort" close error" ;

: report ( -- )
." Day 4, part 1: " %count1 @ . cr
." Day 4, part 2: " %count2 @ . cr ;

setup work finish report BYE
