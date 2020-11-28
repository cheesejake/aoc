\ gforth day05.fs -e part# <.input-day05
\ Make sure to add a new empty line to the end of input

require aoc2015.fs

\ == part1 =====================================================
create &inputword 100 allot
: getstring ( -- len )                  \ and &inputword changed
   0 begin key dup newline? invert while
   over &inputword + c! 1+ repeat drop ;

: vowelcount ( len -- n ) 0 swap 0 do &inputword i + c@
   dup [char] a = rot + swap
   dup [char] e = rot + swap
   dup [char] i = rot + swap
   dup [char] o = rot + swap
       [char] u = + loop negate ;
: doubleletter? ( len -- f ) 1 do &inputword i + dup >r
   c@ r> 1 - c@ = if TRUE unloop exit then loop FALSE ;
: ab,cd,pq,xy? ( len -- f ) 1 do
   &inputword i + dup >r c@ r> 1 - c@
   2dup [char] a = swap [char] b = and if 2drop TRUE unloop exit then
   2dup [char] c = swap [char] d = and if 2drop TRUE unloop exit then
   2dup [char] p = swap [char] q = and if 2drop TRUE unloop exit then
        [char] x = swap [char] y = and if       TRUE unloop exit then
   loop FALSE ;

: nice? ( len -- f )
   dup vowelcount 2 <= if drop FALSE then
   dup doubleletter? invert if drop FALSE then
       ab,cd,pq,xy? invert ;

: part1
   0 begin getstring dup 0 <> while
      nice? - repeat drop
   cr ." Q: How many strings are nice?"
   cr ." A: There are " . ." nice strings." cr cr ;

\ == part2 =====================================================
: ppair? ( i -- f ) &inputword + dup >r c@ r> 1 - c@ = ;
: matchpair? ( len i -- f )
   dup &inputword + c@ rot rot ( &[i] len i )
   2 + do
      dup &inputword j + c@ = if
         &inputword j + 1 - c@ = if
            TRUE unloop exit then
         then
      loop drop FALSE ;

: doublepair? ( len -- f )
   dup 2 - 1 do
      i ppair? if
         dup i matchpair? if
            TRUE unloop exit
            then
         then
      loop
   drop FALSE ;
: tuckedletter? ( len -- f) 2 do &inputword i + dup >r
   c@ r> 2 - c@ = if TRUE unloop exit then loop FALSE ;

: nice2? ( len -- f )
   dup doublepair? invert if drop FALSE then
       tuckedletter? ;

: part2
   0 begin getstring dup 0 <> while
      nice2? - repeat drop
   cr ." Q: How many strings are nice under these new rules?"
   cr ." A: There are " . ." new nice strings." cr cr ;
