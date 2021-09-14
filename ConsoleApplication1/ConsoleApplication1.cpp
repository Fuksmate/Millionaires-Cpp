#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <ctype.h>
#include <string>
#include <sstream>
#include <cwchar>

#pragma comment(lib, "user32")

using namespace std;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
// Globalne zmienne
char SelectCategory;
string name, leader = "Prowadzacy";
int CorrectAnswer = 0, MonetaryThreshold = 1, tab[12];
string SortingAnswerTab[4][2] = { {"",""},{"",""},{"",""},{"",""} };
string Question, AnswerA, AnswerB, AnswerD, AnswerC, Answer;
string Money[13] = { "0", "500", "1 000", "2 000", "5 000", "10 000", "20 000", "40 000", "75 000", "125 000", "250 000", "500 000", "1 000 000" };
bool  PublicOpinionIsReady = true, FiftyToFiftyIsReady = true, PhoneToFriendIsReady = true;

////// TXT COLOR////
void OliveColor() {
    SetConsoleTextAttribute(hConsole, 6);
}
void BlueColor() {
    SetConsoleTextAttribute(hConsole, 9);
}
void YellowColor() {
    SetConsoleTextAttribute(hConsole, 14);
}

///////Centrowanie Tresci/////
void CenterString(char const* s)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize;
    NewSBSize = GetLargestConsoleWindowSize(hOut);
    int l = strlen(s);
    int pos = (int)((NewSBSize.X - l) / 2);
    for (int i = 0; i < pos; i++)
        cout << " ";

    cout << s << endl;
}

void OneQuarterString(char const* s)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD NewSBSize;
    NewSBSize = GetLargestConsoleWindowSize(hOut);
    int l = strlen(s);
    int pos = (int)((NewSBSize.X - l) / 4);
    for (int i = 0; i < pos; i++)
        cout << " ";

    cout << s;
}

////////Fullscreen////
void Fullscreen() {
    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

////remove scrollbar////
void remove_scrollbar()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsole, &info);
    COORD new_size =
    {
        info.srWindow.Right - info.srWindow.Left + 1,
        info.srWindow.Bottom - info.srWindow.Top + 1
    };
    SetConsoleScreenBufferSize(hConsole, new_size);
}

////Przywitanie prowadzacego////
void StartOfTheProgram()
{
    CenterString("Podaj swoje imie:");
    cin >> name;
    system("cls");
    BlueColor();
    CenterString((leader + ": Witam was wszystkich w teleturnieju MILIONERZY").c_str());
    CenterString((leader + ": W dzisiejszym programie wystapi " + name).c_str());
    CenterString((leader + ": " + name + " stresujesz sie?").c_str());
    YellowColor();
    CenterString((name + ": Nie, Przyszedlem po milion i licze na wygrana").c_str());
    BlueColor();
    CenterString((leader + ": No dobrze wiec zaczynajmy").c_str());
}

void Category()
{
    CenterString((leader + ": Pytanie za " + Money[MonetaryThreshold]).c_str());
    CenterString((leader + ": Prosze cie o wybranie kategorii").c_str());
    OneQuarterString("A. Historia");
    CenterString("B. Matematyka");
    OneQuarterString("C. Swiat");
    CenterString("D. Przyroda");
    cin >> SelectCategory;
}

void SelectQuestion()
{
    Category();
    fstream plik;
    switch (toupper(SelectCategory))
    {
    case 'A':
        plik.open("Historia.txt", ios::in);
        break;
    case 'B':
        plik.open("Matematyka.txt", ios::in);
        break;
    case 'C':
        plik.open("Swiat.txt", ios::in);
        break;
    case 'D':
        plik.open("Przyroda.txt", ios::in);
        break;
    default:
        system("cls");
        cout << "Error/ Blad zaladowania pliku" << endl;
    }
    if (plik.good() == true)
    {
        int RandomNumber, pom = 0;
        //For żeby nie powtarzały sie pytania
        for (int i = 0; i != -1; i++) {
            RandomNumber = rand() % 20;
            for (int x = 0; x != 12; x++)
            {
                if (RandomNumber == tab[x]) {
                    pom++;
                }
            }
            if (pom == 0) {
                i = -2;
            }
        }
        tab[MonetaryThreshold] = RandomNumber;
        for (int i = 0; i <= RandomNumber; i++) {
            getline(plik, Question);
            getline(plik, AnswerA);
            getline(plik, AnswerB);
            getline(plik, AnswerC);
            getline(plik, AnswerD);
            getline(plik, Answer);
        }
        plik.close();
    }
}

