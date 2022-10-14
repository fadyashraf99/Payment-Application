#include "app.h"

void appStart(void) {

	/*	data initialization	*/
	ST_cardData_t cardData;
	ST_terminalData_t termData;
	ST_transaction_t transData;

	/*	card	*/
	getCardHolderName(&cardData);
	getCardExpiryDate(&cardData);
	getCardPAN(&cardData);

	/*	terminal	*/
	getTransactionDate(&termData);
	if (isCardExpired(cardData, termData) == EXPIRED_CARD) {
		printf("Expired card\n");
		return ;
	}
	if (isValidCardPAN(&cardData) == INVALID_CARD) {
		printf("Fraud card\n");
		return ;
	}
	getTransactionAmount(&termData);
	setMaxAmount(&termData);
	if (isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT) {
		printf("Amount exceeding limit\n");
		return ;
	}

	/*	sever	*/
	if (isValidAccount(&cardData) == ACCOUNT_NOT_FOUND) {
		printf("Invalid account\n");
		return ;
	}
	if (isAmountAvailable(&termData) == LOW_BALANCE) {
		printf("Insuffecient funds\n");
		return ;
	}
	recieveTransactionData(&transData);
	saveTransaction(&transData);
}

