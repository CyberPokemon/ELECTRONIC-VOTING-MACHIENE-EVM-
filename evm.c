#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#define ENTER 13
#define BACKSPACE 8

enum boolean
{
    false,
    true,
    lock
};
typedef char *string;
struct contestant
{
    // string name,party;
    char name[20];
    char party[20];
    int votes;
    float percentage;
};

struct voter
{
    char name[20];
    int enrollmentNo;
    int votes;
};
struct contestant *con;
struct voter *votr;
char electionName[100];
int numberOfContestents = 0, numberOfVoters = 0;
int conlist = false, votlist = false, reset = false;
void sort(int n)
{
    int i, j;
    struct contestant temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (con[j].votes < con[j + 1].votes)
            {
                temp = con[j];
                con[j] = con[j + 1];
                con[j + 1] = temp;
            }
        }
    }
}
void sortvoter(int n)
{
    int i, j;
    struct voter temp;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (votr[j].enrollmentNo > votr[j + 1].enrollmentNo)
            {
                temp = votr[j];
                votr[j] = votr[j + 1];
                votr[j + 1] = temp;
            }
        }
    }
}
int votersearch(int id)
{
    int low = 0, high = numberOfVoters - 1, mid;
    while (low <= high)
    {
        mid = low + ((high - low) / 2);
        if (votr[mid].enrollmentNo == id)
        {
            return mid;
        }
        if (votr[mid].enrollmentNo > id)
        {
            high = mid - 1;
        }
        if (votr[mid].enrollmentNo < id)
        {
            low = mid + 1;
        }
    }
    return -1;
}
int votersearch2(int id, int k)
{
    int i;
    for (i = 0; i < k; i++)
    {
        if (votr[i].enrollmentNo == id)
            return i;
    }
    return -1;
}
void candidateListDisplay()
{
    printf("BUTTON NO\tNAME                \tPARTY\n");
    int i;
    for (i = 0; i <= numberOfContestents; i++)
    {
        printf("%9d\t%-20s\t%-20s", (i + 1), con[i].name, con[i].party);
        printf("\n");
    }
}
int newpoll()
{

    char *s;
    int i, l;
//    getchar();
//    printf("Enter name of election : ");
//    scanf("%[^\n]", s);
    // fgets(electionName, 100, stdin);
    // l = strlen(electionName);
    // if (electionName[l - 1] == '\n')
    //     electionName[l - 1] = '\0';
//    fgets(s,100,stdin);
//    l=strlen(s);
//    if(s[l-1]=='\n')
//    s[l-1]='\0';
//    
//    getchar();
//    strcpy(electionName, s);
    printf("Enter no of contestents : ");
    scanf("%d", &numberOfContestents);
    getchar();
    if (numberOfContestents < 2)
    {
        printf("VERY LESS NUMBER OF CONTESTENT.. MINIMUM 2 CONTESTANT REQUIRED\n");
    }
    con = (struct contestant *)malloc((numberOfContestents + 1) *
                                      sizeof(struct contestant));
    printf("Enter candidate details : \n");
    for (i = 0; i < numberOfContestents; i++)
    {

        printf("ENTER CANDIDATES NAME : ");

        // fflush(stdin);
        fgets(con[i].name, 20, stdin);
        l = strlen(con[i].name);
        if (con[i].name[l - 1] == '\n')
            con[i].name[l - 1] = '\0';
        printf("ENTER PARTY : ");

        // fflush(stdin);
        fgets(con[i].party, 20, stdin);
        l = strlen(con[i].party);
        if (con[i].party[l - 1] == '\n')
            con[i].party[l - 1] = '\0';
        con[i].votes = 0;
        con[i].percentage = 0;
    }
    strcpy(con[numberOfContestents].name, "NONE");
    strcpy(con[numberOfContestents].party, "NOTA");
    con[numberOfContestents].votes = 0;
    con[numberOfContestents].percentage = 0;
    printf("data entry for contestants completed \n");
    conlist = true;
    Sleep(5000);
    system("cls");
}
int results()
{
    int secuiritykey = 98765, esecuiritykey;
    int track = 0;
    int i;
    while (track < 3)
    {
        char password[128], c;
        int passi = 0;
        printf("Enter security key :");
        while ((c = getch()) != ENTER)
        {
            if (passi < 0)
            {
                passi = 0;
            }
            if (c == BACKSPACE)
            {
                putchar('\b');
                putchar('\0');
                putchar('\b');
                passi--;
                continue;
            }
            password[passi++] = c;
            putchar('*');
        }
        password[passi++] = '\0';
        esecuiritykey = atoi(password);
        // scanf("%d", &esecuiritykey);
        if (esecuiritykey == secuiritykey)
        {
            printf("\nRESULT LOGIN SUCCESSFUL\n");
            break;
        }
        else
        {
            printf("\nINCORRECT SECURITY KEY...ENTER AGAIN\n");
            track++;
        }
    }
    if (track == 3)
    {
        printf("\nSORRY YOU CANNOT ACCESS THE SYSTEM AS YOU HAVE ENTERED WRONG PASSWORD 3 TIMES\n");
        return 0;
    }

    if (votlist == lock && conlist == lock)
    {
        //printf("%s\n", electionName);
        sort(numberOfContestents);
        int totalNumberOfVotes = 0;
        for (i = 0; i <= numberOfContestents; i++)
        {
            totalNumberOfVotes += con[i].votes;
        }
        for (i = 0; i <= numberOfContestents; i++)
        {
            con[i].percentage = (((float)con[i].votes) / (totalNumberOfVotes)) * 100;
        }
        printf("RANK NAME                 PARTY                VOTES PERCENTAGE\n");
        for (i = 0; i <= numberOfContestents; i++)
        {
            printf("%4d %-20s %-20s %5d %.2f\n", (i + 1), con[i].name, con[i].party,
                   con[i].votes, con[i].percentage);
        }
        if (con[0].votes != con[1].votes)
            printf("%s(%s) won by %d votes\n", con[0].name, con[0].party,
                   con[0].votes - con[1].votes);
        else
        {
            printf("CLEAR WINNER CANNOT BE DETERMINED AS IT IS A TIE\n");
        }
    }
    else
    {
        printf("VOTERS LIST AND CANDIDATE LIST NOT LOCKED.\n");
        return -1;
    }
}

