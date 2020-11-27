\ gforth -d100k day03.fs -e part# <.input-day03
\        ^^^^^^ space for `&house`

require global.fs

\ == part1 =====================================================
create &house 10000 2 * cells allot    \ 10000 is enough
   0 &house ! 0 &house 1 cells + !     \ house at (0, 0) visited
create &nhouse 1 ,                     \ 1 house already visited
: nhouse &nhouse @ ;
: &1st-empty-house &house nhouse 2 * cells + ;
: &nth-house ( n -- addr ) 2 * cells &house + ;
: nth-house-xy ( n -- x y ) &nth-house dup >r @ r> 1 cells + @ ;

: xyvisited? ( x y -- f )
   nhouse 0 do 2dup i nth-house-xy same-coords?
      if 2drop TRUE unloop exit then
      loop 2drop FALSE ;

: xyadd ( x y -- ) &1st-empty-house 1 cells + !
                   &1st-empty-house !
                   1 &nhouse +! ;

create &santax 0 , create &santay 0 ,   \ Santa starts at (0, 0)
: SANTAx &santax @ ;
: SANTAy &santay @ ;
: SANTAup    1 &santay +! ;
: SANTAdown -1 &santay +! ;
: SANTAleft -1 &santax +! ;
: SANTAright 1 &santax +! ;

: SANTAtravel dup [char] ^ = if SANTAup then
              dup [char] v = if SANTAdown then
              dup [char] < = if SANTAleft then
                  [char] > = if SANTAright then ;
: SANTAcheck SANTAx SANTAy xyvisited? invert if SANTAx SANTAy xyadd then ;

: part1
   begin key dup newline? invert while SANTAtravel SANTAcheck repeat drop
   cr ." Q: How many houses receive at least one present?"
   cr ." A: " nhouse . ." houses receive at least one present." cr cr ;

\ == part2 =====================================================
create &robotx 0 , create &roboty 0 , \ Robot-Santa starts at (0, 0)
: ROBOTx &robotx @ ;
: ROBOTy &roboty @ ;
: ROBOTup    1 &roboty +! ;
: ROBOTdown -1 &roboty +! ;
: ROBOTleft -1 &robotx +! ;
: ROBOTright 1 &robotx +! ;

create  &onmove 0 ,                  \ 0: santa turn; -1: robot turn
: onmove &onmove @ ;

: switch onmove invert &onmove ! ;

: ROBOTtravel dup [char] ^ = if ROBOTup then
              dup [char] v = if ROBOTdown then
              dup [char] < = if ROBOTleft then
                  [char] > = if ROBOTright then ;
: travel onmove if ROBOTtravel exit then SANTAtravel ;

: ROBOTcheck ROBOTx ROBOTy xyvisited? invert if ROBOTx ROBOTy xyadd then ;
:      check onmove if ROBOTcheck exit then SANTAcheck ;

: part2
   begin key dup newline? invert while travel check switch repeat drop
   cr ." Q: This year, how many houses receive at least one present?"
   cr ." A: This year, " nhouse . ." houses receive at least one present." cr cr ;
