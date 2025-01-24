# Summary of Git commands


## Basic commands  

- git init  
- git status  
- git add ``FILE_NAMES``  

## File Status  

1. Before add  
    Files in the working directory 
2. Added  
    Files in the staging area  
3. Commited   
    Files in the local repository  
4. Pushed   
    Files in the remote server repository  

## Reset  

- git reset ``commit_id``  
    Remove all commits after the given commit_id and make HEAD point to the given commit_id.  
    Working files are not changed, only commits.  
- git reset --hard ``commit_id``  
    git reset ``commit_id`` + working directory also reset to the given commit_id.  
- git reset ``FILE_NAMES``   
    Undo added files  

## Commit  

- git commit [FILE_NAMES]  
- git commit -m "WITH UR COMMENTS..." [FILE_NAMES]  
- git commit -a -m "WITH UR COMMENTS..." [FILE_NAMES]  
    git add [FILE_NAMES] + git commit -m "WITH UR COMMENTS..." [FILE_NAMES]  
- git commit --amend  
    You can redo ur previous commit, modifying commit msg or adding commit files.  
    But you can't redo before the second or more commit.  

## Log    

- git log  
- git log --oneline   
    summerize git log to line by line.  

## Branch  

- git branch  
    See all the exsist local branches.  
- git branch -a  
    See all the exsist branches.  
- git branch harry  
    Make branch named "harry"  
- git branch -M main  
    Change currrent branch name to "main"
- git branch -d harry  
    Delete harry branch  
    If you do this with -D instead of -d, then it means force delete.  
- git branch -r  
    It shows **remote tracking branch** with "[REMOTE_NAME]/[BRANCH]" text template.  
    - remote tracking branch  
          you can commit some changes to main branch without push to your server repo.  
          Then the main branch at the server is not the same with your local main branch.  
          "git branch -r" only shows you the server base branch, not the local branch.  

## Switch  

- git switch harry (or git checkout harry)   
    Change current branch to "harry"  
- git switch -c lily   
    git branch lily & git switch lily  
- git switch -  
    Back to HEAD so that restore current state  

## Merge  

- git merge harry  
    Merge the harry branch into the current branch, for example, if you stay on the main branch and run "git merge harry", the code in the harry branch will be merged into the main branch.
- git merge --abort  
    Abort the merge if a conflict occurs in the merge state.

## Conflict resolution    

1. git add [CONFLICTED_FILES]  
2. git commit -m "Conflict is resolved..."  

## Diff  

- git diff [FILE_NAMES]  
    Working Directory <--> edited Working Directory  
- git diff branch_1 branch_2  
    shows the result of comparison between Repository of branches.
- git diff commit_id_1 commit_id_2  
    shows the result of comparison between commits.
- git diff --staged [FILE_NAMES] (or git diff --cached [FILE_NAMES])  
    Working Directory <--> Staging Area
- git diff HEAD [FILE_NAMES]  
    Working Directory and Staging Area <--> Repository
- git diff [TAG_1] [TAG_2]  
    compare two different tags

## Stash  

- git stash  
    save all the state of files (added or not, it doesn't matter) about staging or not when you switch branch
- git stash list  
    show stash stack
- git stash pop  
    If you return from the other branches, you can load and apply stash to current branch from this command, and that stash literally poped
- git stash apply  
    you can apply latest stash without poping it. you can reuse stash to other branch.
- git stash apply stash@{2}  
    apply specific stash (you can get the stash id from "git stash list" command)
- git stash drop stash@{2}  
    remove specific stash
- git stash clear  
    remove all the stash list

cat .git/HEAD -> show git head info in linux

## Checkout  

- git checkout commit_id  
    Make all the state of files back to specific commit state (detached HEAD state).
    In detached HEAD state by checkout, Back to HEAD (use "git switch -" to restore current state.)  
- git checkout HEAD~1  
    Go back right before HEAD commit. (if "HEAD~2", It means second before.)  
- git checkout HEAD dog.txt (or git checkout -- dog.txt)  
    revert dog.txt file to HEAD commit state. (HEAD is not detached by this command)  
- git checkout [REMOTE_NAME]/[BRANCH]  
    Go back to server branch state of code, which means you can use this command to go most recently pushed state.  
- git checkout [TAG]  
    Go back to specific tag  

## Restore  

- git restore dog.txt  
    Revert dog.txt file to HEAD commit state.
- git restore --source HEAD~2 dog.txt  
    Revert dog.txt file to HEAD~2 commit state.  
- git restore --staged [FILE_NAMES]  
    Undo added files 

git revert commit_id -> almost same as "git reset commit_id", but revert donsn't delete commits, instead of that, it create new reverted commit with commit msg (or without msg). so commit info of given commit_id is still there.

git clone [URL] -> get the code and git history from given url (this make a directory named in repo to current location and all the content are in that directory), you should know only the master or main branch is downloaded from server. if you want to download branch1 too, then you can simply do that with "git switch branch1" command (or "git checkout -b branch1 origin/branch1"), in this case git make local branch "branch1" and connect it with "origin/branch1" which is in the server repo.

## Remote  

- git remote add [REMOTE_NAME] [URL]  
    connect specific git project with specific url (git or bitbucket or gitlab whatever you want), 'origin' is recommanded value to put as remote name arg.
    ex) git remote add origin https://github.com/tongmon/qt-frameless-windows