int voterlist()
{
    int i, l;
    getchar();
    printf("enter number of voters : ");
    scanf("%d", &numberOfVoters);
    getchar();
    votr = (struct voter *)malloc(numberOfVoters * sizeof(struct voter));

    printf("Enter voters details : \n");
    for (i = 0; i < numberOfVoters; i++)
    {

        printf("ENTER VOTERS NAME : ");
        fgets(votr[i].name, 20, stdin);
        l = strlen(votr[i].name);
        if (votr[i].name[l - 1] == '\n')
            votr[i].name[l - 1] = '\0';

        printf("enter enrollment no : ");
        scanf("%d", &votr[i].enrollmentNo);
        getchar();
        votr[i].votes = false;
        if (votersearch2(votr[i].enrollmentNo, i) != -1)
        {
            printf("THIS ENROLLMENT NUMBER AREADY EXISTS\nPLEASE RE ENTER YOUR DETAILS WITH CORRECT CREDENTIALS\n");
            i--;
        }
    }
    sortvoter(numberOfVoters);
    printf("data entry for voters completed \n");
    votlist = true;
    Sleep(5000);
    system("cls");
}
int admin()
{
    int ch, turn = 1;

    int key = 456789;
    int ekey;
    int track = 0;
    while (track < 3)
    {
        char password[128], c;
        int passi = 0;
        printf("Enter security key :");
        while ((c = getch()) != ENTER)
        {
            if (passi < 0)
            {
                passi = 0;
            }
            if (c == BACKSPACE)
            {
                putchar('\b');
                putchar('\0');
                putchar('\b');
                passi--;
                continue;
            }
            password[passi++] = c;
            putchar('*');
        }
        password[passi++] = '\0';
        // scanf("%d", &ekey);
        ekey = atoi(password);
        if (ekey == key)
        {
            printf("\nLOGIN TO ADMIN SUCCESSFUL\n");
            break;
        }
        else
        {
            printf("\nINCORRECT SECURITY KEY...ENTER AGAIN\n");
            track++;
        }
    }
    if (track == 3)
    {
        printf("\nSORRY YOU CANNOT ACCESS THE ADMIN AS YOU HAVE ENTERED WRONG PASSWORD 3 TIMES");
        return 0;
    }

    while (turn)
    {
        printf("MENU\n");
        printf("1. New poll\n");
        printf("2. Voter's List\n");
        printf("3. Results\n");
        printf("4. Back\n");
        printf("ENTER YOUR CHOICE : ");
        scanf("%d", &ch);
        system("cls");
        switch (ch)
        {
        case 1:
            if (conlist != lock)
                newpoll();
            else
                printf("LIST IS LOCKED AND CANNOT BE EDITED NOW\n");
            break;
        case 2:
            if (votlist != lock)
                voterlist();
            else
                printf("LIST IS LOCKED AND CANNOT BE EDITED NOW\n");
            break;
        case 3:
            results();
            break;
        case 4:
            system("cls");
            return 1;
        default:
            printf("IMVALID INPUT.... TRY AGAIN\n");
        }
    }

    return 0;
}
int voting()
{
    int key1 = 234, key2 = 987, key;
    int enrollno, index, confirm, choice;
    if (conlist == true && votlist == true)
    {
        while (true)
        {
            printf("enter secuirity key : ");
            char password[128], c;
            int passi = 0;
            while ((c = getch()) != ENTER)
            {
                if (passi < 0)
                {
                    passi = 0;
                }
                if (c == BACKSPACE)
                {
                    putchar('\b');
                    putchar('\0');
                    putchar('\b');
                    passi--;
                    continue;
                }
                password[passi++] = c;
                putchar('*');
            }
            password[passi++] = '\0';
            key = atoi(password);
            if (key == key2)
            {
                printf("\nVOTING COMPLETED. EMV LOCKED SUCCESSFULLY\n");
                votlist = lock;
                conlist = lock;
                Sleep(3000);
    			system("cls");

                return 1;
            }
            else if (key == key1)
            {
                printf("\nENTER YOUR ENROLLMENT NUMBER : ");
                scanf("%d", &enrollno);
                index = votersearch(enrollno);
                if (index == -1)
                {
                    printf("INVALID ENROLLMENT NUMBER\n");
                    continue;
                }
                else if (votr[index].votes == true)
                {
                    printf("VOTE CASTED ONCE. CANNOT BE CASTED FOR SECOND TIME\n");
                }
                else
                {
                    printf("NAME = %s\n", votr[index].name);
                    printf("CONFIRM WHETHER YOUR NAME IS CORRECT OR NOT(1 for YES/0 for NO) : ");
                    scanf("%d", &confirm);
                    if (confirm == 0)
                    {
                        printf("SORRY FOR THE INCONVINIENCE. PLEASE APPLY FOR NAME CORRECTION.\n");
                    }
                    else if (confirm == 1)
                    {
                        while (true)
                        {
                            candidateListDisplay();
                            printf("ENTER YOUR CHOICE : ");
                            scanf("%d", &choice);
                            if (choice < 1 || choice > (numberOfContestents + 1))
                            {
                                printf("YOU HAVE PRESSED INVALID BUTTON. PLEASE PRESS A VALID BUTTON.\n");
                                       //Sleep(5000);
    system("cls");
                                continue;
                            }
                            con[choice - 1].votes++;
                            votr[index].votes = true;
                            Sleep(3000);
    system("cls");
                            break;
                        }
                    }
                }
            }
            else
            {
                printf("INVALID SECUIRITY KEY.. PLEASE ENTER THE KEY AGAIN\n");
            }
        }
    }
    else if (conlist == false && votlist == false)
    {
        printf("VOTING CANNOT BE DONE AS CONTESTANT LIST AND VOTER LIST IS "
               "INCOMPLETE\n");
    }
    else if (conlist == false)
    {
        printf("VOTING CANNOT BE DONE AS CONTESTANT LIST IS INCOMPLETE\n");
    }
    else if (votlist == false)
    {
        printf("VOTING CANNOT BE DONE AS VOTER LIST IS INCOMPLETE\n");
    }
    return 0;
}
int main()
{
    printf("ELECTION COMMISION\n");
    printf("GOVERNMENT OF ELECTION\n");
    //   char password[128],c;
    //     int passi=0;
    int key = 1234;
    int ekey, choice;
    int track = 0;
    while (track < 3)
    {
        // passi=0;
        char password[128], c;
        int passi = 0;
        printf("Enter security key :");
        while ((c = getch()) != ENTER)
        {
            if (passi < 0)
            {
                passi = 0;
            }
            if (c == BACKSPACE)
            {
                putchar('\b');
                putchar('\0');
                putchar('\b');
                passi--;
                continue;
            }
            password[passi++] = c;
            putchar('*');
        }
        password[passi++] = '\0';
        // scanf("%d", &ekey);
        ekey = atoi(password);
        //printf("ENTERED PASSWORD = %d\n", ekey);
        if (ekey == key)
        {
            printf("\nLOGIN SUCCESSFUL\n");
            break;
        }
        else
        {
            printf("\nINCORRECT SECURITY KEY...ENTER AGAIN\n");
            track++;
        }
    }
    if (track == 3)
    {
        printf("\nSORRY YOU CANNOT ACCESS THE SYSTEM AS YOU HAVE ENTERED WRONG PASSWORD 3 TIMES");
        return 0;
    }

    while (true)
    {
        printf("MENU\n");
        printf("1. Admin\n");
        printf("2. Voting\n");
        printf("3. About\n");
        printf("4. EXIT\n");
        printf("ENTER YOUR CHOICE : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("cls");
            admin();
            break;
        case 2:
            system("cls");
            voting();
            break;
        case 3:
        	printf("THIS IS A EVM DEMO MACHINE. THIS IS A COLLEGE PROJECT. THIS SHALL BE USED ONLY FOR EDUCATIONAL PURPOSE.\nNOTE : THIS APP IS NEITHER MADE BY GOVERNMENT OF INDIA NOR DEVELOPED BY GOVERNMNET OF INDIA. THIS APP HAS NO RELATION WITH GOVERNMENT OF INDIA \nVERSION : 1.0 (STABLE)\nTHIS IS MADE BY IMON MALLIK\nCHECK OUT MY GITHUB PROFILE : https://github.com/CyberPokemon\n");
        	Sleep(15000);
    	system("cls");
			break;
        case 4:
            printf("THANK YOU FOR USING THIS SERVICE");
            sleep(5000);
            return 0;
        default:
            system("cls");
            printf("INVALID INPUT... PLEASE ENTER AGAIN\n");
        }
    }
}