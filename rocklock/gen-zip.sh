#!/bin/bash
for team in 1 2 3 4
do
case $team in
	1)
		password="letmein181"
		;;
	2)
		password="letmein244"
		;;
	3)
		password="letmein364"
		;;
	4)
		password="letmein474"
		;;
esac
	echo "Same Nexus 9 running Android 5.1.1. 

IP: 10.5.18.2
PORT: 500$team

THERE IS NO FLAG -- execute './win' to show you've won.

Good luck." > instructions-team$team.txt
	rm team$team.zip 
	zip team$team.zip instructions-team$team.txt rocklock$team
	rm instructions-team$team.txt
done
