# grepaw

Grepaw is a grep-like line-oriented text searching tool, written in C++. It can:

- read lines from a file and search for specified pattern
- traverse a directory and search for pattern in all regular files
- read from stdin and search for specified pattern


**TODO:**

- [ ] Add search using KMP (Knuth-Morris-Pratt algorithm)


## To use grepaw

```
make
```

Search pattern in file:
```
./grepaw <pattern> <filePath>
```

Search pattern in directory:
```
./grepaw <pattern> <dirPath>
```

Search pattern from stdin:
```
<cmd> | ./grepaw <pattern>
```
