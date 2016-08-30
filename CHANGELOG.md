# Change Log
All notable changes to this project (langtons_ant) will be documented in this file.

This project adheres to [Semantic Versioning](http://semver.org/).

## [1.3.0] - 2016-8-29

### Added
- Variable canvas size - you can now specify a width and length using a flag
- Variable frame skip rate - you can now specify the frame skip rate with a flag

### Fixed
- Bug where cylinder would not terminate when ant crossed y-axis top border
- Typo in README.md

## [1.2.0] - 2016-8-28

### Added 
- Parser for different options
- Cylinder Mode - ant wraps left to right
- Torus Mode - ant wraps on all axes
- Reflect Mode - ant reflects when it hits the border

## [1.1.0] - 2016-08-27

### Changed
- Moved Ant specific code to separate folder `ant/`
- Moved Encoding specific code to separate folder `encode/`
- Updated Makefile with new build instruction rules

## [1.0.0] - 2016-08-25

### Added
- Makefile for building the project.

### Changed
- Implemented basic ant path.
