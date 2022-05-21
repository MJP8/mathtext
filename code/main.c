#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct var {
	char name[20];
	double value;
	struct var *next;
} var;

struct var *rootvar;

int process(char text[]);
int interpret(char filename[]);
void setvar(char name[], double value);
double getvar(char name[]);
int main(int argc, char *argv[]) {
	char filename[255];
	sscanf(argv[1], "%s", filename);
	interpret(filename);
}
int interpret(char filename[]) {
	FILE *file;
	int value;
	file = fopen(filename, "rb");
	int max_size = 5000;
	char filetext[max_size];
	if (file) {
		for (int i = 0; i < max_size - 1; i++) {
			value = fgetc(file);
			if (value == EOF) {
				break;
				filetext[i] = '\0';
			} else {
				filetext[i] = value;
			}
		}
		fclose(file);
		char *line = filetext;
		int max = strlen(filetext) + 1;
		int linecount = 1;
		for (int c = 0; c < max; c++) {
			if (filetext[c] == '\n' || filetext[c] == '\0') {
				filetext[c] = '\0';
				if (!process(line)) {
					printf("Error in code at line %d\n", linecount);
					return 0;
				}
				line = &(filetext[c + 1]);
				linecount++;
			}
		}
	} else {
		printf("Could not find file %s\n", filename);
		return 0;
	}
}
int calculate(int num1, int num2, char operator) {
	switch (operator) {
		case '+':
			return num1 + num2;
		case '-':
			return num1 - num2;
		case '*':
			return num1 * num2;
		case '/':
			return num1 / num2;
		default:
			return -400;
	}
}
int process(char *text) {
	int num1, num2, num3, num4;
	char op1, op2, op3;
	double d1;
	char string[20];
	if (sscanf(text, "write %d %c %d", &num1, &op1, &num2) == 3) {
		int answer = calculate(num1, num2, op1);
		if (answer != -400) {
			printf("%d", answer);
		} else {
			return 0;
		}
	} else if (sscanf(text, "write %d", &num1) == 1) {
		printf("%d", num1);
	} else if (sscanf(text, "write %s", string)) {
		if (strcmp(string, "true") == 0 || strcmp(string, "false") == 0) {
			printf("%s", string);
		} else if (getvar(string)) {
			printf("%f", getvar(string));
		} else {
			return 0;
		}
	} else if (sscanf(text, "var %s = %lf", string, &d1)) {
		setvar(string, d1);
		printf("variable %s: floating point value", string);
	} else {
		return 0;
	}
	printf("\n");
	return 1;
}

void setvar(char name[], double value) {
	struct var *current = rootvar;
	struct var *new = (struct var *) malloc(sizeof(struct var));

	strncpy(new->name, name, 19);
	new->value = value;
	new->next = NULL;

	if(current) {
		while (current->next) {
			current = current->next;
		}
		current->next = new;
	} else {
		rootvar = new;
	}
}

double getvar(char name[]) {
	struct var *current = rootvar;
	while (current) {
		if (strncmp(current->name, name, 19) == 0) {
			return current->value;
		}
		current = current->next;
	}
	return 0.0;
}
// void main(void) {
// 	setvar("test", 1.0);
// 	setvar("test2", 123.456789);
// 	setvar("test3", 4.5);
// 	// printf("%d\n", rootvar->value);
// 	printf("test: %f\n", getvar("test"));
// 	printf("test2: %f\n", getvar("test2"));
// 	printf("test3: %f\n", getvar("test3"));
// }