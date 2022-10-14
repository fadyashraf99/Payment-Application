#include "terminal.h"
#define MAX_AMOUNT 8000

extern ST_cardData_t saved_data;
ST_terminalData_t saved_terminal;

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	/*	for user input date	*/

	/*printf("Please enter the transaction data in the format DD/MM/YYYY, e.g 25/06/2022\n");
	gets(termData->transactionDate);

	if (strlen(termData->transactionDate) == NULL) {
		printf("No transaction data is entered");
		return WRONG_DATE;
	}
	else if (termData->transactionDate[2] != '/' && termData->transactionDate[5] != '/') {
		printf("wrong transaction data format, it must be in the format DD/MM/YYYY, e.g 25/06/2022\n");
		return WRONG_DATE;
	}
	else if (strlen(termData->transactionDate) != 10) {
		printf("wrong transaction data numbers entered, it must be 8 numbers and contains two /\n");
		return WRONG_DATE;
	}
	else {
		printf("You are good to go\n");
		return OK_terminalError;
	}*/

	/*	for real date	*/

	time_t td = time(NULL);
	struct tm date = *localtime(&td);

	sprintf(termData->transactionDate, "%02d/%02d/%02d\n", date.tm_mday, (date.tm_mon + 1), (date.tm_year + 1900));
	printf("Date of the day is %s", termData->transactionDate);
	return OK_terminalError;
}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	/*	for example 11/23 for exp, 13/10/2022 for date*/
	/*	for month index 0,1 for exp and 3,4 for date and for year index 3,4 for exp and 8,9 for date	*/

	char s1[4], s2[4], s3[4], s4[4];

	// Convert both the integers to string and concatenate
	/*	for year index 3,4 for exp and 8,9 for date and for month index 1,2 for exp and 3,4 for date*/
	sprintf(s1, "%c%c", cardData.cardExpirationDate[3], cardData.cardExpirationDate[4]);
	sprintf(s2, "%c%c", termData.transactionDate[8], termData.transactionDate[9]);
	sprintf(s3, "%c%c", cardData.cardExpirationDate[0], cardData.cardExpirationDate[1]);
	sprintf(s4, "%c%c", termData.transactionDate[3], termData.transactionDate[4]);

	// Convert the concatenated string to integer
	int setexp1 = atoi(s1);
	int setdate1 = atoi(s2);
	int setexp3 = atoi(s3);
	int setdate3 = atoi(s4);

	if (setexp1 < setdate1) {
		//printf("Years past\n");
		return EXPIRED_CARD;
	}
	else if((setexp3 < setdate3) && (setexp1 == setdate1)) {
		//printf("Months past\n");
		return EXPIRED_CARD;
	}
	else {
		//printf("Good date not expired\n");
		return OK_terminalError;
	}
}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {
	cardData = &saved_data;
	int PAN_length = strlen(cardData->primaryAccountNumber);

	int sum = 0, isSecond = 0;
	for (int i = PAN_length - 1; i >= 0; i--) {

		int d = cardData->primaryAccountNumber[i] - '0';

		if (isSecond == 1)
			d = d * 2;

		sum += d / 10;
		sum += d % 10;

		isSecond = !isSecond;
    }
	int check = (sum % 10 == 0);
	if (check) {
		//printf("Valid PAN\n");
		return OK_terminalError;
	}
	else {
		//printf("Not valid PAN\n");
		return INVALID_CARD;
	}
}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	termData = &saved_terminal;
	printf("Please enter the transaction amount\n");
	scanf(" %f", &termData->transAmount);

	if (termData->transAmount <= 0) {
		//printf("Can't do this operation\n");
		return INVALID_AMOUNT;
	}
	else
	{
		//printf("Good amount\n");
		termData = &saved_terminal;
		return OK_terminalError;
	}
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	termData = &saved_terminal;
	if (termData->transAmount > termData->maxTransAmount) {
		//printf("Can't do transaction larger amount than the allowed\n");
		return EXCEED_MAX_AMOUNT;
	}
	else {
		//printf("Allowed amount\n");
		return OK_terminalError;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	termData = &saved_terminal;
	printf("Maximum amount is %d\n", MAX_AMOUNT);
	printf("If you wnat to change the maximum amount press y, if not press any key\n");
	uint8_t change;
	scanf(" %c", &change);

	switch (change){
	case 'y':
		printf("Please enter new maximum allowed amount\n");
		scanf(" %f", &termData->maxTransAmount);
		break;
	default:
		termData->maxTransAmount = MAX_AMOUNT;
	}

	if (termData->maxTransAmount <= 0) {
		//printf("Can't do this operation\n");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		//printf("Max amount set to %.2f\n", termData->maxTransAmount);
		return OK_terminalError;
	}
}
