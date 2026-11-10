(branching)=

# Creating branches and commits

The first and most basic task to do in Git is **record changes** using
commits. In this part, we will record changes in two
ways: on a **new branch** (which supports multiple lines of work at once), and directly
on the "main" branch (which happens to be the default branch here).

The goal is to:
- Record new changes to our own copy of Balmorel.
- Understand adding changes in two separate branches.
- See how to compare different versions or branches.


## Background

- Each **commit** is a snapshot of the entire project at a certain
  point in time and has a unique identifier (**hash**) .
- A **branch** is a line of development, and the `main` branch or `master` branch
  are often the default branch in Git.
- A branch in Git is like a **sticky note that is attached to a commit**. When we add
  new commits to a branch, the sticky note moves to the new commit.
- **Tags** are a way to mark a specific commit as important, for example a release
  version. They are also like a sticky note, but they don't move when new
  commits are added.

## Exercise: Creating branches and commits

:::{admonition} Exercise: Practice creating commits and branches (20 min)
1. First create a new branch and then modify an
   existing file and commit the change.  Make sure that you now work **on your
   copy** of the repository. You can for example change the years in the simulation by editing the `Y.inc` file.
1. Switch to the `main` branch and create a commit there.
1. Browse the network and locate the commits that you just created ("Insights" -> "Network").
1. Compare the branch that you created with the `main` branch. Can you find an easy way to see the differences?
:::

The solution below goes over most of the answers, and you are
encouraged to use it when the hints aren't enough - this is by
design.


## Solution and walk-through


### (1) Create a new branch and a new commit

:::::{tabs}
::::{group-tab} GitHub
1. Where it says "main" at the top left, click, enter a new branch
   name (e.g. `new-tutorial`), then click on
   "Create branch ... from main".
1. Make sure you are still on the `new-tutorial` branch (it should say
   it at the top), and click "Add file" → "Create new file" from the
   upper right.
1. Changes some file.
1. Click "Commit changes"
1. Enter a commit message. Then click "Commit
   changes".

You should appear back at the file browser view, and see your
modification there.
::::

::::{group-tab} VS Code
1. Make sure that you are on the main branch.
1. Version control button on left sidebar → Three dots in upper right of source control → Branch → Create branch.
1. VS Code automatically switches to the new branch.
4. Changes some file.
4. In the version control sidebar, click the `+` sign to add the file for the next commit.
4. Enter a brief message and click "Commit".
::::

::::{group-tab} Command line
Create a new branch called `my-branch` from `main` and switch to it:
```console
$ git switch --create my-branch main
```

Then change a file. Finally add and commit the file:
```console
$ git add Y.inc  # or a different file name
$ git commit -m "Changing the years"
```
::::
:::::



### (2) Switch to the main branch and create a commit there

:::::{tabs}
::::{group-tab} GitHub
1. Go back to the main repository page (your user's page).
1. In the branch switch view (top left above the file view), switch to
   `main`.
1. Modify another file that already exists, following the pattern
   from above.
::::

::::{group-tab} VS Code
Use the branch selector at the bottom to switch back to the main branch.  Repeat the same steps as above,
but this time modify a different file.
::::

::::{group-tab} Command line
First switch to the `main` branch:
```console
$ git switch main
```

Then modify a file. Finally `git add` and then commit the change:
```console
$ git commit -m "short summary of the change"
```
::::
:::::


### (3) Browse the commits you just made

Let's look at what we did.  Now, the `main` and the new branches
have diverged: both have some modifications. Try to find the commits
you created.

:::::{tabs}
::::{group-tab} GitHub
Insights tab → Network view (just like we have done before).
::::

::::{group-tab} VS Code
This requires an extension.  Opening the VS Code terminal lets you use the
command line method (View → Terminal will open a terminal at bottom).  This is
a normal command line interface and very useful for work.
::::

::::{group-tab} Command line
```console
$ git graph
$ git log --graph --oneline --decorate --all  # if you didn't define git graph yet.
```
::::
:::::


### (4) Compare the branches

Comparing changes is an important thing we need to do.  When using the
GitHub view only, this may not be so common, but we'll show it so that
it makes sense later on.

:::::{tabs}

::::{group-tab} GitHub
A nice way to compare branches is to add `/compare` to the URL of the repository,
for example (replace USER):
https://github.com/**USER**/Balmorel/compare
::::

::::{group-tab} VS Code
This seems to require an extension.  We recommend you use the command line method.
::::

::::{group-tab} Command line
```console
$ git diff main my-branch
```

Try also the other way around:
```console
$ git diff my-branch main
```

Try also this if you only want to see the file names that are different:
```console
$ git diff --name-only main my-branch
```
::::
:::::


## Summary

In this part, we saw how we can make changes to our files.  With branches, we
can track several lines of work at once, and can compare their differences.

- You could commit directly to `main` if there is only one single line
  of work and it's only you.
- You could commit to branches if there are multiple lines of work at
  once, and you don't want them to interfere with each other.
- In Git, commits form a so-called "graph". Branches are tags in Git function
  like sticky notes that stick to specific commits. What this means for us is
  that it does not cost any significant disk space to create new branches.
- Not all files should be added to Git. For example, temporary files or
  files with sensitive information or files which are generated as part of
  the build process should not be added to Git. For this we use
  `.gitignore`.
- Unsure on which branch you are or what state the repository is in?
  On the command line, use `git status` frequently to get a quick overview.
