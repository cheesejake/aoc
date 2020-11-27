\ gforth day01.fs -e part# <.input-day01
\ assume well-formed input:
\    a single line ending with <NEWLINE>

require global.fs

\ == part1 =====================================================
\ read keyboard: close parenthesis -1: go down
\                open parenthesis   1: go up
\                anyhting else      0: bad key (maybe newline)
\ Use the result of `=` (0 or -1) for the final result of `step`
: step ( -- direction )
   key dup  [char] ( = negate swap [char] ) = + ;

\ keep changing floor until the end of input
: steps ( -- floor )
   0 begin step dup >r + r> 0 = until ; \ add (even 0), no ifs

: part1
    steps
    cr ." Q: To what floor do the instructions take Santa?"
    cr ." A: Santa ends up at floor " . cr cr ;

\ == part2 =====================================================
\ assume the solution is reachable

-1 constant DESTINATION \ basement is floor -1
\ keep changing floor until basement reached
: steps2-before ( -- count )
   0 0 begin step + swap 1 + swap dup DESTINATION = until drop ;

\ consume input to prevent it coming out as output
: steps2-after begin key newline? until ;

: part2
    steps2-before steps2-after
    cr ." Q: What is the position of the character that causes "
       ." Santa to first enter the basement?"
    cr ." A: position #" . cr cr ;
