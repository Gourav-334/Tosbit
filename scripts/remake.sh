<<<<<<< HEAD
if [ "$1" -eq 0 ];
	then
		cp -r build/data backup/data
		cp -r build/logs backup/logs
		cp -r build/users backup/users

		rm -rf build
		mkdir build


elif [ "$1" -eq 1 ];
	then
		cp -r backup/data build/data
		cp -r backup/logs build/logs
		cp -r backup/users build/users
fi
=======
cp -r ../exec/build/data ../exec/backup/data
cp -r ../exec/build/logs ../exec/backup/logs
cp -r ../exec/build/users ../exec/backup/users

rm -rf ../exec/build
mkdir ../exec/build

cp -r ../exec/backup/data ../exec/build/data
cp -r ../exec/backup/logs ../exec/build/logs
cp -r ../exec/backup/users ../exec/build/users

cp gitter.sh ../exec/build/gitter.sh
>>>>>>> 0280440e53f28a2567c15ad2bb11eb97b521e304
