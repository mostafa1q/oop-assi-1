/////////////
// Task 3: Problem is taken from the book: Problem Solving with C++,
// The problem number is 16 on page 505 (Exclude the last paragraph)
// This cpp file build for assignment 1 in programming 2 course
// This problem depends on the last number of student id and the student id who build this file is: 20150397
/////////////
// this lib uses to call the basic functionality of input and output
#include <iostream>
// this lib uses to identify vars with string type
#include <fstream>
// this lib uses to build vectors
#include <vector>
// this lib uses to convert string to integer
#include <sstream>
// this lib uses to call the function setw to add spaces before numbers
#include <iomanip>
// this lib uses to call the function find_if to find index object in vector by object properties
#include <algorithm>
// this lib uses to round float numbers
#include <math.h>

using namespace std;

// this struct uses to store time presented by hours, minutes, sencods
struct RaceTime 
{
    int hour;
    int minute;
    int second;
    
    void setTime(int h, int m, int s) {
        this->hour = h;
        this->minute = m;
        this->second = s;
    }
};

// this function uses to convert RaceTime object to seconds integer value
int GetSecByRaceTime(RaceTime t)
{
    return ((t.hour * 60 * 60) + (t.minute * 60) + t.second);
}

// this struct uses to store racers info
struct RaceTurn
{
    //int turnNumber;
    int racerNumber;
    RaceTime turnTime0;
    RaceTime turnTime1;
    RaceTime turnTime2;
    
    int overallFinishTimeInSecs;
    
    int timeBetweenSensor1And2;
    int timeBetweenSensor2And3;
    
    bool operator > (const RaceTurn& str) const
    {
        return (overallFinishTimeInSecs < str.overallFinishTimeInSecs);
    }
};

// this function to print RaceTime object
void PrintRaceTime(RaceTime rt)
{
      cout << setw(2) << setfill('0') << rt.hour << ":" 
            << setw(2) << setfill('0') << rt.minute << ":" 
            << setw(2) << setfill('0') << rt.second;
}

// this function to convert string value to integer
int StringToInteger(string NumberAsString)
{
	int NumberAsInteger;
	stringstream ss;
	ss << NumberAsString;
	ss >> NumberAsInteger;
	return NumberAsInteger;
}

// this function to get racer index from the vector by racer number
struct GetRaceTurnIndexByRacerID
{
 GetRaceTurnIndexByRacerID(const std::string& s) : s_(s) {}
 bool operator()(const RaceTurn& obj) const
 {
   
   return obj.racerNumber == StringToInteger(s_);
 }
 private: const std::string& s_;
};

// this function to check if the racer exist in the vector
int IsRacerExistInVector(vector<RaceTurn> v, string racerNum)
{
    // find index racer in vector by racer number
    std::vector<RaceTurn>::iterator it = std::find_if(v.begin(), v.end(), GetRaceTurnIndexByRacerID(racerNum));
    
    if(it != v.end()) { 
        return std::distance(v.begin(), it);
    } 
    else {
        return -1;
    }
}

// round float number two decimal places
float Round2(float f)
{
    return roundf((f)*100)/100;
}

// distance for all race
const float raceDistance = 13.1;
// distance between sensor 1 and split 2
const float distanceBetweenSplit1AndSplit2 = 7;
// distance between sensor 2 and split 3
const float distanceBetweenSplit2AndSplit3 = 6.1;

// print all racers info results 
void printAllRacers(vector<RaceTurn> vecOfStrs)
{
    for(int i = 0; i < vecOfStrs.size(); i ++)
    {
        cout << "Overall Place " << (i+1) << ": " << vecOfStrs[i].racerNumber 
             << " - Time Between S 1 and 2: " << Round2((((float)vecOfStrs[i].timeBetweenSensor1And2) / 60) / distanceBetweenSplit1AndSplit2)
             << " - Time Between S 2 and 3: " << Round2((((float)vecOfStrs[i].timeBetweenSensor2And3) / 60) / distanceBetweenSplit2AndSplit3)
             << " - Overall Time " << vecOfStrs[i].overallFinishTimeInSecs 
             << " - Overall Pace " << Round2((raceDistance / (((float)vecOfStrs[i].overallFinishTimeInSecs) / 60))) << " miles/minutes" 
             << endl;
    }
    cout << endl;
}

// print racer info results 
void printRacerInfoByNumber(vector<RaceTurn> vecOfStrs, string racerNum)
{
    int racerIndexInVector = -1;
    racerIndexInVector = IsRacerExistInVector(vecOfStrs, racerNum);
    
    if(racerIndexInVector <= -1)
    {
        cout << "Racer not exist in the file." << endl;
    }
    else
    {
        cout << "Overall Place " << (racerIndexInVector+1) << ": " << vecOfStrs[racerIndexInVector].racerNumber 
             << " - Time Between S 1 and 2: " << Round2((((float)vecOfStrs[racerIndexInVector].timeBetweenSensor1And2) / 60) / distanceBetweenSplit1AndSplit2)
             << " - Time Between S 2 and 3: " << Round2((((float)vecOfStrs[racerIndexInVector].timeBetweenSensor2And3) / 60) / distanceBetweenSplit2AndSplit3)
             << " - Overall Time " << vecOfStrs[racerIndexInVector].overallFinishTimeInSecs 
             << " - Overall Pace " << Round2((raceDistance / (((float)vecOfStrs[racerIndexInVector].overallFinishTimeInSecs) / 60))) << " miles/minutes" 
             << endl;
        cout << endl;
    }
}

static RaceTime fireTime = {};

