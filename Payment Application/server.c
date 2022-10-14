#include "server.h"

#define MAX 255
int Flag;
uint32_t sequence = 1;
EN_serverError_t isAccount, isAmount, isSave;
extern ST_cardData_t saved_data;
extern ST_terminalData_t saved_terminal;
ST_transaction_t saved_transData;

ST_accountsDB_t users[MAX] = {	{6548.00,	"9817393370981739337"},
								{4682.00,	"4202270212009952435"},
								{9413.00,	"5689586848574761523"},
								{1654.00,	"5833063860647747740"},
								{5289.00,	"6108955076360022206"},
								{6900.00,	"123456789123456789"}
};

ST_transaction_t trans[MAX] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	if (isValidAccount(&saved_data) == ACCOUNT_NOT_FOUND) {
		//printf("Declined stolen card\n");
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&saved_terminal) == LOW_BALANCE) {
		//printf("Declined insuffecient fund\n");
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	if (saveTransaction(&saved_transData) == SAVING_FAILED) {
		//printf("Internal server error\n");
		transData->transState = INTERNAL_SERVER_ERROR;
		return INTERNAL_SERVER_ERROR;
	}
	printf("Balance before Transaction %f\r\n", users[Flag].balance);
	users[Flag].balance = users[Flag].balance - saved_terminal.transAmount;
	printf("Transaction Approved and The balance after transaction is %.2f\r\n", users[Flag].balance);
	transData->transState = APPROVED;
	return APPROVED;
}

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	cardData = &saved_data;
	for (int i = 0; i < MAX; i++) {
		if (strcmp(cardData->primaryAccountNumber, users[i].primaryAccountNumber) == 0) {
			Flag = i;
			//printf("Valid account\n");
			return OK_serverError;
		}
	}
	//printf("Stolen card\n");
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	termData = &saved_terminal;
	if (termData->transAmount > users[Flag].balance) {
		//printf("Low balance\n");
		return LOW_BALANCE;
	}
	else {
		//printf("Balance is ok\n");
		return OK_serverError;
	}
}

EN_serverError_t saveTransaction(ST_transaction_t* transData) {
	transData->transactionSequenceNumber = sequence;
	trans[sequence] = *transData;
	if (getTransaction(sequence, transData) == TRANSACTION_NOT_FOUND) {
		//printf("Saving failed\n");
		return SAVING_FAILED;
	}
	else {
		//printf("Transaction saved successfully\n");
		sequence++;
		return OK_serverError;
	}
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData) {
	if (trans[sequence].transactionSequenceNumber != transactionSequenceNumber) {
		//printf("Transaction not found\n");
		return TRANSACTION_NOT_FOUND;
	}
	else {
		//printf("Transaction located\n");
		return OK_serverError;
	}
}
