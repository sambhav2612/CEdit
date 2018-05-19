# Contributing Guide

New users who wish to contribute to the development of this project should go through the entire codebase and understand the key things like what `\x1b` stands for. This would help us and you as well.

## How to add additional language grammars

cd to `hldb/database.h` and add the necessary grammar using a char keyword array and extenions array and passing them to the instance of structure `editorSyntax` => `HLDB[]` in the same format given without breaking any other file because we know how diffcult it is to revert human-errors ;)

Happy Hunting!