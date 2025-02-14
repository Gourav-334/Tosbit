#!/bin/bash

git add --all
git commit -m "Unique attribute names enforced, seg faults in 'queue.h' fixed, performance measuring time unit added."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
