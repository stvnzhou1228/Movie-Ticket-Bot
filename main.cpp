#include <bits/stdc++.h>
using namespace std; 

const int numRows = 15, numCols = 20; //global constant integer variables for dimensions of auditorium 

double** getPrices(double** pricesArray){ //read prices.txt function 

	ifstream prices; //input stream class

	prices.open("prices.txt"); //open prices.txt file 

	while (!prices.eof()){ //while not end of file
		for (int i = 0; i < numRows; i++){ //loop through rows 
			if (i % 2 == 0){ //if even
				for (int j = 0; j < 20; j++){ //even rows have 20 columns 
					prices >> pricesArray[i][j]; //store prices 
				}
			}
			else{ //if odd
				for (int j = 0; j < 15; j++){ //odd rows have 15 columns 
					prices >> pricesArray[i][j]; //store prices  
				}
			}
		}
	}

	return pricesArray; //return filled prices array 

}

char** getSeats(char** seatsArray){ //read seats.txt function 

	ifstream seats; //input stream class

	seats.open("seats.txt"); //open seats.txt file 

	int temp; //temporary variable to store column numbers 

	while (!seats.eof()){ //while not end of file
		for (int i = -1; i < numRows; i++){ //initialize i as -1 to account for the first row of column numbers 
			if (i == -1){ //the first row of numbers 
				for (int j = 0; j < 20; j++){ //cycle through the 20 numbers  
					seats >> temp; //store numbers into temp
				}
			}
			else if (i % 2 == 0){ //if even
				for (int j = 0; j < 20; j++){ //even rows have 20 columns 
					seats >> seatsArray[i][j]; //store seat availability 
				}
			}
			else if(i % 2 == 1){ //if odd 
				for (int j = 0; j < 15; j++){ //odd rows have 15 columns 
					seats >> seatsArray[i][j]; //store seat availability 
				}
			}
		}
	}

	return seatsArray; //return filled seats array 

}

int totalSold(double** pricesArray, char** seatsArray){ //calculate number of tickets sold function 

  int numSold = 0; //initialize numSold variable as 0 

	for (int i = 0; i < numRows; i++){ //loop through rows 
		if (i % 2 == 0){ //if even
			for (int j = 0; j < 20; j++){ //loop through 20 columns
				if (seatsArray[i][j] == 'X'){ //if seat is unavailable
					numSold++; //increment number of tickets sold
				}
			}
		}
		else{ //if odd
			for (int j = 0; j < 15; j++){ //loop through 15 columns
				if (seatsArray[i][j] == 'X'){ //if seat is unavailable
					numSold++; //increment number of tickets sold
				}
			}
		}
	}

	return numSold; //return number of tickets sold 

}

double totalRaised(double** pricesArray, char** seatsArray, double moneyRaised){ //calculate total money raised function 

	for (int i = 0; i < numRows; i++){ //loop through rows 
		if (i % 2 == 0){ //if even
			for (int j = 0; j < 20; j++){ //loop through 20 columns 
				if (seatsArray[i][j] == 'X'){ //if seat is unavailable 
					moneyRaised += pricesArray[i][j]; //add price of seat to total money raised 
				}
			}
		}
		else{ //if odd
			for (int j = 0; j < 15; j++){ //loop through 15 columns 
				if (seatsArray[i][j] == 'X'){ //if seat is unavailable 
					moneyRaised += pricesArray[i][j]; //add price of seat to total money raised 
				}
			}
		}
	}

	return moneyRaised; //return total money raised 

}

void printSeats(char** seatsArray){ //print seating chart function 
	
	cout << endl << right << setw(60) << "Welcome to School Without Walls!" << endl; //print welcome
	cout << setw(78) << "Seats Marked as '#' are Available, and Seats Marked as 'X' are Taken" << endl; //explanation 
	cout << endl << right << setw(50) << "SEATING CHART" << endl; //print title 
	for (int i = 0; i <92; i++){ //printing grid  
		cout<<"-";
	}
	cout << "\n|        | ";
	for (int i = 0; i < numCols; i++){ //printing grid
  	cout << left << setw(1) << "S" << setw(3) << i; 
		if (i == 19){
			cout << "|";
		}
	}
	cout << endl;	
	cout << "|"; 
	for (int i = 0; i < 8; i++){ //printing grid
		cout<<"-";
	}
	cout << "|";
	for (int i = 0; i < 81; i++){ //printing grid
		cout<<"-";
	}
	cout << "|";
	cout << endl; 

	for (int i = 0; i <numRows; i++){ //print seat availability 
		if (i % 2 == 0){ //if even 
			for (int j = 0; j < 20; j++){ //even rows have 20 columns 
				if (j == 0){
					cout << left << setw(6) << "| ROW" << setw(3) << i << setw(3) << "|"; //print row number 
				}
				if (0 <= j && j <=18){ 
					cout << left << setw(3) << seatsArray[i][j] << " "; //print seat availability 
				}
				else if (j == 19){
					cout << left << setw(3) << seatsArray[i][j] << "|"; //print seat availability 
				}
			}
		}
		else{ //if odd 
			for (int j = 0; j < 15; j++){ //odd rows have 15 columns
				if (j == 0){
					cout << left << setw(6) << "| ROW" << setw(3) << i << setw(3) << "|"; //print row number 
				}
				if (0 <= j && j <=13){
					cout << left << setw(3) << seatsArray[i][j] << " "; //print seat availability  
				}
				else if (j == 14){
					cout << left << setw(23) << seatsArray[i][j] << "|"; //print seat availability 
				}
			}
		}
		cout << endl;
	}

	for (int i = 0; i <92; i++){ //printing grid
		cout<<"-";
	}
	cout << endl;

}

