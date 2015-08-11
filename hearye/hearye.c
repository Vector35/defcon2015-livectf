/*
   Title: HearYe
   Author: Jordan Wiens
   Description: Dumb service meant for very fast exploitation.
*/

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define CLEAR "\033[2J\033[1;1H"
#define WELCOME "Hear Ye, Hear Ye, The Ye Old Town Crier Service\n"

int pwnable = 31337;

void anykey()
{
	printf("\nPress Any Key to Continue\n");
	fflush(stdout);
	getchar();
}

int system(char* cmd)
{
	char* argv[4];
	argv[0] = "/system/bin/sh";
	argv[1] = "-c";
	argv[2] = cmd;
	argv[3] = NULL;

	pid_t pid = fork();
	if (pid == 0)
	{
		execve(argv[0], argv, __environ);
		argv[0] = "/bin/sh";
		execve(argv[0], argv, __environ);
		_exit(-1);
	}

	int status;
	waitpid(pid, &status, 0);
	return status;
}

long choice()
{
	char buffer[64];
	fflush(stdout);
	fgets(buffer, 128, stdin);
	return atol(buffer);
}

unsigned int menu()
{
	printf(CLEAR WELCOME);
	printf("1) Cry Havok\n2) Set my name\n3) Cry my name\n4) Pwn\n\n0) Quit\n\nCHOICE: ");
	return choice();
}

char* setname()
{
	static char criername[128];
	printf("Well met, my liege. Please let us know how to identify you: ");
	fflush(stdout);
	fgets(criername,128,stdin);
	strtok(criername,"\n");
	return criername;
}

void cry()
{
	printf("Blood and destruction shall be so in use \nAnd dreadful objects so familiar \nThat mothers shall but smile when they behold \nTheir infants quarter\'d with the hands of war; \nAll pity choked with custom of fell deeds: \nAnd Caesar\'s spirit, ranging for revenge, \nWith Ate by his side come hot from hell, \nShall in these confines with a monarch\'s voice \nCry \'Havoc,\' and let slip the dogs of war; \nThat this foul deed shall smell above the earth \nWith carrion men, groaning for burial.\n\n");
	anykey();
}

void cryname(char *name)
{
	printf("Hear Ye, Hear Ye! All ye Kings and Queens, Knights and Nobles, Peasants and\nPwners. Bask in the glory that is %s and their skills are legion. Cower, and be a feared.",name);
	anykey();
}

void pwn()
{
	printf("Sorry, it's not that easy...\n");
	if (pwnable==35)
	{
		system("cat this-is-not-the-flag");
	}
	anykey();
}


int main(int argc, char* argv[])
{
	unsigned int choice=35;
	char name[128];

	do { 
		choice = menu();
		switch (choice)
		{
		case 1:
			cry();
			break;
		case 2:
			bzero(name,128);
			memcpy(name,setname(),128);
			break;
		case 3:
			cryname(name);
			break;
		case 4:
			pwn();
			break;
		}

	} while (choice != 0);

	printf("\nGoodbye...\n\n");

	return 0;
}
