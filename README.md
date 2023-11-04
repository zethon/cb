# cb

This is a small utility which makes interacting with the clipboard from the command line easier. Output can be directed to the `cb` utility which gets copied to the system's clipboard.

## Usage

#### Copy the output of an `ls` command to the clipboard.

```bash
> ls -al | cb
```

#### Copy a file's content directly to the clipboard

```bash
> cb -f filename.txt
```

#### Output the content of the clipboard
```bash
> cb
```

#### Print current version of cb
```bash
> cb --version
```

#### Print help
```bash
> cb --help
```