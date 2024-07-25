#!/bin/sh

while getopts lm option
do
    case "${option}" in
        l) os="linux";;
        m) os="mac";;
    esac
done

user1="user1.c"
user2="user2.c"

cc $user1 -o ${user1%.*}.out
cc $user2 -o ${user2%.*}.out

if [ $os = "linux" ]
then
    gnome-terminal --window --title=${user1%.*} -- bash -c "./${user1%.*}.out"
    gnome-terminal --window --title=${user2%.*} -- bash -c "./${user2%.*}.out"
elif [ $os = "mac" ]
then
    directory=$(pwd)
    osascript -e 'tell app "Terminal" to do script "'$directory/${user1%.*}.out'"'
    osascript -e 'tell app "Terminal" to do script "'$directory/${user2%.*}.out'"'
else
    echo "OS not found"
    exit
fi

exit