int main(int argc, char **argv)
{
    // this var uses to read a text file line by line as string
	ifstream in("file.txt");
    // this var uses to store file line as a string
    string str; 
    // this flag just to ignore first line in the file because it is the fire time
    bool isFirstLine = true;
    // this var uses to store racers info that read from a text file
    vector<RaceTurn> vecOfStrs;
    // this var uses to get racer number and pass it to a function that will check if racer exist in vector
    string newRacerNumber = "";
    // this var uses to get the position index of racer in the vector
    int racerIndexInVector = 0;
    
    // Read the next line from File untill it reaches the end.
    while (std::getline(in, str))
    {   
        // Line contains string of length > 0 then save it in vector
        if(str.size() > 0)
        {
            // this flag just to ignore first line in the file because it is the fire time
            if(isFirstLine)
            {
                // set fire time in a separate struct
                isFirstLine = false;
                fireTime.hour = StringToInteger(str.substr(0,2));
                fireTime.minute = StringToInteger(str.substr(3,5));
                fireTime.second = StringToInteger(str.substr(6,8));
            }
            else
            {
                RaceTurn tmp = {};
                // get racer number
                newRacerNumber = str.substr(2,5);
                // call function to check if the racer exist in the vector
                racerIndexInVector = IsRacerExistInVector(vecOfStrs, newRacerNumber);
                //////////
                // check if the racer exist in the vector
                if(racerIndexInVector > -1)
                {
                    //  update time of racer if already exist in the vector 
                    if(StringToInteger(str.substr(0,1)) == 0)
                    {
                        vecOfStrs[racerIndexInVector].turnTime0.setTime(
                                      StringToInteger(str.substr(6,8)),
                                      StringToInteger(str.substr(9,11)),
                                      StringToInteger(str.substr(12,14)));
                    }
                    else if(StringToInteger(str.substr(0,1)) == 1)
                    {
                        //cout << "str " << str ;
                        //cout  << " h " << StringToInteger(str.substr(0,2)) << " m " << StringToInteger(str.substr(3,5)) << " s " << StringToInteger(str.substr(6,8)) <<   endl;
                        vecOfStrs[racerIndexInVector].turnTime1.setTime(
                                      StringToInteger(str.substr(6,8)),
                                      StringToInteger(str.substr(9,11)),
                                      StringToInteger(str.substr(12,14)));
                    } 
                    else if(StringToInteger(str.substr(0,1)) == 2) {
                        vecOfStrs[racerIndexInVector].turnTime2.setTime(
                                      StringToInteger(str.substr(6,8)),
                                      StringToInteger(str.substr(9,11)),
                                      StringToInteger(str.substr(12,14)));
                    }
                }
                else
                {
                    // add new racer to vector if not exist
                    tmp.racerNumber = StringToInteger(str.substr(2,5));                    
                    tmp.turnTime0.hour = StringToInteger(str.substr(6,8));
                    tmp.turnTime0.minute = StringToInteger(str.substr(9,11));
                    tmp.turnTime0.second = StringToInteger(str.substr(12,14));
                    
                    vecOfStrs.push_back(tmp);
                }
            }
        }
    }
    
    //////
    // print fire time and it's just an information
    cout << "Fire Time - ";
    PrintRaceTime(fireTime);
    cout << endl;
    //////
    //fill some imporant calculated fields in the RacerTurn struct
    for(int i = 0; i < vecOfStrs.size(); i ++)
    {
        vecOfStrs[i].overallFinishTimeInSecs = (GetSecByRaceTime(vecOfStrs[i].turnTime2) - GetSecByRaceTime(vecOfStrs[i].turnTime0));        
        vecOfStrs[i].timeBetweenSensor1And2 = (GetSecByRaceTime(vecOfStrs[i].turnTime1) - GetSecByRaceTime(vecOfStrs[i].turnTime0));
        vecOfStrs[i].timeBetweenSensor2And3 = (GetSecByRaceTime(vecOfStrs[i].turnTime2) - GetSecByRaceTime(vecOfStrs[i].turnTime1));
    }
    
    //print all racers times//
    for(int i = 0; i < vecOfStrs.size(); i ++)
    {
            cout << " Racer Num: " << vecOfStrs[i].racerNumber;
            cout << " Turn Time: T1 ";
            PrintRaceTime(vecOfStrs[i].turnTime0);
            cout << " T2 ";
            PrintRaceTime(vecOfStrs[i].turnTime1);
            cout << " T3 ";
            PrintRaceTime(vecOfStrs[i].turnTime2);        
            
            cout << endl;
    }
    cout << endl;
    
    ////////////
    //sort racers ascending//
    ////////////
    std::sort(vecOfStrs.begin(), vecOfStrs.end(), greater<RaceTurn>());    
    
    ///////
    //print results of the competition for all racers//
    ///////
    
    bool chek=false;
    while(!chek)
    {
        cout<<"Which operator would you to perform"<<endl;
        cout<<"0- Print all racers "<<endl;
        cout<<"1- Get racer info by number "<<endl;
        cout<<"2- Exit    "<<endl;
        int x;
        cin>>x;
        if(x==0)
        {
            printAllRacers(vecOfStrs);
        }
        else if(x==1)
        {
            string racerNum = "";            
            while (1) {
              if (cin >> racerNum) {
                  // valid number
                  break;
              } else {
                  // not a valid number
                  cout << "Invalid Input! Please input a numerical value." << endl;
                  cin.clear();
                  while (cin.get() != '\n') ; // empty loop
              }
            }
            printRacerInfoByNumber(vecOfStrs, racerNum);
        }
        else if(x==2)
        {           
            chek = true;
        }
    }
    
	return 0;
}

