# Changelog <img src="https://png.pngtree.com/svg/20170719/e584c33d9e.svg" height="48" width="48">
All notable changes to this project will be documented in this file.

- This CHANGELOG file to hopefully serve as a way to keep track of my
  developments towards this project

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.3.1] - 2019-06-05 ### (recent stable release)
### Changed
- unsorted output
- sorted output
- reverse output
- color output

## [1.3.0] - 2019-06-04
### Added
- colored output with **-G**

### [1.2.1] - 2019-06-03
### Changed
- ```t_filedel``` will now free all in list

## [1.2.0] - 2019-06-02
### Added
- merge sorting algorithm

#### other changes [1.1.2]
- mask process to compare

### [1.1.1] -2019-05-28
### Changed
- Makefile
- header file
- moved some files around

# [1.0.0] - 2019-05-26
### Added
- **first working ls program**
- new source file `ft_ls.c`
  - displays contents of current directory or paths specified from the command line
#### other additions [1.1.0]
- sprintf and helper functions
  - ```ft_sprintf``` takes an argument and stores in a buffer of predefined size

## [0.3.0] - 2019-05-24
### Added
- struct member `index` to keep track of directory order
- t_file add function
  - ```t_fileadd``` allocate and assign directory names to struct

### Changed
- print items for testing
  - system leaks
  - contents of struct in order

### [0.2.1] - 2019-05-23
### Added
- new source file `t_init.c`

## [0.2.0] - 2019-05-18
### Added
- t_file delete and t_file initialize functions
  - ```t_filedel``` free memory upon error or exit
  - ```t_fileinit``` malloc for directories to process

### [0.1.9] - 2019-05-18
### Added
- new source file `get_.c` to reduce clutter in `main.c`

### [0.1.3] - 2019-05-18
### Changed
- Makefile
  - new rules debug and 1mo

### [0.1.2] - 2019-05-03
### Added
- print error message upon invalid flag found
- print bitmasked flags in binary
### Changed
- flag output variable using bitmasking

### [0.1.1] - 2019-05-03
### Added
- ```convert_b``` for binary output
### Changed
- ft_printf conversions to meet norm and improve usage

## [0.1.0] - 2019-05-02
### Added
- functionality to parse arguments into flag options

### [0.0.3] - 2019-05-01
### Added
- Makefile

### [0.0.2] - 2019-05-01
### Added
- author file
- Libft source files
- includes folder

## [0.0.1] - 2019-05-01
### Added
- Licence, README, gitignore


### Resources
---
##### [Changelog]
##### [Markdown]
##### [Icons]

[1.3.1]: https://github.com/rpeepz/ft_ls/commit/e5fb8eb3f5f05fde0685c06ec9673ea4baffdb29#diff-4b3678ad9563052d4b2a3adc567a925c
[1.3.0]: https://github.com/rpeepz/ft_ls/commit/931e6250e3644a083952e36e0dcf84424890d36c#diff-1358f7323be5a17dc96f3799ff3e52a9
[1.2.1]: https://github.com/rpeepz/ft_ls/commit/b59adcbf924fbf6309003a86cf84804b1b887809#diff-bb127294234fc295cac1381525c5bc3b
[1.2.0]: https://github.com/rpeepz/ft_ls/commit/2e66bd9b0d529b1ef9f8d9564a18c6d6a65eda71
[1.1.2]: https://github.com/rpeepz/ft_ls/commit/02fddb99f483fabbb27ef0db0779284970e4830e
[1.1.1]: https://github.com/rpeepz/ft_ls/commit/4856bd3d5fa02a57479027d4fbb0de55060705e0#diff-d4d8f5619de638ed5bf912d76c64a641
[1.1.0]: https://github.com/rpeepz/ft_ls/commit/fb3145eb3def48e5a790b306e86e3b48d139011d#diff-f4bab6f0038ea5d72de75b59713acd3c
[1.0.0]: https://github.com/rpeepz/ft_ls/commit/5b05676d39578af7899a9a8c62be5e9407c70af1#diff-72a4340a3a0331efc1b5e08621e0bccc
[0.3.0]: https://github.com/rpeepz/ft_ls/commit/ad75ecc#diff-d73dc5ad42aef24c11e21ceff832111b
[0.2.1]: https://github.com/rpeepz/ft_ls/commit/48059f2d94250433c8a1dc8f9d0607232b4a579c#diff-bb127294234fc295cac1381525c5bc3b
[0.2.0]: https://github.com/rpeepz/ft_ls/commit/ac49840#diff-4840f30cac8e8fd22fe4e253a93849ae
[0.1.9]: https://github.com/rpeepz/ft_ls/commit/f5ef9426c8a0e33f0deecb4d697b35e1cadc1be3#diff-4840f30cac8e8fd22fe4e253a93849ae
[0.1.3]: https://github.com/rpeepz/ft_ls/commit/d869953#diff-b67911656ef5d18c4ae36cb6741b7965
[0.1.2]: https://github.com/rpeepz/ft_ls/commit/2fce750#diff-6fc897d9b03f1b5eda0fdec77e38b736
[0.1.1]: https://github.com/rpeepz/ft_ls/commit/2b2e6b4#diff-9794b6d2b46c4b846fb8244a7fe1aed7
[0.1.0]: https://github.com/rpeepz/ft_ls/commit/e138037#diff-6fc897d9b03f1b5eda0fdec77e38b736
[0.0.3]: https://github.com/rpeepz/ft_ls/commit/d93e694#diff-b67911656ef5d18c4ae36cb6741b7965
[0.0.2]: https://github.com/rpeepz/ft_ls/commit/76bb98f#diff-02bd92faa38aaa6cc0ea75e59937a1ef
[0.0.1]: https://github.com/rpeepz/ft_ls/commit/1060233
[Changelog]: https://github.com/olivierlacan/keep-a-changelog/blob/master/CHANGELOG.md "Formatting style"
[Markdown]: https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet "Cheat sheet"
[Icons]: https://pngtree.com/free-icon "png tree"
