#include <iostream>
#include <cstdlib>   
#include <ctime>
using namespace std;

enum enQuestionsLevel { Easy = 1, Mid = 2, Hard = 3, MixLevel = 4 };

enum enOperatingType { Sum = 1, Sub = 2, Mult = 3, Div = 4, MixOperating = 5 };

enum enFinalResult { fail = 0, Pass = 1, Draw = 2 };

struct stGameInfo
{
    bool IsPass = false;
    short TotalRound = 0;
    enOperatingType OperatingType = ::Sum;
    enQuestionsLevel QuestionsLevel = ::Easy;
    short NumberOfRightQuestions = 0;
    short NumberOfWrongQuestions = 0;
};

// This Function Generate Random Number Between Two Values ;
short RandomNumber(int From, int To)
{
    short randNum = rand() % (To - From + 1) + From;
    return randNum;
}

// Get Number Of Rounds The User Want To Play ;
unsigned short ReadTotalRound(string Message) {

    unsigned short Number = 0;
    cout << Message << "\n";
    cin >> Number;
    return Number;

}

// Get The Level Of Question From User To Generate In Another Function ;
enQuestionsLevel ReadQuestionsLevel(string Message) {

    unsigned short Number = 0;
    do
    {
        cout << Message << "\n";
        cin >> Number;
    } while (!(Number >= Easy && Number <= MixLevel));
    return (enQuestionsLevel)Number;
}

// Get The Operating Type From User To Generate In Another Function ;
enOperatingType ReadOperatingType(string Message) {

    unsigned short Number = 0;
    do
    {
        cout << Message << "\n";
        cin >> Number;
    } while (!(Number >= Sum && Number <= MixOperating));
    return (enOperatingType)Number;
}

// This Function Generate Random Level If User Enter Mix Choice ;
enQuestionsLevel GetRandomLevel(enQuestionsLevel Level) {

    if (Level == enQuestionsLevel::MixLevel) {

        return (enQuestionsLevel)RandomNumber(enQuestionsLevel::Easy, enQuestionsLevel::Hard);
    }
    else {
        return Level;
    }
}

// This Function Knows Level From Another Function And Generates Number Based On It ;
short GenerateNumberByLevel(enQuestionsLevel Level) {

    switch (Level) {
    case enQuestionsLevel::Easy:
        return RandomNumber(1, 10);
    case enQuestionsLevel::Mid:
        return RandomNumber(11, 50);
    case enQuestionsLevel::Hard:
        return RandomNumber(51, 150);
    default:
        return 1;
    }
}

// This Function Generates Random Operating Type If User Enter Mix Choice ;
enOperatingType GetRandomOperatingType(enOperatingType OperatingType) {

    if (OperatingType == enOperatingType::MixOperating)
    {
        return (enOperatingType)RandomNumber(Sum, Div);
    }
    else
    {
        return OperatingType;
    }
}

// This Function Used In Display And Takes Single Source Code Because It Does Not Make Any Confusion ;
char GetOperationSymbol(enOperatingType OpType) {

    switch (OpType) {
    case enOperatingType::Sum: return '+';
    case enOperatingType::Sub: return '-';
    case enOperatingType::Mult: return '*';
    case enOperatingType::Div: return '/';
    default: return '?';
    }
}

// To Know The Right Answer We Should Take The Same Operation Type And First Number And Second Number ( Single Source Code ) ;
short CalculateMathematicsByOperating(enOperatingType OperatingType, short FirstNumber, short SecondNumber) {

    switch (OperatingType)
    {
    case enOperatingType::Sum: return FirstNumber + SecondNumber;
    case enOperatingType::Sub: return FirstNumber - SecondNumber;
    case enOperatingType::Mult: return FirstNumber * SecondNumber;
    case enOperatingType::Div:
        if (SecondNumber == 0)
            return 0;
        else
            return FirstNumber / SecondNumber;

    default:
        return FirstNumber + SecondNumber;

    }
}

// We Use Single Responsibility Principle , This Title Has A Specific Function ;
void DisplayQuestionTitle(unsigned short TotalRound, unsigned short Round) {

    cout << "_________________[" << ++Round << "/" << TotalRound << "]___________________\n";

}

// Display The Question Numbers And Operation Symbol To The User ;
void DisplayQuestion(short FirstNumber, short SecondNumber, char OperType) {

    cout << FirstNumber << "\n";
    cout << OperType << "\n";
    cout << SecondNumber << "\n";
    cout << "____________________________________________\n";
}

// Take User Answer To Send It To The Validation Function ;
short ReadUserAnswer() {
    short UserAnswer = 0;
    cin >> UserAnswer;
    return UserAnswer;
}

// Validation Function That Compares User Answer With The Correct Answer ;
bool CheckAnswer(short UserAnswer, short CorrectAnswer) {

    return (UserAnswer == CorrectAnswer);

}

// Print Result Symbol And Show Correct Answer If Wrong ;
void PrintAnswerResult(bool IsCorrect, short CorrectAnswer) {

    if (IsCorrect) {
        cout << "Right Answer :-) \n";
    }
    else {
        cout << "Wrong Answer :-( \n";
        cout << "The right answer is: " << CorrectAnswer << "\n";
    }
}

