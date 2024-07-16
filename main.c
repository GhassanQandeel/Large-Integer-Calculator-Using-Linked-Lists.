/*GHASSAN QANDEEL
1212397
SECTION 3*/
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

//Doubly linked list has next prevous pointer ,data(digit of number) and sign of number
typedef struct number
{
    int sign, digit ;
    struct number *next;
    struct number *prev;

} number;

//For create an malloc node (number)
number* Create_Number(number* N);
//for insert digit of number in end
void Insert (int Digit,number* N);
//to convert from char to int for input data
int ConvertToInt(char c);
//to know how much number in file
int getNumberOfNumbersInFile() ;
//to read number from file and store it in linked list
void ReadFromFile(FILE*fptr,number*arraOfNumber[]);
//to display choises to user
int DisplayMenu();
//to select numbers for operations
int SelectFirstNumber(number*arrayofnumber[],int operationshappend);
int SelectsecondNumber(number*arrayofnumber[],int operationshappend);
//make addition
number*  AddOperation(number* fnum,number*snum,int sign);
//to decide sign of result and go to additon operation
number* AddResult(number* fnum,number*snum );
//to compare two number
int comparetwonumber(number* fnum,number*snum );
//to know how much digit we have
int SizeOfNumber(number*N);
//to inseret digit in linked list in first
void Insert_first(int Digit,number* N);
//to revese digit from end to first
number* ReverseEndToFirst(number*N);
//to delete zero we used in addition and subtraction
void deletzeros(number*snum,int sizefnum,int sizesnum );
//to set zero we used in addition and subtraction
void setzeros(number*snum,int sizefnum,int sizesnum );
//to decide sign of result and go to subtraction  operation
number* subtract(number* fnum, number*snum,int sign );
//to do subtraction
number* subtractOperation(number* fnum,number*snum );
//to decide sign of result and go to mltiplication  operation
number* Multiplication(number* fnum,number*snum,int sign);
//to  do mltiplication  operation
number* MultiplicationOperation(number* fnum,number*snum );
//to decide sign of result and go to division  operation
number* Division(number* fnum,number*snum,int sign);
//to do division  operation
number* DivisionOperation(number* fnum,number*snum );
//to write on file
void WriteOnFile(FILE*ofile,number*arrayOfNumber[],int numberofnumber);


int main()
{
    int sw;
    int x=getNumberOfNumbersInFile();
    int size=x*4*x*x;
    FILE *fptr,*ofile;
    int numberinarray=0;
    number* arrayOfNumber[size];

    for(int i=0; i<size; i++)
        arrayOfNumber[i]=Create_Number(arrayOfNumber[i]);


    printf("welcome,please choose what you want to do\n\n");
    sw=DisplayMenu();

    while(sw!=0)
    {
        if(sw==1)
        {
            FILE *fptr;
            ReadFromFile(fptr,arrayOfNumber);
            sw=DisplayMenu();
        }
        else if(sw==2)
        {
            int s1,s2;
            s1=SelectFirstNumber(arrayOfNumber,numberinarray);
            s2=SelectsecondNumber(arrayOfNumber,numberinarray);


            arrayOfNumber[numberinarray+getNumberOfNumbersInFile()]=AddResult(arrayOfNumber[s1],arrayOfNumber[s2]);
            numberinarray++;

            sw=DisplayMenu();
        }
        else if(sw==3)
        {
            int s1,s2;
            s1=SelectFirstNumber(arrayOfNumber,numberinarray);
            s2=SelectsecondNumber(arrayOfNumber,numberinarray);

            arrayOfNumber[numberinarray+getNumberOfNumbersInFile()]=subtractOperation(arrayOfNumber[s1],arrayOfNumber[s2]);
            numberinarray++;
            sw=DisplayMenu();

        }
        else if(sw==4)
        {
            int s1,s2;
            s1=SelectFirstNumber(arrayOfNumber,numberinarray);
            s2=SelectsecondNumber(arrayOfNumber,numberinarray);
            if (SizeOfNumber(arrayOfNumber[s1])>=SizeOfNumber(arrayOfNumber[s2]))
                arrayOfNumber[numberinarray+getNumberOfNumbersInFile()]=MultiplicationOperation(arrayOfNumber[s1],arrayOfNumber[s2]);
            else
                arrayOfNumber[numberinarray+getNumberOfNumbersInFile()]=MultiplicationOperation(arrayOfNumber[s1],arrayOfNumber[s2]);

            numberinarray++;
            sw=DisplayMenu();

        }

        else if(sw==5)
        {
            int s1,s2;
            s1=SelectFirstNumber(arrayOfNumber,numberinarray);
            s2=SelectsecondNumber(arrayOfNumber,numberinarray);
            if (comparetwonumber(arrayOfNumber[s1],arrayOfNumber[s2])>=0)
                arrayOfNumber[numberinarray+getNumberOfNumbersInFile()]=DivisionOperation(arrayOfNumber[s1],arrayOfNumber[s2]);
            else
                printf("This division operation is wrong.\n ");
            numberinarray++;
            sw=DisplayMenu();

        }
        else if (sw==6)
        {
            WriteOnFile(ofile,arrayOfNumber,numberinarray);
            break;

        }



    }



    return 0;
}
void ReadFromFile(FILE*fptr,number*arraOfNumber[])
{

    int i = 0;
// Open a file in read mode
    fptr = fopen("Input_file.txt", "r");

// Store the content of the file
    char myString[1000];

// Read the content and print it
    while(fgets(myString, 1000, fptr))
    {
        if(myString[0]=='-')
            arraOfNumber[i]->sign=-1;
        else
            arraOfNumber[i]->sign=1;

        for(int j=0 ; j<(strlen(myString)); j++)
        {

            if (ConvertToInt(myString[j])<10)
                Insert(ConvertToInt(myString[j]),arraOfNumber[i]);

        }
        i++;
    }
// Close the file
    fclose(fptr);
}

