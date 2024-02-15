# TarTool: Archive and Extract Files with Ease

TarTool: Archive and Extract Files with Ease
Description
TarTool is a repository containing C programs for archiving and extracting files using the TAR format. It includes two main programs: an archiver (archive.c) for creating TAR archives and an extractor (extract.c) for extracting files from TAR archives.

Usage

Clone the repository to your local machine:

git clone https://github.com/raresc4/tar-tool.git

Compile the archiver and extractor programs using a C compiler such as GCC:

gcc archive.c -o archive
gcc extract.c -o extract

To create a TAR archive, run the archiver program with the files you want to archive as command-line arguments:

./archive file1.txt file2.txt folder

This command will create a TAR archive named archive.tar containing file1.txt, file2.txt, and the contents of the folder.

To extract files from a TAR archive, run the extractor program with the TAR archive as a command-line argument:

./extract archive.tar

This command will extract the contents of archive.tar to the current directory.

Example
Suppose we have the following files and directories:

file1.txt
file2.txt
folder/
    └── subfile.txt
After archiving using archive.c, we obtain archive.tar. After extracting archive.tar using extract.c, we get:

archive.tar
file1.txt
file2.txt
folder/
    └── subfile.txt
    
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
Special thanks to the contributors who have helped improve TarTool.

Issues
If you encounter any problems or have suggestions for improvements, please open an issue on the GitHub repository
