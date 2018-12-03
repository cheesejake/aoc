\ call with
\ gforth-fast input one.fs

variable kk2 0 kk2 !
variable kk3 0 kk3 !
create c-letters-in-word 200 chars allot

: reset-letters ( -- )
   [char] z 1 + [char] a do
      0 c-letters-in-word i chars + c!
   loop
;

: letter+1 ( ch -- )
   c-letters-in-word swap chars + dup c@ 1 + swap c!
;

: process-word ( c-addr u -- n3 n2 )
   reset-letters
   0 do
      dup i chars + c@ letter+1
   loop
   drop 0 0
   [char] z 1 + [char] a do
      c-letters-in-word i chars + c@
      dup 2 = if swap drop 1 swap then
      3 = if swap drop 1 swap then
   loop
;

: checksum ( w1 w2 w3 ... wN -- chksum )
   begin
      process-word kk2 +! kk3 +!
   depth 0 = until
   kk2 @ kk3 @ *
;

checksum . cr bye