int getNumberOfNumbersInFile()
{

    FILE *fptr;
    int x = 0;
// Open a file in read mode
    fptr = fopen("Input_file.txt", "r");

    char myString[1000];

// check how many number in file
    while(fgets(myString, 1000, fptr))
        x++;


// Close the file
    fclose(fptr);
    return x;
}


number* Create_Number(number* N )
{

    N= (number*)malloc(sizeof(number));

    if(N == NULL)
        printf("Out of memory!\n");


    N->next= NULL;
    N->prev= NULL;
    return N;


}

void Insert (int Digit,number* N)
{
    number* temp;
    temp = (number*)malloc(sizeof(number));

    while(N->next!=NULL)
        N=N->next;

    temp->digit=Digit;
    temp->next=NULL;
    temp->prev=N;
    N->next=temp;
}
void Insert_first(int Digit,number* N)
{
    number* temp;
    temp = (number*)malloc(sizeof(number));
    temp->digit=Digit;
    temp->next=N->next;
    temp->prev=N;
    N->next=temp;
}
int ConvertToInt(char c)
{
    for (int i=0; i<10; i++)
        if ((int)c==(48+i))
            return i ;

}
void PrintNumber(number*N)
{
    if(N->sign==-1)
    {
        printf("-");
        while(N->next!=NULL)
        {
            printf("%d",N->next->digit);
            N=N->next;
        }
    }
    else if (N->sign==1)
        while(N->next!=NULL)
        {
            printf("%d",N->next->digit);
            N=N->next;
        }
}
int DisplayMenu()
{
    int sw;

    printf("1-Read from input file\n");
    printf("2-Add operation\n");
    printf("3-Subtraction operation\n");
    printf("4-Multiplication operation\n");
    printf("5-division operation\n");
    printf("6-Write on output file\n");
    printf("0-Exit\n");
    scanf("%d",&sw);
    return sw;
}
number* AddResult(number* fnum,number*snum )
{
    number*res;
    res=Create_Number(res);

    if(fnum->sign==-1&&snum->sign==-1)
        res=AddOperation(fnum,snum,-1);


    else if(fnum->sign==-1&&snum->sign==1)
    {
        if (comparetwonumber(fnum,snum)==1)
            res=subtract(fnum,snum,-1);


        else if (comparetwonumber(fnum,snum)==-1)
            res=subtract(snum,fnum,1);



    }
    else if (fnum->sign==1&&snum->sign==-1)
    {
        if (comparetwonumber(fnum,snum)==1)
            res=subtract(fnum,snum,1);


        else if (comparetwonumber(fnum,snum)==-1)
            res=subtract(snum,fnum,-1);


    }
    else if(fnum->sign==1&&snum->sign==1)
        res=AddOperation(fnum,snum,1);


    return res;
}
number*  AddOperation(number* fnum,number*snum,int sign )
{
    number*result;
    result =Create_Number(result);
    result->sign=sign;

    if(SizeOfNumber(fnum)==SizeOfNumber(snum))
    {

        fnum=ReverseEndToFirst(fnum);
        snum=ReverseEndToFirst(snum);
        int carry=0;
        while((fnum->next!=NULL) ||(carry==1 ))
        {
            fnum=fnum->next;
            snum=snum->next;
            if((fnum==NULL )&&(carry==1))
            {
                Insert_first(carry,result);
                break;
            }
            if ((fnum->digit+snum->digit+carry)>9)
            {
                Insert_first(((fnum->digit+snum->digit+carry)%10),result);
                carry=1;
            }
            else
            {
                Insert_first((fnum->digit+snum->digit+carry),result);
                carry=0;
            }
        }



    }
    else if (SizeOfNumber(fnum)>SizeOfNumber(snum))
    {
        int sizeofnumberbeforezeros=SizeOfNumber(snum);
        setzeros(snum,SizeOfNumber(fnum),SizeOfNumber(snum));


        fnum=ReverseEndToFirst(fnum);
        snum=ReverseEndToFirst(snum);
        int carry=0;
        while((fnum->next!=NULL) ||(carry==1 ))
        {
            fnum=fnum->next;
            snum=snum->next;
            if((fnum==NULL )&&(carry==1))
            {
                Insert_first(carry,result);
                break;
            }
            if ((fnum->digit+snum->digit+carry)>9)
            {
                Insert_first(((fnum->digit+snum->digit+carry)%10),result);
                carry=1;
            }
            else
            {
                Insert_first((fnum->digit+snum->digit+carry),result);
                carry=0;
            }
        }
        deletzeros(snum,SizeOfNumber(fnum),SizeOfNumber(snum));


    }
    else if (SizeOfNumber(fnum)<SizeOfNumber(snum))
    {
        int sizeofnumberbeforezeros=SizeOfNumber(fnum);
        setzeros(fnum,SizeOfNumber(snum),SizeOfNumber(fnum));
        fnum=ReverseEndToFirst(fnum);
        snum=ReverseEndToFirst(snum);
        int carry=0;
        while((fnum->next!=NULL) ||(carry==1 ))
        {
            fnum=fnum->next;
            snum=snum->next;
            if((fnum==NULL )&&(carry==1))
            {
                Insert_first(carry,result);
                break;
            }
            if ((fnum->digit+snum->digit+carry)>9)
            {
                Insert_first(((fnum->digit+snum->digit+carry)%10),result);
                carry=1;
            }
            else
            {
                Insert_first((fnum->digit+snum->digit+carry),result);
                carry=0;
            }
        }
    }
    return result;
}
int comparetwonumber(number* fnum,number*snum )
{

    if (SizeOfNumber(fnum)>SizeOfNumber(snum))
        return 1;
    else if (SizeOfNumber(fnum)<SizeOfNumber(snum))
        return -1;
    else if(SizeOfNumber(fnum)==SizeOfNumber(snum))
    {

        while(fnum->next!=NULL)
        {
            int countforequality=0;
            if(fnum->next->digit > snum->next->digit )
                return 1;
            else if(fnum->next->digit < snum->next->digit )
                return -1;
            else if(fnum->next->digit == snum->next->digit )
            {
                fnum=fnum->next;
                snum=snum->next;
                countforequality++;
                if(countforequality ==SizeOfNumber(fnum)&&countforequality ==SizeOfNumber(snum))
                    return 0 ;
            }

        }
    }
}
int SizeOfNumber(number*N)
{
    int count=0;
    while(N->next!=NULL)
    {
        count++;
        N=N->next;
    }

    return count;
}
number* ReverseEndToFirst(number*N)
{
    number* rev;
    rev =(number*)malloc(sizeof(number));
    while(N->next!=NULL)
    {
        Insert_first(N->next->digit,rev);
        N=N->next;
    }
    return rev;


}
void deletzeros(number*snum,int sizefnum,int sizesnum )
{
    number*temp;
    temp=Create_Number(temp);

    int i=0;

    while(i<(sizefnum-sizesnum))
    {
        temp=snum;
        snum->next=temp->next;
        snum->prev=NULL;
        free(temp);
        snum=snum->next;
        i++;
    }
    PrintNumber(snum);


}
void setzeros(number*snum,int sizefnum,int sizesnum )
{

    for(int j=0; j<(sizefnum-sizesnum); j++)
        Insert_first(0,snum);


}
int SelectFirstNumber(number*arrayofnumber[],int operationshappend)
{
    int s1;
    printf("choose the first number\n");

    for(int i=0; i<(operationshappend+getNumberOfNumbersInFile()); i++)
    {
        printf("%d-)",(i+1));
        PrintNumber(arrayofnumber[i]);
        printf("\n");
    }

    scanf("%d",&s1);
    s1--;
    return s1;
}
int SelectsecondNumber(number*arrayofnumber[],int operationshappend)
{
    int s2;
    printf("choose the second number\n");

    for(int i=0; i<(getNumberOfNumbersInFile()+operationshappend); i++)
    {
        printf("%d-)",(i+1));
        PrintNumber(arrayofnumber[i]);
        printf("\n");
    }

    scanf("%d",&s2);
    s2--;
    return s2;

}
number* subtract(number* fnum, number*snum,int sign)
{
    number*result;
    result =Create_Number(result);
    result->sign=sign;
    if(SizeOfNumber(fnum)==SizeOfNumber(snum))
    {
        fnum=ReverseEndToFirst(fnum);
        snum=ReverseEndToFirst(snum);
        while(fnum->next!=NULL)
        {
            fnum =fnum->next;
            snum=snum->next;


            if((fnum->digit-snum->digit)<0)
            {
                Insert_first(((fnum->digit+10)-(snum->digit)),result);
                if(fnum->next->digit!=0)
                    fnum->next->digit--;
                else
                    fnum=fnum->next;

            }
            else if((fnum->digit-snum->digit)>=0)
                Insert_first((fnum->digit-snum->digit),result);

        }
    }
    else if (SizeOfNumber(fnum)<SizeOfNumber(snum))
    {
        int sizeofnumberbeforezeros=SizeOfNumber(fnum);
        setzeros(fnum,SizeOfNumber(snum),SizeOfNumber(fnum));
        fnum=ReverseEndToFirst(fnum);
        snum=ReverseEndToFirst(snum);
        while(fnum->next!=NULL)
        {
            fnum =fnum->next;
            snum=snum->next;


            if((fnum->digit-snum->digit)<0)
            {
                Insert_first(((fnum->digit+10)-(snum->digit)),result);
                if(fnum->next->digit!=0)
                    fnum->next->digit--;
                else
                    fnum=fnum->next;

            }
            else if((fnum->digit-snum->digit)>=0)
                Insert_first((fnum->digit-snum->digit),result);
            deletzeros(fnum,SizeOfNumber(snum),SizeOfNumber(fnum));

        }
    }
    else if (SizeOfNumber(fnum)>SizeOfNumber(snum))
    {
        int sizeofnumberbeforezeros=SizeOfNumber(snum);
        setzeros(snum,SizeOfNumber(fnum),SizeOfNumber(snum));
        fnum=ReverseEndToFirst(fnum);
        snum=ReverseEndToFirst(snum);
        while(fnum->next!=NULL)
        {
            fnum =fnum->next;
            snum=snum->next;


            if((fnum->digit-snum->digit)<0)
            {
                Insert_first(((fnum->digit+10)-(snum->digit)),result);
                if(fnum->next->digit!=0)
                    fnum->next->digit--;
                else
                    fnum=fnum->next;

            }
            else if((fnum->digit-snum->digit)>=0)
                Insert_first((fnum->digit-snum->digit),result);
            deletzeros(snum,SizeOfNumber(fnum),SizeOfNumber(snum));
        }
    }
    return result;


}
number* subtractOperation(number* fnum,number*snum )
{
    number*res;
    res=Create_Number(res);

    if(fnum->sign==-1&&snum->sign==-1)
    {
        if (comparetwonumber(fnum,snum)==1)
            res=subtract(fnum,snum,-1);

        else if (comparetwonumber(fnum,snum)==-1)
            res=subtract(snum,fnum,1);

    }
    else if(fnum->sign==-1&&snum->sign==1)
        res=AddOperation(fnum,snum,-1);


    else if (fnum->sign==1&&snum->sign==-1)
        res=AddOperation(fnum,snum,1);


    else if(fnum->sign==1&&snum->sign==1)
    {
        if (comparetwonumber(fnum,snum)==1)
            res=subtract(fnum,snum,1);

        else if (comparetwonumber(fnum,snum)==-1)
            res=subtract(snum,fnum,-1);

    }
    return res;
}
number* Multiplication(number* fnum,number*snum,int sign )
{
    int size=SizeOfNumber(snum);
    number* temp=Create_Number(temp);
    temp->sign=sign;
    number* Foradd=Create_Number(Foradd);
    Foradd->sign=sign;
    number*arrayofresuls[size];
    for(int i=0; i<size; i++)
    {
        arrayofresuls[i]=Create_Number(arrayofresuls[i]);
        arrayofresuls[i]->sign=sign;

    }
    number*ArrayOfmulti[size];
    for(int i=0; i<size; i++)
    {
        ArrayOfmulti[i]=Create_Number(ArrayOfmulti[i]);
        ArrayOfmulti[i]->sign=1;
    }

    fnum=ReverseEndToFirst(fnum);
    snum=ReverseEndToFirst(snum);
    while(snum->next!=NULL)
    {

        while(fnum->next!=NULL)
        {
            Insert(fnum->next->digit*snum->next->digit,temp);
            fnum=fnum->next;
        }

        while(fnum->prev!=NULL)
            fnum=fnum->prev;


        snum=snum->next;
    }
    for(int i=0; i<size; i++)
        for(int j=0; j<i; j++ )
            Insert(0,arrayofresuls[i]);



    for(int i=0; i<size; i++)
        for(int j=0; j<SizeOfNumber(fnum); j++)
        {
            Insert(temp->next->digit,arrayofresuls[i]);
            temp=temp->next;
        }

    for(int i=0; i<size; i++)
    {

        while(arrayofresuls[i]->next!=NULL)
        {


            if(arrayofresuls[i]->next->digit>=10)
            {
                arrayofresuls[i]->next->next->digit+=arrayofresuls[i]->next->digit/10;
                arrayofresuls[i]->next->digit=arrayofresuls[i]->next->digit%10;
            }
            arrayofresuls[i]=arrayofresuls[i]->next;
        }

    }


    for(int i=0; i<size; i++)
        while(arrayofresuls[i]->prev!=NULL)
            arrayofresuls[i]=arrayofresuls[i]->prev;

    for(int i=0; i<size; i++)
    {
        ArrayOfmulti[i]=ReverseEndToFirst(arrayofresuls[i]);
        ArrayOfmulti[i]->sign=sign;
    }




    Foradd=ArrayOfmulti[0];
    for(int i=1; i<size; i++)
        Foradd=AddResult(Foradd,ArrayOfmulti[i] );

    return Foradd;


}
number* MultiplicationOperation(number* fnum,number*snum )
{
    number*res;
    res=Create_Number(res);

    if(fnum->sign==-1&&snum->sign==-1)
        res = Multiplication(fnum,snum,1);

    else if(fnum->sign==-1&&snum->sign==1)
        res =  Multiplication(fnum,snum,-1);

    else if (fnum->sign==1&&snum->sign==-1)
        res = Multiplication(fnum,snum,-1);

    else if(fnum->sign==1&&snum->sign==1)
        res =  Multiplication(fnum,snum,1);

    return res;

}

