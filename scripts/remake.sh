cp -r ../exec/build/data ../exec/backup/data
cp -r ../exec/build/logs ../exec/backup/logs
cp -r ../exec/build/users ../exec/backup/users

rm -rf ../exec/build
mkdir ../exec/build

cp -r ../exec/backup/data ../exec/build/data
cp -r ../exec/backup/logs ../exec/build/logs
cp -r ../exec/backup/users ../exec/build/users

cp gitter.sh ../exec/build/gitter.sh
