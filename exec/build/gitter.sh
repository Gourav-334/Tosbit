#!/bin/bash

git add --all
git commit -m "Bugs for PUSH fixed."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
