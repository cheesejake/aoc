\ call with
\ gforth-fast .noplus-input.txt one.fs
\ then execute doit and bye

: sumstack ( n1 n2 n3 ... nN -- sum )
   begin + depth 1 = until ;

: doit sumstack . ;
