# Welcome to Weather app contributing guide

:+1::tada: First off, thanks for taking the time to contribute! :tada::+1:

The following is a set of guidelines for contributing to Weather app and its packages,
which are hosted in the [nino-kin Organization](https://github.com/nino-kin) on GitHub.
These are mostly guidelines, not rules. Use your best judgment, and feel free to
propose changes to this document in a pull request.

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

- [Quick Links](#quick-links)
- [Code of Conduct](#code-of-conduct)
- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Making Changes](#making-changes)
  - [Making Trivial Changes](#making-trivial-changes)
  - [Report bugs using GitHub's issues](#report-bugs-using-githubs-issues)
  - [Testing](#testing)
- [Style Guides](#style-guides)
  - [Naming Git Branches](#naming-git-branches)
    - [Use Separators](#use-separators)
    - [Start Name with Category Word](#start-name-with-category-word)
    - [Avoid Long Branch Names](#avoid-long-branch-names)
  - [Git Commit Messages](#git-commit-messages)
  - [Documentation](#documentation)
- [License](#license)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->

## Quick Links

Docs:

- [User Guide](docs/getting_started.md)
<!-- - [Roadmap]() -->

Bugs:

- [Issue tracker](https://github.com/nino-kin/car-app/issues)

## Code of Conduct

This project and everyone participating in it is governed by the [Code of Conduct](CODE_OF_CONDUCT.md).
By participating, you are expected to uphold this code. Please report unacceptable
behavior to [nino-kin@github.com](mailto:nino-kin@github.com).

We have an official message board with a detailed FAQ and where the community chimes
in with helpful advice if you have questions.

- [GitHub Issues](https://github.com/nino-kin/craft/issues)

## Getting Started

We use [GitHub](https://github.com/nino-kin/car-app) to host code, to track issues
and feature requests, as well as accept pull requests.

### Installation

Learn how to set up and use this application locally following [the instructions](docs/getting_started.md).

### Making Changes

Pull requests are the best way to propose changes to the codebase
(we use [GitHub Flow](https://docs.github.com/en/get-started/quickstart/github-flow)).
We actively welcome your pull requests:

1. Fork the repo and create your branch from master. (e.g. `feature/<description>`,
   `bugfix/<description>`, etc.)
2. If you've added code that should be tested, add tests.
3. If you've changed APIs, update the documentation.
4. Ensure the test suite passes.
5. Make sure your code lints.
6. Issue that pull request!
7. Get review by [code owners](.github/CODEOWNERS).

### Making Trivial Changes

For changes of a trivial nature, it is not always necessary to create a new ticket
in _GitHub Issues_. In this case, it is appropriate to create a new branch like `trivial/<description>`
and start the first line of a commit with one of `docs` or `chore`.

If a issue ticket exists for the documentation commit, you can include it after
the `docs` token.

For commits that address trivial repository maintenance tasks or packaging issues,
start the first line of the commit with `chore`, respectively.

### Report bugs using GitHub's issues

We use GitHub issues to track public bugs. Report a bug by [opening a new issue](https://github.com/nino-kin/car-app/issues)
if one does not already exist; it's that easy!

- Clearly describe the issue including steps to reproduce when it is a bug
  (with detail, background, and sample code).
- Make sure you fill in the earliest version that you know has the issue.
- A ticket is not necessary for trivial changes.

### Testing

We use [GoogleTest](http://google.github.io/googletest/) for testing.
If you made any changes, you shall add or update tests as necessary.

## Style Guides

### Naming Git Branches

#### Use Separators

When writing a branch name, using separators such as hyphen (-) or slash (/) helps
to increase readability of the name. But remember to be consistent with the chosen
separator for all branches names.

Example:

```console
feature/weather-data-collection
trivial/fix-typos
```

#### Start Name with Category Word

It is recommended to begin the name of a branch with a **category word**, which indicates
the type of task that is being solved with that branch. Some of the most used
**category words** are:

| Category Word | Meaning                                                                  |
| ------------- | ------------------------------------------------------------------------ |
| hotfix        | for quickly fixing critical issues, usually with a temporary solution    |
| bugfix        | for fixing a bug                                                         |
| feature       | for adding, removing or modifying a feature                              |
| trivial       | for adding, removing or modifying a stuff (**NOT** linked issue tickets) |
| test          | for experimenting something which is not an issue                        |

#### Avoid Long Branch Names

As much as the branch name needs to be informative, it also needs to be precise
and short. Detailed and long names can affect readability and efficiency.

### Git Commit Messages

Follow [the commit conventions](https://www.conventionalcommits.org/en/).
We recommend setting [`.gitmessage`](https://github.com/nino-kin/craft/blob/main/.gitmessage)
as the commit template.

- Use the present tense ("Add feature" not "Added feature")
- Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
- Limit the first line to 72 characters or less
- Reference issues and pull requests liberally after the first line
- When only changing documentation, include `[ci skip]` in the commit title
  (see [here](https://docs.github.com/en/actions/managing-workflow-runs/skipping-workflow-runs))

### Documentation

- Use [Markdown](https://www.markdownguide.org/).
- [User Guide](docs/getting_started.md) is generated by [MkDocs](https://www.mkdocs.org/)
- Use the theme of [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/)

## License

By contributing, you agree that your contributions will be licensed under its
MIT License.
