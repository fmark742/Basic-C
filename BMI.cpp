#include<toolbox.h>
#include<string.h>

//file pointer declaration
FILE *fp;
//function declarations
void forInput();
//string declarations
char sid[20],sname[20],input_sid[20];
//float declarations
float weight,height;

void mainMenu()
{
	//clears last screen
	system("cls");
	//main border
	line2(17,3,63,12);
	//prompt border
	line1(19,9,61,11);
	//prints conditions
	printxy(20,4,"A] Data Entry");
	printxy(20,5,"B] View");	
	printxy(20,6,"C] Search");
	printxy(20,7,"D] Close");
	printxy(20,8,"Select an option: ");
	//calls function for input
	forInput();
}

void dataEntry()
{
	//clears last prompt
	clearportion(20,9,60,9);
	//closes previous file
	fclose(fp);
	//int declarations
	int dup=0;
	//clears last screen
	clearportion(20,4,62,7);
	//opens file to read
	fp=fopen("bmi.txt","r");
	//for input
	printxy(20,5,"Student ID:");
	printxy(20,6,"Student name:");
	printxy(45,5,"Weight(kg):");
	printxy(45,6,"Height(m):");
	//scans the input
	gotoxy(32,5); scanf("\n"); gets(input_sid);
	gotoxy(34,6); gets(sname);
	gotoxy(57,5); scanf("%f",&weight);
	gotoxy(56,6); scanf("%f",&height);
	//scans the file
	while(fscanf(fp,"%s",sid)!=EOF)
	{
		//compares input and student id
		dup=strcmp(input_sid,sid);
		//condition for duplication
		if (dup==0){
			//prints prompt
			center(10,"The ID already exists");
			//breather
			Sleep(500);
			//repeat for another input
			dataEntry();
			//breather
			Sleep(500);
		}
	}
	//closes previous file
	fclose(fp);
	//opens file to append
	fp=fopen("bmi.txt","a");
	//prints the input
	fprintf(fp,"%s %s %.2f %.2f\n",input_sid,sname,height,weight);
	//closes the file
	fclose(fp);
	//prints prompt
	center(10,"The data has been added");
	//back to main menu
	getch(); mainMenu();
}

void view()
{
	//clears last screen
	system("cls");
	//int decalarations
	int row=4;
	//prints header
	printxy(10,2,"Student Id\t Student Name\t Height\t Weight\t BMI\t Remarks");
	//opens file to read
	fp=fopen("bmi.txt","r");
	//scans file
	while (fscanf(fp,"%s %s %f %f",sid,sname,&height,&weight)!=EOF)
	{
		//prints file content
		gotoxy(10,row); printf("%s",sid);
		gotoxy(25,row); printf("%s",sname);
		gotoxy(41,row); printf("%.2f",height);
		gotoxy(49,row); printf("%.2f",weight);
		
		//bmi formula
		float bmi=weight/(height*height);
		
		//prints bmi and remarks
		gotoxy(57,row); printf("%.2f",bmi);
		
		//conditionals for remarks
		if (bmi<=18.5)
			printf("   Underweight");
		else if (bmi>=18.6&&bmi<=24.99)	
			printf("   Normal");
		
		else if (bmi>=25&&bmi<=29.99)
			printf("   Overweight");
		else if (bmi>=30&&bmi<=34.99)
			printf("   Obese(Class 1)");
		else if (bmi>=35&&bmi<=39.99)
			printf("   Obese(Class 2)");
		else if (bmi>=40)
			printf("   Morbid Obese");
		else
			printf("   Invalid Input");
			
		//increments
		row++;
	}
	//closes the file
	fclose(fp);
	//breather
	getch();
	//back to main menu
	mainMenu();
}

void search()
{
	//clears last screen
	clearportion(20,4,62,8);
	clearportion(21,10,60,10);
	//integer declaration
	int cmp=0;
	//input
	printxy(20,5,"Student number: ");
	gotoxy(36,5); gets(input_sid);
	//opens file for reading
	fp=fopen("bmi.txt","r");
	//scans the file
	while (fscanf(fp,"%s %s %f %f",sid,sname,&height,&weight)!=EOF)
	{
		//compares the input and the student number
		cmp=strcmp(input_sid,sid);
		//condition if the input is found
		if (cmp==0){
			//prints the student name
			printxy(20,6,"Name:");
			printxy(26,6,sname);
			//bmi formula
			float bmi=weight/(height*height);
			//prints bmi
			gotoxy(20,7); printf("BMI: %.2f",bmi);
			//closes file
			fclose(fp);
			getch();
			//repeats the function
			mainMenu();
		}
	}
	//condition if the input is not found
	center(10,"Student number does not exist");
	//closes file
	fclose(fp);
	//breather
	getch();
	//repeats the function
	mainMenu();
}

void forInput()
{
	//clears last prompt
	clearportion(20,10,60,10);
	clearportion(38,8,60,8);
	//cursor
	gotoxy(38,8);
	//scans and holds the input
	char option=tolower(getche());
	//conditonals for input
	switch (option)
	{
		case 'a':
			//calls the function to input data
			dataEntry();
			break;
		case 'b':
			view();
			break;
		case 'c':
			search();
			break;	
		case 'd':
			//exits the program
			abort();
		default:
			//prints prompt
			center(10,"Invalid Input");
			//breather
			Sleep(500);
			//repeats for another input
			forInput();
			break;
	}
}

int main()
{
	//calls main menu
	mainMenu();
}