double getCost(double** pricesArray, char** seatsArray, int userRow, int userCol){ //get ticket cost function 

	double cost = 0; //intialize cost varaible as 0

	if (userRow % 2 == 0){ //if user inputted column is even (20 rows)
		if (0 <= userRow && userRow <=14 && 0 <=userCol && userCol <= 19){ //if user input is valid 
			if (seatsArray[userRow][userCol] == '#'){ //if seat is available 
				cost = pricesArray[userRow][userCol]; //get price from pricesArray 
			}
		}
	}
	else{ //if user inputted column is odd (15 rows)
		if (0 <= userRow && userRow <=14 && 0 <=userCol && userCol <= 14){ //if user input is valid 
			if (seatsArray[userRow][userCol] == '#'){ //if seat is available 
				cost = pricesArray[userRow][userCol]; //get price from pricesArray 
			}
		}
	}

	return cost; //returns ticket price if seat is available and returns 0 if seat is invalid/unavailable

}

void printPrice(double** pricesArray, char** seatsArray, int userRow, int userCol){ //print price of ticket function 

	double cost = getCost(pricesArray, seatsArray, userRow, userCol); //initialize cost with getCost function 

	if (cost == 0){ //if seat is invalid/unavailable 
			if (userRow % 2 == 0){ //if user inputted column is even (20 rows)
				if (0 <= userRow && userRow <=14 && 0 <=userCol && userCol <= 19){ //if user input is valid 
					cout << "\nSorry, Row " << userRow << " Seat " << userCol << " is unavailable." << endl; 
				}
				else{ //if user input is invalid 
					cout << "\nInvalid Seat." << endl;
				}
			}
			else{ //if user inputted column is odd (15 rows)
				if (0 <= userRow && userRow <=14 && 0 <=userCol && userCol <= 14){ //if user input is valid 
					cout << "\nSorry, Row " << userRow << " Seat " << userCol << " is unavailable." << endl; 
				}
				else{ //if user input is invalid 
					cout << "\nInvalid Seat." << endl;
				}
			}
		}

	else{ //if seat is available 
		cout << "\nPrice: $" << fixed << setprecision(2) << cost << endl; //display ticket price
	}

	cout << endl;

}

char** updateSeats(char** seatsArray, int userRow, int userCol){ //update seats function 

	if (userRow % 2 == 0){ //if user inputted column is even (20 rows)
		if (0 <= userRow && userRow <=14 && 0 <=userCol && userCol <= 19){ //if user input is valid 
			if (seatsArray[userRow][userCol] == '#'){ //if seat is available 
				seatsArray[userRow][userCol] = 'X'; //update seat to unavailable 
			}
		}
	}
	else{ //if user inputted column is odd (15 rows)
		if (0 <= userRow && userRow <=14 && 0 <=userCol && userCol <= 14){ //if user input is valid 
			if (seatsArray[userRow][userCol] == '#'){ //if seat is available 
				seatsArray[userRow][userCol] = 'X'; //update seat to unavailable 
			}
		}
	}

	return seatsArray; //return updated seats array 
	
}

void updateFile(char** seatsArray){ //update "seats.txt" file function 

	ofstream seats; //output stream class

	seats.open("seats.txt"); //open seats.txt file

	for (int i = 0; i < 10; i++){ //print column numbers 
		seats << i << " ";
	}
	for (int i = 0; i < 10; i++){ //print column numbers 
		seats << i << " ";
	}
	seats << endl; 

	for (int i = 0; i < numRows; i++){ //loop through rows 
		if (i % 2 == 0){ //if even
			for (int j = 0; j < 20; j++){ //even rows have 20 columns 
				seats << seatsArray[i][j] << " "; //input seat availability 
			}
			seats << endl;
		}
		else{ //if odd 
			for (int j = 0; j < 15; j++){ //odd rows have 15 columns 
				seats << seatsArray[i][j]<< " "; //input seat availability 
			}
			seats << endl;
		}
	}

	seats.close(); //close file 

}

