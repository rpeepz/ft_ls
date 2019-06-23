# Changelog <img src="https://png.pngtree.com/svg/20170719/e584c33d9e.svg" height="48" width="48">
All notable changes to this project will be documented in this file.

- This CHANGELOG file to hopefully serve as a way to keep track of my
  developments towards this project

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

<br/>
<br/>

## [1.8.0] - 2019-06-20
### Added
- output to account for extended attributes
### Changed
- buffer size in `first` to prevent *SIGABRT*
- first call to function `ft_ls` will always use `-1` flag

<br/>

## [1.7.1] - 2019-06-20
### Changed
- something in this commit broke my reverse sort but still able to sort by last modification time according to seconds *and* nano seconds

<br/>

## [1.7.0] - 2019-06-20
## Added
- sort by time modified with `-t`

<br/>

## [1.6.1] - 2019-06-20
### Changes
- output to account for major and minor devices

<br/>

## [1.6.0] - 2019-06-18
## Added
- output to account for symbolic links

<br/>

## [1.5.1] - 2019-06-18
### Changes
- adjustments to `s_printf` to account for padding
### other changes [1.5.2]
- added x conversion for hexadecimal output

<br/>

## [1.5.0] - 2019-06-17
### Added
- list in long format with `-l`
- new source files
  - `get_first.c`
    - holds functions for finding date, permisisons, and type of requested file
  - `get_longest_long.c `
    - finds and returns an array holding the lengths of the longest link count, user name, group name, and block size
  - `long_output.c `
    - prints the long format output of files in a directory

<br/>

## [1.4.1] - 2019-06-08
### Changed
- "dump buffer" style print method

## [1.4.0] - 2019-06-06
### Added
- recursive search and display
- consistency with colored output

### Changed
- full path allocation for struct member

<br/>

## [1.3.1] - 2019-06-05
### Changed
- unsorted output
- sorted output
- reverse output
- color output

<br/>

## [1.3.0] - 2019-06-04
### Added
- colored output with **-G**

<br/>

## [1.2.1] - 2019-06-03
### Changed
- ```t_filedel``` will now free all in list

<br/>

## [1.2.0] - 2019-06-02
### Added
- merge sorting algorithm

<br/>

### other changes [1.1.2]
- mask process to compare

## [1.1.1] -2019-05-28
### Changed
- Makefile
- header file
- moved some files around

<br/>

# [1.0.0] - 2019-05-26
### **first working version**
### Added
- new source file `ft_ls.c`
  - displays contents of current directory or paths specified from the command line
#### other additions [1.1.0]
- sprintf and helper functions
  - ```ft_sprintf``` takes an argument and stores in a buffer of predefined size

<br/>

## [0.3.0] - 2019-05-24
### Added
- struct member `index` to keep track of directory order
- t_file add function
  - ```t_fileadd``` allocate and assign directory names to struct

### Changed
- print items for testing
  - system leaks
  - contents of struct in order

<br/>

## [0.2.1] - 2019-05-23
### Added
- new source file `t_init.c`

<br/>

## [0.2.0] - 2019-05-18
### Added
- t_file delete and t_file initialize functions
  - ```t_filedel``` free memory upon error or exit
  - ```t_fileinit``` malloc for directories to process

<br/>

## [0.1.9] - 2019-05-18
### Added
- new source file `get_.c` to reduce clutter in `main.c`

<br/>

## [0.1.3] - 2019-05-18
### Changed
- Makefile
  - new rules debug and 1mo

<br/>

## [0.1.2] - 2019-05-03
### Added
- print error message upon invalid flag found
- print bitmasked flags in binary
### Changed
- flag output variable using bitmasking

<br/>

## [0.1.1] - 2019-05-03
### Added
- ```convert_b``` for binary output
### Changed
- ft_printf conversions to meet norm and improve usage

<br/>

## [0.1.0] - 2019-05-02
### Added
- functionality to parse arguments into flag options

<br/>

## [0.0.3] - 2019-05-01
### Added
- Makefile

<br/>

## [0.0.2] - 2019-05-01
### Added
- author file
- Libft source files
- includes folder

<br/>

## [0.0.1] - 2019-05-01
### Added
- Licence, README, gitignore


### Resources
---
##### [Changelog]
##### [Markdown]
##### [Icons]


[1.8.0]: https://github.com/rpeepz/ft_ls/commit/7c3ba444207d00eec0c33d5bb4a5e3267e17c147#diff-aba7bd875a7ddb7e38da307469b26360
[1.7.1]: https://github.com/rpeepz/ft_ls/commit/0d6d8d24db4669328eb9ed75bbc6363c1615bdd0#diff-8c0c99094aadc1dc37dbb4dea582a8d0
[1.7.0]: https://github.com/rpeepz/ft_ls/commit/7b9d0ed1f0ce22ccb131e7375dbc432151a018f6#diff-8c0c99094aadc1dc37dbb4dea582a8d0
[1.6.1]: https://github.com/rpeepz/ft_ls/commit/cf65a4b629cc4bb837e3a8d8d447831a3ce62584#diff-607e89b6186ce88d62c556408ed4b08b
[1.6.0]: https://github.com/rpeepz/ft_ls/commit/99eee69cd3d2b92b387dc18ebc9fcac5dcbd3e39#diff-607e89b6186ce88d62c556408ed4b08b
[1.5.2]:https://github.com/rpeepz/ft_ls/commit/ae5512d70c7ba8fa9e2cdaacbcca0952c90797be#diff-deab028ce7dab6102dc6fb0e6f96315c
[1.5.1]: https://github.com/rpeepz/ft_ls/commit/c7265435ffde5e6d428ee7be31f2eea24a6658c8#diff-e254f6494dcd74d6791d3a1ede6d834f
[1.5.0]: https://github.com/rpeepz/ft_ls/commit/ba3b2f4e93743e282f1393fd49abfa07368c36d8#diff-43f6b09cf18cb3a93ace138ba02ed33d
[1.4.1]: https://github.com/rpeepz/ft_ls/commit/9c568ab2aa2da166b6e6b8897654fcda7ff6acab#diff-72a4340a3a0331efc1b5e08621e0bccc
[1.4.0]: https://github.com/rpeepz/ft_ls/commit/c9723db1862a282d6c7698efa9fe2d1bb7e4435b#diff-72a4340a3a0331efc1b5e08621e0bccc
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
