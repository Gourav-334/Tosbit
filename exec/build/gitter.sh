#!/bin/bash

git add --all
git commit -m "UPDATE command successfully completed along with auto-adjusting console tables."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
