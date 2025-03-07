(merging)=

# Merging changes and contributing to the project

Git allows us to have different development lines where we can try things out.
It also allows different people to work on the same project at the same.  This
means that we have to somehow combine the changes later. In this part we will
practice this: **merging**.

Goals for this section:
- Understand that on GitHub merging is done through a **pull request** (on GitLab: "merge request"). Think
  of it as a **change proposal**.
- Create and merge a pull request within your own repository.
- Understand (and optionally) do the same across repositories, to contribute to
  the upstream public repository.


## Exercise: Merging & contributing to the main repository


::::::{admonition} Exercise: Merging branches
:::::{tabs}
::::{group-tab} GitHub

First, we make something called a pull request, which allows
review and commenting before the actual merge.

We assume that in the previous exercise you have created a new branch with one
or few new commits.  We provide basic hints. You should refer to the solution
as needed.

1. Navigate to your branch from the previous exercise
   (hint: the same branch view we used last time).

1. Begin the pull request process
   (hint: There is a "Contribute" button in the branch view).

1. **(Only GitHub)** Add or modify the pull request title and description, and verify the other data.
   In the pull request verify the target repository and the target
   branch. Make sure that you are merging within your own repository.
   **GitHub: By default, it will offer to make the change to the
   upstream repository, `balmorelcommunity`.  You should change this**, you
   shouldn't contribute your commit(s) upstream yet.  Where it says
   `base repository`, select your own repository.

1. **(Only GitHub)** Create the pull request by clicking "Create pull request". Browse
   the network view to see if anything has changed yet.

1. Merge the pull request, or if you are not on GitHub you can merge
   the branch locally. Browse the network again. What has changed?

1. Find out which branches are merged and thus safe to delete. Then remove them
   and verify that the commits are still there, only the branch labels are
   gone (hint: you can delete branches that have been merged into `main`).

1. Optional: Try to create a new branch with a new change, then open a pull
   request but towards the original (upstream) repository. We will later merge few of
   those.
::::

::::{group-tab} Local (VS Code, Command line)

When working locally, it's easier to merge branches: we can just do
the merge, without making a pull request.  But we don't have that step
of review and commenting and possibly adjusting.

1. Switch to the `main` branch that you want to merge the *other*
   branch into. (Note that this is the other way around from the
   GitHub path).

Then:

5. Merge the other branch into `main` (which is then your current branch).

6. Find out which branches are merged and thus safe to delete. Then remove them
   and verify that the commits are still there, only the branch labels are
   gone. (Hint: you can delete branches that have been merged into `main`).

7. Optional: Try to create a new branch, and make a
   GitHub pull request with your change, and contribute it to our
   upstream repository.
::::
:::::
::::::

The solution below goes over most of the answers, and you are
encouraged to use it when the hints aren't enough - this is by design.


## Solution and walk-through

### (1) Navigate to your branch

Before making the pull request, or doing a merge, it's important to
make sure that you are on the right branch.  Many people have been
frustrated because they forgot this!

:::::{tabs}
::::{group-tab} GitHub
GitHub will notice a recently changed branch and offer to make a pull request (clicking there will bring you to step 3):
   :::{figure} ./img/pull_request.png
   :alt: Screenshot on GitHub suggesting to compare and make a pull request.
   :width: 80%
   :class: with-border
   :::

If the yellow box is not there, make sure you are on the branch you want to
merge **from**:
   :::{figure} ./img/own_branch.png
   :alt: Screenshot on GitHub where we navigate to the branch we wish to merge.
   :width: 80%
   :class: with-border
   :::
::::

::::{group-tab} VS Code
Remember, you need to switch to the `main` branch, the branch we want to merge **to**.
This is different from the GitHub path.
::::

::::{group-tab} Command line
Remember, you need to switch to the `main` branch, the branch we want to merge **to**.
This is different from the GitHub path:
```console
$ git switch main
```
::::
:::::


(create-pull-request)=

### (2) Begin the pull request process

In GitHub, the pull request is the way we propose to merge two
branches together.  We start the process of making one.

:::::{tabs}
::::{group-tab} GitHub
   :::{figure} ./img/contribute.png
   :alt: Screenshot on GitHub where we get to the pull request process.
   :width: 80%
   :class: with-border
   :::
::::

::::{group-tab} VS Code
It is possible to open pull requests from the editor, but
we don't cover that here.

If you are working locally, continue to step 5.
::::

::::{group-tab} Command line
It is possible to open pull requests from the command line, but
we don't cover that here.

If you are working locally, continue to step 5.
::::
:::::


### (3) Fill out and verify the pull request

Check that the pull request is directed to the right repository and branch
and that it contains the changes that you meant to merge.

