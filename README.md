# CLIKVStore
A simple key value store for shell scripts.

Current there is a flaw in the retrieving function causing the tool not to display setted and succesfully saved entries. It will fixed soon.

## How to build

To build the tool simple run: ```make```

## Install system wide

How to install the tool system wide: Run ```make install``` to install it to the directory /usr/local/bin

## How to use

For the following commands, you should replace these variable names with values appropriate for you:

```FILE``` is the file to store the entries. By default it is stored in the current working directory.

```KEY``` ist the signifier to identify entries.

```VALUE``` is the value associated with the key.

How to add keys: ```./clikv FILE set KEY VALUE```

How to get keys: ```./clikv FILE get KEY```

How to search if a key exists: ```./clikv FILE search KEY```

## Limitations

Keys can contain any character exept the new line character (U+000A) and the white space character (U+0020).

Values can contain any character exept the new line character (U+000A).