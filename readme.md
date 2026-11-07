# **C**-age (read as cage)

Lightweight Container runtime for linux implemented in C (just like god intended)

`cage` is a learning project focused on understanding the Linux primitives behind containerization. It creates isolated processes using Linux namespaces and executes commands within them.

## Current Features

- **PID namespace isolation:** Runs child processes in a separate PID namespace.
- **Command execution:** Executes user-specified commands using `execvp()`.
- **Process management:** Creates and waits for isolated child processes using `clone()` and `waitpid()`.
- **Argument handling:** Passes command-line arguments to the executed process.

## Getting Started

### Requirements

- Linux
- GCC
- GNU Make
- Permissions to create PID namespaces

### Build

Clone the repository:

```bash
git clone https://github.com/simplycode07/cage.git
cd cage
```

Compile the project:

```bash
make
```

Clean build artifacts:

```bash
make clean
```

## Usage

Run a command inside a new PID namespace:

```bash
sudo ./container run /bin/echo "Hello world"
```

Launch a shell:

```bash
sudo ./container run /bin/sh
```

Execute a shell command:

```bash
sudo ./container run /bin/sh -c "echo hello world"
```

Inspect the process ID from inside the namespace:

```bash
sudo ./container run /bin/sh -c 'echo "Container PID: $$"; sleep 5'
```

The first process created in a new PID namespace receives PID `1`, while the host sees it using its PID in the host namespace.

## Architecture

At a high level, `cage` uses the following execution flow:

1. The CLI receives a command and its arguments.
2. The runtime allocates a stack for the child process.
3. `clone()` creates a child process with `CLONE_NEWPID`.
4. The child executes the requested command using `execvp()`.
5. The parent waits for the child using `waitpid()`.

### Project Structure

```text
cage/
├── Makefile
├── include/
│   └── container.h
└── src/
    ├── main.c
    └── container.c
```

## Technical Details

- **Language:** C
- **Platform:** Linux
- **Process creation:** `clone()`
- **Isolation:** Linux PID namespaces
- **Command execution:** `execvp()`
- **Process synchronization:** `waitpid()`
- **Memory management:** `mmap()`

## Roadmap

- [x] Improve process lifecycle management and exit-status propagation.
- [x] Add UTS namespace isolation.
- [ ] Add mount namespace isolation.
- [ ] Implement filesystem isolation.
- [ ] Integrate cgroups v2 for resource management.
- [ ] Explore network namespace isolation.
- [ ] Add integration tests for namespace isolation.

## Limitations

`cage` is currently an experimental learning project, not a production container runtime.

- It does not currently provide complete filesystem isolation.
- Resource limits through cgroups are not implemented.
- Network isolation is not implemented.
- It does not provide production-grade security boundaries for untrusted workloads.

## References

- [Linux namespaces — man7](https://man7.org/linux/man-pages/man7/namespaces.7.html)
- [clone(2) — Linux manual](https://man7.org/linux/man-pages/man2/clone.2.html)
- [exec(3) — Linux manual](https://man7.org/linux/man-pages/man3/exec.3.html)
- [waitpid(2) — Linux manual](https://man7.org/linux/man-pages/man2/waitpid.2.html)
- [Linux cgroup v2 documentation](https://www.kernel.org/doc/html/latest/admin-guide/cgroup-v2.html)

---

*Built as an exploration of Linux process isolation and the fundamentals of container runtimes.*
