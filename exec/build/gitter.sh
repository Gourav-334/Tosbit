#!/bin/bash

git status
git add --all
git status
git commit -m "Now attributes can be assigned a key."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
