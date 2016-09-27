/*
 ============================================================================
 Name        : wordgensc.c
 Author      : Carlos Timoshenko R. Lopes
 Version     : v0.29
 Copyright   : SoftCtrl.com.br (C)
 Description : Word Generator in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

//------------------------------------------------------------------------------
static void showHelpMessage() {

	fprintf(stderr, "WordGenSC- Word Generator-SoftCtrl.com LTDA (C) 2012\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Author      : Carlos Timoshenko R. Lopes\n");
	fprintf(stderr, "Version     : v0.29\n");
	fprintf(stderr, "Contact     : carlostimoshenkorodrigueslopes@gmail.com\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "\n");
	fprintf(stderr,
			"\twordgensc -s <inputFile(N-1)> <inputFile(1)> <outputFileName(N)>]");
	fprintf(stderr, "\n");
	fprintf(stderr,
			"\t\t-s\tGenerate all possible permutations with N letters\n"
					"\t\t\tusing as a basis a file <inputFile(1)> containing the letter\n"
					"\t\t\tcombinations with 1 and other file <inputFile(N-1)>\n"
					"\t\t\tcontaining the letter combinations with (N-1) letters,\n"
					"\t\t\tinformed by the User.\n");
	exit(EXIT_FAILURE);
}
//------------------------------------------------------------------------------
static void genPermutedFile(const char *inputFileNameN_1,
		const char *inputFileName1, const char *outputFileNameN) {

	char row1[15];
	char row2[15];
	char *result;

	FILE *inputFileN_1 = fopen(inputFileNameN_1, "rt");
	if (inputFileN_1 == NULL ) {
		printf(stderr, "Error in open file (%s)\n", inputFileNameN_1);
		exit(EXIT_FAILURE);
	}

	FILE *outputFileN;
	outputFileN = fopen(outputFileNameN, "wt");
	if (outputFileN == NULL ) {
		printf(stderr, "Error on create file (%s)\n", outputFileNameN);
		exit(EXIT_FAILURE);
	}

	FILE *inputFile1;
	while (!feof(inputFileN_1)) {
		result = fgets(row1, 15, inputFileN_1);
		if (result) {
			row1[strlen(row1) - 1] = 0;
			inputFile1 = fopen(inputFileName1, "rt");
			if (inputFile1 == NULL ) {
				printf(stderr, "Error in open file (%s)\n", inputFileName1);
				fclose(inputFileN_1);
				exit(EXIT_FAILURE);
			}

			while (!feof(inputFile1)) {
				result = fgets(row2, 15, inputFile1);
				if (result) {
					result = fprintf(outputFileN, "%s%s", row1, row2);
					if (result == EOF) {
						printf(stderr, "Error on insert data in file (%s)\n", outputFileNameN);
						fclose(inputFileN_1);
						fclose(inputFile1);
						exit(EXIT_FAILURE);
					}

				}
			}
			fclose(inputFile1);
		}
	}

	fclose(inputFileN_1);
	fclose(outputFileN);

}
//------------------------------------------------------------------------------
static void validateOptionA(const int min, const int max, const char *charset) {

	if (max < min) {
		printf(stderr, "the value in <max>(%d), not be less than value in <min>(%d) ", max, min);
		exit(EXIT_FAILURE);
	}
	if (!charset || (*charset == '\0')) {
		exit(EXIT_FAILURE);
	}

}
//------------------------------------------------------------------------------
static void validateOptionS(const char *inputFileNameN_1,
		const char *inputFileName1, const char *outputFileNameN) {

	if (!inputFileNameN_1 || (*inputFileNameN_1 == '\0')) {
		printf(stderr, "The name oj <inputFileNameN_1> must be informed.");
		exit(EXIT_FAILURE);
	}
	if (!inputFileName1 || (*inputFileName1 == '\0')) {
		printf(stderr, "The name oj <inputFileName1> must be informed.");
		exit(EXIT_FAILURE);
	}
	if (!outputFileNameN || (*outputFileNameN == '\0')) {
		printf(stderr, "The name oj <outputFileNameN> must be informed.");
		exit(EXIT_FAILURE);
	}

}
//------------------------------------------------------------------------------
int main(int argc, char **argv) {

	if (argc < 5) {
		showHelpMessage();
	}

	if (strncmp(argv[1], "-s", 2) == 0) {
		char *inputFileNameN_1 = argv[2];
		char *inputFileName1 = argv[3];
		char *outputFileNameN = argv[4];
		validateOptionS(inputFileNameN_1, inputFileName1, outputFileNameN);
		genPermutedFile(inputFileNameN_1, inputFileName1, outputFileNameN);
	} else {
		showHelpMessage();
	}

	return EXIT_SUCCESS;
}
