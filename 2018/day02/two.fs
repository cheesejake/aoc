\ call with
\ gforth-fast input two.fs -e bye

: save-words ( w1 w2 w3 ... wN -- )
   begin
      drop drop
   depth 0 = until
;

save-words
0 . cr