void GoodAnswer() {
    SetConsoleTextAttribute(hConsole, 2);
    CenterString((leader + ": To jest poprawna odpowiedz").c_str());
    CenterString((leader + ": Obecnie masz " + Money[MonetaryThreshold] + " zolotych").c_str());
    system("pause");
    system("cls");
    CorrectAnswer++;
}

void WrongAnswer() {
    SetConsoleTextAttribute(hConsole, 4);
    CenterString((leader + ": Niestety, to byla zla odpowiedz").c_str());
    CenterString((leader + ": Poprawna odpowiedz to: " + Answer).c_str());
    CenterString((leader + ": Wygrales " + Money[MonetaryThreshold - 1] + " zlotych. Gratulacje").c_str());
    MonetaryThreshold = 12;
}

void Victory()
{
    string pom;
    system("cls");
    CenterString((leader + ": Gratulacje wygrales " + Money[MonetaryThreshold]).c_str());
    CenterString((leader + "Na co wydasz te pieniadze ").c_str());
    cin >> pom;
    CenterString((leader + "No dobrze wiec powodzenia ").c_str());
    CenterString("Koniec Gry");
    CenterString("******//********//*******||*|**********||***________***|/******|");
    CenterString("*****/**/******/**/******||*|**********||**|********|**|*/*****|");
    CenterString("****/****/****/****/*****||*|**********||**|********|**|**/****|");
    CenterString("***/******/**/******/****||*|**********||**|********|**|***/***|");
    CenterString("**/********//********/***||*|**********||**|********|**|****/**|");
    CenterString("*/********************/**||*|________**||**|________|**|*****/*|");
}

void ShowingAudienceVotes(int auxiliary) {
    BlueColor();
    for (int i = 0; i != auxiliary; i++)
        cout << "|";
    YellowColor();
    for (auxiliary; auxiliary != 100; auxiliary++)
        cout << "|";

    cout << endl;
}

void PercentageChance(string a) {
    for (int i = 0; i < 4; i++)
    {
        if (SortingAnswerTab[i][1] == a) {
            OneQuarterString((a + "  " + SortingAnswerTab[i][0]).c_str());
            ShowingAudienceVotes(stoi(SortingAnswerTab[i][0]));
        }
    }
}

void GeneratingInterest() {
    int auxiliary, LastNumber = 0;
    for (int i = 0; i != 3; i++) {
        SortingAnswerTab[i][0] = to_string(rand() % (100 - LastNumber));
        istringstream(SortingAnswerTab[i][0]) >> auxiliary;
        LastNumber = LastNumber + auxiliary;
    }
    SortingAnswerTab[3][0] = to_string(100 - LastNumber);
}

void SortingAnswer() {
    int CorrectAnswerNumber = 0, auxiliary = 0;
    string taba[4] = { "A","B","C","D" };
    for (CorrectAnswerNumber; CorrectAnswerNumber < 4; CorrectAnswerNumber++) {
        if (Answer == taba[CorrectAnswerNumber]) {
            break;
        }
    }
    for (CorrectAnswerNumber; CorrectAnswerNumber < 4; CorrectAnswerNumber++) {
        SortingAnswerTab[auxiliary][1] = taba[CorrectAnswerNumber];
        auxiliary++;
        if (auxiliary == 4) {
            break;
        }
        if (CorrectAnswerNumber == 3) {
            CorrectAnswerNumber = -1;
        }
    }
}

void PublicOpinion() {
    GeneratingInterest();
    SortingAnswer();
    YellowColor();
    PercentageChance("A");
    PercentageChance("B");
    PercentageChance("C");
    PercentageChance("D");
}

void CheckingResponses(string CorrectAnswer) {
    char char_Answer;
    char_Answer = CorrectAnswer[0];
    char char_Answer2;
    char_Answer2 = Answer[0];
    if (char_Answer2 == toupper(char_Answer)) {
        GoodAnswer();
    }
    else {
        WrongAnswer();
    }
}

