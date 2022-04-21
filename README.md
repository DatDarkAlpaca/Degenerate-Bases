# Degenerate Bases

The active development version of the degenerate bases algorithm that supports GUI.

This project was developed to analyze oligonucleotide sequences containing 
degenerate bases and generate a file with all possible outcomes with non-degenerate
bases considering the conversion of degenerate bases into conventional bases.

Currently, this project only supports Windows builds, so if you're looking for the version without a graphical user interface, and consequently, "cross-platform", visit the [legacy repository](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI).


# Getting Started

These instructions are aimed towards getting you a copy of the project up and running on your local machine for development and testing purposes.

## Prerequisites

In order to build this project, you'll need to download the following dependencies and IDEs:

- [Qt](https://www.qt.io/download-qt-installer)
- [Visual Studio](https://visualstudio.microsoft.com/pt-br/downloads/)

Make sure to install the MSVC compiler when installing Qt.

## Installing

It is fairly easy to install the project, all you need to do is to 
[clone](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/) it from
GitHub. There is also the option to [download](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/archive/refs/heads/main.zip)
a copy of the repository.

If you want to clone the repository using the terminal instead, use:

    git clone https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/


## Visual Studio Setup

Once everything is downloaded, open the solution `Degenerate-Bases.sln`, click on `Extensions` and `Manage Extensions`. A dropdown list will show up. You'll need to install the [Qt Visual Studio Tools](https://marketplace.visualstudio.com/items?itemName=TheQtCompany.QtVisualStudioTools-19123) extension. You may need to restart Visual Studio.

Once installed, open the versions menu under `Extensions` > `Qt VS Tools` > `Qt Version`, then click on the plu sign, and select the `qmake.exe` path from your Qt installation. It can usually be found under `C:\Qt\Version\msvc...\bin\qmake.exe`.

## Building the project

To build the project, click `Build` then `Build Solution` on Visual Studio. Alternatively, you can use the shortcut `Ctrl+Shift+B`.
The executable files are generated under `bin/Configuration/Platform`, and the intermediate files are generated under `intermediate/Configuration/Platform`.

Once you run the application, a folder called `results` and a file called `settings.ini` will be generated in the current directory.
They will be recreated if you delete them.

## Configuring the project

This program offers you a certain degree of customization regarding the folder which you want to save your results,
the pattern used in the fasta results, the size of the chunks that will be written or 
whether you need extra information about the execution.

The following table lists the settings which you can modify on the `settings.ini` folder. 
You will need to restart the application in order to apply the settings.

| Default    | Entry Name          |  Description |
| :---       | :---:               |  :---:       |
| >          | header_character    | The initiation character on the outcome's header.                                     |
| seq        | header_template     | The template name for the outcome's header.                                           |
| Result_    | results-prefix      | The template name of the generated files.                                             |
| fas        | results-format      | The file type which the file will be generated as.                                    |
| ./results/ | results-directory   | The directory where the results will be saved on.                                     |
| 1024       | chunk_size          | The size of outcome chunks that will be written to the file.                          |
| false      | debug-enable        | Displays additional information about the program at the end of the execution.        |
| false      | chunk_size          | A feature designed for testing the chunk writting system.                             |

## Degenerate Bases

The following table lists the available bases.

| Base  | Outcomes   |
| :---: | :---:      |
|   N   | A, C, G, T |
|   D   | A, G, T    |
|   V   | A, C, G    |
|   B   | C, G, T    |
|   H   | A, C, T    |
|   W   | A, T       |
|   S   | C, G       |
|   K   | G, T       |
|   M   | A, C       |
|   Y   | C, T       |
|   R   | A, G       |
|   A   | A          |
|   C   | C          |
|   G   | G          |
|   T   | T          |
|   .   | .          |
|   -   | -          |
|   *   | *          |

## License

This project is licensed under the [MIT License](https://opensource.org/licenses/MIT) - see the
[LICENSE](LICENSE) file for details
