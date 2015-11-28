/**
 *
 * simpon.c
 *
 * Simpon - A Simple Phonebook
 *      A demo program used for the CSc 101 Final Project
 *
 * Cyrus G. Gabilla
 *
 * Version  0.0.1 (Major.Minor.Revision)
 *  - First Release
 *
 * Version  0.0.2
 *  - Bug fixes
 *      - Initialized strings to empty value.
 *
 * Version  0.0.3
 * November 20, 2015
 *  - Observe standards for naming convention like, println (ln stands for a newline).
 *      Ex. println, a print having a newline
 *  - Remove unnecessary functions.
 *  - Add some UI improvements on the main menu.
 *
 *
 * Version 0.0.4
 * November 28, 2015
 *  - Modified to run in Windows without the header conio.h
 *  - Capitalize every first char of every name if has multiple words
 *  - Fixed empty input in last name.
 */

/*  December 12, conflict schedule
 *  // TODO Bug in displaying lastname if empty.
 *  // Capitalize every letter of the word in first name.
 */

#include <stdio.h>
#include <string.h>     /* provides strcpy(), strcat()  */
#include <ctype.h>      /* provides tolower(c), toupper(c)  */

/* #include <conio.h>      provides clrscr();   */
#include <stdlib.h>     /* system(cmd)          */

#define MAXSTR  20
#define MAXCHR  2
#define MAXENT  50

#define True    1
#define False   0

typedef int boolean;
/* boolean isEmpty = True; */
/* int isEmpty = 1; */

char EMPTY_STRING[]     = "";
char APP_TITLE[]        = "Simpon - Just a Simple Phonebook";
char* APP_TAGLINE[]     =  {
    "In Simpon . . .",
    ". . . We could always keep in touch with our LOVE ones."
};

#define MNULEN    7

#define MNUQUIT   'B'
#define MNUVIEW   'V'
#define MNUFIND   'F'
#define MNUMODI   'M'
#define MNUDELE   'D'
#define MNUADDE   'A'
#define MNUHACK   'H'

char* MENUS[] = {
    "[A]dd a Contact Entry",
    "[V]iew the Simpon Phonebook",
    "[F]ind a Contact",
    "[M]odify a Contact",
    "[D]elete a Contact",
    "Simpon [H]ack",
    "[B]ye for now"
};

/*** a phonebook entry */
typedef struct  aPhoneBookEntry {
    /* a fullname */
    char firstName[MAXSTR];
    char lastName[MAXSTR];
    char mInitial[MAXCHR];

    /* a mobile number */
    char mobileNumber[12];
} phoneBookEntry;

typedef struct aPhoneBook {
    int count;
    phoneBookEntry entry[MAXENT];

} phoneBook;

void deleteContactEntry(phoneBook*);
void displaySplashScreen(void);
void displayByeScreen(void);

void printlnProjectName(void);
void printlnInfoMessage(char* msg);
void pressAnyKeyToContinue(void);

void initPhoneBook(phoneBook* simpon);
void initPhoneBookEntry(phoneBookEntry* entry);

void scanPhoneBookEntry(phoneBookEntry* entry);
void printlnPhoneBookEntry(phoneBookEntry entry);
void printlnPhoneBook(phoneBook simpon);
void addEntryPhoneBook(phoneBookEntry entry, phoneBook* simpon);
void copyPhoneBookEntry (phoneBookEntry entrySource, phoneBookEntry* entryDest);
void addContactEntry(phoneBook* simpon);
void printlnPhoneBookMenu(void);
boolean hasEntrySlot(phoneBook simpon);
void hackSimpon(phoneBook* simpon);

/** Helper functions that will made easier to print a string on screen with or without newlines. */
void newline(void);
void nnewline(int n);
void print(char* str);
void println(char* str);

/** Will clear the console, depending on the system command. Use "cls" in Windows, otherwise "clear" for Linux */
void stdclrscr(void);

/**
 * strings related helper functions
 **/

void chrToStr(char aChar,
              char aStr[MAXCHR]);           /* char to string conversion */
void initString(char str[MAXSTR]);          /* string initializer */
void getline(char str[MAXSTR]);             /* input a string line with multiple words until the user presses the enter key. */

