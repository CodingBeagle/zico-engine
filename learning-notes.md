# Learning Notes

## Windows API

### Unicode

https://docs.microsoft.com/en-us/windows/win32/intl/unicode-in-the-windows-api

Windows API functions which somehow use characters are generally implemented in three formats:

- A generic version that can be compiled for ANSI or Unicode
- An ANSI version with the letter "A" used to indicate "ANSI"
- A Unicode version with the letter "W" used to indicate "Wide"

For newer applications, it's recommended to simply call the Unicode versions of functions and structures directly, unless you for some reason need to be able to compile for ANSI support.