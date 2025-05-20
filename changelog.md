# Changelog

## [alpha 0.2] - ?
### Notes


- Now you can change the filename without recompiling
### Added


### Fixed
- Program wasn't able to decompressed files with decompressed size > 4 kiB

### Known Issues


## [alpha 0.1] - 2025-05-14
### Notes
- First public working version

### Added
- Support for opening `.schematic` files (both compressed and uncompressed)
- Support for opening uncompressed NBT files
- Decompression of `.schematic` files using zlib
- Parsing of tags from NBT files and displaying content in the console
- Windows: Precompiled object files for zlib and the static library itself

### Known Issues
- Program is expected to output parsed content to a file, but this is not yet implemented, I will fix it later