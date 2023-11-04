# cb

ClipBoard is a command line utility for interacting with the system's clipboard. Output can be directed to the `cb` utility which copies the text to the clipboard. There are also options for outputing the clipboard contents and copying files directly from disk to the clipboard.

## Usage

|Option|Default|Description|
|---|---|---|
|`-e`, `--echo`|`false`|Echo the data captured by `stdin`|
|`-n`, `--nostrip`|`false`|Trim whitespace from the end of input|
|`-p`, `--print`| |Print the contents of the clipboard to `stdout`|
|`-f`, `--file <arg>`|| Copy file content to clipboard|
|`-s`, `--shell <arg>`|| Run command and copy output to clipboard|

## Examples 

#### Copy the output of an `ls` command to the clipboard.

```bash
> ls -al | cb
```

#### 

#### Copy a file's content directly to the clipboard

```bash
> cb -f filename.txt
```

#### Output the content of the clipboard
```bash
> cb -p
``````
