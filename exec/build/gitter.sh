#!/bin/bash

git add --all
git commit -m "Probably at least half the issue solved, subtle bugs & minute detailing in approach."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
