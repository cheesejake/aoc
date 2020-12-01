\ sum all the numbers in each line of input.txt       2020-11-30

require simplified-file.fs

: work ( fname -- sum )
open-input 0 begin
   over input>pad while
   pad>number + repeat
drop swap close-input ;

s" input.txt" work
.( result: ) . cr bye
