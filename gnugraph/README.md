# Gaussian Graphing
For this, the following GitHub project was utilized with some modifications to the file `GnuGraph.h`: https://github.com/AnyarInc/gnugraph
The gnugraph files can be found here along with the accompanying `LICENSE`.
## Dependencies
- gnugraph
- gnuplot
  - I am using gnuplot 5.2 (patchlevel 2).
## Files from gnugraph
- `GnuGraph.h` -- Modified
  - This file has been modified to allow for saving a png image of the graph when the program is run. The png file is saved to a specified location with a timestamp. Changes made are denoted with comments ending with '-- amitchell'.
- `GnuGraphFormatter.h` -- Unmodified
- `GnuGraphPiping.h` -- Unmodified
## Other files
- `Gauss_main.cpp`
  - Generates 1000 pseudo-random Gaussian numbers and uses the gnugraph library to output the graph in gnuplot as well as to create a png file of that plot when the program is run.
  - Depending on your setup, you'll need to modify both the path for `gnuplot.exe` as well as the `file_name`.
- This `README.md`
  - You're currently reading this file, which documents changes made to the gnugraph project as well as describes how it was used for this checkers project.
- The graphs...
  - ... can be found in `gaussian_graphs`.