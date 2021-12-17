# Degenerate Bases

The active development version of the degenerate bases algorithm that supports GUI.

This project was developed to analyze oligonucleotide sequences containing 
degenerate bases and generate a file with all possible outcomes with non-degenerate
bases considering the conversion of degenerate bases into conventional bases.

If you're looking for the NoGUI version ( 4.6f ), visit the [legacy repository](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI).

## Getting Started

These instructions are aimed towards getting you a copy of the project up and running on your local
machine for development and testing purposes.

### Prerequisites

In order to build this project, it is recommended to open the 
[Visual Studio](https://visualstudio.microsoft.com/pt-br/downloads/) solution,
but shortly the option to build in Linux or OSX environments using CMake will be available.
You can also download the project directly from [Releases](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/releases).

### Installing

It is fairly easy to install the project, all you need to do is to 
[clone](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/) it from
GitHub. There is also the option to [download](https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/archive/refs/heads/main.zip)
a copy of the repository.

If you wish to clone the repository using the terminal, you'll need to run:

```bash
git clone https://github.com/DatDarkAlpaca/Degenerate-Bases-NoGUI/
```

## Building the project

To build the project using Visual Studio, **after correctly
[installing the project](README.md#Installing)**, you'll need to build/download [wxWidget](https://www.wxwidgets.org),
the GUI library used in this project. After that, create the folder `wxWidgets` under `src/vendor`. Inside this folder,
add the `include` and `lib` folders.

Finally, click `Build` then `Build All` on Visual Studio. Alternatively, you can use the shortcut `Ctrl+Shift+B`.
The executable files are generated under `bin/Configuration/Platform`.

Once you open the application, it'll generate a folder called `results` and a file called `settings.ini` in the current directory.
They are recreated if you delete them.

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
