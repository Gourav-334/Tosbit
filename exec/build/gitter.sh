#!/bin/bash

git add --all
git commit -m "Work continues on self-adjustable SHOW ALL console table."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
