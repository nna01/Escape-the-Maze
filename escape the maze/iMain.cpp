#include<iostream>
#include<conio.h>
#include<string.h>
# include "iGraphics.h"
#include<vector>
using namespace std; 

#define MAX 10000
int Grid[MAX][MAX];
int mouseFlag=0;
bool gameover=false;
enum Directions{Left, Right, Up, Down, Okay, NotOkay, Quit, Continue, Pause};
enum Directions dir;
int DIR[MAX];
int HumX, HumY, SnakeX, SnakeY, ShowSnake;
//int TrailX[MAX], TrailY[MAX];
int flag=0, StartScreen, SnakeFlag, GridScreenFlag, HumFlag, KeyFlag,TailFlag,leftflag,rightflag,frontflag,backflag,gameBack, newGame, SnakeInCage;
int SnakeHeadRadius;
int Score=0, ScreenWidth=1340, ScreenHeigth=700;  
int TailX[1000],TailY[1000],nTail,SnakeTrailX[MAX], SnakeTrailY[MAX];

int BoundaryX[5000]={360};
int BoundaryY[5000]={120};

bool Menuplay=false,MenuScore=false,MenuExit=false,MenuControl=false,game=false,showScore=false,ControlScreen=false;

//pausing and resuming variable
bool pauseGame=false,resumeGame=true;
int pause,resume,resumeExit,resumeMenu;

int timeFlag,tsec=0;
vector<int>TrailX;
vector<int>TrailY;

//Speeding up variables
time_t StartTime, CurrTime;

//double TimeDiff=difftime(CurrTime, StartTime);
int increase;
int speedFlag;

int i,j,k,l,m,n,t1,s;
char printScore[100],printTime[1000],p2[1000],p1[1000],printHighScores[100][100];
int ScoreFlag[100]={0},coinFlag[100]={0};

int timeCount,minCount,secCount, menuFlag,ActualTime,backFlag,controlFlag,lastpageback,snakepicture;

//Coordinates where player has to click in order to increase score
int FoodX_Lower[100]={120,420,390,390,510,630,720,1050,810,960,1170,1230,200,1185};
int FoodX_Upper[100]={150,450,420,450,540,660,750,1080,840,990,1200,1260,230,1215};

int FoodY_Lower[100]={240,200,320,400,320,160,520,520,300,360,480,160,600,560};
int FoodY_Upper[100]={280,240,360,440,360,200,560,560,340,400,520,200,640,600};
int t;

//SpeedUp Variables
int  iteration=6;


//file variables
int highScoreFlag,currentTime,nHighScores=5,HScoreTemp;
FILE *fp,*p;

struct FileData{

    int HScore;
    char str[1000];
    int prevTime;
}temp,data[1000];

//reading data from file
void ReadData()
{
     //reading from the file
     fp=fopen("result.txt","r");
     for(i=0;i<nHighScores;i++)
     {
         fscanf(fp,"%d\t\t%s\t\t%d",&data[i].HScore,&data[i].str,&data[i].prevTime);
     }
      fclose(fp);
}
void sortData()
{
       for(i=0;i<nHighScores;i++)
      {
           for(j=i+1;j<nHighScores;j++)
           {
               //sorted by time
               if(data[i].prevTime>data[j].prevTime)
               {
                   temp=data[i];
                   data[i]=data[j];
                   data[j]=temp;
               }

                if(data[i].prevTime==data[j].prevTime)
               {
                   if(data[i].HScore<data[j].HScore)
                   {
                          HScoreTemp=data[i].HScore;
                          data[i].HScore=data[j].HScore;
                          data[j].HScore=HScoreTemp;
                   }
               }

           }
      }
}
void WritingData()
{
     sortData();
     p=fopen("output.txt","w");
     fp=fopen("result.txt","w");
     for(i=0;i<nHighScores;i++)
     {
         fprintf(p,"%d\t\t%s\n",data[i].HScore,data[i].str);
     }
     fclose(p);
     //writing the swapped data
     for(i=0;i<nHighScores;i++)
     {
         fprintf(fp,"%d\t\t%s\t\t%d\n",data[i].HScore,data[i].str,data[i].prevTime);
     }
    fclose(fp);
}
//Game Controls
void GameControl()
{
		if(KeyFlag==Quit)
			gameover=true;
}

