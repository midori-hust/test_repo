#include <iostream>
#include <string>
#include <cstdlib>
#include "chess.h"
    bool touchMove(Board*,Piece [],int,int,bool);
    bool checkMove(int);
    bool emptySpot(Piece [],int , int);
    bool pieceMove(Piece [],string ,string ,int ,int );
    int switchNum(int,char);
    void resetBoard(Board *,Piece []);

   using namespace std;
   int main()
   {             /////   2   6   10  14  18  22  26  30
   string arrPcs[26]={"--1---2---3---4---5---6---7---8---",
                      "-    ####    ####    ####    ####-",
                      "1    ####    ####    ####    ####1",//2
                      "-    ####    ####    ####    ####-",
                      "-####    ####    ####    ####    -",
                      "2####    ####    ####    ####    2",//5
                      "-####    ####    ####    ####    -",
                      "-    ####    ####    ####    ####-",
                      "3    ####    ####    ####    ####3",//8
                      "-    ####    ####    ####    ####-",
                      "-####    ####    ####    ####    -",
                      "4####    ####    ####    ####    4",//11
                      "-####    ####    ####    ####    -",
                      "-    ####    ####    ####    ####-",
                      "5    ####    ####    ####    ####5",//14
                      "-    ####    ####    ####    ####-",
                      "-####    ####    ####    ####    -",
                      "6####    ####    ####    ####    6",//17
                      "-####    ####    ####    ####    -",
                      "-    ####    ####    ####    ####-",
                      "7    ####    ####    ####    ####7",//20
                      "-    ####    ####    ####    ####-",
                      "-####    ####    ####    ####    -",
                      "8####    ####    ####    ####    8",//23
                      "-####    ####    ####    ####    -",
                      "--1---2---3---4---5---6---7---8---"
                      };
   Board gameBoard;
   gameBoard.setItsBoard(arrPcs );

   Piece pcs[64];

    resetBoard(&gameBoard,pcs);

   gameBoard.DisplayBoard();/////display the game board on screen
   cout<<"0 to end the game anytime"<<endl;
   cout<<"entry:2 digits each from 1-8.first: vertical count"<<endl;
   bool exit = false;
   bool white= true; //////the turn is for white
   cout<<"White Turn"<<endl;

while(exit==false)
{
int touch,move;
cout<<"Choose the piece you want to move!"<<endl;
cin>>touch;
if(touch!=0)
{
cout<<"Choose the target location "<<endl;
cin>>move;
if((checkMove(move))&&(checkMove(touch))&&(touchMove(&gameBoard,pcs,touch,move,white)))
{
  gameBoard.DisplayBoard();/////display the game board on screen
  if(white)
  {
  white=false;/////switch player
  cout<<"Black Turn"<<endl;
  }
  else
  {
    white=true;
    cout<<"White Turn"<<endl;
  }
}
  else cout<<"not accepted"<<endl;
}
else
exit=true;
}

   return 0;
   }


 bool touchMove(Board *aboard,Piece pieces[],int addtouch,int addmove,bool white) ////
 {
     string nameT,nameM;
     bool ok_touch = false;
     int THorz = addtouch%10;
     int TVert = addtouch/10;
     int MHorz = addmove%10;
     int MVert = addmove/10;
   THorz=switchNum(THorz,'h');
   MHorz=switchNum(MHorz,'h');
   TVert=switchNum(TVert,'v');
   MVert=switchNum(MVert,'v');

for(int i=0;i<=64;i++)//searching for the touched piece
       if((pieces[i].getItsHorzAddress()==TVert)&&(pieces[i].getItsVertAddress()==THorz)&&(pieces[i].getItsName()!="  "))
       {
        nameT=pieces[i].getItsName();
       if((white)&&(nameT[0]=='W')) ////white can move white only
       {
    for(int k=0;k<=64;k++)////searching for the target
    if((pieces[k].getItsHorzAddress()==MVert)&&(pieces[k].getItsVertAddress()==MHorz))
       {
           nameM=pieces[k].getItsName();
           if((white)&&(nameM[0]!='W'))
       {
           if(pieceMove(pieces,nameT,nameM,addtouch,addmove))////////////fuction for the rules of each piece movement
           {
        pieces[k].setItsName(pieces[i].getItsName());
     aboard->setPcsLoc(pieces[k].getItsName(),MHorz,MVert);

 pieces[i].setItsName("  ");
 aboard->setPcsLoc(pieces[i].getItsName(),THorz,TVert);
         ok_touch=true;
           }///////////////////////////////////////////////////
         }
       }
       }
       else if
             ((!white)&&(nameT[0]=='B')) ////black can move black only
       {
    for(int k=0;k<=64;k++) ///////searching for the touched piece
    if((pieces[k].getItsHorzAddress()==MVert)&&(pieces[k].getItsVertAddress()==MHorz))
       {
           nameM=pieces[k].getItsName();
           if((!white)&&(nameM[0]!='B'))
       {
           ///////////////////////////////////////////////////
         if(pieceMove(pieces,nameT,nameM,addtouch,addmove))////////////fuction for the rules of each piece movement
           {
        pieces[k].setItsName(pieces[i].getItsName());
     aboard->setPcsLoc(pieces[k].getItsName(),MHorz,MVert);

 pieces[i].setItsName("  ");
 aboard->setPcsLoc(pieces[i].getItsName(),THorz,TVert);
         ok_touch=true;
           }
         //////////////////////////////////////////////////////////
         }
       }
       }
       else ok_touch=false;
       }
     return ok_touch;
 }

  int switchNum(int num,char xChar)
  {
     if(xChar=='h')
      switch(num)
     {
         case 1 : num =2;
         break;
         case 2 : num =6;
         break;
         case 3 : num =10;
         break;
         case 4 : num =14;
         break;
         case 5 : num =18;
         break;
         case 6 : num =22;
         break;
         case 7 : num =26;
         break;
         case 8 : num =30;
         break;
         default :
         break;
     }
      else
          switch(num)
     {
         case 1 : num =2;
         break;
         case 2 : num =5;
         break;
         case 3 : num =8;
         break;
         case 4 : num =11;
         break;
         case 5 : num =14;
         break;
         case 6 : num =17;
         break;
         case 7 : num =20;
         break;
         case 8 : num =23;
         break;
         default :
         break;
     }
     return num;

  }

  void resetBoard(Board *gameBoard,Piece pcs[])
  {

   for(int i=0,j=2;i<8;i++)
   {
       pcs[i].setItsName("WP");
       pcs[i].setItsVertAddress(j);
       pcs[i].setItsHorzAddress(5);
       gameBoard->setPcsLoc(pcs[i].getItsName(),j,5);
        j+=4;
   }

   for(int i=8,j=2;i<16;i++)
   {
       pcs[i].setItsName("BP");
       pcs[i].setItsVertAddress(j);
       pcs[i].setItsHorzAddress(20);
       gameBoard->setPcsLoc(pcs[i].getItsName(),j,20);
        j+=4;
    }
/////set rook locations
     for(int i=16,j=2;i<18;i++)
   {
       //////set location for white rook
      pcs[i].setItsName("WR");
       pcs[i].setItsVertAddress(j);
       pcs[i].setItsHorzAddress(2);
       gameBoard->setPcsLoc(pcs[i].getItsName(),j,2);


        ////set location for black rook
           pcs[i+2].setItsName("BR");
      pcs[i+2].setItsVertAddress(j);
       pcs[i+2].setItsHorzAddress(23);
       gameBoard->setPcsLoc(pcs[i+2].getItsName(),j,23);
        j=30;


   }

   /////set Knight locations
     for(int i=20,j=6;i<22;i++)
   {
       //////set location for white knight
       pcs[i].setItsName("WN");
      pcs[i].setItsVertAddress(j);
       pcs[i].setItsHorzAddress(2);
       gameBoard->setPcsLoc(pcs[i].getItsName(),j,2);


        ////set location for black knight
         pcs[i+2].setItsName("BN");
       pcs[i+2].setItsVertAddress(j);
       pcs[i+2].setItsHorzAddress(23);
       gameBoard->setPcsLoc(pcs[i+2].getItsName(),j,23);
        j=26;
   }

    /////set Bishops locations
     for(int i=24,j=10;i<26;i++)
   {
       //////set location for white bishop
       pcs[i].setItsName("WB");
       pcs[i].setItsVertAddress(j);
       pcs[i].setItsHorzAddress(2);
       gameBoard->setPcsLoc(pcs[i].getItsName(),j,2);


        ////set location for black bishop
           pcs[i+2].setItsName("BB");
       pcs[i+2].setItsVertAddress(j);
       pcs[i+2].setItsHorzAddress(23);
       gameBoard->setPcsLoc(pcs[i+2].getItsName(),j,23);
        j=22;
   }

   /////set Queens locations
       //////set location for white queen
       pcs[28].setItsName("WQ");
       pcs[28].setItsVertAddress(14);
       pcs[28].setItsHorzAddress(2);
       gameBoard->setPcsLoc(pcs[28].getItsName(),14,2);

        ////set location for black queen
           pcs[29].setItsName("BQ");
       pcs[29].setItsVertAddress(14);
       pcs[29].setItsHorzAddress(23);
       gameBoard->setPcsLoc(pcs[29].getItsName(),14,23);

 /////set kings locations
       //////set location for white king
       pcs[30].setItsName("WK");
       pcs[30].setItsVertAddress(18);
       pcs[30].setItsHorzAddress(2);
       gameBoard->setPcsLoc(pcs[30].getItsName(),18,2);

        ////set location for black king
           pcs[31].setItsName("BK");
      pcs[31].setItsVertAddress(18);
       pcs[31].setItsHorzAddress(23);
       gameBoard->setPcsLoc(pcs[31].getItsName(),18,23);

/////////////set the other spots
int k=8;
   for(int i=32,j=2;i<64;i++)
   {
       //////set location for white knight
       pcs[i].setItsName("  ");
      pcs[i].setItsVertAddress(j);
       pcs[i].setItsHorzAddress(k);
       gameBoard->setPcsLoc(pcs[i].getItsName(),j,k);
        if(j<30)
            j+=4;
        else
        {
            j=2;
            k+=3;
        }
    }
  }

