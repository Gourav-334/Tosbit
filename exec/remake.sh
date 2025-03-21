if [ "$1" -eq 0 ];
	then
		rm -rf backup/data
		rm -rf backup/logs
		rm -rf backup/users

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
