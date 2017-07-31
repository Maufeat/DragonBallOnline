# Dragonball Online
Source Code for the Korean Client 0.50

# Working with DBO
Our goal is to implement features that the TAIWAN Client has, like flying.
But I will also try to implement complete new features.
There is currently NO SERVER, all is done with the internal virtual server.
Join my Discord for this project: https://discord.gg/Ybwd2yy

# Development flow
1. Pull latest version of master
    * `git fetch -p`
    * `git pull origin master`
2. Checkout to a new branch
    * `git checkout -b <branch_name>`
3. Make changes, do commits
    * `git status` - List of changed files
    * `git add <filename>` - Stage file for commit
    * `git add -u` - Stage all updated files for commit
    * `git add -A` - Stage all unstaged files for commit
    * `git commit -m "<commit message>"` - Create commit
4. Push to github
    * `git push origin <branch_name>`
5. Create pull request
6. Checkout back to master
    * `git checkout master`
7. Repeat

# Opening and Building

You need only 3 programs to build the client. Some of the tools require additional resources that are currently outside the scope of this readme

The client can only be build in debug mode at this moment.

* `Microsoft Visual Studio 2013 or 2017 (Please don't upgrade the Toolset, else you will break it)`
* `MFC- and ATL-Support (x86 and x64) (Visual Studio 2017 will automatically ask to install it)`
* `DirectX SDX(Feb. 2010)`
