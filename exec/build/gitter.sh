#!/bin/bash

git add --all
git commit -m "Strong modifications going on in profile manager."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
