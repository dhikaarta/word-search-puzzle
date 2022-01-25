#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>
using namespace std;
using namespace std::chrono;
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      
#define RED     "\033[31m"      
#define GREEN   "\033[32m"      
#define YELLOW  "\033[33m"      
#define BLUE    "\033[34m"     
#define MAGENTA "\033[35m"      
#define CYAN    "\033[36m"      
#define WHITE   "\033[37m"     
#define BOLDBLACK   "\033[1m\033[30m"      
#define BOLDRED     "\033[1m\033[31m"      
#define BOLDGREEN   "\033[1m\033[32m"      
#define BOLDYELLOW  "\033[1m\033[33m"      
#define BOLDBLUE    "\033[1m\033[34m"      
#define BOLDMAGENTA "\033[1m\033[35m"      
#define BOLDCYAN    "\033[1m\033[36m"      
#define BOLDWHITE   "\033[1m\033[37m"      

int colorCode = 1;

void initializeVector(vector<vector<int>> &vect, int row, int col)
{
    int i,j;
    vector<int> v1;

    for(i = 0; i <col ; i++)
    {
        v1.push_back(0);
    }

    for(j = 0; j < row;j++)
    {
      vect.push_back(v1);
    }
}


void matrixBuilder(vector<vector<int>> &vect,int foundRow, int foundCol, int dirRow, int dirCol,string text, int count)
{
    int i;
    for(i = 0; i < text.size(); i++)
    {
        if (vect.at(foundRow).at(foundCol) == 0)
        {
            vect.at(foundRow).at(foundCol) = count;
        }
        
        foundRow += dirRow;
        foundCol += dirCol;
    }
}

void vector2DPrint(vector<vector<int>> vect)
{
    int i,j;

    for(i = 0 ; i < vect.size() ; i++)
    {
        for(j = 0 ; j < vect[0].size() ; j++)
        {
            cout<<vect.at(i).at(j);
        }
        cout<<endl;
    }
}

void wordSearch(vector<vector<char>> vect,vector<vector<int>> &vectInt, int curRow, int curCol, string text, int& comparisonCount, bool& found)
{
    int i,j,changedRow,changedCol;
    //fungsi untuk mencari sebuah kata pada baris dan kolom tertentu pada puzzle
    int directions[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},};
    //menentukan arah pencarian, misal 0,1 berarti mencari ke kanan , karena baris sama dan kolom bertambah 1

    comparisonCount++;
    if(vect.at(curRow).at(curCol) != text[0])
    {
        return;
    }

    for(i = 0; i<8; i++)
    {
        changedRow = curRow + directions[i][0];
        changedCol = curCol + directions[i][1];
        for(j = 1; j < text.size(); j++)
        {
            if(changedRow >= vect.size() || changedRow < 0 || changedCol >= vect[0].size() || changedCol < 0)
            {
                break;
            }
            comparisonCount++;
            if(vect.at(changedRow).at(changedCol) != text[j])
            {
                break;
            }
            changedRow += directions[i][0];
            changedCol += directions[i][1];
        }
        if (j == text.size())
        {
            found = true;
            matrixBuilder(vectInt,curRow,curCol,directions[i][0],directions[i][1],text,colorCode);
            colorCode += 1;
            colorCode %= 12;
            return;
        }
    }
    return;
}


void solutionPrint(vector<vector<char>> vect,vector<vector<int>> vectInt)
{
    int i,j;

    for(i = 0 ; i < vect.size() ; i++)
    {
        for(j = 0 ; j < vect[0].size() ; j++)
        {
            if(vectInt.at(i).at(j) == 0)
            {
                cout << BOLDBLACK << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 1)
            {
                cout << RED << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 2)
            {
                cout << GREEN << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 3)
            {
                cout << YELLOW << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 4)
            {
                cout << BLUE << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 5)
            {
                cout << MAGENTA << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 6)
            {
                cout << CYAN << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 7)
            {
                cout << BOLDRED << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 8)
            {
                cout << BOLDGREEN << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 9)
            {
                cout << BOLDYELLOW << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 10)
            {
                cout << BOLDBLUE << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 11)
            {
                cout << BOLDMAGENTA << vect.at(i).at(j) << RESET;
            }
            else if(vectInt.at(i).at(j) == 12)
            {
                cout << BOLDCYAN << vect.at(i).at(j) << RESET;
            }
            if(j != vect[0].size())
            {
                cout<< " ";
            }
        }
        cout<<endl;
    }
}


int main() 
{
    string fileName;
    int comparisonCount = 0;bool found = false;
    int colorCode = 1;
    cout<<"Masukkan nama file : ";
    cin>>fileName;
    string filePath = "../test/" + fileName;
    ifstream myfile(filePath);
    string text;
    int i,j,k,l;
    vector<char> v1;
    vector<vector<char>> vect;
    vector<string> vString;
    vector<vector<int>> vectInt;
    
    if(myfile.is_open())
    {
        while(getline(myfile,text))
        {
            if(!text.size())
            {
                break;
            }
            else
            {
                for(i = 0 ; i < text.size() ; i++)
                {
                    if (text[i] != ' ')
                    {
                        v1.push_back(text[i]);
                    }
                }
                vect.push_back(v1);
                v1.clear();
            }
        }

        while(getline(myfile,text))
        {
            text.erase(remove(text.begin(), text.end(), ' '), text.end());
            vString.push_back(text);
        }
    }

    initializeVector(vectInt,vect.size(), vect[0].size());
    auto start = high_resolution_clock::now();
    for(i = 0 ; i < vString.size() ; i++)
    {
        found = false;
        for(j = 0; j < vect.size(); j++)
        {
            if (found)
            {
                break;
            }
            for(k = 0; k < vect[0].size(); k++)
            {
                if (found)
                {
                    break;
                }
                wordSearch(vect,vectInt,j,k,vString[i],comparisonCount, found);
            }
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout <<endl;
    solutionPrint(vect,vectInt);
    cout <<endl;
    cout << "==========================================="<<endl;
    cout << "Total perbandingan kata pada program adalah " << comparisonCount << " kali." << endl;
    cout << "Runtime program selama " <<  (float)duration.count()/1000000 << " sekon"  << endl;
    cout << "===========================================";
    
}
