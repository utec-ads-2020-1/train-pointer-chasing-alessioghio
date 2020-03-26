#include <iostream>
# include <stdio.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
using namespace std;

void chasing(int **A[], int a, int *B[], int b, int C[], int c);

int main() {
        int a = 5, b = 4, c = 3;
        // First you need to initialize all elements in A and B to NULL
        int **A[5] = {}, *B[4] = {}, C[3] = {2, 1, 4};
        // A is an array of pointers, and each non-NULL element points to an element of B
        // B is an array of pointers, and each non-NULL element points to an element of C
        chasing(A, a, B, b, C, c);

        int **ansA[5] = {} ,*ansB[4] = {};
        for (int i = 0; i < a; i++)
                ansA[i] = NULL;
        for (int i = 0; i < b; i++)
                ansB[i] = NULL;
        
        char sampleInputNum = 3; // Change number depending on the sample inputs
        switch (sampleInputNum)
        {
        case 1:
                ansA[0] = &B[0], ansA[1] = &B[2], ansB[0] = &C[2], ansB[1] = &C[1];
                break;
        case 2:
                ansA[0] = &B[1];
                break;
        case 3:
                ansA[2] = &B[1], ansA[3] = &B[0], ansB[1] = &C[1], ansB[2] = &C[0];
                break;
        default:
                break;
        }
        // Check A
        for (int i = 0; i < a; i++)
                if (A[i] != ansA[i] )
                cout << "A[" << i << "] " << "wrong answer" << endl;
 
        // Check B
        for (int i = 0; i < b; i++)
                if (B[i] != ansB[i] )
                        cout << "B[" << i << "] " << "wrong answer" << endl;

        return 0;
}

void chasing(int **A[], int a, int *B[], int b, int C[], int c){
        // Another way to input data, but if a wrong string is inputed, error is thrown
        /*scanf(" %c %d  %c %d", &letter1, &n, &letter2, &m); // the %c conversion specifier won't automatically skip any leading whitespace
        printf("Letter1: %c n: %d Letter2: %c m: %d", letter1, n, letter2, m); // This print is for debug purposes*/
        // Input
        // There are many lines in the input file, each line is an instruction(length < 64)
        char maxL = 0;
        string input;
        vector<int> result;
        do{
                getline(cin, input);
                // Remove whitespaces
                input.erase(remove(input.begin(), input.end(), ' '), input.end());
                stringstream ss(input);
                // only process data that is in the format "XnYm" (4 length string)
                if (input.size() == 4){
                        // Pass data into a char, because sscanf cannot work with strings
                        // There might be a better way to do it, check it later
                        char letters[4];
                        for (int i = 0; i < 4; i++){
                                ss >> letters[i];
                        }
                        char letter1, letter2;
                        int n, m;
                        sscanf(letters, " %c %d  %c %d", &letter1, &n, &letter2, &m);
                        // n and m are strings of digits only
                        bool condition1 = !((n>b) || (m>c));
                        // A n B m, then we set A[n] point to B[m]
                        bool condition2 = (letter1 == 'A') && (letter2 == 'B');
                        // B n C m, then we set B[n] point to C[m]
                        bool condition3 = (letter1 == 'B') && (letter2 == 'C');
                        if (condition1&&(condition2||condition3)){
                                // set letter1[n] point to letter2[m]
                                switch (letter1)
                                {
                                case 'A':
                                        A[n] = &B[m];
                                        break;
                                
                                default: // letter 1 can only be either A or B
                                        B[n] = &C[m];
                                        break;
                                }
                                // If the command is valid then 1 is printed, otherwise 0
                                result.push_back(1);
                        }
                        else{
                                result.push_back(0);
                        }       
                }else{ // all other cases we consider the instruction invalid and simply ignore
                        result.push_back(0);
                }
                maxL++;
        } while (((input != "")) && (maxL < 64));
        // Last iteration will append 0 to the vector so it must be deleted
        result.pop_back();
        for (int i = 0; i < maxL-1; i++){
                cout << result.at(i) << endl;
        }
}
        
        
