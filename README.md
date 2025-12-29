# just-roll-credits
a basic raylib project that handles "rolling credits" from a configuration file.

# dependencies
dunno, raylib c++ and cmake stuff?

## building
execute `cmake -S . -B build` in project root directory then `cmake --build build`

## run
`./build/just-roll-credits/just-roll-credits /path/to/credits/file`

## TODO
- [ ] get music into the credits
- [ ] make credits last as long as the music?

## credits file
requires a well formed credits file as an argument.
an example credits file is in the example/ directory.
the structure of the file is having a type at the start of each line followed by comma seperated values depending on the type.

|type|structure|description|
|:-|:-|:-|
|FADE_IN|<int seconds>,<credit>,<font-size>|credit text fades in, hangs for seconds, then fades out|
|WHITE_SPACE|<pixel count>|number of pixels to have before next credit|
|PAUSE|<frame count>|a number of frames to halt for|
|CREDIT|<credit>,<font-size>|a standard credit, scrolls at a constant rate|
|GRID|<columns>,<font-size>,<credit1>,<credit2>...|creates a grid of list of credits|



