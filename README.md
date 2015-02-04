LOLDOG
======

What is this?
-------------

I like [lolcat](https://github.com/busyloop/lolcat). Unfortunatelly, it is
written in Ruby which does not need to be available everywhere nor can be
installed everywhere. Hence **loldog**. It is written in the "plain" C
(or something like that).

The program simply takes the input from the standard input or files just as
cat does and colorizes it to the standard output.

Disclaimer
----------

I do not know much about various types of the terminals. For coloring, I
simply use what I found on the
[Wikipedia](http://en.wikipedia.org/wiki/ANSI_escape_code#Colors).
I have tested loldog only on a few terminals.

I hope it builds fine on your machine. On mine, it does (Linux, MacOSX + GCC).

Some things may be a bit odd. I have not touched plain C for a long time and
used this "project" for to refresh my memory.

Comments, suggestions, bug reports
----------------------------------

Please send me anything of this type to my e-mail
address: <pavel.jiranek@gmail.com>.

Installation
------------

No sophisticated configuration and installation is implemented. Simply
modify the makefile in the source directory (set the compiler and options)
and run make. Copy the resulting binary file wherever you want.

Manual
------

Type

```
loldog -h
```

TODO
----

- Moar funky ways to colorize the output.
- Moar options...
- Sell it for a big pile of money.

