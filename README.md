LOLDOG
======

What is this?
-------------

Similarly to tools like [fortune](http://en.wikipedia.org/wiki/Fortune_%28Unix%29),
[cowsay](http://en.wikipedia.org/wiki/Cowsay), and
[figlet](http://www.figlet.org), loldog is yet another indispensable utility
for each (256-color) terminal. It is inspired by
[lolcat](https://github.com/busyloop/lolcat) but written in C and hence
Ruby is not required.

The program works in a similar way as the well-known Unix command `cat` which
concatenates files and/or standard input to the standard output except that
loldog will make the output more colorful :-). The program itself is very simple
and I have used it to just refresh a bit the plain-C programming and to learn
some basics about programming in the Unix-like systems.

Installation
------------

The program uses CMake. You can build and install it by executing the following
commands:
```
$ cd src
$ cmake .
$ make
$ make install
```
The executable installs by default to the directory `/usr/local/bin`.
If you wish to change it, configure the project by the following command:
```
$ cmake -DCMAKE_PREFIX=<your_prefix>
```
replacing `<your_prefix>` by the path where you wish the installation to be
performed. The executable then installs to the directory `<your_prefix>/bin`.

The program requires [curses](http://en.wikipedia.org/wiki/Curses_%28programming_library%29)
to be available in the system.

FAQ
---

**Q.** Loldog works fine. What is it good for?

**A.** Honestly, nothing much. Just for fun.

**Q.** Loldog halts with the message
```
Terminal supports only <N> colors.
```
What should I do?

**A.** Loldog requires a terminal which supports 256 colors but your terminal
supports only `N` colors. You can try to fix the problem by inserting the line
```
export TERM=xterm-256color
```
to your `.bashrc` or `.profile` file.
Of course, your terminal should be *able* to use 256 colors first.

**Q.** The program halts with the message
```
Output is not a terminal.
```

**A.** You are probably trying to redirect the standard output of loldog to something
else than a terminal. Why?

Manual
------

There is no manual page (yet). The program is easy to use. Type
```
$ loldog -h
```
in your terminal.

Comments, suggestions, bug reports
----------------------------------

Please send me anything of this type to my e-mail
address: <pavel.jiranek@gmail.com>.

**Enjoy!**

