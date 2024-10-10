# winter24-sft221-nff-6 Project Setup Guide

Welcome to the winter24-sft221-nff-6 project! Before you dive into coding, please follow these setup instructions to ensure a smooth workflow.

## Getting Started

1. **Update to the Latest Code**:

   - Ensure you have the latest version of the code by running:

     ```
     git pull
     ```

2. **Switch to the Correct Milestone Branch**:

- Each milestone in the project has a dedicated branch named mX, where X is the milestone number. Before creating your personal branch, make sure to switch to the correct milestone branch. For example, to switch to the milestone 1 branch:

  ```
  git checkout m1
  ```

3. **Switch to the Correct Branch**:
   - From the milestone branch, create and switch to a new branch for your personal work. The branch should follow the naming convention mX-yourFirstName, where X is the milestone number. For example:
   - To create and switch to your milestone branch, use:
     ```
     git checkout -b m1-hanbi
     ```
   - This command creates a new branch named m1-hanbi based on the milestone 1 branch (m1) and switches to it.

## Before Pushing Your Code

1. **Check Your Current Branch**:

   - Before pushing your changes, always check that you're on the correct branch with:
     ```
     git status
     ```

2. **Pushing Local Changes**:

   - Push your local changes to the remote repository using:
     ```
     git push
     ```
   - If you encounter a message like the following:

     ```
     fatal: The current branch m1-hanbi has no upstream branch.
     To push the current branch and set the remote as upstream, use

     git push --set-upstream origin m1-hanbi
     ```

   - Simply copy and paste the suggested command (`git push --set-upstream origin m1-hanbi`) and press enter to push your changes.

This guide should help you set up and start contributing to the winter24-sft221-nff-6 project smoothly. Happy coding!
