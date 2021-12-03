//Program made by Victor Ekpenyong

//Included libraries
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
using namespace std;

//Function Declarations
int read_questions();
int read_answers();
void show_question();
void player_try();
void show_question2();
void player_try2();
void play_game();
void sort_score();

//Needed Global Variables
string qarray[50][5];
char ansarray[50];
char choice;
int randomNum;
int score = 1;
int finalScore = 0;
string name;
int fixed_seed;
string qFile;
string aFile;

//Main Function
int main(int argc, char* argv[])
{

    //Error checking to make sure argument count equals 4
    if(argc !=4)
    {
        cout << "Incorrect program usage." << endl << "Please read the program description and try again. Exiting." << endl;
        return -1;
    }

    //Declaration of question and answer file which will be used (user provides in argument count)
    qFile = argv[1];
    aFile = argv[2];

    //Converts last argument into an integer to use for srand()
    fixed_seed = atoi(argv[3]);

    read_questions();

    read_answers();

    //If either files could not be opened program terminates
    if(read_questions() == -5 || read_answers() == -5)
    {
        return -1;
    }

    //Checks to see if either questions or answers file is empty
    if(read_questions() == 0 || read_answers() == 0)
    {
        cout << "The question file or the answer file is empty." << endl << "Please check the files and try again. Exiting." << endl;
        return -1;
    }

    //Checks to see if questions and answers files match; if not program terminates
    if(!(read_questions() == read_answers()))
    {
        cout << "The question and answer files do not match." << endl << "Please check the files and try again. Exiting." << endl;
        return -1;
    }

    play_game();

    sort_score();


    //Graceful Exit
    return 0;
}

//Driving Functions

//reads questions from file and stores in 2D array
int read_questions()
{
    //Opening of questions text file
    ifstream fin4;
    fin4.open(qFile.c_str());

    //Error checking to see if questions file was opened
    if(!fin4.is_open())
    {
        cout << "Could not open questions file." << endl;
        return -5;
    }



    string question;
    int numq = 0;

    //Storing questions into array
    while (getline(fin4, question))
    {
        while (question.length() == 1)
        {
            getline(fin4, question);
        }

        qarray[numq][0] = question;

        for(int i=1; i<5; i++)
        {
            getline(fin4, qarray[numq][i]);
        }
        numq++;
    }

    //Closing of question file
    fin4.close();

    //Return value to determine if questions and answers files match
    return numq;

}


// reads answers from file and stores in 1D array
int read_answers()
{

    //Opening of answers text file
    ifstream fin5;
    fin5.open(aFile.c_str());

    //Error checking to see if answers file was opened
    if(!fin5.is_open())
    {
        cout << "Could not open answers file." << endl;
        return -5;
    }

    char answer;
    int numa = 0;

    //Storing answers into array
    while (fin5 >> answer)
    {
        ansarray[numa] = answer;
        numa++;
    }

    //Closing of answers file
    fin5.close();

    //Return value to determine if questions and answers files match
    return numa;

}


// displays question and responses
void show_question()
{

    //Switch statement within for loop which creates question display
    for(int j=0; j<5; j++)
    {
        switch(j)
        {
            case 0: cout << qarray[randomNum][0] << endl;
            break;
            case 1: cout << "A. " << qarray[randomNum][1] << endl;
            break;
            case 2: cout << "B. " << qarray[randomNum][2] << endl;
            break;
            case 3: cout << "C. " << qarray[randomNum][3] << endl;
            break;
            case 4: cout << "D. " << qarray[randomNum][4] << endl;
        }
    }
    cout << endl;

}



