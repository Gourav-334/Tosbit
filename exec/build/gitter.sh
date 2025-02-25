#!/bin/bash

git add --all
git commit -m "More progress made on console-table self adjust for SHOW ALL."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