// Generate Color Mode For Terminal Based On Answer Result ;
void SetScreenColor(bool IsCorrect) {

    if (IsCorrect) {
        system("color 2F");
    }
    else {
        system("color 4F");
        cout << "\a";
    }
}

// Reset Screen Color Back To Black ;
void ResetScreenColor() {
    system("color 0F");
}

// Ask User If He Wants To Repeat The Game ;
bool ShouldContinue() {
    char Response;
    cout << "\nDo you want to play again? (Y/N): ";
    cin >> Response;
    return (Response == 'y' || Response == 'Y');
}

// Count Right And Wrong Questions To Store Them In Game Info ;
stGameInfo CountRightQuestion(stGameInfo& GameInfo, bool State) {

    if (State == true)
    {
        GameInfo.NumberOfRightQuestions++;
    }
    else
    {
        GameInfo.NumberOfWrongQuestions++;
    }
    return GameInfo;
}

// Convert Level Enum To Readable Text To Display In Final Card ;
string GetLevelText(enQuestionsLevel Level) {
    string arrLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
    return arrLevelText[Level - 1];
}

// Convert Operating Type Enum To Readable Text To Display In Final Card ;
string GetOperatingTypeText(enOperatingType OpType) {
    string arrOpText[5] = { "Sum", "Sub", "Mult", "Div", "Mix" };
    return arrOpText[OpType - 1];
}

// Compare Right And Wrong Questions Count To Determine The Final Result ;
enFinalResult FinalResult(stGameInfo& GameInfo)
{
    if (GameInfo.NumberOfRightQuestions > GameInfo.NumberOfWrongQuestions)
    {
        return enFinalResult::Pass;
    }
    else if (GameInfo.NumberOfRightQuestions < GameInfo.NumberOfWrongQuestions)
    {
        return enFinalResult::fail;
    }
    else
    {
        return enFinalResult::Draw;
    }
}

// Convert Final Result Enum To Readable Text To Display In Final Card ;
string GetFinalResultText(enFinalResult FinalResult) {

    string arrOpText[3] = { "fail","Pass","Draw" };
    return arrOpText[FinalResult];

}

// Print All Game Statistics And Final Result At The End Of The Game ;
void PrintFinalResultsCard(stGameInfo& GameInfo, enOperatingType& OpType, enQuestionsLevel& Level) {

    enFinalResult Result = FinalResult(GameInfo);

    cout << "\n____________________________________________\n";
    cout << "           Final Results Card               \n";
    cout << "____________________________________________\n";
    cout << " Total Rounds     : " << GameInfo.TotalRound << endl;
    cout << " Question Level   : " << GetLevelText(Level) << endl;
    cout << " Operation Type   : " << GetOperatingTypeText(OpType) << endl;
    cout << " Right Answers    : " << GameInfo.NumberOfRightQuestions << endl;
    cout << " Wrong Answers    : " << GameInfo.NumberOfWrongQuestions << endl;
    cout << "____________________________________________\n";
    cout << " Final Result     : " << GetFinalResultText(Result) << endl;
    cout << "____________________________________________\n";

    if (Result == enFinalResult::Pass) system("color 2F");
    else if (Result == enFinalResult::fail) system("color 4F");
    else system("color 6F");
}

// Main Game Loop That Controls All Rounds And Calls All Functions ;
void StartGame() {

    do {
        stGameInfo GameInfo;

        system("cls");

        unsigned short TotalRound = ReadTotalRound("Please Enter Total Round Do You Want Play It ?");

        GameInfo.TotalRound = TotalRound;

        enQuestionsLevel QLevel = ReadQuestionsLevel("Please Enter Questions Level You Want It [1]= Easy [2]= Mid [3]= Hard [4]= Mix");



        enOperatingType OpeType = ReadOperatingType("Please Enter Operating Type You Want It [1]= Sum [2]= Sub [3]= Mult [4]= Div [5]= Mix");



        for (unsigned short CurrentRound = 0; CurrentRound < TotalRound; CurrentRound++) {

            enQuestionsLevel QuestionsLevel = GetRandomLevel(QLevel);

            enOperatingType OperatingType = GetRandomOperatingType(OpeType);

            char OperationSymbol = GetOperationSymbol(OperatingType);

            short FirstNumber = GenerateNumberByLevel(QuestionsLevel);

            short SecondNumber = GenerateNumberByLevel(QuestionsLevel);

            short RightAnswer = CalculateMathematicsByOperating(OperatingType, FirstNumber, SecondNumber);

            DisplayQuestionTitle(TotalRound, CurrentRound);

            DisplayQuestion(FirstNumber, SecondNumber, OperationSymbol);

            short UserAnswer = ReadUserAnswer();

            bool IsCorrect = CheckAnswer(UserAnswer, RightAnswer);

            SetScreenColor(IsCorrect);

            PrintAnswerResult(IsCorrect, RightAnswer);

            CountRightQuestion(GameInfo, IsCorrect);

        }

        PrintFinalResultsCard(GameInfo, OpeType, QLevel);

        ResetScreenColor();

    } while (ShouldContinue());
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}