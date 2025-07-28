# esoteric-language-interpreter
Machine which takes in a programming language consisting of 10 words (brainfuck) and interprets it to produce correct outputs.

Here are the rules of the language that this machine interprets:

- chalo -> move pointer right by 1 cell 
- ruko -> move pointer left by 1 cell 
- badhao -> increment current value by 1 
- ghatao -> decrement current value by 1 
- bolo -> output value at current pointer 
- suno -> input value at current pointer 
- ghumo -> if current cell is 0, move forward to corresponding baitho 
- baitho -> jump backwards to matching ghumo if current cell is non-zero 
- taana -> start of single line comment
- taane -> start of multi-line comment 
- baane -> end of multiline comment 
