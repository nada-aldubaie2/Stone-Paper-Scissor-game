#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int RandomNumber(int From, int To) {
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

short roundNumber;

enum enPlayers { Computer = 1, Player = 2, Even = 3 };
enum enStonePaperScissor { Stone = 1, Paper = 2, Scissor = 3 };

struct stPlayers {
	enStonePaperScissor playerChoice;
	enStonePaperScissor computerChoice;
	enPlayers winner;
};

short roundNumberFun() {
	do {
		cout << "How Many Rounds will you play choose 1 - 10 ?\n";
		cin >> roundNumber;
	} while (roundNumber < 1 || roundNumber > 10);
	return roundNumber;
}

enStonePaperScissor playerChoose() {
	short choice;
	string again = "Please Try Again bro.. >_<  \n";

	do {
		cout << "Your Choice Number: [1]:Stone, [2]:Paper, [3]:Scissor ?!";
		cin >> choice;
		if (choice < 1 || choice > 3) {
			cout << again;
		}
	} while (choice < 1 || choice > 3);
	return (enStonePaperScissor)choice;
}

enStonePaperScissor computerChoose() {
	return (enStonePaperScissor)RandomNumber(1, 3);
}

enPlayers gameWinner(stPlayers roundResult) {
	if (roundResult.playerChoice == roundResult.computerChoice) {
		return Even;
	}
	switch (roundResult.playerChoice) {
	case Stone:
		if (roundResult.computerChoice == Paper) {
			cout << "\a";
			return Computer;
		}
		break;
	case Paper:
		if (roundResult.computerChoice == Scissor) {
			return Computer;
		}
		break;
	case Scissor:
		if (roundResult.computerChoice == Stone) {
			return Computer;
		}
		break;
	}
	return Player;
}

void printRoundResult(stPlayers roundResults) {
	cout << "Player Choice: " << roundResults.playerChoice << endl;
	cout << "Computer Choice: " << roundResults.computerChoice << endl;
	cout << "The Winner is: " << roundResults.winner << endl;
}

void ResetScreen() {
	system("cls");
	system("color 0F");
}

void playRounds() {
	int playerWins = 0, computerWins = 0, evenResult = 0;

	for (short i = 1; i <= roundNumber; i++) {
		cout << "Round [" << i << "] begins:\n";
		enStonePaperScissor playerChoice = playerChoose();
		enStonePaperScissor computerChoice = computerChoose();
		stPlayers roundResults = { playerChoice, computerChoice, gameWinner({ playerChoice, computerChoice, Even }) };
		printRoundResult(roundResults);

		if (roundResults.winner == Player) {
			system("color 2F"); // Green
			playerWins++;
			cout << "Player Wins! ;)\n";
		}
		else if (roundResults.winner == Computer) {
			system("color 4F"); // Red
			computerWins++;
			cout << "\a";       //the sound
			cout << "Computer Wins!\n";
		}
		else {
			system("color 6F"); // Yellow
			evenResult++;
			cout << "It's a Tie!\n";
		}
	}

	ResetScreen(); // Reset screen color after rounds

	string line = "================================================================";
	cout << line << "\n Game Over!\n" << line;
	cout << "\n Player wins: " << playerWins << " rounds ♥\n";
	cout << "Computer wins: " << computerWins << " rounds\n";
	cout << "Even Times: " << evenResult << " rounds\n";


	if (playerWins > computerWins) {
		cout << "Player wins the game....<^_^> Yus \n \n";
	}
	else if (playerWins < computerWins) {
		cout << "Computer wins the game....<~_~>\n \n";
	}
	else {
		cout << "It's a tie game!\n \n";
	}
}

void playAgain() {
	char choice;
	do {
		cout << "Do you want to play again bra? (Y/N): ";
		cin >> choice;
		if (choice == 'n' || choice == 'N') {
			cout << "Thank you for playing!\n bye..........................";
			system("color 1F");
			return;
		}
		else if (choice == 'y' || choice == 'Y') {
			roundNumber = roundNumberFun();
			playRounds();
		}
		else {
			cout << "Opps invalid choice *_*. \n Please enter Y or N.\n";
		}
	} while (choice != 'n' && choice != 'N');
}

int main() {
	srand((unsigned)time(NULL));

	roundNumberFun();
	playRounds();
	playAgain();

	return 0;
}
