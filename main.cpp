//
//  main.cpp
//  project1
//
//  Created by Srinivas Lingutla on 9/9/17.
//  Copyright © 2017 Srinivas Lingutla. All rights reserved.
//

/*main.cpp*/

//
// iClicker Analysis program in modern C++.
//
// Srinivas Lingutla
// U. of Illinois, Chicago
// CS 341: Fall 2017
// Project 01
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

#include "student.h"

using namespace std;


//
// FileExists:
//
// Returns true if the file exists, false if not.
//
bool FileExists(string filename)
{
    ifstream file(filename);
    
    return file.good();
}

ifstream printStartingDetails()
{
    string filename;
    cout << "**Starting**" << endl;
    cout << "**Filename?**" << endl;
    cin >> filename;
    cout << filename << endl;
    
    
    ifstream myfile (filename);
    
    if (!FileExists(filename))
    {
        cout << "Error: '" << filename << "' not found, exiting..." << endl;
        exit(-1);
    }

    cout << "**Analysis**" << endl;
    
    cout << "Date: " << filename[3] << filename[4] << "/" << filename[5] << filename[6] << "/" << filename[1] << filename[2] << endl;
    cout << "Time: " << filename[7] << filename[8] << ":" << filename[9] << filename[10] << endl;
    

    return myfile;
    
}

vector<Student> inputFileData(ifstream &myfile, iClickerSession &session)
{
    vector<Student> students;
    string line;
    string currentCorrectAnswer;
    
    while(! myfile.eof()) //Getting the main session info
    {
        getline(myfile, line);
        //cout << line << endl;
        std::size_t found = line.find("<ssn");
        if (found!=std::string::npos)
        {
            
            size_t found2 = line.find("Session");
            if (found2!=std::string::npos)
            {
                string session = line.substr(found2, 9);
                cout << "Name: \"" << session << "\"" << endl;
            }
            
            getline(myfile, line);
            break;
        }
    }
    
    while(!myfile.eof()) //Getting the iclicker info
    {
        
        size_t found = line.find("<p ");
        if (found!=std::string::npos)
        {
            
            session.incrementQuestions();
            
            size_t findCorrectAnswer = line.find("cans=");
            if (findCorrectAnswer!=std::string::npos)
            {
                currentCorrectAnswer = line.substr(findCorrectAnswer + 6, 1); //get multiple answers
                int n = 7;
                while(line.substr(findCorrectAnswer + n,1) == "|")
                {
                    currentCorrectAnswer.append(line.substr(findCorrectAnswer + n+1, 1));
                    n = n+2;
                }
            }
            
            while(getline(myfile, line))
            {
                size_t currentStudent = line.find("<v ");
                if (currentStudent!=std::string::npos)
                {
                    string id;
                    int NumberAnswered = 0;
                    int NumberAnsweredCorrectly = 0;
                    
                    found = line.find(" ans=");
                    string StudentAnswer = line.substr(found + 6, 1);
                    if(StudentAnswer != "\"") NumberAnswered = 1;
                    if(currentCorrectAnswer.find(StudentAnswer) != std::string::npos)
                        NumberAnsweredCorrectly = 1;
                    
                    found = line.find("id=");
                    id = line.substr(found + 5, 8);
                    
                    auto result = std::find_if(students.begin(), students.end(),
                                               [id](const Student& s)
                                               {
                                                   if (s.getid() == id)
                                                       return true;
                                                   else
                                                       return false;
                                                   
                                               } );
                    
                    if(result == students.end())
                    {
                        Student s(id, NumberAnswered, NumberAnsweredCorrectly);
                        students.push_back(s);
                        session.incrementiClickers();
                        //cout << id << "  " << NumberAnsweredCorrectly << "   " << StudentAnswer <<endl;
                        
                    }
                    else if(StudentAnswer != "\"")
                    {
                        result->incrementAnswered();
                        if(NumberAnsweredCorrectly == 1) result->incrementAnsweredCorrectly();
                        //cout << id << "  " << result->getAnsweredCorrectly() << "   " << StudentAnswer << "   " << currentCorrectAnswer << endl;
                        
                    }
                    
                    
                }
                
                else
                    break;
            }
            //cout << endl;
            getline(myfile, line);
            
        }
        
        found = line.find("</ssn>");
        if (found!=std::string::npos)
        {
            break;
        }
        
    }
    

    return students;
    
}

