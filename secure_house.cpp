#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

int state = 0;
//State 0: Awaiting Input
//State 1: Key in
//State 2: Turn key
//State 3: Enter house
//State 4: Rekey house
//State 5: Leave house
//State 6: Who's inside

std::string command;
std::string word;
std::string userName;
std::string output;
std::string correctUser;
std::string secretKey = "FIREFIGHTER_SECRET_KEY";
std::vector<std::string> home;
std::vector<std::string>::iterator check;
std::string key;
bool mainFlag = false;
bool keyFlag = false;
bool correctKey = false;
bool rekeyFlag = false;
bool resize = 0;
std::string rekeyArr[200];
int j;

int main(int argc, char *argv[]){
    std::string keyArr[argc-1];
    std::string owner = argv[1];
    int size = argc - 2;
    for(int i = 2; i < argc; i++){
        keyArr[i-2] = argv[i]; 
    }
    std::stringstream ss;
    while(mainFlag == false){
        switch(state){
            case 0:
                ss.clear();
                std::getline(std::cin, command, '\n');
                if(command == ""){
                    mainFlag = true;
                    break;
                }
                ss.str(command);
                ss >> word;
                command = word;
                ss >> word;
                command = command + " " + word;
                ss >> word;
                userName = word;
                
                if(command == "INSERT KEY"){
                    correctUser = userName;
                    state = 1;
                    command = "";
                }
                if(command == "TURN KEY"){
                    state = 2;
                    command = "";
                }
                if(command == "WHO'S INSIDE?"){
                        state = 6;
                        command = "";
                }
                if(command == "ENTER HOUSE"){
                    if(correctKey == true && correctUser == userName){
                        state = 3;
                        command = "";
                    }
                    else{
                        std::cout << "ACCESS DENIED" << std::endl;
                        state = 0;
                        command = "";
                    }
                }
                if(command == "LEAVE HOUSE"){
                    state = 5;
                    command = "";
                }
                if(command == "CHANGE LOCKS"){
                    state = 4;
                    command = "";
                }

                if(command != ""){
                    std::cout << "ERROR" << std::endl;
                }
                break;
            case 1:
                ss >> word;
                key = word;
                std::cout << "KEY " << key << " INSERTED BY " << userName << std::endl;
                state = 0;
                break;
            case 2:
                if(rekeyFlag == true){
                    for(int i = 0; i < resize+2; i++){
                        
                        if(key == rekeyArr[i] || key == secretKey){
                            correctKey= true;
                            i = resize+2;
                        }
                        else{
                            correctKey = false;
                        }
                    }
                }
                else{
                    for(int i = 0; i < size; i++){
                        if(key == keyArr[i] || key == secretKey){
                            correctKey= true;
                            i = size;
                        }
                        else{
                            correctKey = false;
                        }
                    }
                }
                if(correctKey == true && userName == correctUser){
                    std::cout << "SUCCESS " << userName << " TURNS KEY " << key << std::endl;
                }
                else{
                    std::cout << "FAILURE " << userName << " UNABLE TO TURN KEY " << key << "\n";  
                }
                state = 0;
                break;
            case 3:
                std::cout << "ACCESS ALLOWED" << std::endl;
                home.emplace(home.begin(),userName);
                correctKey = false;
                state = 0;
                break;
            case 4:
                if(userName == owner){
                    check = std::find(home.begin(),home.end(), userName);
                    if(check != home.end()){
                        j = 0;
                        while(ss >> word){
                            rekeyArr[j] = word;
                            std::cout << rekeyArr[j] << std::endl;
                            j++;
                        }
                        resize = j;
                        std::cout << "OK" << std::endl;
                        rekeyFlag = true;
                    }
                    else{
                        std::cout << "ACCESS DENIED" << std::endl;
                    }
                }
                else{
                    std::cout << "ACCESS DENIED" << std::endl;
                }
                state = 0;
                break;  
            case 5:
                check = std::find(home.begin(),home.end(), userName);
                if(check != home.end()){
                    home.erase(check);
                    std::cout << "OK" << std::endl;
                }  
                else{
                    std::cout << userName << " NOT HERE" << std::endl; 
                }
                state = 0;
                break; 
            case 6:
                if(home.empty()){
                    std::cout << "NOBODY HOME" << std::endl;
                }
                else{
                    for(int i = home.size()-1; i >= 0; i--){
                        std::cout << home.at(i);
                        if(i > (0)){
                            std::cout << ", ";
                        }
                    }
                    std::cout << std::endl;
                }
                state = 0;
                break;
        }
    }
    return 0;
}

