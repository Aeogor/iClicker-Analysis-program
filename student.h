//
//  student.h
//  project1
//
//  Created by Srinivas Lingutla on 9/9/17.
//  Copyright © 2017 Srinivas Lingutla. All rights reserved.
//

#ifndef student_h
#define student_h


#endif /* student_h */


/*student.h*/

#pragma once

using namespace std;

class Student
{
    
    private:
    string id;
    int answered;
    int answered_correctly;
    
    public:
    Student(std::string id, int ans, int ans_cor)
    : id(id), answered(ans), answered_correctly(ans_cor)
    {
        
    }
    
    string getid() const
    {
        return id;
    }
    
    int getQuestionsAnswered() const
    {
        return answered;
    }
    
    int getAnsweredCorrectly() const
    {
        return answered_correctly;
    }
    
    void incrementAnswered()
    {
        answered++;
    }
    
    void incrementAnsweredCorrectly()
    {
        answered_correctly++;
    }
    
};

class iClickerSession
{
private:
    int totalQuestions;
    int totaliClickers;
    
public:
    iClickerSession(int questions, int clickers)
    : totalQuestions(questions), totaliClickers(clickers)
    {
        
    }
    
    void incrementQuestions()
    {
        totalQuestions++;
    }
    
    void incrementiClickers()
    {
        totaliClickers++;
    }
    
    int getNumber() const
    {
        return totalQuestions;
    }
    
    int getClickers() const
    {
        return totaliClickers;
    }
};