//Generates Starting page
void StartGame()
{
	if(gameover==false)
	{
		 StartScreen=Okay;
		 HumX=30;
		 HumY=40;
		 //SnakeX=20;
		 //SnakeY=0;
		  Score=0;
	}
	else 
	{
	   StartScreen=NotOkay;
	}

}

void SnakeTail(){
	int prevX = TailX[0];
    int prevY = TailY[0];
    int prev2X, prev2Y;
    TailX[0] = SnakeX;
    TailY[0] = SnakeY;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = TailX[i];
        prev2Y = TailY[i];
        TailX[i] = prevX;
        TailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

	
}

//Snake body
void Snake()
{
	SnakeX=370;
	SnakeY=-10;
	SnakeHeadRadius=7;
	SnakeFlag=Okay;
}

//Human Struct
void Human()
{
	HumX=360;
	HumY=0;
	//HumX=690;
	//HumY=300;
	backflag=1;
	HumFlag=Okay;
	/*HumBodyWidth=12;
	HumBodyHeigth=25;
	HumHeadRadius=6;*/

}

void Timer()
{    
	
	if(secCount<10 && minCount==0)
	{     
		  sprintf (p1, "%d", secCount); 
		  strcpy(printTime,"00:0");
		  strcat(printTime,p1);
		  iText(565, 675,  printTime ,GLUT_BITMAP_TIMES_ROMAN_24);
	   	 
	}
	else if(secCount<=60 && minCount==0)
	{     
		 sprintf (p1, "%d", secCount); 
		 strcpy(printTime,"00:");
		 strcat(printTime,p1);
		 iText(565, 675,  printTime ,GLUT_BITMAP_TIMES_ROMAN_24);		 
	}
	else if(minCount>0&&minCount<10)
	{     
			  if(secCount<10)
		      {     
			    	sprintf (p2, "%d",minCount); 
					sprintf (p1, "%d",secCount); 
					strcpy(printTime,"0");
					strcat(printTime,p2);
					strcat(printTime,":0");
					strcat(printTime,p1);
					iText(565, 675,  printTime ,GLUT_BITMAP_TIMES_ROMAN_24);
					
		      }
			   else if(secCount<60)
		      {     
				    sprintf (p2, "%d",minCount); 
					sprintf (p1, "%d",secCount); 
					strcpy(printTime,"0");
					strcat(printTime,p2);
					strcat(printTime,":");
					strcat(printTime,p1);
					 iText(565, 675, printTime ,GLUT_BITMAP_TIMES_ROMAN_24);
				
		      }
	}

	else if(minCount>=10)
	{     
			  if(secCount<10)
		      {     
				    sprintf (p2, "%d",minCount); 
					sprintf (p1, "%d",secCount); 
					strcpy(printTime,p2);
					strcat(printTime,":0");
					strcat(printTime,p1);
					iText(565, 675, printTime ,GLUT_BITMAP_TIMES_ROMAN_24);
					
		      }
			   else if(secCount<60)
		      {     
				    sprintf (p2, "%d",minCount); 
					sprintf (p1, "%d",secCount); 
					strcpy(printTime,p2);
					strcat(printTime,":");
					strcat(printTime,p1);
					iText(565, 675, printTime ,GLUT_BITMAP_TIMES_ROMAN_24);	
		      }
	}

		
}
void time()
{   
	if(newGame==1)
	{    
		secCount=0;
		newGame=0;
		pauseGame==false;
		resumeGame=true;
	}
	
	secCount++;
	
	//SpeedUp
	
	if(secCount%5==0&&iteration>0)
		iteration--;
	
	
	cout<<"\nTime "<<secCount<<" iteration "<<iteration<<"\n";
	if(secCount>59)
	{   
		secCount=0;
		minCount++;
	}
    currentTime=(minCount*60)+secCount;
}

void Menu()
{
	
	iShowBMP(0,0,"menu.bmp");

	//play
	if(Menuplay==true)
		iShowBMP(0,0,"menuplay.bmp");
	//score
	else if(MenuScore==true)
	{	
		iShowBMP(0,0,"menuHighScore.bmp");
	}
	//control
	else if(MenuControl==true)
	{	
		iShowBMP(0,0,"menuControls.bmp");
	}
	//exit
	else if(MenuExit==true)
		iShowBMP(0,0,"menuexit.bmp");

	

}


