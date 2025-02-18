#!/bin/bash

git add --all
git commit -m "Modifications to be done on queue."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
