#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>

int getkey();
void display(int, int, int, int[]);
void calendar(int, int);
void displayAllMonths(int);

// GOTO function definition
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
// Change text color
void SetColor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

char *month[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
char *week[] = {"Mon","Tue","Wed","Thu","Fri","Sat","Sun"};

int main()
{
    int nmonth, nyr, ch;
    enteryear:
    while(1)
    {
        printf("Enter year and month(number): ");
        scanf("%d%d", &nyr, &nmonth);

        if(nyr < 1945)
        {
            printf("\n\t Please enter year above 1945\n");
            continue;
        }
        else
        {
            calendar(nyr, nmonth);
        }

        while(1)
        {
            gotoxy(20,20); printf("(*) Use LEFT, RIGHT, UP and DOWN arrow.");
            gotoxy(20,22); printf("(*) Press P to go to particular year and month.");
            gotoxy(20,24); printf("(*) Press A to display all months of year.");
            gotoxy(20,26); printf("(*) Press ESC to Exit.");

            ch = getkey();

            switch(ch)
            {
                case 80: // DOWN arrow (next month)
                    if(nmonth == 12) {
                        nmonth = 1;
                        nyr++;
                    } else {
                        nmonth++;
                    }
                    calendar(nyr, nmonth);
                    break;

                case 77: // RIGHT arrow (next year)
                    nyr++;
                    calendar(nyr, nmonth);
                    break;

                case 72: // UP arrow (previous month)
                    if(nmonth == 1) {
                        nyr--;
                        nmonth = 12;
                    } else {
                        nmonth--;
                    }
                    calendar(nyr, nmonth);
                    break;

                case 75: // LEFT arrow (previous year)
                    if(nyr == 1945) {
                        gotoxy(15,2); printf("Year below 1945 not available");
                    } else {
                        nyr--;
                        calendar(nyr, nmonth);
                    }
                    break;

                case 'a':
                    displayAllMonths(nyr);
                    calendar(nyr, nmonth);
                    break;

                case 'p':
                    system("cls");
                    goto enteryear;
                    break;

                case 27: // ESC
                    system("cls");
                    gotoxy(50,14); printf("Exiting program.\n\n\n\n\n");
                    exit(0);
            }
        }
        break;
    }
    getch();
    return 0;
}

void display(int nyr, int nmonth, int tdays, int days[])
{
    int i, j, pos;
    SetColor(12); // Red
    gotoxy(56,6); printf("%s %d", month[nmonth-1], nyr);

    for(i = 0, pos = 30; i < 7; i++, pos += 10)
    {
        if(i == 6)
            SetColor(9); // Sunday (blue)
        else
            SetColor(10); // Weekdays (green)

        gotoxy(pos,8); printf("%s", week[i]);
    }

    SetColor(15); // White

    tdays++;
    switch(tdays % 7)
    {
        case 0: pos = 91; break;
        case 1: pos = 31; break;
        case 2: pos = 41; break;
        case 3: pos = 51; break;
        case 4: pos = 61; break;
        case 5: pos = 71; break;
        case 6: pos = 81; break;
    }

    for(i = 0, j = 10; i < days[nmonth-1]; i++, pos += 10)
    {
        if(pos == 91)
            SetColor(8); // Sunday (gray)
        else
            SetColor(7); // Weekdays (white)

        gotoxy(pos, j); printf("%d", i + 1);

        if(pos == 91)
        {
            pos = 21;
            j++;
        }
    }

    SetColor(5); // Purple
    for(i = 22; i < 102; i++)
    {
        gotoxy(i,4); printf("%c",196);
        gotoxy(i,17); printf("%c",196);
    }

    gotoxy(21,4); printf("%c",218);
    gotoxy(102,4); printf("%c",191);
    gotoxy(21,17); printf("%c",192);
    gotoxy(102,17); printf("%c",217);

    for(i = 5; i < 17; i++)
    {
        gotoxy(21,i); printf("%c",179);
        gotoxy(102,i); printf("%c",179);
    }

    SetColor(11);
    gotoxy(24,11); printf("%c",174); // left arrow
    gotoxy(98,11); printf("%c",175); // right arrow
}

int getkey()
{
    int ch = getch();
    if(ch == 0 || ch == 224)
    {
        return getch();
    }
    return ch;
}

void calendar(int nyr, int nmonth)
{
    int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int tdays = 0, k, myear;
    system("cls");

    myear = nyr - 1;
    if(myear >= 1945)
    {
        for(k = 1945; k <= myear; k++)
        {
            if(k % 4 == 0)
                tdays += 366;
            else
                tdays += 365;
        }
    }

    if(nyr % 4 == 0)
        days[1] = 29;
    else
        days[1] = 28;

    for(k = 0; k < (nmonth - 1); k++)
    {
        tdays += days[k];
    }

    tdays = tdays % 7;
    display(nyr, nmonth, tdays, days);
}

void displayAllMonths(int year) 
{
    int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if(year % 4 == 0)
        days[1] = 29;

    int startDay = 0, i, j, k;
    system("cls");

    gotoxy(25, 2); SetColor(14); printf("Calendar for %d", year); // Further adjusted title
    SetColor(15);

    for(i = 0; i < 12; i++) 
    {
        int row = (i / 3) * 7 + 4; // Adjusted row spacing
        int col = (i % 3) * 32 + 5; // Further adjusted column spacing

        gotoxy(col + 7, row); SetColor(12); printf("%s %d", month[i], year); // Adjusted month title

        for(k = 0; k < 7; k++) 
        {
            gotoxy(col + k * 4, row + 1);
            if (k == 6) SetColor(9);
            else SetColor(10);
            printf("%s", week[k]);
        }

        SetColor(7);
        int offset;
        switch ((startDay + 1) % 7) 
        {
            case 0: offset = 6; break;
            default: offset = (startDay + 1) % 7 - 1; break;
        }

        int day = 1;
        for (j = 0; j < 6 && day <= days[i]; j++) {
            for (k = 0; k < 7 && day <= days[i]; k++) {
                if (j == 0 && k < offset) continue;
                gotoxy(col + k * 4, row + 2 + j);
                if (k == 6) SetColor(8);
                else SetColor(7);
                printf("%2d", day++);
            }
        }
        startDay += days[i];
    }

    SetColor(11);
    gotoxy(30, 38); printf("Press any key to return..."); // Adjusted "press any key" position
    getch();
    system("cls");
}