To Generate the documentation for Github
switch to working branch
    git checkout [workingBranch/master]
run doxygen
    doxygen Doxyfile
commit the changes made to Documentation for the active branch
    git add Documentation/*
    git commit 
switch to the gh-pages branch and bring the changes from the desired branch
    git checkout gh-pages
    git checkout [workingBranch/master] Documentation/*
    git add Documentation/*
    git commit
Publish the changes to the github Documentation page
    git push origin gh-pages
