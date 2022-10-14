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
		return 0;
	}
	if (isValidCardPAN(&cardData) == INVALID_CARD) {
		printf("Fraud card\n");
		return 0;
	}
	getTransactionAmount(&termData);
	setMaxAmount(&termData);
	if (isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT) {
		printf("Amount exceeding limit\n");
		return 0;
	}
	
	/*	sever	*/
	if (isValidAccount(&cardData) == ACCOUNT_NOT_FOUND) {
		printf("Invalid account\n");
		return 0;
	}
	if (isAmountAvailable(&termData) == LOW_BALANCE) {
		printf("Insuffecient funds\n");
		return 0;
	}
	recieveTransactionData(&transData);
	saveTransaction(&transData);
}
