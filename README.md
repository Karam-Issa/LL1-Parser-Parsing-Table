# LL(1) Parser and Parsing Table Generator

This C++ program implements an LL(1) parser to calculate the First and Follow sets of a given context-free grammar, fill a parsing table, and perform parsing to determine if a given input string is accepted by the grammar.

## Features
- Calculates the First sets of non-terminal characters in the grammar.
- Computes the Follow sets of non-terminal characters in the grammar.
- Generates a parsing table based on the calculated First and Follow sets.
- Parses input strings using the generated parsing table to check if they are accepted by the grammar.

## How It Works
1. The grammar's production rules are hard-coded into the `productionSet` array.
2. The `firstOf` and `followOf` functions compute the First and Follow sets for non-terminal characters, respectively.
3. The `firstFollow` function computes the First set of a character and fills the result array.
4. The `findParsingTable` function populates the parsing table using the calculated First and Follow sets.
5. The `parsingProg` function implements the LL(1) parsing algorithm using a stack and the parsing table.

## Usage
1. Compile and run the `LL1_Parser.cpp` file using a C++ compiler.
2. The program will display the First and Follow sets for each non-terminal character.
3. The generated parsing table will be displayed in tabular format.
4. Enter an input string to check if it is accepted by the grammar.

## Disclaimer
This program provides a simplified demonstration of an LL(1) parser and parsing table generator. It may not cover all possible scenarios or handle complex grammars. For production use, thorough testing, optimization, and handling of edge cases are essential.

## Contributors
- Karam Issa (20200585)
- Beybars Abaza (20200715)
- Jude Hamdan (20200856)
- Aws Almahasneh (20200388)
