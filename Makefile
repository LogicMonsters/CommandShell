CCFlags = -std=gnu++98 -ggdb3 -Wall -Werror -pedantic

all: myShell a b c d segmentation parse

myShell: myShell.h RedirectInfo.h prompt.h read.h parse.h specialCommand.h sysCommand.h myShell.cpp
	g++ -o myShell $(CCFlags) myShell.cpp

a: a.cpp
	g++ -o a $(CCFlags) a.cpp
b: b.cpp
	g++ -o b $(CCFlags) b.cpp
c: c.cpp
	g++ -o c $(CCFlags) c.cpp
d: d.cpp
	g++ -o d $(CCFlags) d.cpp
segmentation: segmentation.cpp
	g++ -o segmentation $(CCFlags) segmentation.cpp
parse: parse.cpp
	g++ -o parse $(CCFlags) parse.cpp
clean:
	rm -r myShell a b c d *~ *.dSYM
