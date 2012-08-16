chess-knight-moves
==================


PROBLEM
=======

Given a standard 8x8 chessboard, design a C++ application that accepts two
squares identified by algebraic chess notation. The first square is the
starting position, and the second square is the ending position. Find the
shortest sequence of valid moves to take a Knight piece from the starting
position to the ending position. Each move must be a legal move by a Knight.
For any two squares there may be more than one valid solution.

Vital information
-----------------
Algebraic chess notation identifies each square with a letter from A to H and a
number from 1 to 8. The columns are labeled with letters, and the rows are
numbered. The lower left is A1.  A Knight moves two steps in a straight line
from its starting position, and then one square to either the left right. A
Knight can jump over other pieces. In the diagram to the right the Knight at
position B8 can move either A6 or C6, while the Knight at position G8 can move
to F6 or H6.

Input
-----
Must be two squares identified in algebraic chess notation representing the
starting and ending positions of the Knight. The two squares are separated by a
space.

Output
------
Must be a list of squares through which the Knight passes, in algebraic chess
notation. This must include the ending position, but exclude the starting
position.

Example
-------
Test Input: A8 B7
Expected Output: C7 B5 D6 B7


COMPILE:
========
while PWD is chess-knight-moves, for normal build run

`g++ -Wall -o main -Ilib src/main.cxx`

for `debug` build

`g++ -DDEBUG -Wall -o main -Ilib src/main.cxx`


SOLUTION
========

Piece
+-- Knight

Board
+-- ChessBoard


Example Run
===========
```
$ ./main --from d3 --to h11
From: (D3)
To: (H11)
Path: (E5), (F7), (G9), (H11), 
$ ./main --from a1 --to h6
From: (A1)
To: (H6)
Path: No path!
$ ./main --from a1 --to g8
From: (A1)
To: (G8)
Path: (B3), (C5), (D7), (E9), (G8), 
```


DEPENDENCIES
============
```
$ g++ -v
Using built-in specs.
COLLECT_GCC=/usr/bin/g++
COLLECT_LTO_WRAPPER=/usr/libexec/gcc/x86_64-redhat-linux/4.6.3/lto-wrapper
Target: x86_64-redhat-linux
Configured with: ../configure --prefix=/usr --mandir=/usr/share/man --infodir=/usr/share/info --with-bugurl=http://bugzilla.redhat.com/bugzilla --enable-bootstrap --enable-shared --enable-threads=posix --enable-checking=release --with-system-zlib --enable-__cxa_atexit --disable-libunwind-exceptions --enable-gnu-unique-object --enable-linker-build-id --enable-languages=c,c++,objc,obj-c++,java,fortran,ada,go,lto --enable-plugin --enable-java-awt=gtk --disable-dssi --with-java-home=/usr/lib/jvm/java-1.5.0-gcj-1.5.0.0/jre --enable-libgcj-multifile --enable-java-maintainer-mode --with-ecj-jar=/usr/share/java/eclipse-ecj.jar --disable-libjava-multilib --with-ppl --with-cloog --with-tune=generic --with-arch_32=i686 --build=x86_64-redhat-linux
Thread model: posix
gcc version 4.6.3 20120306 (Red Hat 4.6.3-2) (GCC) 
```

License
=======
This software is released under the [MIT License] [license].

[license]: http://www.opensource.org/licenses/mit-license.php
