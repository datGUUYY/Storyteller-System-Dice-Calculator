//Roughly the equivalent of an h file.
//Struct for the organization of dice.
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
struct dORG {
	int twos;
	int ones;
	int nones; //more fun than saying 'zeroes', I don't care.
};
int factorial(int); //ONLY FOR POSITIVE VALUES
vector<struct dORG> Append(vector<struct dORG>);
vector<struct dORG> organize(int, int);
double calcProb(vector<struct dORG>);
double calcProbdORG(struct dORG);

int main()
{
	//Tests
//	cout<<"Factorial of 3, 4, 5. Should be 6, 24, 120\n"<<factorial(3)<<' '<<factorial(4)<<' '<<factorial(5)<<' ';
//	cout<<"Factorial test passed. Testing Append. All values should have 1 for their 'twos' value. Should return 1\n";
//	cout<<"Append has passed. Testing dice organization function, should return 0,1,0:\n";
//	cout<<"In minimal testing, organization function has passed. Testing calculate function on dORG:\n";
//	cout<<"Tested a fair number of dORG calculations, consider testing to be done.\n\n";
//	int input = 1;
//	int nDice = 1;
//	int sTotal = 0;
	/*
	do {
		cin>>nDice;
		cout<<"Enter a desired total:\n";
		cin>>input;
		sTotal = input;
		cout<<"The probability of rolling "<<sTotal<<" on "<<nDice<<"dice is "<<calcProb(organize(nDice,sTotal));
		cout<<"\nEnter a number of dice:\n";
	} while(input != 25);
	*/
	//calcProb(organize(nDice,sTotal)); THIS IS THE IMPORTANT THING!!!
	int nDice = 1; //number of dice
	while (nDice != 0)
	{
		cout<<"Enter the number of dice you want to roll!\n";
		cin>>nDice;
		for(int sTotal = 0; sTotal < 1 + nDice * 2; sTotal++)
		{
			cout<<sTotal<<"||";
			double percentage = calcProb(organize(nDice,sTotal));
			for (double i = 0.0; i <1.0; i += 0.01)
				if(i < percentage)
					cout<<'!';
				else
					cout<<'.';
			cout<<100*percentage<<'\%'<<'\n';
		}
	}
	
	return 0;
}

//recursive factorial function
int factorial(int value)
{
	if (value <= 1)
		return 1;
	else
		return value * factorial(value - 1);
}
//function that takes the vector of organizations and returns a vector with one more double.
vector<struct dORG> Append(vector<struct dORG> value)
{
	vector<struct dORG> temp; //return value
	for(int i = 0; i < value.size(); i ++)
	{
		struct dORG dice_temp = value.at(i);
		dice_temp.twos++;
		temp.push_back(dice_temp);
	}
	return temp;
}


//Function that organizes the dice.
vector<struct dORG> organize(int numDice, int outcome)
{
	vector<struct dORG> value;
	if(outcome <= numDice)
	{
		struct dORG temp = {0, outcome, numDice - outcome};
		value.push_back(temp);
	}
	if (outcome >= 2)
	{
		vector<struct dORG> tempValue = Append(organize(numDice - 1, outcome - 2));
		for (int i = 0; i < tempValue.size(); i++)
			value.push_back(tempValue.at(i));
	}
	return value;
}
//Function that calculates the probabilities of each organization of the dice.

double calcProb(vector<struct dORG> value)
{
	double sum = 0.0; //Take the sum over each organization.
	for (int i = 0; i < value.size(); i++) //iterate over the possible die combinations.
	{
		//usually I would give a different step for calculating this but fuck it IM GOIN IN RAW
		//CALCULATE THE ODDS OF EACH DIE VALUE COMBINATION THAT ADDS TO THIS NUMBER.
		double temp; //this is the odds of rolling a given combination of dice.
		temp = calcProbdORG(value.at(i));
		
		sum+=temp;
	}
}

double calcProbdORG(struct dORG value)
{
	double temp;
	temp = pow(0.6, value.nones) * pow(0.3, value.ones) * pow(0.1, value.twos);
	//cout<<" POWERS: "<<temp; //Testing.
	temp *= factorial(value.nones+value.ones+value.twos); //X pick Y; find the factorial of the number of total dice, and divide by the factorial of each sub-group
	temp /= factorial(value.ones) * factorial(value.twos) * factorial(value.nones);
	//cout<<" FACT:"<<factorial(value.ones)*factorial(value.twos)*factorial(value.nones);
	return temp;
}