// displays question and responses after 1st incorrect response (hides previous answer)
void show_question2()
{

    //Switch statement within for loop which creates question display
    for(int j=0; j<5; j++)
    {
        switch(j)
        {
            case 0: cout << qarray[randomNum][0] << endl;
            break;
            case 1: if(choice == 'A'){cout << endl;} else {cout << "A. " << qarray[randomNum][1] << endl;}
            break;
            case 2: if(choice == 'B'){cout << endl;} else {cout << "B. " << qarray[randomNum][2] << endl;}
            break;
            case 3: if(choice == 'C'){cout << endl;} else {cout << "C. " << qarray[randomNum][3] << endl;}
            break;
            case 4: if(choice == 'D'){cout << endl;} else {cout << "D. " << qarray[randomNum][4] << endl;}
        }
    }
    cout << endl;

}



//Allows for player input
void player_try()
{

    //do while loop which runs until proper input is registered
    do
    {
        //Calling of show_question() fucntion to display question
        show_question();

        cout << "Your choice? >";
        cin >> choice;
        //toupper function allowing for input of any case
        choice = toupper(choice);

        //Output message if input is not A through D
        if(!(choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D'))
        {
            cout << "Invalid Input, Try again" << endl;
        }
    }while(!(choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D'));

    cout << endl;
}



//Allows for player input after 1st incorrect response
void player_try2()
{

    //do while loop which runs until proper input is registered
    do
    {
        //Calling of show_question() fucntion to display question
        show_question2();

        cout << "Your choice? >";
        cin >> choice;
        //toupper function allowing for input of any case
        choice = toupper(choice);

        //Output message if input is not A through D
        if(!(choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D'))
        {
            cout << "Invalid Input, Try again" << endl;
        }
    }while(!(choice == 'A' || choice == 'B' || choice == 'C' || choice == 'D'));

    cout << endl;
}



//Function which enacts the game play
void play_game()
{

    //srand() initialized
    srand(fixed_seed);

    int qnum = 1;
    char tryagain;
    bool used[50];

    //Prompts the user for their name; Referred as this name throughout program
    cout << "What's your name?>";
    cin >> name;

    //For loop used to store random generated values
    for (int i = 0; i < 50; i++)
    {
        used[i] = false;
    }

    //Do while loop which runs until after the completion of the 6th question
    do
    {

        //Storing of random number into variable
        randomNum = rand()%50;

        //if else statements which checks if random value has been used yet
        if(used[randomNum]==false)
        {
            used[randomNum] = true;
        }
        else
        {
            do
            {
                randomNum = rand()%50;
            }while(used[randomNum]==true);
        }
        used[randomNum] = true;


        //First line shown at the start of new question
        cout << name << "  Here's Question Number " << qnum << endl;

        //Calling of player_try() function
        player_try();



        //If Else statements which check if user inputted choice is equal to character in answer array

        //Input matches answer on file (user gets the answer correct)
        if(choice == ansarray[randomNum])
        {
            //If question number is 6, add up final score and do while loop ends
            if(qnum == 6)
                    {
                        score *= 10;
                        finalScore += score;
                        cout << "Goodjob!" << endl << "That's the end of the game, there are no more questions!" << endl << endl;
                    }
            //If question number does not equal 6, add to score and add score to final score and run loop again
            else
            {
                score *= 10;
                finalScore += score;
                cout << "You got that right for " << score << " points!" << endl;
                cout << "Goodjob, next question" << endl << endl;
            }
        }

        //Input does not match answer on file (user gets the answer incorrect)
        else
        {

            //do while loop which prompts user if they would like to try again; loop runs until proper character input is given
            do
            {
                cout << "Incorrect Answer, would you like to try again for half(1/2) points? (Y/N)>";
                cin >> tryagain;
                //toupper function allowing for input of any case
                tryagain = toupper(tryagain);

                //Output message if input is not Y for yes or N for no
                if(!(tryagain == 'Y' || tryagain == 'N'))
                {
                    cout << "Invalid Input, try again" << endl;
                }
            }while(!(tryagain == 'Y' || tryagain == 'N'));

                //User elects to try question again
                if(tryagain == 'Y')
                {
                    //Calling of player_try() function
                    cout << name << "  Here's Question Number " << qnum << " (2nd Try)" << endl;
                    player_try2();

                    //Input matches answer on file (user gets the answer correct)
                    if(choice == ansarray[randomNum])
                    {
                        //If question number is 6, add up final score and do while loop ends
                        if(qnum == 6)
                        {
                            //Score worth half points now
                            score = (score * 10) / 2;
                            finalScore += score;
                            cout << "You got that right for " << score << " points!" << endl;
                            cout << "Goodjob!" << endl << "That's the end of the game, there are no more questions!" << endl << endl;
                        }
                        //If question number does not equal 6, add to score and add score to final score and run loop again
                        else
                        {
                            //Score worth half points now
                            score = (score * 10) / 2;
                            finalScore += score;
                            cout << "You got that right for " << score << " points!" << endl;
                            cout << "Goodjob, next question" << endl << endl;
                        }
                    }

                    //Input does not match answer on file (user gets the answer incorrect AGAIN)
                    else
                    {
                        //Game ENDS; score becomes 0; Loop execution stops
                        cout << "Incorrect again. Sorry, but you've lost." << endl << "Come back again after you've studied some more" << endl << endl;
                        score = 0;
                        finalScore = score;
                        break;
                    }
                }

                //User does not elect to try question again
                if(tryagain == 'N')
                {
                    //If question number was 6, game ends
                    if(qnum == 6)
                    {
                        cout << "That's the end of the game, there are no more questions!" << endl << endl;
                    }
                    //If question number is less than 6 move onto the next question
                    else
                    {
                        cout << "Onto the next question" << endl << endl;
                    }
                }

        }
        //question number is increased
        qnum++;
    }while(qnum < 7);

    //User got every question incorrect, but chose not to have a second attempt at all
    if(finalScore == 1)
    {
        finalScore = 0;
    }

    //Output message after completion of game
    cout << name << ", your final score was: " << finalScore << endl << "This will be recorded to the game history file." << endl << endl;
}

//Function which sorts score into file and outputs positions
void sort_score()
{
    //Output file being opened
    ofstream fout;
    fout.open("summary.txt", std::ofstream::app);

    //Error checking to see if summary text file is open; (should not run since file will be created if not already existing)
    if(!fout.is_open())
    {
        cout << "Could not open summary file." << endl;
    }

    //Layout of each participant and their score being stored in file
    fout << setw(20) << left << name << setw(10) << " " << setw(7) << right << finalScore << endl;
    //Closing of summary file
    fout.close();

    //Opening of summary file (in order to write to it)
    ifstream fin3;
    fin3.open("summary.txt");

    //Error checking to see if summary text file is open;
    if(!fin3.is_open())
    {
        cout << "Could not open summary file." << endl;
    }

    string sumName[500];
    int sumScore[500];
    string sumArray[500];

        //Storing name and score values from function into 2 arrays
        for(int i=0; i<500; i++)
        {
            fin3 >> sumName[i] >> sumScore[i];
        }

        //Storing each line of summary file into string array
        for(int z=0; z<500; z++)
        {
            getline(fin3, sumArray[500]);
        }

    int big, tempint, place;
    string temp;
    //Rank sort which sorts scores and names from file from greatest to smallest to determine highest score member
    for (int i = 0; i < 499; ++i)
    {
      big = i;
      for (int j = i + 1; j < 500; ++j) {

         if ( sumScore[j] > sumScore[big] ) {
            big = j;
         }
    }


      temp = sumName[i];
      sumName[i] = sumName[big];
      sumName[big] = temp;

      tempint = sumScore[i];
      sumScore[i] = sumScore[big];
      sumScore[big] = tempint;
   }

   //Running for loop to place new order of names in position after sort
   for(int q=0; q<500; q++)
   {
       if(name==sumName[q])
       {
           place = q;
       }
   }

    //Out put message after game is over
    cout << "The current record holder is " << sumName[0] << " with " << sumScore[0] << " points." << endl;
    cout << "Your have achieved rank " << place + 1 << " with " << finalScore << " points!" << endl << endl << "Thanks for playing, we hope you'll send all your friends to play." << endl;

    //closing of summary text file
    fin3.close();


}


