#!/bin/bash

git add --all
git commit -m "DD (first tester who defends a developer bug saying its feature) found out bug at last hour before 3rd weekly report."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
