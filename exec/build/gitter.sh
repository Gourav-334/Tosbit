#!/bin/bash

git add --all
git commit -m "UPDATE command as of last in prototype is under development (debugging seg faults)."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