void PhoneToFriend() {
    CenterString((leader + ": Dzien dobry Panie Wojtku dzwonimy z programu Milionerzy ").c_str());
    CenterString(("Wojtek: Wdlug mnie to odpowiedz " + Answer).c_str());
}

void FiftyToFifty() {
    string tab1[4] = { "A","B","C","D" };
    string tabP[2];
    int i, a;
    for (i = 0; i <= 3; i++) {
        if (tab1[i] == Answer) {
            tabP[0] = Answer;
            break;
        }
    }

    for (a = 0; ; a++) {
        a = (rand() % 4);
        if (a == i) {

        }
        else {
            break;
        }
    }
    if (a == 0 || i == 0) {
        CenterString(("A. " + AnswerA).c_str());

        if (a == 1 || i == 1) {
            CenterString(("B. " + AnswerB).c_str());
        }
        if (a == 2 || i == 2) {
            CenterString(("C. " + AnswerC).c_str());
        }
        if (a == 3 || i == 3) {
            CenterString(("D. " + AnswerD).c_str());
        }

    }
}

void CheckingAnswer(string CorrectAnswer) {
    if (CorrectAnswer == "1") {
        PublicOpinion();
        PublicOpinionIsReady = false;
        cin >> CorrectAnswer;
        CheckingResponses(CorrectAnswer);
    }
    else if (CorrectAnswer == "2") {
        FiftyToFifty();
        FiftyToFiftyIsReady = false;
        cin >> CorrectAnswer;
        CheckingResponses(CorrectAnswer);
    }
    else if (CorrectAnswer == "3") {
        PhoneToFriend();
        PhoneToFriendIsReady = false;
        cin >> CorrectAnswer;
        CheckingResponses(CorrectAnswer);
    }
    else if (CorrectAnswer == "P") {
        Victory();
        MonetaryThreshold = 12;
    }
    else {
        CheckingResponses(CorrectAnswer);
    }

}

void FAQ(int QuestionNumber) {

    string CorrectAnswer, Number = to_string(QuestionNumber), auxiliary;

    BlueColor();
    CenterString((leader + ": " + Number + ". " + Question).c_str());
    OliveColor();
    OneQuarterString(("A. " + AnswerA).c_str());
    CenterString(("B. " + AnswerB).c_str());
    OneQuarterString(("C. " + AnswerC).c_str());
    CenterString(("D. " + AnswerD).c_str());
    CenterString("KOLA RATUNKOWE");
    if(PublicOpinionIsReady)
    CenterString("1. Zapytaj Publicznosci");
    if(FiftyToFiftyIsReady)
    CenterString("2. 50 na 50");
    if(PhoneToFriendIsReady)
    CenterString("3. Telefon do przyjaciela");
    CenterString("Mozesz zrezygnowac klikajac 'P'");
    cin >> CorrectAnswer;
    if (!PublicOpinionIsReady && CorrectAnswer == "1" || !FiftyToFiftyIsReady && CorrectAnswer == "2" || !PhoneToFriendIsReady && CorrectAnswer == "3") {
        CenterString("Wykorzystales to kolo ratunkowe");
        cin >> CorrectAnswer;
        CheckingAnswer(CorrectAnswer);
    }else {
        if (CorrectAnswer == "1" || CorrectAnswer == "2" || CorrectAnswer == "3") {
            CheckingAnswer(CorrectAnswer);
        }
        else {
            CenterString((leader + ": Czy jestes pewny?").c_str());
            CenterString("Tak/Nie");
            cin >> auxiliary;
            if (auxiliary == "Tak") {
                CheckingAnswer(CorrectAnswer);
            }
            else if (auxiliary == "Nie") {
                cin >> CorrectAnswer;
                CenterString((leader + ":   Podaj jeszcze raz odpowiedz").c_str());
                CheckingAnswer(CorrectAnswer);
            }
        }
    }
}
int main()
{
    remove_scrollbar();
    Fullscreen();
    srand((unsigned int)time(NULL));
    StartOfTheProgram();
    for (MonetaryThreshold; MonetaryThreshold != 13; MonetaryThreshold++) {
        SelectQuestion();
        FAQ(MonetaryThreshold);
        if (CorrectAnswer == 12) {
            Victory();
        }
    }
    return 0;
}