number* Division(number* fnum,number*snum,int sign)
{
    int count ;
    number *diviend,*result;
    diviend=Create_Number(diviend);
    diviend->sign=1;
    result=Create_Number(result);
    result->sign=sign;
    number *temp ;
    temp =Create_Number(temp );
    temp->sign=1;

    while(fnum->next!=NULL)
    {
        count=0;
        fnum=fnum->next;
        Insert(fnum->digit,diviend);

        while((comparetwonumber(diviend,snum)==-1)&&fnum->next!=NULL)
        {
            fnum=fnum->next;
            Insert(0,result);
            Insert(fnum->digit,diviend);

        }

        temp=diviend;

        while(comparetwonumber(temp,snum)>=0)
        {
            temp=subtractOperation(temp,snum);
            count++;
        }
        Insert(count,result);
        diviend=temp;
    }

    printf("\n");
    return result;
}
number* DivisionOperation(number* fnum,number*snum )
{
    number*res;
    res=Create_Number(res);

    if(fnum->sign==-1&&snum->sign==-1)
        res = Division(fnum,snum,1);

    else if(fnum->sign==-1&&snum->sign==1)
        res =  Division(fnum,snum,-1);

    else if (fnum->sign==1&&snum->sign==-1)
        res = Division(fnum,snum,-1);

    else if(fnum->sign==1&&snum->sign==1)
        res =  Division(fnum,snum,1);

    return res;
}
void WriteOnFile(FILE*ofile,number*arrayOfNumber[],int numberofnumber)
{

    ofile=fopen("Output_file.txt","w");
    for(int i=0; i<(getNumberOfNumbersInFile()+numberofnumber); i++)
    {
        if(arrayOfNumber[i]->sign==-1)
            fprintf(ofile,"%c",'-');
        for(int j=0; j<=SizeOfNumber(arrayOfNumber[i])+1; j++)
        {

            fprintf(ofile,"%d",arrayOfNumber[i]->next->digit);
            arrayOfNumber[i]=arrayOfNumber[i]->next;
        }
        fprintf(ofile,"\n","\n");
    }
    fclose(ofile);


}
