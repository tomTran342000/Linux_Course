#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Calc{
    private:
        float A, B;
    public:
        Calc(){
            this->A = 0;
            this->B = 0;
        }
        ~Calc(){
        
        }
        void set(float a, float b){
            this->A = a;
            this->B = b;
        }
        float add(){
            return this->A + this->B;
        }
        float sub(){
            return this->A - this->B;
        }
        float mul(){
            return this->A * this->B;
        }
        float div(){
            if(this->B == 0){
                cout << "invalid second number";
                return 1;
            }else{
                return this->A / this->B;
            }
        }
};

int solve(float a, float b, char oper, Calc *cal){
    cal->set(a,b);
    switch (oper)
    {
    case '+':
        return cal->add();
        break;
    case '-':
        return cal->sub();
        break;
    case '*':
        return cal->mul();
        break;
    case '/':
        return cal->div();
        break;
    default:
        cout << "Incorrect Operator. Do Again: " << endl;
        return 1;
        break;
    }
}

void history(string num1, string num2, char oper, float res){
    ofstream myFile;
    myFile.open("/home/tor9hc/Linux_Course/lab2/history.txt", fstream::app);
    if(myFile.is_open()){
        myFile << num1 << " " << oper << " " << num2 << " = " << res << endl;
        myFile.close();
    }else{
        cout << "Unable to open file";
    }
}

void displayHistory(){
    string line;
    ifstream myFile;
    myFile.open("/home/tor9hc/Linux_Course/lab2/history.txt");
    if(myFile.is_open()){
        for(int i=0;i<5;i++){
            getline(myFile, line);
            cout << line << endl;
        }
        myFile.close();
    }else{
        cout << "Unable to open file";
    }
}

int main(){
    Calc *cal = new Calc();

    string num1, num2;
    char math;
    string doAgain = "yes";
    float ANS = 0;

    while(doAgain == "yes" | doAgain == "history"){
        //Input
        cout << ">> ";
        cin >> num1 >> math >> num2;
        //check ANS
        if(num1 == "ANS"){
            num1 = to_string(ANS);
        }
        else if (num2 == "ANS"){
            num2 = to_string(ANS);
        }
        
        float result = solve(stof(num1), stof(num2), math, cal);

        //history equation
        history(num1, num2, math, result);

        cout << result << endl;

        //save the result
        ANS = result;
        cout << "==> Type 'yes' to keep equation" << endl;
        cout << "==> Type 'history' to keep equation" << endl;
        cout << "==> Another type to exit" << endl;

        cin >> doAgain;
        
        if(doAgain == "history"){
            displayHistory();
        }
        

    }
    cout << "ANS = " << ANS;


    
    delete cal;
    return 0;
}