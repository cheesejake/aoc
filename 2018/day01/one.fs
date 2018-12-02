\ call with
\ gforth-fast input one.fs -e bye

: sumstack ( n1 n2 n3 ... nN -- sum )
   begin + depth 1 = until ;

sumstack . cr
