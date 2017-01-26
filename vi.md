# vi
## vi [cheatsheet:](http://www.lagmonster.org/docs/vi.html)
### Motion
- h	Move left
- j	Move down
- k	Move up
- l	Move right
- w	Move to next word
- W	Move to next blank delimited word
- b	Move to the beginning of the word
- B	Move to the beginning of blank delimted word
- e	Move to the end of the word
- E	Move to the end of Blank delimited word
- (	Move a sentence back
- )	Move a sentence forward
- {	Move a paragraph back
- }	Move a paragraph forward
- 0	Move to the begining of the line
- $	Move to the end of the line
- 1G	Move to the first line of the file
- G	Move to the last line of the file
- nG	Move to nth line of the file
- :n	Move to nth line of the file
- fc	Move forward to c
- Fc	Move back to c
- H	Move to top of screen
- M	Move to middle of screen
- L	Move to botton of screen
- %	Move to associated ( ), { }, [ ]
### Delete
- x	Delete character to the right of cursor
- X	Delete character to the left of cursor
- D	Delete to the end of the line
- dd	Delete current line
- :d	Delete current line
### Searching
- /string	Search forward for string
- ?string	Search back for string
- n	Search for next instance of string
- N	Search for previous instance of string
### Replace
- :s/pattern/string/flags	Replace pattern with string according to flags.
- g	Flag - Replace all occurences of pattern
- c	Flag - Confirm replaces.
- &	Repeat last :s command
### Regular Expressions
- . (dot)	Any single character except newline
- *	zero or more occurances of any character
- [...]	Any single character specified in the set
- [^...]	Any single character not specified in the set
- ^	Anchor - beginning of the line
- $	Anchor - end of line
- \<	Anchor - begining of word
- \>	Anchor - end of word
- \(...\)	Grouping - usually used to group conditions
- \n	Contents of nth grouping