:::::{tabs}
::::{group-tab} GitHub
Things to check:
- Base repository: this should be your own and not `balmorelcommunity`
- Title: make it descriptive
- Description: make it informative
- Scroll down to see commits: are these the ones you want to merge?
- Scroll down to see th
e changes: are these the ones you want to merge?
   :::{figure} ./img/comparing_changes.png
   :alt: Screenshot on GitHub where we verify the changes we want to merge.
   :width: 80%
   :class: with-border

   This screenshot only shows the top part. If you scroll down, you
   can see the commits and the changes. We recommend to do this before
   clicking on "Create pull request".
   :::
::::

::::{group-tab} VS Code
If you are working locally, continue to step 5.
::::

::::{group-tab} Command line
If you are working locally, continue to step 5.
::::
:::::


### (4) Create the pull request

We actually create the pull request.  Don't forget to navigate to the Network
view after opening the pull request.  Note that the changes proposed in the
pull request are not yet merged.

:::::{tabs}
::::{group-tab} GitHub
Click on the green button "Create pull request".

If you click on the little arrow next to "Create pull request", you can also
see the option to "Create draft pull request". This will be interesting later
when collaborating with others. It allows you to open a pull request that is
not ready to be merged yet, but you want to show it to others and get feedback.
::::

::::{group-tab} VS Code
It is possible to create pull requests from the editor, but
we don't cover that here.

If you are working locally, continue to step 5.
::::

::::{group-tab} Command line
It is possible to create pull requests from the command line, but
we don't cover that here.

If you are working locally, continue to step 5.
::::
:::::


### (5) Merge the pull request

Now, we do the actual merging. We see some effects now.

:::::{tabs}
::::{group-tab} GitHub
Review it again (commits and changes), and then click "Merge pull request".

After merging, verify the network view. Also navigate then to your "main"
branch and check that your change is there.
::::

::::{group-tab} VS Code
Just like with the command line, when we merge we modify our *current* branch.  Verify you are on the `main` branch.

1. Verify current branch at the bottom.
1. From the version control sidebar → Three dots → Branch → Merge.
1. In the selector that comes up, choose the branch you want to merge *from*.
   The commits on that branch will be added to the current branch.
::::

::::{group-tab} Command line
On the command line, when we merge, we always modify our *current* branch.

If you are not sure anymore what your current branch is, type:
```console
$ git branch
```
... or equally useful to see where we are right now:
```console
$ git status
```

In this case we merge the `new-tutorial` branch into our current branch:
```console
$ git merge my-branch
```
::::
:::::


### (6) Delete merged branches

Before deleting branches, first check whether they are merged.

If you delete an un-merged branch, it will be difficult to find the commits
that were on that branch. If you delete a merged branch, the commits are now
also part of the branch where we have merged to.

:::::{tabs}
::::{group-tab} GitHub
One way to delete the branch is to click on the "Delete branch" button after the pull
request is merged. But what if we forgot? Then navigate to the branch view:
   :::{figure} ./img/branch_view.png
   :alt: Screenshot on GitHub where we navigate to the branches view.
   :width: 80%
   :class: with-border
   :::

In the overview we can see that it has been merged and we can delete it.
::::

::::{group-tab} VS Code
From the Source Control sidebar → the three dots (as before) → Branch → Delete Branch.  Select the branch name to delete.
::::

::::{group-tab} Command line
Verify which branches are merged to the current branch:
```console
$ git branch --merged

* main
  my-branch
```

This means that it is safe to delete the `new-tutorial` branch:
```console
$ git branch -d my-branch
```

Verify then that the branch is gone but that the commits are still there:
```console
$ git branch
$ git log --oneline
```
::::
:::::


### (7) Contribute to the original repository with a pull request

This is an advanced step. We will practice this tomorrow and
it is OK to skip this at this stage.

:::::{tabs}
::::{group-tab} GitHub
Now that you know how to create branches and opening a pull request, try to
open a new pull request with a new change but this time the base repository
should be the upstream one.

In other words, you now send a pull request **across repositories**: from your fork
to the original repository.

In case you try to merge into the `main` upstream repository, you will see that you do not have permission for that. This is to protect the repository from unwanted changes. You can still create a pull request, which will then get reviewed from members of the `balmorelcommunity`.
::::

::::{group-tab} VS Code
Not described.

You would create a new branch locally like above, push it to GitHub to your own
user's repository, and from there open a pull request towards the upstream
repository.
::::

::::{group-tab} Command line
Not described.

You would create a new branch locally like above, push it to GitHub to your own
user's repository, and from there open a pull request towards the upstream
repository.
::::
:::::


## Summary

- We learned how to merge two branches together.
- When is this useful? This is not only useful to combine development lines in
  your own work. Being able to merge branches also **forms the basis for collaboration**.
- Branches which are merged to other branches are safe to delete, since we only
  delete the "sticky note" next to a commit, not the commits themselves.
