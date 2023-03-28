Batch Static Deobfuscator
=======================

Batch Static Deobfuscator is a command-line tool that allows you to deobfuscate batch files that use environment variables.

## Usage
`batch_decrypt.exe batch_file`

Where `batch_file` is the path to the batch file you want to deobfuscate.

## How it works
Batch Static Deobfuscator reads the contents of the input batch file and searches for lines starting with set, which define environment variables. It then replaces all instances of `%variable_name%` with the corresponding variable value. The deobfuscated content is written to a new file with the `.decrypted` extension.

## License
This code is distributed under the [MIT License](LICENSE).

## Author
This tool was created by Kaimi (Sergey Belov) - https://kaimi.io

© Kaimi (Sergey Belov) - https://kaimi.io. [MIT License](LICENSE).