void printQuestionsAndClickers(iClickerSession &session)
{
    cout << "# questions: " << session.getNumber() << endl;
    cout << "# clickers: "  <<session.getClickers() << endl;
}

void NumberofStudentsAnswered(vector<Student> &students, iClickerSession &session)
{
    
    cout << "# of students who answered: " << endl;
    
    size_t count = count_if(students.begin(), students.end(), [=](Student s1)
                     {
                         if(s1.getQuestionsAnswered() == session.getNumber())
                             return true;
                         else 
                             return false;
                     } );
    
    cout << "  All questions: " << count << endl;
    
    count = count_if(students.begin(), students.end(), [=](Student s1)
                            {
                                if(s1.getQuestionsAnswered() >= session.getNumber()/2)
                                    return true;
                                else
                                    return false;
                            } );

    cout << "  At least half: " << count << endl;
    
    count = count_if(students.begin(), students.end(), [=](Student s1)
                     {
                         if(s1.getQuestionsAnswered() >= 1)
                             return true;
                         else
                             return false;
                     } );
    
    cout << "  At least one: " << count << endl;
    
    count = count_if(students.begin(), students.end(), [=](Student s1)
                     {
                         if(s1.getQuestionsAnswered() == 0)
                             return true;
                         else
                             return false;
                     } );
    
    cout << "  None: " << count << endl;

}

void NumberofStudentsAnsweredCorrectly(vector<Student> &students, iClickerSession &session)
{
    
    cout << "# of students who answered correctly: " << endl;
    
    size_t count = count_if(students.begin(), students.end(), [=](Student s1)
                            {
                                if(s1.getAnsweredCorrectly() == session.getNumber())
                                    return true;
                                else
                                    return false;
                            } );
    
    cout << "  All questions: " << count << endl;
    
    count = count_if(students.begin(), students.end(), [=](Student s1)
                     {
                         if(s1.getAnsweredCorrectly() >= session.getNumber()/2)
                             return true;
                         else
                             return false;
                     } );
    
    cout << "  At least half: " << count << endl;
    
    count = count_if(students.begin(), students.end(), [=](Student s1)
                     {
                         if(s1.getAnsweredCorrectly() >= 1)
                             return true;
                         else
                             return false;
                     } );
    
    cout << "  At least one: " << count << endl;
    
    count = count_if(students.begin(), students.end(), [=](Student s1)
                     {
                         if(s1.getAnsweredCorrectly() == 0)
                             return true;
                         else
                             return false;
                     } );
    
    cout << "  None: " << count << endl;
    
}

void printStudentDetails(vector<Student> &students, iClickerSession &session)
{
    cout << "Students who answered < half:" <<  endl;
    
    for(auto& s1:students)
    {
        if(s1.getQuestionsAnswered() < session.getNumber()/2)
            cout << "  " << s1.getid() << endl;
    }
    
    cout << "Students with 0 correct:" <<  endl;
    
    for(auto& s1:students)
    {
        if(s1.getAnsweredCorrectly() == 0)
            cout << "  " << s1.getid() << endl;
    }
    
}



int main()
{

    
    
    iClickerSession session(0,0);
    

    
    ifstream myfile = printStartingDetails();
    
    vector<Student> students = inputFileData(myfile, session);
    
    printQuestionsAndClickers(session);
    
    NumberofStudentsAnswered(students, session);
    
    NumberofStudentsAnsweredCorrectly(students, session);
    
    printStudentDetails(students, session);
    
    
    
    
    cout << "**END**" << endl;
    return 0;
}
