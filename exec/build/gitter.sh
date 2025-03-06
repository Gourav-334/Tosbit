#!/bin/bash

git add --all
git commit -m "Screw the tester. Worst kind of bugs without any explanations. (Reason for my BP)"
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
