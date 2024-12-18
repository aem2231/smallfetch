# smallfetch

A simple system information fetching tool written in C. It provides a basic overview of your system's specifications in a compact and (maybe) visually appealing format.

## Features

- Display ASCII art logo
- Show hostname
- Display kernel information
- Show CPU details
- Report memory usage
- List installed packages

## Building

This project uses CMake for building. To build the project, follow these steps:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage 

Either run `./smallfetch` from the build directory or add it to your path and run `smallfetch` from anywhere within your shell.

## Contributing

Anyone is of course welcome to contribute, this is my first project in C so any criticism or suggestions is welcomed and appreciated.