/** Formatting display in string */
void toUpperCase(char src[], char dst[]);
void toUpperCaseFirstOnly(char src[], char dst[]);
void toMobileNumberFormat(char src[], char dst[]);

/**
 * The main simpon program will starts here.
 */

int main(void)
{
    phoneBook simpon;
    char input = '\0';

    initPhoneBook(&simpon);
    displaySplashScreen();

    /** This is the other way of saying, int isPlaying = 1; */
    boolean isPlaying = True;

    while (isPlaying) {
        stdclrscr();
        printlnProjectName();
        nnewline(2);
        println("+--------------------------------------------------+");
        print("|"); printlnInfoMessage("The input is not case-sentitive.            |");
        print("|"); printlnInfoMessage("(e.g.: 'A' and 'a' is the same thing.)      |");
        print("|"); printlnInfoMessage("The boxed character is the user key input.  |");
        print("|"); printlnInfoMessage("(i.e.: [A]dd, 'A' is the user key input.)   |");
        println("+--------------------------------------------------+");
        newline();

        printlnPhoneBookMenu();
        nnewline(2);
        print("What would like to do? ");
        input = getchar();  /* scanf("%c", &input); */

        /* If the user will not input a value,
         * then bring the user to the main menu again. */
        if (input == '\n') {
            continue;
        }

        stdclrscr();

        /* char upperChar = toupper(input);
         * if (upperChar == MNUQUIT) {
         *      // do something
         * } else if (upperChar == MNUVIEW) {
         *      // do something
         * }    // ...
         * else {
         *      // do something
         * }
         *
         *
         */
        switch(toupper(input)) {
            case MNUQUIT:
            {
                isPlaying = False;
                displayByeScreen();
                break;
            }
            case MNUVIEW:
            {
                printlnPhoneBook(simpon);
                break;
            }
            case MNUMODI:
            {
                printf("TODO:  Modify...");

                break;
            }
            case MNUDELE:
            {
                /* deleteContactEntry(&simpon); */
                printf("TODO:  Delete...");

                break;
            }
            case MNUFIND:
            {
                printf("TODO:  Find...");

                break;
            }
            case MNUADDE:
            {
                addContactEntry(&simpon);
                break;
            }
            case MNUHACK:
            {
                hackSimpon(&simpon);
                break;
            }
            default:
            {
                char msg[MAXSTR];
                char chrStr[MAXCHR];

                /* initialize strings before using them */
                initString(msg);
                initString(chrStr);
                /*
                 * printf("INFO:    Unknown input => %c", input);
                 */
                strcat(msg, "Unknown input => ");
                chrToStr(input, chrStr);
                strcat(msg, chrStr);
                printlnInfoMessage(msg);

                break;
            }
        }
        newline();
        pressAnyKeyToContinue();

        getchar();
    }
    newline();
    return 0;
}

void deleteContactEntry(phoneBook* simpon) {
    /* input entry to be deleted */
    /* modify simpon */
}

void hackSimpon(phoneBook* simpon)
{
    char input;

    printlnInfoMessage("WARNING!!!");
    printlnInfoMessage("You are in HACK mode...");
    nnewline(3);

    do {
        newline();
        printf("Alter count (y/N)? ");
        /* input = getche();    */
        input = getchar();
        switch(toupper(input)) {

            case 'Y':
            {
                int count;

                printf("\nInput a new Simpon.count value=");
                scanf("%d", &count);
                simpon->count = count;
                break;
            }
        }

        if (toupper(input) == 'Y' || toupper(input) == 'N' || input == '\n')
            break;

    } while (toupper(input) != 'Y' || toupper(input) != 'N' || input != '\n' || input != EOF);
}

void stdclrscr(void)
{
    system("cls");  /* for Windows only */
    /* system("clear");   for Linux command only */
}
void chrToStr(char aChar, char aStr[2])
{
    aStr[0] = aChar;
    aStr[1] = '\0';
}

void initString(char str[MAXSTR])
{
    str[0] = '\0';
    strcpy(str, EMPTY_STRING);
}

void addContactEntry(phoneBook* simpon)
{
    phoneBookEntry entry;

    stdclrscr();
    scanPhoneBookEntry(&entry);
    addEntryPhoneBook(entry, simpon);
}

