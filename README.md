# OS_Assignment_2

Written by:
1. Halel Itzhaki - 322989674
2. Ori Ekshtein - 213562069

This assignment includes the following programs:
1. cmp tool - implementing the shell cmp command, supporting -v and -i flags (-v for verbose output, -i for ignoring char case)
2. copy tool - implementing the shell copy command, supporting -v and -f flags (-v for verbose output, -f for forcing openning new target file)
3. codecA encode/decode tool - encoding/decoding strings by coverting all lower case chars to upper case, and all upper case to lower case
4. codecB encode/decode tool - encoding/decoding strings by coverting all chars to the 3-rd next char
5. stshell tool - student running shell, that implements every shell command with supporting '>', '>>' and at least two '|'.

## Installation

To install OS_Assignment_2, run on terminal - 
```bash
git clone https://github.com/halelitzhaki/OS_Assignment_2.git
```

## Usage

Run on terminal the following command:
```bash
make all
```

To use cmp, run on terminal the following command:

./cmp [file1] [file2] [flag] [flag]

For example:
```bash
./cmp first_file.txt second_file.txt -v
```


To use copy, run on terminal the following command:

./copy [file1] [file2] [flag] [flag]

For example:
```bash
./copy source.txt target.txt -f -v
```


To use codecA, run on terminal the following command:

./encode or ./decode [codecA] [message]

For example:
```bash
./encode codecA aaaBBB
```


To use codecB, run on terminal the following command:

./encode or ./decode [codecB] [message]

For example:
```bash
./decode codecB EEEddd
```


To use stshell, run on terminal the following command:
```bash
./stshell
```
