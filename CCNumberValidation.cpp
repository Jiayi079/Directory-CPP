//
// Created by Eva Gu on 3/4/22.
//

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

bool isvalidcc(const string& cardNumbers);
bool cardValdations(const string& cardNumbers);
int doubleOddsSum(const string& cardNumbers);
int doubleEvenSum(const string& cardNumbers);

int getSingleDigit(int num);

int main()
{
    //
    // PLEASE DO NOT CHANGE function main
    //

    vector<string> cardnumbers = {
            "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
            "4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
            "5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
            "4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
            "5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
            "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
            "4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
            "5556551555555557", "6011316011016011"
    };



    int i;
    vector<string>::iterator itr;

    for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
        cout << setw(2) << i << " " << setw(17) << *itr
             << ((isvalidcc(*itr)) ? " is valid " : " is not valid") << endl;
        //cout << "Default : " << char(result) << endl;
        //cout << "RESULT : " << char(result) << endl;
    }

    return 0;
}
bool isvalidcc(const string& cardNumbers) {
    if (13 <= cardNumbers.size()  &&
        cardNumbers.size() <= 16 &&// check credit card number must between 13 and 16 digits
        cardValdations(cardNumbers) && // check if the starting number are valid
        // check if the sum of second-digit and the single-digit is divisible by 10
        (doubleEvenSum(cardNumbers) + doubleOddsSum(cardNumbers)) % 10 == 0) {
        return true;
    } else {
        return false;
    }
}

/* this method will check the card numbers' starting number car valid or not
 * 4, 5, 37, 6 --> valid
 * others --> invalid
 */
bool cardValdations(const string& cardNumbers) {
    if (cardNumbers[0] == '4' ||
        cardNumbers[0] == '5' ||
        (cardNumbers[0] == '3' && cardNumbers[1] == '7') ||
        cardNumbers[0] == '6') {
        return true;
    } else {
        return false;
    }
}

/* Double every second digit from right to left. If doubling of a digit results in
 * a two-digit number, add the two digits to get a single digit number.
 */
int doubleEvenSum(const string& cardNumbers) {
    int total = 0;

    // get right to left each second number
    for (int i = cardNumbers.size() - 2; i >= 0; i -= 2) {
        // call getSingleDigit method will return the sum of the number if number is two-digit number
        total += getSingleDigit((cardNumbers[i] - 48) * 2);
    }
    return total;
}

/*
 * if num --> 1 digit --> return single digit
 * if num --> 2 digit --> return sum of those two digits
 */
int getSingleDigit(int num) {
    if (num >= 10) {
        return ((num / 10) + (num % 10));
    }
    return num;
}

// add all digits in the odd places from right to left in the card number
int doubleOddsSum(const string& cardNumbers) {
    int total = 0;
    for (int i = cardNumbers.size() - 1; i >= 0; i -= 2) {
        total += cardNumbers[i] - 48;
    }
    return total;
}






#include "CCNumberValidation.h"
