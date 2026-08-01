# Contributing to Love-Mind Lang

First off, thank you for considering contributing to Love-Mind Lang! It's people like you that make this tool better for everyone.

## 1. Getting Started & Environment Setup

To build and test the project locally, you will need a standard C build environment along with a few specific dependencies.

### Dependencies
- A C23-compatible compiler (e.g., `gcc` or `clang`)
- `make`
- `libedit` (for the interactive REPL)
- `cunit` (for running the test suite)
- `clang-format` (for code formatting)

**On Arch Linux:**
```bash
sudo pacman -S base-devel libedit cunit clang
```

**On Debian / Ubuntu:**
```bash
sudo apt-get update
sudo apt-get install build-essential libedit-dev libcunit1-dev clang-format
```

Once installed, you can build the project by running:
```bash
make build
```

---

## 2. Branching & Pull Requests

We use a feature-branch workflow. Please follow these steps for any contributions:

1. **Create a Feature Branch:** Do not commit directly to `main`. Create a new branch for your work:
   ```bash
   git checkout -b feat/add-new-directive
   ```
2. **Work and Commit:** Make your changes and commit them using the Conventional Commits standard (see below).
3. **Squash Merge:** When your Pull Request is approved, it will be squash-merged into the `main` branch to keep the history clean and readable.

---

## 3. Commit Message Standards

We strictly follow the [Conventional Commits](https://www.conventionalcommits.org/) specification. This helps us automatically generate changelogs and makes it easy to understand the project history.

Your commit messages should look like this:
```
<type>: <short summary>
```

**Common Types:**
- `feat:` A new feature or parser directive.
- `fix:` A bug fix in the parsing logic or application.
- `docs:` Documentation changes (like updating `SYNTAX.md`).
- `style:` Formatting changes that do not affect logic.
- `refactor:` Code changes that neither fix a bug nor add a feature.
- `test:` Adding missing tests or correcting existing ones.

*Example:* `feat: add support for the .define directive`

---

## 4. Code Formatting & Testing Requirements

Before opening a Pull Request, you **must** ensure that your code is properly formatted and passes all tests.

1. **Format the code:** We use `clang-format` to maintain a consistent style. Run the following command to format your code automatically:
   ```bash
   make format
   ```
2. **Run the tests:** Ensure that your changes haven't broken any existing functionality and that any new features are covered by tests:
   ```bash
   make test
   ```

If your Pull Request fails the formatting check or the test suite, it will not be merged. Please ensure both `make format` and `make test` exit cleanly locally!
