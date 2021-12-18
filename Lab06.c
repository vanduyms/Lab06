#include <stdio.h>
#include <stdlib.h>
void START_MENU();
void FRAME_INSERT_MENU();
void OPTIONS_MENU();
void defA_to_A(int defA[], int A[]);
void A_Insert(int A[], int n);
void Output(int A[], int arr[100][100], char str[], int nums, int n, int m, int faults);

void FIFO(int A[], int frames[], int nums, int n);
void OPT(int A[], int frames[], int nums, int n);
void LRU(int A[], int frames[], int nums, int n);

int main()
{
	int default_A[] = { 2, 0, 5, 2, 0, 9, 9, 1, 0, 0, 7};
	int A[100];

	int nums, frames[100];
	int n;
	int choice;

	START_MENU();
	do {
		printf("Your selection: ");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2);
	if (choice == 2) {
		printf("Enter the number of elements in the reference array: ");
		scanf("%d", &n);
		A_Insert(A, n);
	}
	else defA_to_A(default_A, A);

	FRAME_INSERT_MENU();
	printf("Enter number of page frame: ");
	scanf("%d", &nums);

	OPTIONS_MENU();
	int choice2;
	do {
		printf("Your selection: ");
		scanf("%d", &choice2);
	} while (choice2 < 1 && choice2 > 3);
	if (choice == 1) {
		switch (choice2)
		{
		case 1:
			FIFO(A, frames, nums, 11);
			break;
		case 2:
			OPT(A, frames, nums, 11);
			break;
		case 3:
			LRU(A, frames, nums, 11);
			break;
		}
	}
	else {
		switch (choice2)
		{
		case 1:
			FIFO(A, frames, nums, n);
			break;
		case 2:
			OPT(A, frames, nums, n);
			break;
		case 3:
			LRU(A, frames, nums, n);
			break;
		}
	}
	return 0;
}

void START_MENU()
{
	printf(" _________________________________________\n");
	printf("|  -----Page Replacement Algorithm-----   |\n");
	printf("|      1. Default referenced sequence     |\n");
	printf("|      2. Manual input sequence           |\n");
	printf("|_________________________________________|\n");
}

void FRAME_INSERT_MENU()
{
	printf(" _________________________________________\n");
	printf("|  -----Page Replacement Algorithm-----   |\n");
	printf("|          Input page frames:             |\n");
	printf("|_________________________________________|\n");

}

void OPTIONS_MENU()
{
	printf(" _________________________________________\n");
	printf("|  -----Page Replacement Algorithm-----   |\n");
	printf("|          1. FIFO algorithm              |\n");
	printf("|          2. OPT algorithm               |\n");
	printf("|          3. LRU algorithm               |\n");
	printf("|_________________________________________|\n");
}

void defA_to_A(int defA[], int A[]) {
	for (int i = 0; i < 11; i++)
		A[i] = defA[i];
}

void A_Insert(int A[], int n) {
	printf("Input array of references: ");
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
}

