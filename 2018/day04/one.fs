\ call with
\ gforth-fast -d 100k .string-input.txt one.fs
\             ^^^^^^^ data stack size
\ then execute doit and bye

variable nstrings 0 nstrings !
\ 1200 lines of up to 60 chars
create strings 1200 60 * chars allot

\ save input into an array
: input>memory ( s1 s2 s3 ... sN -- )
   begin
      strings nstrings @ 60 * chars + swap cmove \ don't care about extra garbage
      nstrings @ 1 + nstrings !
   depth 0 = until
;

: doit
   input>memory
;
