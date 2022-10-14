#include "card.h"
ST_cardData_t saved_data;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	cardData = &saved_data;
	printf("Please enter the cardholder's name\n");
	gets(cardData->cardHolderName);

	if (strlen(cardData->cardHolderName) == NULL) {
		//printf("No name is entered\n");
		return WRONG_NAME;
	}
	else if (strlen(cardData->cardHolderName) < 20) {
		//printf("You entered a name less than 20 characters\n");
		return WRONG_NAME;
	}
	else if (strlen(cardData->cardHolderName) > 24) {
		//printf("You entered a name more than 24 characters\n");
		return WRONG_NAME;
	}
	else {
		//printf("You are good to go\n");
		return OK_cardError;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	printf("Please enter the card expiry date in the format \"MM/YY\", e.g \"05/25\"\n");
	gets(cardData->cardExpirationDate);

	if (strlen(cardData->cardExpirationDate) == NULL) {
		//printf("No card expiry date is entered\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/' && strlen(cardData->cardExpirationDate) == 5) {
		//printf("Wrong card expiry numbers entered and it should contain /\n");
		return WRONG_EXP_DATE;
	}
	else if (cardData->cardExpirationDate[2] != '/') {
		//printf("Wrong card expiry format, it must be in the format \"MM/YY\", e.g \"05/25\"\n");
		return WRONG_EXP_DATE;
	}
	else if (strlen(cardData->cardExpirationDate) != 5) {
		//printf("Wrong card expiry numbers entered, it must be 4 numbers\n");
		return WRONG_EXP_DATE;
	}
	else {
		//printf("You are good to go\n");
		return OK_cardError;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	cardData = &saved_data;
	printf("Please enter the card's Primary Account Number\n");
	gets(cardData->primaryAccountNumber);

	if (strlen(cardData->primaryAccountNumber) == NULL) {
		//printf("No PAN is entered\n");
		return WRONG_PAN;
	}
	else if (strlen(cardData->primaryAccountNumber) < 16) {
		//printf("You entered a PAN less than 16 characters\n");
		return WRONG_PAN;
	}
	else if (strlen(cardData->primaryAccountNumber) > 19) {
		//printf("You entered a PAN more than 19 characters\n");
		return WRONG_PAN;
	}
	else {
		//printf("You are good to go\n");
		return OK_cardError;
	}
}

