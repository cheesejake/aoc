\ gforth day02.fs -e part# <.input-day02
\ add an extra <newline> to input for `key` to detect

\ == part1 =====================================================
\ read 0+ digits and 1 non-digit ('x' or <newline>), put number on TOS
: getInteger ( -- n )
    0 begin key
       dup [char] 0 < if drop exit then
       dup [char] 9 > if drop exit then
           [char] 0 - swap 10 * + again ;

\ assume well-formed input LxWxH<newline>...<newline><newline>
\ and no presents with 0 side
: getLWH ( -- L W H | -- 0 )
   getInteger dup 0= if exit then \ blank final line
   getInteger getInteger ;

\ surface of box + area of smallest side
: paper ( L W H -- paper-needed )
   sort3asc 2dup * >r rot tuck * >r * 3 * r> r> + 2 * + ;

: part1
   0 begin getLWH dup 0 <> while paper + repeat drop
   cr ." Q: How many total square feet of wrapping paper should they order?"
   cr ." A: They should order " . ." square feet of wrapping paper." cr cr ;

\ == part2 =====================================================
\ smallest perimeter on any face + volume of box
: ribbon ( L W H -- ribbon-needed )
   sort3desc 2dup + 2 * >r * * r> + ;

: part2
   0 begin getLWH dup 0 <> while ribbon + repeat drop
   cr ." Q: How many total feet of ribbon should they order?"
   cr ." A: They should order " . ." feet of ribbon." cr cr ;
