\ simplified file operations                          2020-11-30
\ assume all ok, no I/O errors, no overflows

: open-input                                    ( fname -- fid )
( fname ) r/o open-file abort" open failed" ;
: close-input                                         ( fid -- )
( fid ) close-file abort" close failed" ;
: input>pad                         ( fid -- n f ; pad changed )
\ reads up to 78 characters from file to pad
\ stack holds quantity read and flag (0 means no input)
pad 78 rot read-line abort" read failed" ;
: pad>number                                     ( n -- number )
\ converts the first n digits in pad to number
0 0 rot pad swap >number drop drop d>s ;
