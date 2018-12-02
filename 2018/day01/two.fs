\ call with
\ gforth-fast -m3M input.txt two.fs -e bye
\             ^^^^ larger dictionary size

1000000 constant LIMIT
: 2LIMIT LIMIT 2 * ;

variable freq 0 freq !
variable index 1 index !

create c!freqs 2LIMIT chars allot
create seq 1000 cells allot

\ zero all elements of freqs (including freqs itself)
: clear-freqs ( -- )
   0 c!freqs !
   2LIMIT 1 do 0 c!freqs i chars + c! loop
;

\ fill seq with stack in reverse order
\ seq[1] = bottom of stack; seq[n] = top of stack
\ seq itself gets the number of items
: fill-seq ( n1 n2 ... nN -- )
   depth seq !
   depth 1 swap do
      seq i cells + !
   -1 +loop
;

: seq-fetch ( index -- seq[index] )
   seq swap cells + @
;

: markseen ( n -- )
   1 swap c!freqs swap LIMIT + chars + c!
;

: unseen? ( n -- f )
   c!freqs swap LIMIT + chars + c@ 0 =
;

: update-freq ( index -- ) \ update frequency with value at index
      seq-fetch freq @ + freq !
;

: wraparound-inc ( limit n1 -- n2 ) \ 1 <= n2 <= limit
   1 + dup rot
   > if drop 1 then
;

: find-1st
   fill-seq
   clear-freqs
   0 markseen
   begin
      index @ update-freq
   freq @ unseen? while
      freq @ markseen
      seq @ index @ wraparound-inc index !
   repeat
;

find-1st freq ? cr
