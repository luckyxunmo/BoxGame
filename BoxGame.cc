#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
/*using std::cin;
using std::cout;
using std::string;
using std::endl;
using std::vector;
using std::ifstream;
*/

class BoxMap
{
public:
	BoxMap():personRow(1),personColunm(1),boxRow(2),boxColunm(2),NextpersonRow(personRow),
	NextpersonColunm(personColunm),NextboxRow(boxRow),NextboxColunm(boxColunm){	

	};
	~BoxMap(){};

	void readfile(std::ifstream &infile)
	{
		string data;
	  while(!infile.eof())
      {
        getline(infile,data);
        Map.push_back(data);
      }


	}
	void UpMove()
	{ 
       --NextpersonRow;
	   --NextboxRow;
	}

	void DownMove()
	{ 
       ++NextpersonRow;
	   ++NextboxRow;
	}

	void LeftMove()
	{ 
       --NextpersonColunm;
	   --NextboxColunm;
	}
	void RightMove()
	{ 
       ++NextpersonColunm;
	   ++NextboxColunm;
	}

	char getPersonPlace()
	{
		return Map[personRow][personColunm];
	}
	char getBoxPlace()
	{
		return Map[boxRow][boxColunm];
	}
	char getPersonNextPlace()
	{
		return Map[NextpersonRow][NextpersonColunm];
	}
	char getBoxNextPlace()
	{
		return Map[NextboxRow][NextboxColunm];
	}

	void  setPersonPlace(const char temp)
	{
		Map[personRow][personColunm] = temp;
	}
	void setBoxPlace(const char temp)
	{
		 Map[boxRow][boxColunm] = temp;
	}
	void setPersonNextPlace(const char temp)
	{
		Map[NextpersonRow][NextpersonColunm] = temp;
	}
	void setBoxNextPlace(const char temp)
	{
		 Map[NextboxRow][NextboxColunm] = temp;
	}

	void updatePersonCoord()
	{
		personRow = NextpersonRow;
		personColunm = NextpersonColunm;
	}
	void updateBoxCoord()
	{
		boxRow = NextboxRow;
		boxColunm = NextboxColunm;
	}
	void DrawMap()
	{
		vector<string>::iterator ite = Map.begin();
		for(;ite != Map.end(); ++ite)
		{
		  cout<< *ite <<endl;
		}
	}
	bool isWin()
	{
		if(NextboxRow == row-2 && NextboxColunm == colunm-2 )
			return true;
	
		return false;
	}
	bool isFailed()
	{
		 char deadquater = '#';
		  if(  (Map[boxRow+1][boxColunm] == deadquater&&Map[boxRow][boxColunm+1]==deadquater)
       ||(Map[boxRow-1][boxColunm] == deadquater&&Map[boxRow][boxColunm+1]==deadquater)
       ||(Map[boxRow-1][boxColunm] == deadquater&&Map[boxRow][boxColunm-1]==deadquater)
       ||(Map[boxRow+1][boxColunm] == deadquater&& Map[boxRow][boxColunm-1]==deadquater)
       ) return true;
    return false;
	}

	void resetNextPersonCoord()
	{
		NextpersonRow = personRow;
		NextpersonColunm = personColunm;
	}

	void resetNextBoxCoord()
	{
		NextboxRow = boxRow;
		NextboxColunm = boxColunm;
	}
private:
	int personRow,personColunm;	
	int NextpersonRow,NextpersonColunm;
	int boxRow,boxColunm;
	int NextboxRow,NextboxColunm;
	static const int row = 10;
	static const  int colunm = 11;
	vector<string> Map;
};

void playerChoice(BoxMap& mapTest)
{
	cout<<"please input [w,a,s,d] which mean[up left down right]"<<endl;
	  
    char direction = ' ';
	cin>>direction;
   
    switch (direction) {
        case 'w':
        case 'W':
			mapTest.UpMove();
            break;
        case 'a':
        case 'A':
			mapTest.LeftMove();
            break;
        case 's':
        case 'S':
			mapTest.DownMove();
            break;
        case 'D':
        case 'd':
			mapTest.RightMove();
            break;
        default:
			cout<<"input wrong please input again:"<<endl;
            break;
    }
}

void updateBoxMap(BoxMap& mapTest)
{
	char street = ' ';
	char box = 'X';
	char wall = 'O';
	if(mapTest.getBoxNextPlace() == street&&  // person and box can move together
		mapTest.getPersonNextPlace() == box)
	{
		// move box
		char temp = mapTest.getBoxNextPlace();
		mapTest.setBoxNextPlace( mapTest.getBoxPlace());
		mapTest.setBoxPlace(temp);
		mapTest.updateBoxCoord();

		// move person
		 temp = mapTest.getPersonNextPlace();
		mapTest.setPersonNextPlace( mapTest.getPersonPlace());
		mapTest.setPersonPlace(temp);
		mapTest.updatePersonCoord();
		

	}
	else if(mapTest.getPersonNextPlace() == street)
	{
		// move person
		char temp = mapTest.getPersonNextPlace();
		mapTest.setPersonNextPlace( mapTest.getPersonPlace());
		mapTest.setPersonPlace(temp);
		mapTest.updatePersonCoord();
	}

}


int main()
{
	ifstream infile;
	 char* file_path = "map.txt";
    infile.open(file_path);
	BoxMap mapTest;
	mapTest.readfile(infile);
	bool isWin = false;
	mapTest.DrawMap();
	while(!isWin)
	{
		mapTest.resetNextPersonCoord();
		mapTest.resetNextBoxCoord();

		playerChoice(mapTest);

		updateBoxMap(mapTest);
		mapTest.DrawMap();

		if(mapTest.isWin())
		{  isWin = true;
		   cout<<"congratulation"<<endl;
		}
		if(mapTest.isFailed())
		{
			cout<<"Game over"<<endl;
			break;
		}
		
	}

	system("pause");
	return 0;
}
