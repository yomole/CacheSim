# CacheSim
CacheSim is a program written to simulate caches with different associatitivites, block sizes, cache sizes, and replacement strategies. To save time, I wrote a decently robust CLI interface that allows one to set different cache sizes, block sizes, associativities, memory sizes, replacement strategies, and more. These variables are simulated one at a time in different combinations created from these program arguments. CacheSim also comes with debug commands and line by line view to see what is going on in each simulation. 

A PDF of a cache analysis paper using CacheSim can be found in the top level folder for the application. The source Jupyter Notebook can be found in the analysis folder.

## Compiling CacheSim
So far, I have only compiled CacheSim on Windows 11, so these instructions are for windows. Compiling CacheSim requires:
- [CMake](https://cmake.org/)
- [Ninja](https://ninja-build.org/)
- [MinGW-w64](https://www.mingw-w64.org/)

The location of these tools must also be in your system's `PATH` variable so that they are accessible from the command prompt.

To compile CacheSim,
1. Open a command prompt and navigate to the top level folder for the CacheSim application.
2. Enter the command `cmake -Bbuild -G=Ninja`. CMake should run and compile the CacheSim project.
3. Navigate to the build folder.
4. Enter the command `ninja`. This will link the files from CMake into an executable that will be placed in the top level folder.
5. Navigate back to the top level folder.

## Using CacheSim
Running CacheSim with no arguments will print a help screen with a list of program arguments. These arguments are the only way to interact with the CacheSim application.

CacheSim will take the list of arguments presented and run a simulation with every possible combination. However, the application will not run a simulation if the cache is not possible to create or if the block size is smaller than four bytes. 

CacheSim requires a trace file to perform its simulations. Any trace file one wishes to use must be placed in the `traces/` folder and then specified in an argument. There is no validity check for trace files besides a check for a .trace extension. These files must be structured in the way shown for the trace files that are already in the `traces/` folder. For best performance, the number of memory bits should correspond with the number of memory bits in the addresses of the trace files. Trace files should also consist of at least 1000 lines for best performance and data collection.

CacheSim will record the results of each simulation while it is cycling through them in a csv file. The csv file is created before the first simulation if it does not already exist. If the file does exist, CacheSim will append data to that csv file.

At the end of all simulations, CacheSim will report the number of valid and invalid simulations. This will match the number of rows in the generated csv file unless the file already contained data.

### Line by Line Mode
CacheSim contains a flag for line by line mode. This mode was originally meant for debugging the application, but it is a useful learning tool for caches, so it was preserved. In line by line mode, the application pauses after each line in the trace file and allows user input. A user can:
- Display all line by line mode commands.
- Proceed to the next memory request.
- Print the cache in a table format.
- Print current statistics of the cache.
- Skip until the next simulation.
- Skip until the end of the program.

Line by line mode keeps track of a user's previous input, and entering a blank string will execute that input.

Note that silent mode takes precedence over line by line mode. 