/**
 * The following will be initialized:
 *  - count, make it zero
 *  - entries, make every entry member fields to empty string
 */
void initPhoneBook(phoneBook* simpon)
{
    int i;

    for (i = 0; i < MAXENT; i++) {
        initPhoneBookEntry(simpon->entry);
    }

    simpon->count = 0;
}

void initPhoneBookEntry(phoneBookEntry* entry)
{
    initString(entry->firstName);
    initString(entry->lastName);
    initString(entry->mInitial);
    initString(entry->mobileNumber);
}

/**
 * char name[20] = "";
 * char first[] = "Cyrus";
 * char last[] = "Gabilla';
 *
 * //
 * // append to add after   => str + value  => str value
 * // prepend to add before => value + str  => value str
 * strcat(name, first);
 * strcat(name, " ");
 * strcat(name, last);
 * printf(name); => "Cyrus Gabilla"
 *
 * strcpy(name, "Cyrus G. Gabilla");
 *
 *
 * strlen(name); => 16
 */

void insertStrToStringAfterFirstSpace(char strToInsert[], char inStr[], int maxLen)
{
    int i, j;
    for (i = 0; i < strlen(inStr); i++)
        if (inStr[i] == ' ')
            break;
    j = ++i;
    i = maxLen;
    for (; j < strlen(strToInsert) && j < i; j++)
        inStr[j] = strToInsert[i];
}


void addEntryPhoneBook(phoneBookEntry entry, phoneBook* simpon)
{
    stdclrscr();
    printf("Adding a new Contact Entry for Entry Slot #%d", (simpon->count + 1));
    newline();
    printlnPhoneBookEntry(entry);
    newline();
    if (hasEntrySlot(*simpon)) {
        char msg[MAXSTR];
        char intStr[MAXSTR];

        /* initialize strings before using them */
        initString(msg);
        initString(intStr);

        copyPhoneBookEntry (entry, &simpon->entry[simpon->count++]);
        strcat(msg, "Added Contact Entry Slot #");
        itoa(simpon->count, intStr, 10);
        strcat(msg, intStr);

        printlnInfoMessage(msg);
    } else {
        printlnInfoMessage("[simpon] is FULL . . .");
        printlnInfoMessage("Cannot add a new Contact Entry . . .");
    }
}

void copyPhoneBookEntry (phoneBookEntry entrySource, phoneBookEntry* entryDest)
{
    /**
     * # Common string function
     *      Copy the source value to dest. dest is the LHS value, and source is the RHS value: LHS = RHS
     *
     *      strcpy(dest, source)
     *
     * # Usage
     * char name[20];
     *
     * strcpy(name, "Cyrus");
     */
    /* copy fullname */
    strcpy(entryDest->firstName, entrySource.firstName);
    strcpy(entryDest->lastName, entrySource.lastName);
    strcpy(entryDest->mInitial, entrySource.mInitial);

    strcpy(entryDest->mobileNumber, entrySource.mobileNumber);
}

void printlnInfoMessage(char* msg)
{
    printf("INFO: %s\n", msg);
}

boolean hasEntrySlot(phoneBook simpon)
{
    return (simpon.count < MAXENT);
}

void printlnPhoneBook(phoneBook simpon)
{
    int i;
    stdclrscr();
    printf("Simpon Entries");
    newline();
    for (i = 0; i < simpon.count; i++) {
        printf("#%d - ", (i+1));
        printlnPhoneBookEntry(simpon.entry[i]);
        newline();
    }
}

void displayByeScreen(void)
{
    stdclrscr();
    printf(APP_TAGLINE[0]);
    newline();
    putchar('\t');
    printf(APP_TAGLINE[1]);
}

void pressAnyKeyToContinue()
{
    printf("Press any key to continue . . .");
    /* getch(); */
    getchar();
}

void printlnProjectName(void)
{
    print("[[");
    print(APP_TITLE);
    println("]]");

}

void displaySplashScreen(void)
{
    /* printf("%s", APP_TITLE); */
    stdclrscr();
    printlnProjectName();
    pressAnyKeyToContinue();
}

/**
 * improved reading a string with set of words
 *
 */