- git remote -v  
    see remote list
- git remote remove  
    remove url connection from specific repo
- git remote rename [OLDNAME] [NEWNAME]
    change remote name

## Push  

- git push [REMOTE_NAME] [BRANCH]  
    ex) git push origin master, upload the code to remote server, you should push always after commits if you want to apply some changes to your own server repo.
- git push origin branch1:master
    upload code in local branch1 to server repo branch master, intuitively it means branch1 -> master
- git push -u origin branch1  
    if your current local branch is branch1, you can use "git push" without [REMOTE_NAME] and [BRANCH]. git automatically connect local branch1 with server repo branch1
- git push -u origin branch1:branch2  
    this is not recommanded. link the local branch1 with server repo branch2, so if you use "git push" changes in branch1 are automatically uploaded to server repo branch2
- git push [REMOTE_NAME] [TAG]  
    push created tag
- git push [REMOTE_NAME] --tags  
    push all created tags

## Fetch  

- git fetch [REMOTE_NAME]  
    fetch all branches. fetch apply changes from server repo to your local repo but not integrate with your local code changes. your local code changes remain as local branch but fetched local branches is sync with newest origin/[BRANCH_NAME]. so in this case, if you want to see the newest fetched changes, you can do that with "git checkout origin/[BRANCH_NAME]" command cause your local branch is still stay at your work. this command also can be use in feching new branches.  
- git fetch [REMOTE_NAME] [BRANCH]  
    fetch specific branch  

## Pull  

- git pull [REMOTE_NAME] [BRANCH]  
    git fetch + git merge, so this can generate conflict some files, you can solve that with the solution that used in merge, like resolve conflict code files and add that files and commit again but also in this case you should do push too.
- git pull  
    pull the code from origin/current_branch  

Add collaborator in github project
enter the github page -> choose specific repository -> settings -> manage access -> invite a collaborator -> enter username or email

What is gist.github.com
Gist can be use to share part of your code or guide markdown documents.

Pull Request (PR)
Open the discussion for some feature branches which is about to merge by branch charger.
select specific branch -> click "pull request"
If there is a conflict when you do a pull request, you can modify code via github desktop app or view the command line guide via clicking "command line instructions" link. (and follow up the guided commands)

Branch protection rules -> changes to "Rulesets"
you can force protected branch name to be in specific template with this.
you can set options for protected branch, something like there must be at least 2 approved reviewers in the pull request to be merged.
also there is an option for making collaborators can't commit directly to protected branch rather they should open pull request to merge other branches.

Forking
Fork -> copy other project and make it to your own repo
forked repo 1 ==> upstream repo (base repo) <== forked repo 2
forked repo can pull from upstream repo. (this can be done after executing the "git remote add upstream [BASE_REPO_URL]" command and "git pull upstream [BRANCH]")
owner of forked repo can make pull request for merging upstream repo cause owner of forked repo is usually not in upstream repo collaborator list so can't push directly to upstream repo.

So there is two ways to collaborate repository with others.
1. With forked repo
2. Add collaborators in repo
   
there is two ways to integrate branch in git
1. merge -> parralle way, every time when you merge, merge commit log is created
2. rebase -> linear way, there is no log creation when you rebase branch

There are some cases that you need to merge the main branch frequently, to update new things from the others work to your own feature branch.
Every time you merge the main branch to apply new code to your own feature branch, a merge commit log is generated, and that can be annoying.
Unlike merging, rebasing doesn't create logs when you rebase, rebasing just extent logs of your own feature banch after logs of main branch (not only main, any target branch can be located).

git rebase [BRANCH] -> do rebase, if your current branch is "branch1" and you execute the "git rebase main" command, and then log structure of "branch1" is changed, logs of main branch are shown first and logs of "branch1" are shown next, so log structure looks like linear. simply what "git rebase main" command does is making base of "branch1" to "main", just re - base. rebase make merge to be fast foward merge. so merge after rebase doesn't create any logs.
git rebase --abort -> cancel rebase when conflict is happened in rebasing.
git rebase --continue -> after resolve conflict and add conflict resolved files, you can continue rebase with this command (there is not commit process, just add --> continue)
git rebase -i HEAD~4 -> show commit message from HEAD to HEAD~4 that user want to modify, then git will show you 4 logs with command guideline (pick, reword, edit... etc), the default state is "pick" for example there is 4 lines something like "pick 519aaf3 add basic navbar feature". if you change "pick" word in specific line and save the file then you can modify some commit message of selected line.

option for rebase "-i" mode
1. pick -> leave it, don't change
2. reword -> change commit message
3. drop -> remove commit, not only message but also code content is removed.
4. fixup -> remove selected commit message and selected commit code content is moved to previous commit. after this process commit id after this commit are changed
5. squash -> like fixup, remove selected commit message and selected commit code content is moved to previous commit. but this time selected commit message is integrated with previous commit message.
6. edit -> change commit message and commit code content, this is just like git time machine, HEAD is move to selected commit id so you should do "git commit --amend" and if you done editing, just do "git rebase --continue" to finish edit rebase.