int main(){

	double** pricesArray = new double* [numRows]; //create array of double pointers with 15 rows 
	for (int i = 0; i < numRows; i++){
		if (i % 2 == 0){ //if even
			pricesArray[i] = new double [20]; //create 20 columns in the even rows of double pointers 
		}
		else{ //if odd
			pricesArray[i] = new double [15]; //create 15 columns in the odd rows of double pointers
		}
	}

	char** seatsArray = new char* [numRows]; //create array of character pointers with 15 rows 
	for (int i = 0; i < numRows; i++){
		if (i % 2 == 0){ //if even
			seatsArray[i] = new char [20]; //create 20 columns in the even rows of double pointers 
		}
		else{ //if odd
			seatsArray[i] = new char [15]; //create 15 columns in the odd rows of double pointers
		} 
	}

	getPrices(pricesArray); //call on getPrices function 

	getSeats(seatsArray); //call on getSeats function 

	printSeats(seatsArray); //call on printSeats function 

	double moneyRaised = 0; //intialize variable for total money raised 

	int numPurchase; //variable for number of tickets user would like to buy
												 
	int userRow, userCol; //variables for user inputed row and column 

	string option = "y"; //initialize option as 'y'

	double totalCost = 0; //variable for total cost of each customer purchase 

	while (option == "y" || option == "Y"){ //while the user choses to continue 

		if (totalSold(pricesArray, seatsArray) < 265){ //if tickets are available 

			cout << "\nPlease Input the Number of Tickets You Would Like to Purchase: "; //prompt user for number of tickets 
			cin >> numPurchase; //store input 
			cout << endl;

			if (numPurchase <= 265 - totalSold(pricesArray, seatsArray)){ //if there are enough seats available 

				for (int i = 0; i < numPurchase; i++){ //loop through number of purchases 
					cout << "\nTicket " << i + 1 << endl; //print seat number
					cout << "\nRow Number: "; //prompt user for row number 
					cin >> userRow; //store input 
					cout << "Seat Number: "; //prompt user for seat number 
					cin >> userCol; //store input 

					printPrice(pricesArray, seatsArray, userRow, userCol); //call on printPrice function 

					totalCost += getCost(pricesArray, seatsArray, userRow, userCol); //add cost onto total cost 
					
					updateSeats(seatsArray, userRow, userCol); //update seatsArray 

					updateFile(seatsArray); //call on updateFile function to update "seats.txt"
				}
				cout << "\nYour Subtotal is $" << fixed << setprecision(2) << totalCost << endl; //display cost of subtotal 
			}

			else{ //if there aren't enough seats available 
				cout << "\nSorry, there are only " << 265 - totalSold(pricesArray, seatsArray) << " Seat(s) Available." << endl;
			} 

			cout << "\n\nContinue Purchase? (y/n): "; //ask user if they would like to make another purchase 
			cin >> option; 
			cout << endl;

			while (option != "y" && option != "Y" && option != "n" && option != "N"){ //if the input is invalid, loop until the user enteres a valid input  
				cout << "Invalid Input.";
				cout << "\n\nContinue Purchase? (y/n): ";
				cin >> option; 
				cout << endl;
			}

		}

		else{ //if all the tickets are sold 
			cout << endl << "Sorry, All Tickets are Sold Out." << endl << endl;
			break; //exit loop 
		}

	}

		if (totalCost > 0){ //if user bought tickets
			cout << "\nPlease Pay Your $" << totalCost << " Total" << endl << endl; //display the total cost of all of the user's purchases 
			cout << "Thank You for Your Purchase" << endl << endl << endl; //display thank you message
		}
		else{ //if user didn't buy tickets or all tickets are sold out 
			cout << "\nYour Total is $0.00" << endl << endl << endl; //display the total cost of all of the user's purchases
		} 

		moneyRaised = totalRaised(pricesArray, seatsArray, moneyRaised); //call on totalRaised function 
	
		cout << "Total Amount of Money Raised: $" << fixed << setprecision(2) << moneyRaised << endl << endl; //display total money raised 

		cout << "Total Number of Seats Sold: " << totalSold(pricesArray, seatsArray) << endl << endl; //display number of seats sold 

		cout << "Number of Available Seats: " << 265 - totalSold(pricesArray, seatsArray) << endl << endl; //display number of available seats 

}