void showHighScorePage()
{   


	p= fopen("output.txt","r");
	if(backFlag==0)
	iShowBMP(0,0,"scorepage1.bmp");

	else if(backFlag==1)
		iShowBMP(0,0,"scorepage2.bmp");


	//printing the highScores from File output on screen
   for(i=0;i<nHighScores;i++)
	{   
		fscanf(p,"%d\t\t%s",&data[i].HScore,&data[i].str);
		sprintf (printHighScores[i], "%d",data[i].HScore); 
		iText(1085, 160+(50*i),data[nHighScores-i-1].str ,GLUT_BITMAP_TIMES_ROMAN_24);
		iText(700, 160+(50*i), printHighScores[nHighScores-i-1] ,GLUT_BITMAP_TIMES_ROMAN_24);	
	}
	fclose(p);
	
    
}
/*double SpeedDown(){
	
	//iteration=4;
    //return iteration;
}*/
void SpeedUp(){
		
	/*if(iteration>0)
	{
		iteration--;
	}
	printf("iteration= %d\n",iteration);
   
	/*if(currentTime>0&&currentTime<=5){
		iteration=3;
	}
	else if(currentTime>5&&currentTime<=10){
		iteration=2;
	}
		
	else if (currentTime>10&&currentTime<=15){
		iteration=1;
	}
	else if (currentTime>15&&currentTime<=20){
		iteration=0;
	}
	//cout<<" TD: "<<currentTime<<" Iteration="<<iteration;
	return iteration;*/




}