void scanPhoneBookEntry(phoneBookEntry* entry)
{
    printlnInfoMessage("Please input valid values to avoid errors.");
    printlnInfoMessage("An enter key is considered as a blank input.");

    println("[FULL NAME ENTRY]");
    printf("Firstname>>      ");
    getline(entry->firstName);
    printf("Lastname>>       ");
    getline(entry->lastName);
    printf("Middle Initial>> ");
    getline(entry->mInitial);
    println("\n[CONTACT NUMBER]");
    printlnInfoMessage("Format: DDDDDDDDDDD");
    printlnInfoMessage("Invalid input characters are non-digit value.");
    printlnInfoMessage("It will be marked as 'X' when displaying a phoneBookEntry.");
    printf("Personal No.>>   ");
    getline(entry->mobileNumber);
    pressAnyKeyToContinue();
}

/**
 * An example of input, considering an enter is is valid and empty string.
 */
void getline(char str[MAXSTR])
{
    initString(str);

    /* flush the buffer to get an empty buffer to avoid error. */
    fflush(stdin);
    fgets(str, MAXSTR, stdin);
    str[strlen(str)-1] = '\0';
}

void printlnPhoneBookEntry(phoneBookEntry entry)
{
    char tFirst[MAXSTR], tLast[MAXSTR], tMi[MAXCHR];
    char tMobile[14];

    toUpperCase(entry.lastName, tLast);
    toUpperCaseFirstOnly(entry.firstName, tFirst);
    toUpperCase(entry.mInitial, tMi);

    toMobileNumberFormat(entry.mobileNumber, tMobile);

    fflush(stdout);
    printf("[[Contact for %s]]\n", entry.firstName);
    printf("%s, %s, %s.\n", tLast, tFirst, tMi);
    printf("%s", tMobile);
    newline();
}

void toUpperCase(char src[MAXSTR], char dst[MAXSTR]) {
    int len = strlen(src);
    int i;

    initString(dst);
    if (len <= 0) {
        strcpy(dst, "<empty>");
    } else {
        for (i = 0; i < len; i++)
            dst[i] = toupper(src[i]);
        dst[i] = '\0';
    }
}

void toUpperCaseFirstOnly(char src[MAXSTR], char dst[MAXSTR]) {
    int len = strlen(src);
    int i;

    initString(dst);

    if (len <= 0) {
        strcpy(dst, "<empty>");
    } else {
        if (len <= 1) {
            dst[0] = toupper(src[0]);
            dst[1] = '\0';
        }
        else {
            boolean isBeforeSpace = False;
            dst[0] = toupper(src[0]);
            for (i = 1; i < len; i++) {
                if (isBeforeSpace) {
                    dst[i] = toupper(src[i]);
                    isBeforeSpace = False;
                }
                else
                    dst[i] = tolower(src[i]);

                if (isspace(src[i]))
                    isBeforeSpace = True;
            }
            dst[i] = '\0';
        }
    }
}

/**
 * Will replace invalid value as X
 */
void toMobileNumberFormat(char src[12], char dst[14])
{
    int i, j;

    if (strlen(src) == 0) {
        strcpy(dst, "<empty>");
        return;
    }

    initString(dst);
    /* dddd-ddd-dddd */
    for (i = 0, j = 0; i < 4; i++)
        dst[j++] = src[i] == ' ' ? '0' : src[i];
    dst[j++] = '-';
    for (i = 0; i < 3; i++) {
        switch (src[i+4]) {
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9': {
                dst[j++] = src[i+4];
                break;
            }
            default: {
                dst[j++] = 'X';
                break;
            }
        }
    }
    dst[j++] = '-';
    for (i = 0 ; i < 4; i++)
        switch (src[i+7]) {
            case '0': case '1': case '2':
            case '3': case '4': case '5':
            case '6': case '7': case '8':
            case '9': {
                dst[j++] = src[i+7];
                break;
            }
            default: {
                dst[j++] = 'X';
                break;
            }
        }
    dst[j] = '\0';
}

void newline(void)
{
    putchar('\n');
}

void nnewline(int n)
{
    int i;
    for (i = 0; i < n; i++)
        newline();
}

void println(char* str)
{
    printf(str);
    newline();
}

void print(char* str)
{
    printf(str);
}

void printlnPhoneBookMenu(void)
{
    int i;
    for (i = 0; i < MNULEN; i++)
        println(MENUS[i]);
}
