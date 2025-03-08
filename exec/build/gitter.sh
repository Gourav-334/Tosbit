#!/bin/bash

git add --all
git commit -m "This bug makes me cry every time I see it, it mocks me."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
