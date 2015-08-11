#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

static bool locked = true;
static char greeting[1024] = "Enter your authentication code to access this facility.";

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

void check_lock_status()
{
	if (locked)
		printf("Device is LOCKED\n");
	else
		printf("Device is UNLOCKED\n");
}

void set_lock_status()
{
	printf("This feature is disabled by administrative policy. This setting\n");
	printf("can be modified using the physical link interface.\n");
}

void change_greeting(char* buf)
{
	char data[1024];
	printf("New greeting: ");
	if (!fgets(data, 1023, stdin))
		_exit(1);

	size_t len = strlen(data);
	if ((len > 0) && (data[len - 1] == '\n'))
		data[len - 1] = 0;

	strcpy(buf, data);
}

void display_greeting()
{
	printf("Current greeting: %s\n", greeting);
}

void menu()
{
	char buf[256];
	while (true)
	{
		printf("\nMenu:\n");
		printf("1) Check lock status\n");
		printf("2) Set lock status (DISABLED by policy)\n");
		printf("3) Change greeting\n");
		printf("4) Display greeting\n");
		printf("5) Exit\n\n");
		printf("Choose an option: ");
		fflush(stdout);

		char opt[32];
		if (!fgets(opt, 31, stdin))
			_exit(1);
		int choice = atoi(opt);
		if ((choice < 1) || (choice > 5))
			continue;

		printf("\n");

		if (choice == 1)
		{
			check_lock_status();
		}
		else if (choice == 2)
		{
			set_lock_status();
		}
		else if (choice == 3)
		{
			change_greeting(buf);
			strcpy(greeting, buf);
		}
		else if (choice == 4)
		{
			display_greeting();
		}
		else if (choice == 5)
		{
			break;
		}
	}
}

int main()
{
	int i;
	printf("Rock Lock RLK8239 Wireless Management Interface\n");
	system("date");
	printf("\nPassword: ");
	fflush(stdout);

	char pwd[256];
	if (!fgets(pwd, 255, stdin))
		_exit(1);
	if (strcmp(pwd, "letmeinplz\n") != 0)
		return 1;

	menu();
	return 0;
}