Never rebase commits that have been shared with others.
Just use rebase only in your own feature branch.
When you use rebase in branch that two or more people work with, here is some problem scenario.
I called it "G branch". A rebase "G branch" with main. so history of "G branch" is totally changed.
After that rebase happened, B push some code to "G branch". in this situation A's local computor don't have B's pushed code.
A want to push rebased branch code but A can't cause A's G branch history is diff from G branch B's history.
In this moment, if A push the code with "-f" force option, A's work and rebase will push succesfully but B's work will just be gone... B will upset because of that.

In any case, even you use rebase, you need to use merging to integate your branch to main branch.
but once you rebase your own branch and merge after that, that merge is fast-foward merge so that merge commit log is not created.

semantic versioning
famous versioning rule and good for git tag versioning
template -> major_rel.minor_rel.patch_rel ==> 1.0.0 is initial version
patch_rel -> small patches, bug fix, very minor patch, there should be no new feature, don't surprise users, frequently happened
minor_rel -> middle changes, new feature is optional but there should be no breaking changes, if this up, have to reset patch_rel number
major_rel -> breaking changes, previous version may not compatible, some feature can be deleted, if this up, have to reset minor_rel, patch_rel number

Tagging
sticky note for commit history.
Many users use it as tag release version.
tag name should be unique.
tags are not pushed as default, so when you clone or fork some repo, you need to push exsisting tags to your own remote repo

lightweight tag -> only name and lable can be exsisted in this tag type.
annotated tag -> author, email, date, messages etc many datas can be contained in this tag types.

git tag -l -> show all tags in repo
git tag -l "*beta*" -> show tags that contain beta text, you can write down your own filter with wild cards what ever you want
git tag [NEW_TAG_NAME] -> create new lightweight tag
git tag -a [NEW_TAG_NAME] -> create new annotated tag, if you do this, editor will open to write down some data for tag
git tag [NEW_TAG_NAME] [COMMIT_ID] -> create new lightweight tag at selected commit id
git tag -f [TAG] [COMMIT_ID] -> move exsisting tag to other commit point
git tag -d [TAG] -> delete exsisting tag

git show [TAG] -> show info about selected tag

Reflog -> when you change HEAD or move branch or commit, git record that in specific log file, devs call it as "reflog", so we can use that file to restore problems, but reflog is deleted after 90 days and refreshed, also reflog is local file, you can't know about other collaborator's reflog data. reflog is manage by branch pointer, so if you have 2 branches there are 3 reflogs (HEAD, branch 1, branch 2), reflog index is looks like this "[HEAD | BRANCH]@{index}", so most recent reflog line in HEAD should be "HEAD@{0}", reflog line could shows commit message or branch moving message or rebase message or whatever every move you made in git. as a result, you can undo every move by using reflog file

reflog qualifiers is like below
HEAD@{0}
branch1@{2.days.ago}
main@{one.week.ago}
main@{yesterday}
main@{two.minute.ago}

git reflog show [HEAD | BRANCH] -> show the log of a specific reference, it just shows reflog 

git checkout HEAD@{2} -> this is different from "git checkout HEAD~2", this means go back to state when reflog HEAD@{2} point
git diff HEAD@{2} HEAD@{4} -> compare reflog states
git reset --hard master@{2} -> you can restore mistake by using reset command with timestamp in reflog. you can time warp to master@{2} timestamp and head of master branch is going to be master@{2}. all the timestamp in reflog contains other branch relationships so you can even restore "rebase -i" command

Modify git config file
.git/config -> git configuration setting is located in that file. there are many config file preset out there made by git users, you can use others config file, applying other's color setting or work setting is useful and funny, you can see all of the config manual in https://git-scm.com/docs/git-config 
.gitconfig -> global git config file

all of the commands below can be done by modifing config file manually.
git config user.name -> print "name" entry in [user] section which written in global git config file
git config --global user.name -> print "name" entry in [user] section which written in global git config file
git config --local user.name "some name" -> change user name in this local repo to "some name"
git config user.name "some name" -> change user name to "some name" globaly in git
git config user.email "tongstar@nate.com" -> change user email to "tongstar@nate.com"

Setting git alias
you can set and save specific command shortcut by modifing the git config file

below is git config file
```
[alias]
    s = status
    l = log --oneline
    cm = commit -m
```
if your git config file is like above, "git s" is same as "git status", "git l" is same as "git log --oneline"
Of course, you can modify config file with git command something like ```git config --global alias.s "status"```
Command shortcut that require some args is just same, ```git cm "My msg"``` is same as ```git commit -m "My msg"```

you can write complicated command in alias like below
```
[alias]
    la = "!git config -l | grep alias | cut -c 7-"
```
```!``` means it is a bash command, not just git command
"git la" shows all of the alias command shortcut list to users.


I need to reorganize this file to upload to your own feature website. by tongstar