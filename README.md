# Degenerate Bases
This algorithm generates a list of possible sequences derived from a sequence containing degenerate bases.

## 1. Setup

### 1.0 Cloning

Make sure you have CMake installed on your machine. For Windows users, make sure you have defined the appropriate environment path to it.

### 1.1 Cloning the Main Repository
Click the `Code` button, then chose your preferred method of cloning.

If you want to clone it using the command line, please make sure you have Git installed and use the code below:
``` bash
> mkdir degenerate-bases & cd degenerate-bases
> git clone https://github.com/DatDarkAlpaca/Degenerate-Bases/
```

## 2. Building

### 2.1 Building for Windows

You can either use `CMakeGUI` or the command prompt to build the project.

Upon completion, open the generated *.sln* file under the build directory. After that, right-click the `degenerate-bases` project and click `Build`. The executable files will be generated at `/build/src/'Configuration'`.


The following code is an example that you can use in the command prompt.
``` bash
> mkdir build
> cmake -S . -B build
```

### 2.2 Building for Linux

You can use the following code to build the project:
``` bash
> mkdir build & cd build
> cmake ..
> make
```

## 3. Instructions

First of all, **place the generated executable file inside a folder for easier management**. It will generate the logs, results and bin folders, and a settings file located inside the bin folder.

### 3.1 Settings

The settings are displayed below:

| Key                        | Default Value   | Description  |
| :------------------------: |:--------------: | :-----------:|
| initializationCharacter    | >               | The initialization character to be used on the fasta file.                               |
| sequenceTemplate           | seq             | The default name for results on the fasta file.                                          |
| resultPrefix               | Result_         | The prefix for fasta file names.                                                         |
| resultFormat               | .fas            | The generated file type. (Note: it only changes the file format name)                    |
| resultsFolder              | ./results/      | The folder where the fasta files will be generated.                                      |
| enableLogging              | true            | This option enables the generation of log files.                                         |
| logPrefix                  | Log_            | The prefix for log file names.                                                           |
| logsFolder                 | ./logs/         | The folder where the log files will be generated.                                        |
| chunkSize                  | 2048            | The number of bases the program will process before saving it to the results folder.     |
| writeDebug                 | false           | Writes every chunk operation to the screen. It will significantly slow the program down. |
| debug                      | true            | Displays a few debug information at the end of the program's execution.                  |

### 3.2 Using the program

The usage of the program is straightforward. First, open the program. You'll see the option to write a sequence. Depending on the terminal version and operating system you're using, you may even be capable of copying the sequence straight into it. The inputs are always converted to uppercase letters with no trailing whitespaces. The following table shows the available bases:

| Base    | Results    |
| :-----: |:---------: |
| N       | A, C, T, G |
| D       | A, G, T    |
| V       | A, C, G    |
| B       | C, T, G    |
| H       | A, C, T    |
| W       | A, T       |
| S       | C, G       |
| K       | G, T       | 
| M       | A, C       |
| Y       | C, T       |
| R       | A, G       |
| A       | A          |
| C       | C          |
| G       | G          |
| T       | T          |
| .       | .          |
| -       | -          |
| *       | *          |

You can find this table using the command "bases" or "base" on the program. Use these keywords instead of a sequence.

## 4. Performance

The program is highly dependent on the performance of the processor's single core speed, since it doesn't have any multi-threading implementation. Some conclusion were made from a variety of tests:

* The addition of single-generating bases (A, C, G, T, ., -, \*) barely affects the performance of the program;
* Using only single-generating bases will cause the program to enter the SBI (Single-Base Insertion) algorithm, which will simply "paste" the sanitized sequence (uppercase without trailing spaces) into a results file, decreasing even further the processing time;
* The program processes 2^20 possibilities in approximately five seconds;
* Theoretically, any sequence will be processed. However, some sequences produce massive numbers of possibilities, and thus create a enourmous results file. Those may take much longer;
* The biggest sequence tested so far (regarding possible results) was the 13.N (NNNNNNNNNNNNN), taking 
* The peak of memory usage identified was 7.2MB (6.7MB was the console window) after the implementation of the Lazy Cartesian Product algorithm.
