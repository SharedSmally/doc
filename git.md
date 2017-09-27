git
======

## [Commands](https://git-scm.com/docs)
- clone
- checkin:
-- add the changes
-- commit the changes
-- push the changes
- revert:

## Tips
- Comment out * text=auto in .gitattributes
- Setup Credential
   - $ git config --global user.name "John Doe"
   - $ git config --global user.email johndoe@example.com
   - $ git config --global credential.helper "cache --timeout=3600"
   - $ git config credential.helper store
   - $ git push http://example.com/repo.git
  
    Username: <type your username>
  
    Password: <type your password>
  
    [several days later]
    
  - $ git push http://example.com/repo.git
    
    [your credentials are used automatically]
    
- Clone the repository:
    
    git clone remote_url local_dir
  
- Current changes:
   
   git status 
   
   git diff
   
-  Changes Log

   git log
   
   git show  _id_
   
- Commit changes

   git add file(s)
   
   git commit -m "message"

- Push changes to repository

   git push
   
- Add all modified/untracked

   git add -u: all modified
   
   git add -A:  all untracked
   
   
- Branch

   git branch:  list current branch
   
   git branch -a : list all branches
   
   git branch -r : list active branches
   
   git checkout -b $branchName$:  switch to another branch   
   
   git diff branch_1..branch_2: the diff between the tips of the two branches
   
   git diff branch_1...branch_2:  the diff from the common ancestor to test

- [Merge](https://git-scm.com/book/en/v2/Git-Tools-Advanced-Merging)

   git merge $branchName$
   
   git merge  -Xignore-all-space or -Xignore-space-change  $branchName$ : ignore whitespace and multiple spaces 
   
   git merge --abort:   Abort merge
   
   git status -sb
   
   git reset --hard origin/$branch-name$:  discard local commits and everything in work tree(local files)
   
   git reset HEAD^: uncommit, See [Notes](https://stackoverflow.com/questions/2845731/how-to-uncommit-my-last-commit-in-git)
   
      - git reset --soft HEAD^: undo the act of committing, leave everything else intact
      - git reset HEAD^:  undo the act of committing and everything staged, but leave the work tree (files intact):
      - git reset --hard HEAD^: completely undo it, throw away all uncommitted changes, and reset everything to the previous commit
   
   git log -p -1: see latest commits
   
- Check potential conflicts: 
   make an alias:

    git config --global alias.mergetest '!f(){ git merge --no-commit --no-ff "$1"; git merge --abort; echo "Merge aborted"; };f '

   the call the following to find out if there are any conflicts.

    git mergetest <branchname>

