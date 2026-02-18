# Notes from programmer:
* Code will be documented with doc strings. These will be started
  using snippets within vscode and/or emacs

* emacs & vscode have extension to commit using 

    set -x
    d=$(date "+%Y-%m-%d %H:%M:%S")
    msg="Commit: ${d}"
    git add . 
    git commit -a -m "${msg}"


* Initial directory created by cookiecutter cpp, some files may
  contain things I'll throw away.

* Code will be intermittently checked into git to allow free editing
  and hacking on solution(s). `commit.sh` - does checking with timestamp.

* `TODO` comments to inform reader that code isn't as robust as it
  could be, or that it could be developed further.

* `CHW` comments (my initials) are left as place holders for me while
  I'm programming.

* Makefile is for convenience, usually this would be a Justfile, not
  assume that is on reviewer's machine 
