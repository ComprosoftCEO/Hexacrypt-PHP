# Hexacrypt-PHP
PHP extension for Hexacrypt programmed using PHP-CPP

<br>

## Compiling and Installing
1. Install [PHP-CPP](http://www.php-cpp.com/documentation/install).
2. Modify the MakeFile to specify the PHP extension directories
    * INI_DIR (Location of the PHP conf.d directory)
    * INI_DIR_CMD (Location of the PHP command line conf.d directory)
3. Open a terminal, and type `make` then `make install`

<br>

## Algorithm Differences
*This algorithm a few differences from the other [Hexacrypt Repository](https://github.com/ComprosoftCEO/Hexacrypt).*
1. Uses a custom pseudo random number generator called Rand64
2. A checksum is appended to the front of the string to make verification easier
3. String is reversed before trash is added
