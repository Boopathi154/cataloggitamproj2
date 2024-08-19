#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<ctime>
#include<cstdlib>
#include<algorithm>

using namespace std;

struct User{
    string name;
    int score;
};

void shuffleOptions(vector<string>&options){
    srand(unsigned(time(0)));
    random_shuffle(options.begin(),options.end());
}

void showInstructions(){
    cout<<"Instructions:\n";
    cout<<"1. The quiz will ask you about the capitals of Indian states.\n";
    cout<<"2. The teacher sets the number of questions and whether there is negative marking.\n";
    cout<<"3. You can skip a question if unsure; it won't affect your score.\n";
    cout<<"4. Try to answer as many questions correctly as possible.\n";
    cout<<"5. Scores will be recorded, and you can view the leaderboard after the quiz.\n";
    cout<<endl;
}

int conductQuiz(const unordered_map<string,string>&stateCapitals,vector<string>&questions,vector<string>&answers,vector<string>&userResponses,int numQuestions,bool negativeMarking){
    int score=0;
    vector<string>options(4);
    vector<string>states;
    for(const auto&entry:stateCapitals){
        states.push_back(entry.first);
    }
    random_shuffle(states.begin(),states.end());
    for(int k=0;k<numQuestions;k++){
        string state=states[k];
        string correctAnswer=stateCapitals.at(state);
        questions.push_back(state);
        options[0]=correctAnswer;
        int i=1;
        vector<string>selectedOptions;
        selectedOptions.push_back(correctAnswer);
        for(const auto&opt:stateCapitals){
            if(opt.second!=correctAnswer&&find(selectedOptions.begin(),selectedOptions.end(),opt.second)==selectedOptions.end()&&i<4){
                options[i++]=opt.second;
                selectedOptions.push_back(opt.second);
            }
        }
        shuffleOptions(options);
        cout<<"What is the capital of "<<state<<"?\n";
        for(int j=0;j<4;j++){
            cout<<j+1<<". "<<options[j]<<"\n";
        }
        int choice;
        cout<<"Enter your choice (1-4) or 5 to skip: ";
        cin>>choice;
        if(choice==5){
            userResponses.push_back("Skipped");
            answers.push_back(correctAnswer);
            cout<<"You skipped this question.\n";
            continue;
        }
        string userAnswer=options[choice-1];
        userResponses.push_back(userAnswer);
        answers.push_back(correctAnswer);
        if(userAnswer==correctAnswer){
            cout<<"Correct!\n";
            score++;
        }
        else{
            cout<<"Wrong! The correct answer is "<<correctAnswer<<".\n";
            if(negativeMarking)score--;
        }
        cout<<endl;
    }
    return score;
}

void mainMenu(vector<User>&leaderboard,const unordered_map<string,string>&stateCapitals){
    int numQuestions;
    bool negativeMarking;
    cout<<"Teacher, enter the number of questions: ";
    cin>>numQuestions;
    cout<<"Enable negative marking? (1 for Yes, 0 for No): ";
    cin>>negativeMarking;
    int choice;
    do{
        cout<<"Welcome to the States and Capitals Quiz!\n";
        cout<<"1. Start Quiz\n";
        cout<<"2. View Instructions\n";
        cout<<"3. View Leaderboard\n";
        cout<<"4. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;
        cin.ignore();
        switch(choice){
            case 1:{
                string userName;
                cout<<"Enter your name: ";
                getline(cin,userName);
                vector<string>questions,answers,userResponses;
                int score=conductQuiz(stateCapitals,questions,answers,userResponses,numQuestions,negativeMarking);
                leaderboard.push_back({userName,score});
                cout<<"Quiz finished! Your total score is: "<<score<<"/"<<numQuestions<<"\n";
                cout<<"Review:\n";
                for(int i=0;i<numQuestions;i++){
                    cout<<"Q"<<i+1<<": What is the capital of "<<questions[i]<<"?\n";
                    cout<<"Your answer: "<<userResponses[i];
                    if(userResponses[i]==answers[i]){
                        cout<<" - Correct\n";
                    }
                    else if(userResponses[i]=="Skipped"){
                        cout<<" - Skipped (Correct answer: "<<answers[i]<<")\n";
                    }
                    else{
                        cout<<" - Wrong (Correct answer: "<<answers[i]<<")\n";
                    }
                }
                sort(leaderboard.begin(),leaderboard.end(),[](User a,User b){
                    return a.score>b.score;
                });
                break;
            }
            case 2:
                showInstructions();
                break;
            case 3:{
                cout<<"Leaderboard:\n";
                for(const auto&user:leaderboard){
                    cout<<user.name<<" - "<<user.score<<"\n";
                }
                cout<<endl;
                break;
            }
            case 4:
                cout<<"Thank you for playing!\n";
                break;
            default:
                cout<<"Invalid choice, please try again.\n";
        }
    }while(choice!=4);
}

int main(){
    unordered_map<string,string>stateCapitals={
        {"Andhra Pradesh","Amaravati"},{"Arunachal Pradesh","Itanagar"},
        {"Assam","Dispur"},{"Bihar","Patna"},{"Chhattisgarh","Raipur"},
        {"Goa","Panaji"},{"Gujarat","Gandhinagar"},{"Haryana","Chandigarh"},
        {"Himachal Pradesh","Shimla"},{"Jharkhand","Ranchi"},
        {"Karnataka","Bengaluru"},{"Kerala","Thiruvananthapuram"},
        {"Madhya Pradesh","Bhopal"},{"Maharashtra","Mumbai"},
        {"Manipur","Imphal"},{"Meghalaya","Shillong"},{"Mizoram","Aizawl"},
        {"Nagaland","Kohima"},{"Odisha","Bhubaneswar"},{"Punjab","Chandigarh"},
        {"Rajasthan","Jaipur"},{"Sikkim","Gangtok"},{"Tamil Nadu","Chennai"},
        {"Telangana","Hyderabad"},{"Tripura","Agartala"},{"Uttar Pradesh","Lucknow"},
        {"Uttarakhand","Dehradun"},{"West Bengal","Kolkata"}
    };
    vector<User>leaderboard;
    mainMenu(leaderboard,stateCapitals);
    return 0;
}
