# Development of a small rogue like game, very small

The goal of this memory is to keep track on the development of a small rogue-like game from the very
start till the end.

## Index

1. Introduction
    - General Links
	- Programming Links
2. Development steps
	- Step 1: decide to write a game
	- Step 2: Hello World!
	- Step 3: It's a Boy





## General Links

[RogueBasin Wiki](http://www.roguebasin.com/index.php?title=Main_Page): wiki about roguebasin, with
very good and multiple articles about rogueLike games development, some programming tutorials...

[Procedural Content Generation Wiki](http://pcg.wikidot.com/): wiki about procedural content 
generation: programming, algorithms, maths...

## Programming Links

[API Ncurses](http://invisible-island.net/ncurses/man/ncurses.3x.html): Ncurses library Api
a must to use terminals without reinventing the wheel.

[Small Ncurses turorial](http://heather.cs.ucdavis.edu/~matloff/UnixAndC/CLanguage/Curses.pdf): 
Small tutorial about Ncurses ( 10 pages ) well writen, comented, with examples and using linux.

## Development steps

### Decide to write a game 

Ideas about the game, rigth now the only stable idea is to make a roguelike game.

### Hello world!

**Text Editor used:** gedit with markdown plugin, integrated Terminal and side panel with documents and
folders, also C syntax highlighting.

**Language and libraries:** C and Ncurses.

**Plataform (OS):** Ubuntu 14.04 Desktop 64 bits

### It's a boy
Things it does:
- [x] It moves
- [x] There are collisions
- [x] There are boundaries
- [x] Also doors

Things to do:
- [ ] make a notification area (Health, position , Messages...)
- [ ] Make the message handling routines to make debugging much easier (text as a log file)