void startScreen()
{
	 menuFlag=1;
	 StartScreen=NotOkay;
	 iPauseTimer(t1);
}
//	function iDraw() is called again and again by the system.
void iDraw()
{   

	//StartScreen
	iClear();
	
	//generating start page  "Escape The Maze"
	if(StartScreen==Okay)
	{      
		  iShowBMP(0, 0,"cover.bmp");
	}

	//Generating the Menu

	else if(menuFlag==1){
		    
		    highScoreFlag=0;
			Menu();
			//ControlScreen=false;
	}
	//Generating the HighScore Page
	else if(highScoreFlag==1)
	{   
		 menuFlag=0;
		 showHighScorePage();
	}

	//Generating the controls page
	else if(ControlScreen==true)
	{    
		 if(controlFlag==0)
		      iShowBMP(0,0,"controls.bmp");
		 if(controlFlag==1)
		     iShowBMP(0,0,"controls2.bmp");
	}
	
	//In case the start sceen doesn't open
	//Generating The Game page

	else if(StartScreen==NotOkay)
	{   
		 
		if(pause==1)
			  iShowBMP(0, 0, "gamepause.bmp");
		 else
            iShowBMP(0, 0, "game1.bmp");

		if(snakepicture==1)
		{	
			iShowBMP(0, 0, "InCage.bmp");
		}

		 //printing the score on demoo screen.
         sprintf (printScore, "%d", Score); 
         iText(1050, 675, "SCORE: " ,GLUT_BITMAP_TIMES_ROMAN_24);
	     iText(1150, 675, printScore ,GLUT_BITMAP_TIMES_ROMAN_24);
		

		 //last black box
		 iFilledRectangle(1290, 560, 30, 40);
		
		 //Timer Function
		 Timer();

	     //SnakeHead
	     if(ShowSnake==0)
	    {
			 //iSetColor(10,112,46);
			 iSetColor(255,0,0);
			 // iFilledCircle(SnakeX+2, SnakeY+2, 7, 100);
			if(dir==Right)
				iShowBMPWOBG(SnakeX, SnakeY, "SnakeRight.bmp");
			else if(dir==Left)
				iShowBMPWOBG(SnakeX, SnakeY, "SnakeLeft.bmp");
			else if(dir==Up)
				iShowBMPWOBG(SnakeX, SnakeY, "Snakeback.bmp");
			else if(dir==Down)
				iShowBMPWOBG(SnakeX, SnakeY, "SnakeFront.bmp");
						
			 /*if((dir==Left||dir==Right)&&(SnakeX==HumX+40||HumX-40))
				iFilledRectangle(SnakeX, SnakeY, 12, 7);
			 else if(dir==Left||dir==Right)
				iFilledRectangle(SnakeX, SnakeY, 7, 12);*/
		  
	    }

		 //the coin positions
		 for(i=0;i<14;i++)
		 {
		       if(coinFlag[i]==0)
		             iShowBMPWOBG(FoodX_Lower[i], FoodY_Lower[i], "coin1.bmp");
		 }
	    
	     if(HumFlag==Okay)
	    {
			
	
	      //GridScreen
		  /*iSetColor(0, 0, 0);
		  for(i=0; i<=ScreenWidth; i+=30)
		  {
			   iLine(i, 0, i, ScreenHeigth);
		  }
		  for(i=0; i<=ScreenHeigth; i+=40)
		  {
			   iLine(0, i, ScreenWidth, i);
		  }*/


		//Snake head following the trail? :C 
			
		 
		 
		  //point following the trail
		  for(int i=0 ;i<ScreenWidth; i++)
		  {
			  for(int j=0; j<ScreenHeigth; j++)
			 {				
				    if(Grid[i][j]==1)
				   {
			     	   // iSetColor(255,255,0);
					    //iPoint(i,j,2);
					    int countX=0;
						for(vector<int>::iterator it = TrailX.begin() ; it != TrailX.end(); ++it){
					    countX++;
						if(countX>6){
						SnakeX=*(it-iteration);//+SpeedUp();
				        }

					}
						 int countY=0;
						 for(vector<int>::iterator it = TrailY.begin() ; it != TrailY.end(); ++it){
						 countY++;
						 if(countY>6){
						 SnakeY=*(it-iteration);//+SpeedUp();
						}

					  }
				
					}

					/*if(Grid[HumX][HumY] >1){	
						 if(dir==Right){
							 int countX=0;
						for(vector<int>::iterator it = TrailX.begin() ; it != TrailX.end(); ++it){
					    countX++;
						if(countX>6){
						SnakeX=*(it-iteration)--;//+SpeedUp();
				        }

					  }
					}

					if(dir==Left){
							 int countX=0;
						for(vector<int>::iterator it = TrailX.begin() ; it != TrailX.end(); ++it){
					    countX++;
						if(countX>6){
						SnakeX=*(it-iteration)++;//+SpeedUp();
				        }

					  }
					}
					if(dir==Up){
							 int countY=0;
						for(vector<int>::iterator it = TrailY.begin() ; it != TrailY.end(); ++it){
					    countY++;
						if(countY>6){
						SnakeY=*(it-iteration)--;//+SpeedUp();
				        }

					  }
					}
					if(dir==Down){
							 int countX=0;
						for(vector<int>::iterator it = TrailY.begin() ; it != TrailY.end(); ++it){
					    countX++;
						if(countX>6){
						SnakeY=*(it-iteration)++;//+SpeedUp();
				        }

					  }
					}
					/*SnakeY-=40;
				if(dir==Down)
					SnakeY+=40;
				if(dir==Left)
					SnakeX+=30;
				if(dir==Right)
					SnakeX-=30
						//cout<<"SnakeX"<<SnakeX<<"SnakeY"<<SnakeY;
			
			}*/

				//printing the tail?:@ :C
		
				for(k=0; k<nTail; k++)
				{
					if(TailX[k]==i && TailY[k]==j)
					{
						//iSetColor(10, 112, 46);
						iSetColor(255,0,0);
						//iFilledCircle(i, j, 5, 100);
						
						/*if((dir==Left||dir==Right)&&(SnakeX==HumX+40||HumX-40))
						iFilledRectangle(i, j, 12, 7);
						else //if(dir==Left||dir==Right)
						iFilledRectangle(i, j, 7, 12);*/

						
					
					}
				}
			 }
		  }
		   //HumanBody
		      if(backflag==1)
		             iShowBMPWOBG(HumX, HumY, "back3.bmp");

			  if(leftflag==1)
					 iShowBMPWOBG(HumX, HumY, "leftf.bmp");

			  if(frontflag==1)
					  iShowBMPWOBG(HumX, HumY, "front1.bmp");

			  if(rightflag==1)
					 iShowBMPWOBG(HumX, HumY, "right.bmp");
	
		iSetColor(0, 0, 0);
		//tail
		//if(TailFlag==1)
		     // iFilledCircle(TailX[0], TailY[0], SnakeHeadRadius, 100);	



	   }
	   
		 if(pauseGame==true)
		{
			iShowBMP(449, 150, "pausepage1.bmp");
			
			if(resume==1)
				iShowBMP(449, 150, "resumebutton.bmp");

			else if(resumeMenu==1)
				iShowBMP(449, 150, "resumeMenu.bmp");

			else if(resumeExit==1)
				iShowBMP(449, 150, "resumeExit.bmp");

				 //resumeGame=true;		
		}
		
			 

	   if(gameover==true)
	   {    
		   iPauseTimer(t);
		   //iShowBMP(0, 0, "C:\\Users\\USER NAME\\Desktop\\pictures_Final\\InCage.bmp");
		    if(lastpageback==1)
				
		       iShowBMP(0, 0, "lastpage1.bmp");
		   else
                iShowBMP(0, 0, "lastpage2.bmp");

		   sprintf (printScore, "%d", Score); 
       
	        iText(507, 232, printScore ,GLUT_BITMAP_TIMES_ROMAN_24);
		    iText(507, 166, printTime ,GLUT_BITMAP_TIMES_ROMAN_24);
	   }
   
   }
	
} 

