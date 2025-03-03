#!/bin/bash

git add --all
git commit -m "Most bizzare segmentation fault ever, believe me."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
