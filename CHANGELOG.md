# Changelog
All notable changes to this project will be documented in this file.

- This CHANGELOG file to hopefully serve as a way to keep track of my
  developments towards this project

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.3.0] - 2019-05-24
### Added
- t_file add function
 - ```t_fileadd``` allocate and assign directory names to struct
- struct member `index` to keep track of directory order

### Changed
- output for testing
 - system leaks
 - all struct members in order

## [0.2.1] - 2019-05-23
### Added
- new source file `t_init.c`

## [0.2.0] - 2019-05-18
### Added
- t_file initailize and t_file delete functions
 - ```t_fileinit``` malloc for directories to process
 - ```t_filedel``` free memory upon error or exit

## [0.1.9] - 2019-05-18
### Added
- new source file `get_.c` to reduce clutter in `main.c`

## [0.1.3] - 2019-05-18
### Changed
- Makefile

## [0.1.2] - 2019-05-03
### Added
- print error message upon invalid flag found
- print bitmasked flags in binary
### Changed
- flag output variable using bitmasking

## [0.1.1] - 2019-05-03
### Added
- ```convert_b``` for binary output
### Changed
- ft_printf conversions to meet norm and improve usage

## [0.1.0] - 2019-05-02
### Added
- functionality to parse arguments into flag options

## [0.0.3] - 2019-05-01
### Added
- Makefile

## [0.0.2] - 2019-05-01
### Added
- author file
- Libft source files
- includes folder

## [0.0.1] - 2019-05-01
### Added
- Licence, README, gitignore

[0.3.0]: https://github.com/rpeepz/ft_ls/commit/ad75ecc
[0.2.1]: https://github.com/rpeepz/ft_ls/commit/48059f2d94250433c8a1dc8f9d0607232b4a579c#diff-bb127294234fc295cac1381525c5bc3b
[0.2.0]: https://github.com/rpeepz/ft_ls/commit/ac49840
[0.1.9]: https://github.com/rpeepz/ft_ls/commit/f5ef9426c8a0e33f0deecb4d697b35e1cadc1be3#diff-4840f30cac8e8fd22fe4e253a93849ae
[0.1.3]: https://github.com/rpeepz/ft_ls/commit/d869953
[0.1.2]: https://github.com/rpeepz/ft_ls/commit/2fce750
[0.1.1]: https://github.com/rpeepz/ft_ls/commit/2b2e6b4
[0.1.0]: https://github.com/rpeepz/ft_ls/commit/e138037
[0.0.3]: https://github.com/rpeepz/ft_ls/commit/d93e694
[0.0.2]: https://github.com/rpeepz/ft_ls/commit/76bb98f
[0.0.1]: https://github.com/rpeepz/ft_ls/commit/1060233