void Output(int A[], int arr[100][100], char str[], int nums, int n, int m, int faults) {
	for (int i = 0; i < n; i++)
		printf("%d\t", A[i]);
	printf("\n");
	for (int i = 0; i < nums; i++) {
		for (int j = 0; j < m; j++)
		{
			if (arr[i][j] == -1)
				printf(" \t");
			else printf("%d\t", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for (int i = 0; i < m; i++) {
		if (str[i] == '-')
			printf(" \t");
		else printf("%c\t", str[i]);
	}
	printf("\n\nNumber of page fault: %d\n", faults);
}

void FIFO(int A[], int frames[], int nums, int n) {
	printf(" _____________________________________\n");
	printf("|---FIFO Page Replacement Algorithm---|\n");
	printf("|_____________________________________|\n");
	int i, j, k, flag, faults = 0;

	for (i = 0; i < nums; i++)
		frames[i] = -1;
	j = 0;
	int arr[100][100], p = 0, m = 0;
	char str[100];
	for (i = 0; i < n; i++)
	{
		flag = 0;
		for (k = 0; k < nums; k++)
			if (frames[k] == A[i])
				flag = 1;
		if (flag == 0)
		{
			frames[j] = A[i];
			j = (j + 1) % nums;
			for (int i = 0; i < nums; i++)
				arr[i][m] = frames[i];
			faults++;
			str[m] = '*';
		}
		else
		{
			for (int i = 0; i < nums; i++)
				arr[i][m] = frames[i];
			str[m] = '-';
		}
		m++;
	}
	Output(A, arr, str, nums, n, m, faults);
}

void OPT(int A[], int frames[], int nums, int n) {
	printf(" ____________________________________\n");
	printf("|---OPT Page Replacement Algorithm---|\n");
	printf("|____________________________________|\n");
	int i, j, k, flag;
	int x, y, z;
	int arr[100][100], p = 0, m = 0;
	char str[100];
	int temp[100], faults = 0;
	for (int i = 0; i < n; i++)
		temp[i] = n;
	for (i = 0; i < nums; i++)
		frames[i] = -1;
	j = 0;
	for (i = 0; i < n; i++)
	{
		flag = 0;
		for (k = 0; k < nums; k++)
			if (frames[k] == A[i])
				flag = 1;
		if (flag == 0)
		{
			if (p < nums)
			{
				frames[j] = A[i];
				j = (j + 1) % nums;
				p++;
			}
			else
			{
				j = 0;
				for (x = 0; x < nums; x++)
					for (y = i + 1; y < n; y++)
						if (frames[x] == A[y]) {
							temp[x] = y;
							y = n;
						}
				for (x = 0; x < nums; x++)
					if (temp[x] > j) {
						j = temp[x];
						z = x;
					}
				for (j = 0; j < nums; j++)
					temp[j] = n;
				frames[z] = A[i];
			}
			faults++;
			for (int i = 0; i < nums; i++)
				arr[i][m] = frames[i];
			str[m] = '*';
		}
		else
		{
			for (int i = 0; i < nums; i++)
				arr[i][m] = frames[i];
			str[m] = '-';
		}
		m++;
	}
	Output(A, arr, str, nums, n, m, faults);
}

void LRU(int A[], int frames[], int nums, int n) {
	printf(" ____________________________________\n");
	printf("|---LRU Page Replacement Algorithm---|\n");
	printf("|____________________________________|\n");
	int i, j, k, flag;
	int a, b, c;
	int arr[100][100], p = 0, m = 0;
	char str[100];
	int faults = 0;
	int temp[100];
	for (int i = 0; i < n; i++)
		temp[i] = n;
	for (i = 0; i < nums; i++)
		frames[i] = -1;
	j = 0;
	for (i = 0; i < n; i++)
	{
		flag = 0;
		for (k = 0; k < nums; k++)
			if (frames[k] == A[i])
				flag = 1;
		if (flag == 0)
		{
			if (p < nums)
			{
				frames[j] = A[i];
				j = (j + 1) % nums;
				p++;
			}
			else
			{
				j = n;
				for (a = 0; a < nums; a++)
					for (b = i - 1; b >= 0; b--)
						if (frames[a] == A[b])
						{
							temp[a] = b;
							b = 0;
						}
				for (a = 0; a < nums; a++)
					if (temp[a] < j)
					{
						j = temp[a];
						c = a;
					}
				for (j = 0; j < nums; j++)
					temp[j] = -1;

				frames[c] = A[i];
			}
			faults++;

			for (int i = 0; i < nums; i++)
				arr[i][m] = frames[i];
			str[m] = '*';
		}
		else
		{
			for (int i = 0; i < nums; i++)
				arr[i][m] = frames[i];
			str[m] = '-';
		}
		m++;
	}
	Output(A, arr, str, nums, n, m, faults);
}