/* 
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{   	
	//place your codes here	
}

/* 
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{        
	 
   if(menuFlag==1)
   {    
	    
	   //when play button is clicked...the playing screen is displayed
	    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Menuplay==true)
        {     
			  Human();
			  Snake();
			  menuFlag=0;
			  ControlScreen=false;
			  StartScreen=NotOkay;
			  resumeGame=true;
		      pauseGame=false;
			  gameover=false;
			  newGame=1;
			  iResumeTimer(t);
        }

		//score screen is displayed
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && MenuScore==true)
        {     
			   menuFlag=0;
			  highScoreFlag=1;
        }
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && MenuControl==true)
        {     
			   menuFlag=0;
			   //highScoreFlag=0; 
			   ControlScreen=true;
        }
		else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && MenuExit==true)
        {     
			  exit(0);
        }
		
		
   }
   //when back button on HighScore screen is clicked...this shifts back to main menu
   if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN&&(mx>=25&&mx<=190)&&(my>=598&&my<=670))
   {
	   menuFlag=1;
   }

   //control page    
	 if(controlFlag==1)
		   menuFlag=1;
	 

	 //pauses game by clicking pause button of game screen
	 if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && pause==1)
	 {
		 iPauseTimer(t);
		 pauseGame=true;
		 resumeGame=false;
		 pause=0;

	 }

	 //when exit button of paused screen is clicked then the screen turns off
	 if(resumeExit==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		exit(0);
	 
	 //resumes to menu
	 if(resumeMenu==1 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	 {	
		 menuFlag=1;	
	 }

	 //resumes game by clicking resume button of game screen
	 if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && resume==1)
	 {
		 iResumeTimer(t);
		 resumeGame=true;
		 pauseGame=false;	
		 resume=0;
	 }

    
}
/*iPassiveMouseMove is called to detect and use 
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	 //highlights the buttons of menu when cursor is on the button
	if(menuFlag==1)
   {    
	   
	   //times of game paused until play button is clicked
	   iPauseTimer(t);

	   //highlights play
	    if((mx>=158&&mx<=492)&&(my>=550&&my<=605))
        {     
		      Menuplay=true;
        }
		else
			Menuplay=false;

		 //highlights Score button
		if((mx>=158&&mx<=492)&&(my>=431&&my<=487))
        {     
		      MenuScore=true;
        }
		else
			MenuScore=false;

		 //highlights control button
		if((mx>=158&&mx<=492)&&(my>=310&&my<=363))
		{
			MenuControl=true;
		}
		else
           MenuControl=false;

		//highlights exit button
		if((mx>=158&&mx<=492)&&(my>=203&&my<=259))
        {     
		      MenuExit=true;
        }
		else
			MenuExit=false;

   }

	
    //highlights high back button of score page
	if(highScoreFlag==1)
	{
	   if((mx>=25&&mx<=190)&&(my>=598&&my<=670))
		  backFlag=1;
      else
		  backFlag=0;
	}

	//highlights high back button of control page
    if(ControlScreen==true)
	{    
		 if((mx>=1068&&mx<=1250)&&(my>=588&&my<=667))
		     controlFlag=1;
		 else
			 controlFlag=0;
	}

	//highlighting the last page back button
	if(gameover==true)
	{
		if((mx>=44&&mx<=259)&&(my>=611&&my<=669))
		     lastpageback=1;
		 else
			 lastpageback=0;
	}

	//higlighting the pausing and resuming buttons in game screen
	if(resumeGame==true)
	{
		if((mx>=14&&mx<=98)&&(my>=673&&my<=692))
		    pause=1;
		 else
			 pause=0;
	}

	if(pauseGame==true)
	{   
		//higlighting the resume button
		if((mx>=623&&mx<=758)&&(my>=444&&my<=493))
		    resume=1;
		 else
			 resume=0;

		//highlighting the menu button
		if((mx>=623&&mx<=758)&&(my>=335&&my<=387))
		    resumeMenu=1;
		 else
			 resumeMenu=0;
		//highlighting the exit button
		if((mx>=623&&mx<=758)&&(my>=238&&my<=289))
		    resumeExit=1;
		 else
			 resumeExit=0;
	}
 
}

	//function iKeyboard() is called whenever the user hits a key in keyboard.
	//key- holds the ASCII value of the key pressed. 


void iKeyboard(unsigned char key)
{   
	
	//m button has to be clicked in order to get the coin from the specific positions
	for(i=0;i<14;i++)
	{
		if((HumX>=FoodX_Lower[i]&&HumX<=FoodX_Upper[i])&&(HumY>=FoodY_Lower[i]&&HumY<=FoodY_Upper[i])&& key== 'm'&& Grid[HumX][HumY]==1)
		{       
			    speedFlag=Okay;
				if(iteration<6)iteration++;
				 printf("Iteration =%d\n",iteration);
				coinFlag[i]=1;
				//SpeedDown();
				if( ScoreFlag[i]==0)
				{
					ScoreFlag[i]=1;
					Score+=10;
				}		         
		}
		if( (HumX==1185&&HumY==560) && key== 'm'&& Grid[HumX][HumY]==1)
		{	 
			snakepicture=1;
			ShowSnake=1;
			SnakeFlag=NotOkay;
		}
		
		 if((HumX>=FoodX_Lower[i]&&HumX<=FoodX_Upper[i])&&(HumY>=FoodY_Lower[i]&&HumY<=FoodY_Upper[i])&& key== 'n'&&Grid[HumX][HumY]==1)
         {
             nTail++;
             TailFlag=1;
			 //SpeedUp();
			 //Score-=5;
         }
		
		 
	}
	
	//increasing the speed of the snake
	/*if(speedFlag==true)
	{   
			iPauseTimer(s);
			iteration++;
			//SpeedDown();
			speedFlag=false;
	}
	else if(speedFlag==false)
		iResumeTimer(s);
		*/
	speedFlag=NotOkay;
	if((HumX>=1290&&HumX<=1320)&&(HumY>=560&&HumY<=600)&& key== 'm')
	{      
		 iPauseTimer(t);
		 Human();
		 Snake();
		//swaping the last score with present score if time is less than
			if(currentTime<data[nHighScores-1].prevTime&&currentTime!=0)
			{
				 data[nHighScores-1].HScore=Score;
				 data[nHighScores-1].prevTime=currentTime;
				 strcpy(data[nHighScores-1].str,printTime);
			}

			//Snake In The Cage
			//SnakeInCage=Okay;
			//calling the writing data function whenever the game ends
			WritingData();
			gameover=true;	   
	}
	

}
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use 
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, 
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, 
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT 
*/
void iSpecialKeyboard(unsigned char key)
{   
	//human only moves when game is played or resumed
	if(pauseGame==false)
	{
		//Move Up 
	if((HumX==360&&(HumY>=0&&HumY<120))||(HumX==120&&(HumY>=120&&HumY<=220))||(HumX==210&&(HumY>=240&&HumY<=320+20))||
		(HumX==300&& (HumY>=180&&HumY<240))||(HumX==390&&(HumY>=200&&HumY<=280+20))||(HumX==510&&(HumY>=200&&HumY<=480+20))||
		(HumX==540&&(HumY>=440&&HumY<=480+20))||
		(HumX==270&&(HumY>=400&&HumY<=600-20))||
		(HumX==30&&(HumY>=320&&HumY<=400+15+15))||
		(HumX==0&&(HumY>=440&&HumY<=600-20))||
		((HumX==90||HumX==150)&&(HumY>=510&&HumY<=620-20-20))||
		(HumX==450&&(HumY>=560&&HumY<=600))||
		(HumX==720&&(HumY>=480&&HumY<=600-20))||
		(HumX==660&&(HumY>=360&&HumY<=440+20))||
		(HumX==690&&(HumY>=200&&HumY<=320+20))||
		(HumX==630&&(HumY>=40&&HumY<=160+20))||
		(HumX==975&&(HumY>=200&&HumY<=420))||
		(HumX==960&&(HumY>=40&&HumY<=80+20))||
		(HumX==810&&(HumY>=200&&HumY<=330+20))||
		(HumX==1065&&(HumY>=440&&HumY<=540))||
		(HumX==1140&&(HumY>=120&&HumY<=260))||
		(HumX==1245&&(HumY>=120&&HumY<=380))||(HumX==1170&&(HumY>=400&&HumY<=440+20)))
   {       
	       
	       if(key == GLUT_KEY_UP)
          {	  
			  backflag=1;
		      leftflag=0;
			  frontflag=0;
			  rightflag=0;
			  dir=Up;
		      HumY+=20;			
          }
	}
	//Move Down
	if((HumX==360&&(HumY>=20&&HumY<=120))||
		(HumX==120&&(HumY>=120+20&&HumY<=240))||
		(HumX==210&&(HumY>=280-20&&HumY<=360))||
		(HumX==300&&(HumY>=220&&HumY<=280))||
	   (HumX==390&&(HumY>=240-20&&HumY<=320))||
	   (HumX==510&&(HumY>=240-20&&HumY<=520))||
	   (HumX==540&&(HumY>=480-20&&HumY<=520))||
	   (HumX==270&&(HumY>=440-20&&HumY<=640))||
	   (HumX==30&&(HumY>=360&&HumY<=440))||
	   (HumX==0&&(HumY>=440+15&&HumY<=620))||
	   ((HumX==90||HumX==150)&&(HumY>=540&&HumY<=620))||
	   (HumX==450&&(HumY>=600-20&&HumY<=640))||
	   (HumX==720&&(HumY>=480+20&&HumY<=600))||
	   (HumX==660&&(HumY>=400-20&&HumY<=480))||
	   (HumX==690&&(HumY>=240-20&&HumY<=360))||
	   (HumX==630&&(HumY>=80-20&&HumY<=200))||
	   (HumX==975&&(HumY>=220&&HumY<=440))||
	   (HumX==960&&(HumY>=80-20&&HumY<=120))||
	   (HumX==810&&(HumY>=240-20&&HumY<=360))||
	   (HumX==1065&&(HumY>=460&&HumY<=560))||
	    (HumX==1140&&(HumY>=130&&HumY<=280))||
		(HumX==1230&&(HumY>=150-20&&HumY<=440))||
		(HumX==1170&&(HumY>=440-20&&HumY<=480)))
   {       
		   //Move Down
	       if(key == GLUT_KEY_DOWN)
	      {	
		      dir=Down;
	       	  HumY-=20;		
			  backflag=0;
		      leftflag=0;
			  frontflag=1;
			  rightflag=0;
	     }
	}
	//Move Left
	if((HumY==120&&((HumX<=360+15&&HumX>=130)||(HumX<=1230&&HumX>=1050)))||
		(HumY==240&&(HumX<=320&&HumX>=120+15))||
		(HumY==360&&(HumX<=210&&HumX>=120))||
	   (HumY==200&&((HumX<=510&&HumX>=330-15)||(HumX<=690&&HumX>=600)||(HumX<=960+15&&HumX>=840-15)))||
	   (HumY==400&&(HumX<=510&&HumX>=280))||
	   ((HumY==520||HumY==480)&&(HumX<=570&&HumX>=540-15))||
	   (HumY==440&&((HumX<=600&&HumX>=540-15)||(HumX<=1050+15&&HumX>=990)||(HumX<=270&&HumX>=10)))||
	   (HumY==520&&(HumX<=150&&HumX>=90+15))||
	   (HumY==600&&((HumX<=100&&HumX>=0+15)||(HumX<=300&&HumX>=160)||(HumX<=740&&HumX>=460)))||
       (HumY==560&&((HumX<=450&&HumX>=280)||(HumX<=180&&HumX>=90)||(HumX<=1340&&HumX>=1080)))||
	   (HumY==480&&(HumX<=720&&HumX>=690-15))||
	   (HumY==360&&(HumX<=810&&HumX>=690-15))||
	   (HumY==40&&(HumX<=960&&HumX>=660-15))||
	   (HumY==280&&(HumX<=1140&&HumX>=990))||
	   (HumY==400&&(HumX<=1245&&HumX>=1200-15)))
	{
		   if(key == GLUT_KEY_LEFT)
	      {	  
			  
		      dir=Left;
		      HumX-=15;
			   leftflag=1;
		       backflag=0;
			   frontflag=0;
			   rightflag=0;
	      }
	}
	//MOve Right
	if((HumY==120&&((HumX<=330+15&&HumX>=120)||(HumX<=1200+30&&HumX>=1020)))||
		(HumY==240&&(HumX<=300-15&&HumX>=120))||
		(HumY==360&&(HumX<=180&&HumX>=90))||
		(HumY==200&&((HumX<=500&&HumX>=300)||(HumX<=660+15&&HumX>=570)||(HumX<=930+30&&HumX>=810)))||
		(HumY==400&&(HumX<=480+15&&HumX>=270))||
		((HumY==520||HumY==480)&&(HumX<=510+15&&HumX>=480))||
		(HumY==440&&((HumX<=570&&HumX>=510)||(HumX<=1050&&HumX>=960)||(HumX<=280-15&&HumX>=0)))||
		(HumY==520&&(HumX<=150-15&&HumX>=90))||
		(HumY==600&&((HumX<=90-15&&HumX>=0)||(HumX<=250+15&&HumX>=150)||(HumX<=720-15&&HumX>=450)))||
		(HumY==560&&((HumX<=440&&HumX>=270)||(HumX<=1300&&HumX>=1050)))||
		(HumY==480&&(HumX<=690+15&&HumX>=660))||
		(HumY==360&&(HumX<=780+15&&HumX>=660))||
		 (HumY==40&&(HumX<=930+15&&HumX>=630))||
		 (HumY==280&&(HumX<=1130&&HumX>=960))||
         (HumY==400&&(HumX<=1200+15&&HumX>=1170)))
	{
		   if(key == GLUT_KEY_RIGHT)
	      {	    
	        	dir=Right;
		        HumX+=15;
				backflag=0;
		       leftflag=0;
			   frontflag=0;
			   rightflag=1;
	      }
	}
	
	        
		//snake doesn't collides with man
		    Grid[HumX][HumY]++;
			//Grid[HumX][HumY]=1;
			TrailX.push_back(HumX);
			TrailY.push_back(HumY);
			//if(Grid[HumX][HumY] % 2 !=0)
			
			/*if(Grid[HumX][HumY] >1)
			{	 if(dir==Up)
					SnakeY-=40;
				if(dir==Down)
					SnakeY+=40;
				if(dir==Left)
					SnakeX+=30;
				if(dir==Right)
					SnakeX-=30;
				cout<<"SnakeX"<<SnakeX<<"SnakeY"<<SnakeY;
			
			}*/
			
			
		if(HumX==SnakeX && HumY==SnakeY)
			{	
				gameover=true;
			}
			
			printf("HumX= %d HumY=%d Grid[HumX][HumY]=%d\n",HumX,HumY,Grid[HumX][HumY]);
			
			//SpeedUpY();

	}

}
int main()
{ 
	
	StartGame();
	//iSetTimer(500, SnakeTail);
	//s=iSetTimer(5000,SpeedUp);
	//genrating the start screen for 5 seconds
	t1= iSetTimer(3500,startScreen);
	
	// timer in the game
    t= iSetTimer(1000,time);
    iPauseTimer(t);

	ReadData();
	WritingData();

  //place your own initialization codes here. 
	iInitialize(ScreenWidth,ScreenHeigth, "Escape the maze");

	
	
	return 0;
}	
