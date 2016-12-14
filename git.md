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
   
   
