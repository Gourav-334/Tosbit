#!/bin/bash

git add --all
git commit -m "SHOW command to print ALL rows created. Subtle unconnected & nasty bugs found while pushing data though."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
