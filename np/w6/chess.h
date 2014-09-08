#ifndef CHESST01_H_INCLUDED
#define CHESST01_H_INCLUDED
#include <string>
using namespace std;
class Piece
{
    private:
        string itsName;
        int itsVertAddress;
        int itsHorzAddress;

        public:
        void   setItsVertAddress (int address){itsVertAddress = address;}
        void   setItsHorzAddress (int address){itsHorzAddress = address;}
        int    getItsVertAddress()           {return itsVertAddress;}
        int    getItsHorzAddress()           {return itsHorzAddress;}
        void   setItsName   (string name){itsName=name;}
        string getItsName   ()           {return itsName;}
};

class Board
{
    private:
    string itsBoard[26];
    public:
    void setItsBoard(string []);
    void setPcsLoc(string,int,int);
    void DisplayBoard();
    bool emptySpot(int ,int );

};

///////////////////
// bool searchTouch(Piece [],int);
// bool searchMove(Piece [],int,int);
/////////////////////
void Board::setItsBoard(string arr[])
{
    for(int i=0;i<26;i++)
    itsBoard[i]=arr[i];
}
void Board::DisplayBoard()
{
    for(int i=0;i<26;i++)
    cout<<itsBoard[i]<<endl;;

}

void Board::setPcsLoc(string name,int horz,int vert)
{
    itsBoard[vert].replace(horz,2,name);
}

bool Board::emptySpot(int horz,int vert)
{
    cout<<"\n"<<itsBoard[horz][vert]<<endl;
    if(itsBoard[horz][vert]=='.')
    {

    return true;
    }
    return false;
}
/*
 bool searchTouch(Piece pieces[],int address) ////to check if the player is choosing the right Piece
 {
     bool ok_touch = false;
     int Horz = address%10;
     int Vert = address/10;
     for(int i=0;i<32;i++)

       if((pieces[i].getItsHorzAddress()==Horz)&&(pieces[i].getItsVertAddress()==Vert))
       return ok_touch;

     return ok_touch;
 }

 bool searchMove(Piece pieces[],int addtouch,int addmove) ////to check if the player is choosing the right Piece
 {
     bool ok_touch = false;
     int THorz = addtouch%10;
     int TVert = addtouch/10;
     int MHorz = addmove%10;
     int MVert = addmove/10;
     for(int i=0;i<32;i++)

       if((pieces[i].getItsHorzAddress()==THorz)&&(pieces[i].getItsVertAddress()==TVert))
       {
           pieces[i].setPcsLoc(pieces[i].getItsName(),MHorz,MVert);
       return ok_touch;
       }
     return ok_touch;
 }
 */
#endif // CHESST01_H_INCLUDED
