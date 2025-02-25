#!/bin/bash

git add --all
git commit -m "Rebase situation cooled down."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
