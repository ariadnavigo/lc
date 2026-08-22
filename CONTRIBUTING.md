# How to Contribute to lc

Contributing to lc is easy. This is a small project, so the requirements are
simple.

## Non-Code Contributions: Ideas, Bug Reports, etc.

If your contribution isn't code, open an Issue! All that is asked is that you
clearly state:

- What is the current situation that you believe must change?
- What do you think should change and how?
- Give as much context as possible.

Don't be shy!

## Code Contributions

Basic requirements are as follow:

- Always branch from _main._
- Follow the [Conventional Commits specification][convcom] for your commit
  messages.
- Format code with [_clangd_'s][clangdweb] formatter. Refer to your editor's
  documentation on how to install the LSP and enable the formatter.
- Don't bother with rebasing or "clean git history" (see a discussion about this
  [here][gitrant]). git is smarter than people give it credit. Code quality is
  much more important.

If some change implies radically changing huge chunks of the code or the
direction of the project, please discuss it first as an Issue.

## Some Obvious Stuff

Be respectful and be nice to others. Communicate before acting. Respect the
license of the project and other projects' licenses if you're reusing code from
somewhere else.

AI? Be reasonable. You can use it, but be open about it and _read_ the generated
code first.

## _Fin_

This is about having fun, learning, and creating something nice and simple in
the process. Keep that always in mind :)

And thank you for your contributions and interest!

[convcom]: https://www.conventionalcommits.org/
[clangdweb]: https://clangd.llvm.org/
[gitrant]: https://lucasoshiro.github.io/posts-en/2024-04-08-please_dont_squash/