bool checkMove(int move)
{
   int first  = move/10;
   int second = move%10;
   if((first<1)||(first>8)||(second<1)||(second>8))
   return false;
   return true;
}


bool pieceMove(Piece pieces[],string nameT,string nameM,int touch ,int move )
{
     int moving=touch;
     int THorz = touch%10;
     int TVert = touch/10;
     int MHorz = move%10;
     int MVert = move/10;
     int movingH=THorz;
     int movingV=TVert;
     int diff=abs(touch-move);
     int signedDiff=touch-move;



    if(nameT[1]=='P') ////if its  pawn
    {
    if(nameT[0]=='W')//////white pawn
    {
       if(nameM[0]==' ')//////////////piece not attacking
       {
          if(move==touch+10)////one step forward ?
          return true;//yes? go
          return false;//no ? not accepted
       }
         else if(nameM[0]!=' ')////attacking abviously black piece
         if((move==touch+11)||(move==touch+9)) //moving diagonal down?
         return true; /////diagonal
          return false;/////not diagonal
    }
     if(nameT[0]=='B')//////black pawn
    {
       if(nameM[0]==' ')//////////////piece not attacking
       {
          if(move==touch-10)////one step up
          return true;/////up ok
           return false;/////not up not accepted
       }
          if(nameM[0]!='.')////attacking abviously white piece
         if((move==touch-11)||(move==touch-9)) ////diagonal up
         return true;/////ok move
         return false;////not accepted
    }
    return false;////any unexpected mistake will return a non accepted move
    }///////////////////////////////////////////////////////////////////end of pawn statment
    ////////////knight
     if(nameT[1]=='N')
    {
   int Hdiff=abs(THorz-MHorz);
   int Vdiff=abs(TVert-MVert);
   cout<<"Hdiff   and Vdiff are "<<Hdiff<<"  "<<Vdiff<<endl;
   if(((Hdiff==1)&&(Vdiff==2))||((Hdiff==2)&&(Vdiff==1)))
   return true;
   return false;
    }
    ////////////////////////////////////////////////////////////////////end night statement
      if(nameT[1]=='K')
    {
     if((diff==1)||(diff==11)||(diff==9)||(diff==10))////one step any direction
     return true; /////good move
     return false;////not accepted
        //////king
    }

     else if(nameT[1]=='R')
    {
     if((movingH==MHorz)||(movingV==MVert)) ////if its vertical or horizontal moving rook or queen
    {
        ////while loop to the check that there are no objects to block the moving objects's way
     while(moving!=move) ////the while loop ends if we reach the target
      {
      if(movingH>MHorz)//theobjects is moving to the left
          movingH--;
      if(movingH<MHorz)////right direction
          movingH++;
      if(movingV>MVert)//theobjects is moving Down
          movingV--;
      if(movingV<MVert)////Up direction
          movingV++;
          ////after we move and before we accept the movement we need to check if
          ////there is no object is  blocking the way of our moving object
           moving=movingV*10+movingH;
          if(moving!=move)
          if(!emptySpot(pieces,switchNum(movingH,'h'),switchNum(movingV,'v')))
          return false; ////if an object is found the movement cant be done



      }
      ////if the while loop ends  it means the path is clear and its ok to move
       return true;
        }
       else return false;
    }

    /////////different selection
     if(nameT[1]=='B')
    {
        if((diff%9==0)||(diff%11==0)) ////if its diagonal moving bishop or queen
        {
        ////while loop to the check that there are no objects to block the moving objects's way
      while(moving!=move) ////the while loop ends if we reach the target
      {
          if((MHorz>THorz)&&(MVert>TVert))//theobjects is moving to the left
          {
          movingH++;
          movingV++;
          }
          if((MHorz<THorz)&&(MVert<TVert))////right direction
          {
          movingH--;
          movingV--;
          }
           if((MHorz>THorz)&&(MVert<TVert))////right direction
          {
          movingH++;
          movingV--;
          }
           if((MHorz<THorz)&&(MVert>TVert))////right direction
          {
          movingH--;
          movingV++;
          }
          ////after we move and before we accept the movement we need to check if
          ////there is no object is  blocking the way of our moving object
          moving=movingV*10+movingH;
          if(moving!=move)
          if(!emptySpot(pieces,switchNum(movingH,'h'),switchNum(movingV,'v')))
          return false; ////if an object is found the movement cant be done
      }
      ////if the while loop ends  it means the path is clear and its ok to move
       return true;
        }
        else return false;
    }
        if(nameT[1]=='Q')
       {
            if((movingH==MHorz)||(movingV==MVert)) ////if its vertical or horizontal moving rook or queen
    {
        ////while loop to the check that there are no objects to block the moving objects's way
     while(moving!=move) ////the while loop ends if we reach the target
      {
      if(movingH>MHorz)//theobjects is moving to the left
          movingH--;
      if(movingH<MHorz)////right direction
          movingH++;
      if(movingV>MVert)//theobjects is moving Down
          movingV--;
      if(movingV<MVert)////Up direction
          movingV++;
          ////after we move and before we accept the movement we need to check if
          ////there is no object is  blocking the way of our moving object
           moving=movingV*10+movingH;
          if(moving!=move)
          if(!emptySpot(pieces,switchNum(movingH,'h'),switchNum(movingV,'v')))
          return false; ////if an object is found the movement cant be done
      }
      ////if the while loop ends  it means the path is clear and its ok to move
       return true;
        }
        if((diff%9==0)||(diff%11==0)) ////if its diagonal moving bishop or queen
        {
        ////while loop to the check that there are no objects to block the moving objects's way
      while(moving!=move) ////the while loop ends if we reach the target
      {
             if((MHorz>THorz)&&(MVert>TVert))//theobjects is moving to the left
          {
          movingH++;
          movingV++;
          }
          if((MHorz<THorz)&&(MVert<TVert))////right direction
          {
          movingH--;
          movingV--;
          }
           if((MHorz>THorz)&&(MVert<TVert))////right direction
          {
          movingH++;
          movingV--;
          }
           if((MHorz<THorz)&&(MVert>TVert))////right direction
          {
          movingH--;
          movingV++;
          }

          ////after we move and before we accept the movement we need to check if
          ////there is no object is  blocking the way of our moving object

          moving=movingV*10+movingH;
          if(moving!=move)
          if(!emptySpot(pieces,switchNum(movingH,'h'),switchNum(movingV,'v')))
          return false; ////if an object is found the movement cant be done


      }
      ////if the while loop ends  it means the path is clear and its ok to move
       return true;
       }
    }
return false;
}

bool emptySpot(Piece pieces[],int h, int v)
{
    for(int i=0;i<=64;i++)
       if((pieces[i].getItsHorzAddress()==v)&&(pieces[i].getItsVertAddress()==h)&&(pieces[i].getItsName()=="  "))
       return true;
       return false;
}