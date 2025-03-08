#!/bin/bash

git add --all
git commit -m "Proper commenting done to socket programs -> client.c, server.c"
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
