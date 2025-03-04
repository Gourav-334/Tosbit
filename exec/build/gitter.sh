#!/bin/bash

git add --all
git commit -m "UPDATE almost done, just positioning & I/O debugging remaining."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
