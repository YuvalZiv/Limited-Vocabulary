// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <stdio.h>
#include "Functions.h"

#define MAX_WORD 50
#define TRUE 1 
#define FALSE 0
#define MALLOC_ERR -1
#define MALLOC_ERR_MSG "Malloc error: Unable to associate memory.\n"
#define MODE "rb"
#pragma warning(disable:4996)

void wrongUse(char* path);
char* getFileNameFromPath(char* path);
char* readFile(char* path);
void createDictionary(char* voc);
char* replace(list_t* list, char* text);
char* getValue(list_t* list, char* key);
void writeFile(char* path, char* text);
int findLast(char* string, char chr);


int main(int argc, char* argv[])
{
	char* text;
	char* voc;
	char* data;
	list_t* list;
	if (argc != 3) {
		wrongUse(argv[0]);
		exit(-1);
	}
	printf("Reading text from '%s'\n", argv[1]);
	text = readFile(argv[1]);
	printf("Read text:\n%s\n\n", text);

	printf("Reading vocabulary from '%s'\n", argv[2]);
	voc = readFile(argv[2]);
	printf("Read vocabulary:\n%s\n\n", voc);

	list = create_list();
	createDictionary(list, voc);
	data = replace(list, text);
	writeFile(argv[1], data);
	destroy_list(list);
	return 0;
}

void wrongUse(char* path) {
	/*
	Prints the correct useage from the program.
	input: char*
	output: void
	*/
	char* name = getFileNameFromPath(path);
	printf(
		"Wrong useage of program.\n"
		"Useage:\n"
		"%s text voc\n"
		"Example:\n"
		"%s textFile.txt vocFile.txt\n", name, name);
}

char* getFileNameFromPath(char* path) {
	/*
	Extractes the filename from a path.
	input: char*
	output: char*
	*/
	int i = 0;
	for (i = strlen(path) - 1; TRUE; i--)
	{
		if (path[i] == '/' || path[i] == '\\')
		{
			return &path[i + 1];
		}
	}
	return path;
}

char* readFile(char* path) {
	/*
	Reads a file binary data.
	input: char*, const char*
	output: char*
	*/
	char* data = NULL;
	int len, read;
	FILE* file;
	file = fopen(path, MODE);
	if (file) {
		fseek(file, 0, SEEK_END);
		len = ftell(file);
		rewind(file);

		data = (char*)malloc(sizeof(char) * (len + 1));
		if (data == NULL) {
			printf("Malloc error.\n");
			exit(-1);
		}
		read = fread(data, sizeof(char), len, file);
		data[len] = '\0';
		if (len != read) {
			printf("len: %d\nread: %d\n", len, read);
			printf("Error when reading file.\n");
			free(data);
			data = NULL;
			exit(-1);
		}
		fclose(file);
	}
	else {
		printf("Error when opening file.\n");
		exit(-1);
	}
	return data;
}

void createDictionary(list_t* list, char* voc) {
	/*
	*/
	char* key = NULL;
	char* value = NULL;
	int length = strlen(voc);
	int start = 0, end;
	int i = 0;
	for (i = 0; i < length; i++)
	{
		/*find key*/
		start = i;
		while (voc[i] != ':' && i < length) {
			i++;
		}
		end = i;
		key = malloc(sizeof(char) * (end - start + 1));
		memcpy(key, &voc[start], end - start);
		key[end - start] = '\0';

		i++;
		/*find value*/
		start = i;
		while (!isspace(voc[i]) && i < length) {
			i++;
		}
		end = i;
		value = malloc(sizeof(char) * (end - start + 1));
		memcpy(value, &voc[start], end - start);
		value[end - start] = '\0';
		i++;

		/*add key/value pair to list*/
		item_t * item = NULL;
		item = malloc(sizeof(item_t));
		if (item == NULL) {
			printf("%s", MALLOC_ERR_MSG);
			exit(MALLOC_ERR);
		}
		item->key = key;
		item->value = value;
		add_node(list, item);
	}
}

char* replace(list_t* list, char* text) {
	/*
	Replace every replaceable word from text with the dictionary in list.
	input: list_t*, char*
	output: char*
	*/
	int length = strlen(text), i = 0;
	int start, end;
	char* newText = NULL;
	char word[MAX_WORD];
	char* newWord = NULL;
	int written = 0;
	newText = (char*)realloc(NULL, sizeof(char) * MAX_WORD);
	newText[0] = '\0';
	if (newText == NULL) {
		printf("%s", MALLOC_ERR_MSG);
		exit(MALLOC_ERR);
	}

	for (i = 0; i < length; i++) {
		start = i;
		while (!isspace(text[i]) && i < length) {
			i++;
		}
		end = i;
		memcpy(word, &text[start], end - start);
		word[end - start] = '\0';
		newWord = getValue(list, word);
		strcat(newText, newWord == NULL ? word : newWord);
		written += newWord == NULL ? strlen(word) : strlen(newWord);
		newText[written] = text[i];
		newText[written + 1] = '\0';
		newText = (char*)realloc(newText, sizeof(char) * (written + MAX_WORD));
		written++;
	}
	newText[written - 1] = '\0';
	newText = realloc(newText, written);
	return newText;
}

char* getValue(list_t* list, char* key) {
	/*
	Returns the value of a given key.
	input: list_t*, char*
	output: char*
	*/
	if (strcmp(key, "tired") == 0) {
		int i = 0;
	}
	node_t* cur = list->first;
	while (cur != NULL) {
		if (strcmp(cur->item->key, key) == 0) {
			return strdup(&cur->item->value[0]);
		}
		cur = cur->next;
	}
	return NULL;
}

void writeFile(char* path, char* text) {
	/*
	Writes the text into a file with a given path.
	input: char*, char*
	output: void
	*/
	int lastIndex;
	char* writePath;
	char* extension;
	FILE* file;

	writePath = malloc(sizeof(char) * strlen(path));
	if (writePath == NULL) {
		writePath = path;
		/*Writes to the same file if there's an error with the malloc.*/
	}
	strcpy(writePath, path);
	lastIndex = findLast(writePath, '.');
	writePath[lastIndex] = '\0';
	strcat(writePath, " - Rewritten by Yuval Ziv");
	extension = strchr(path, '.');
	strcat(writePath, extension);
	printf("Writing new text to '%s':\n%s\n", writePath, text);



	file = fopen(path, "wb");
	if (file) {
		fprintf(file, text);
		fclose(file);
	}
	else {
		printf("Error when opening file.\n");
		exit(-1);
	}
}

int findLast(char* string, char chr) {
	/*
	Finds the last occurence of a given char in a string.
	input: char*, char
	output: int
	*/
	int index = 0, lastIndex = 0;
	for (index = 0; index < strlen(string); index++) {
		if (string[index] == chr) {
			lastIndex = index;
		}
	}
	return lastIndex;
}