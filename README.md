# Todo — a minimal command-line todo manager in C

A small, dependency-free todo manager written in C. Tasks are stored in a plain-text file in your home directory — no database, no server, no JSON.

## Features

- Add, list, complete, undo, edit, and delete tasks
- Priorities (low / medium / high)
- Due dates
- Tags
- Search and stats
- `--json` output for scripting
- Exit codes for use in shell scripts

## Requirements

- A C compiler (gcc or clang)
- `make`

## Build

```sh
make
```

The binary lands in the project root as `todo`. To install system-wide:

```sh
sudo make install
```

## Usage

```sh
todo add "Buy groceries" -p high --due 2026-09-10
todo list
todo list --status pending --tag work
todo done a1b2c3
todo undo a1b2c3
todo edit a1b2c3 --text "Buy milk and eggs"
todo delete a1b2c3
todo search "grocer"
todo stats
```

## Commands

| Command | Description |
|--------|-------------|
| `add` | Create a new task |
| `list` | Show tasks, optionally filtered by status or tag |
| `done` | Mark a task complete |
| `undo` | Re-open a completed task |
| `edit` | Change a task's text, priority, or due date |
| `delete` | Remove a task |
| `search` | Find tasks matching text |
| `stats` | Show counts by status and priority |

## Storage

Tasks live in a single plain-text file at `~/.todo/tasks`. Each line is one task, with fields separated by `|`:

```
id|status|priority|due|text
a1b2c3|0|2|2026-09-10|Buy groceries
```

The file is written atomically (temp file + rename), so a crash won't corrupt your list. Back up by copying that one file.

## Exit Codes

| Code | Meaning |
|-------|---------|
| `0` | Success |
| `1` | Runtime error (e.g. task not found) |
| `2` | Usage error (bad flags or unknown command) |

## Development

```sh
make test    # run the test suite
```

Build with address sanitizer to catch memory bugs during development:

```sh
make CFLAGS="-Wall -Wextra -std=c11 -g -fsanitize=address,undefined"
```

## Project Layout

```
src/        source files (main, cli, store, task, render, util)
include/    shared headers
tests/      test suite
Makefile    build script
```

## License

MIT
