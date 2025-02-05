#!/bin/bash

git add --all
git commit -m "Table structure printing avoids printing attribute key symbol (due to modified removeKeySymbol)."
git pull origin gouravTest
git push origin gouravTest
git checkout main
git pull origin main
git merge gouravTest
git push origin main
git checkout gouravTest
