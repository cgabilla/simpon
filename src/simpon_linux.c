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
 *
 *
 */

#include <stdio.h>
#include <string.h>     /* provides strcpy(), strcat()  */
#include <ctype.h>      /* provides tolower(c), toupper(c)  */

/* #include <conio.h>       provides clrscr();   */
#include <stdlib.h>     /* system(cmd)          */


#define MAXSTR  20
#define MAXCHR  2
#define MAXENT  50

#define True    1
#define False   0

typedef int boolean;
/* boolean isEmpty = True; */
/* int isEmpty = 1; */


char* APP_TITLE
    = "Simpon - Just a Simple Phonebook";
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

void pressAnyKeyToContinue(void);
void printSplashScreen(void);
void printByeMessage(void);
void printInfoMessage(char* msg);

void scanPhoneBookEntry(phoneBookEntry* entry);
void printPhoneBookEntry(phoneBookEntry entry);
void printPhoneBook(phoneBook simpon);
void addEntryPhoneBook(phoneBookEntry entry, phoneBook* simpon);
void initPhoneBook(phoneBook* simpon);
void copyPhoneBookEntry (phoneBookEntry entrySource, phoneBookEntry* entryDest);
void addContactEntry(phoneBook* simpon);
void printPhoneBookMenu(void);
boolean hasEntrySlot(phoneBook simpon);
void hackSimpon(phoneBook* simpon);

int mainSample(void);
int mainT(void);


void newline(void);
void nnewline(int n);
void println(char* str);
void makeStr(char aChar, char aStr[2]);
void stdclrscr(void);

int mainT(void)
{
    mainSample();
    return 0;
}

int main(void)
{
    phoneBook simpon;
    int input;
    boolean isPlaying = True;

    initPhoneBook(&simpon);
    while (isPlaying) {
        stdclrscr();
        printPhoneBookMenu();
	printf("What would like to do? ");
        input = getchar();
	getchar();
        stdclrscr();
        switch(toupper(input)) {
            case MNUQUIT:
            {
                isPlaying = False;
                printByeMessage();
                break;
            }
            case MNUVIEW:
            {
                printPhoneBook(simpon);
                break;
            }
            case MNUMODI:
            {
                printf("TODO:  Modify...");

                break;
            }
            case MNUDELE:
            {
                printf("Delete...");

                break;
            }
            case MNUFIND:
            {
                printf("Find...");

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

                strcat(msg, "Unknown input => ");
                makeStr(input, chrStr);
                strcat(msg, chrStr);
                printInfoMessage(msg);

                break;
            }
        }
        pressAnyKeyToContinue();

    }
    newline();
    return 0;
}

void hackSimpon(phoneBook* simpon)
{
    char input;

    printInfoMessage("WARNING!!!");
    printInfoMessage("You are in HACK mode...");
    nnewline(3);

    do {
        printf("Alter Simpon.count (Y/N)? ");
        input = getchar();
	getchar();
        switch(input) {

            case 'y': case 'Y': case '\n':
            {
                int count;

                printf("\nInput a new Simpon.count value=");
                scanf("%d", &count);
                simpon->count = count;
                break;
            }
        }

        if (toupper(input) == 'Y' || toupper(input) == 'N')
            break;

    } while (toupper(input) != 'Y' || toupper(input) != 'N' || input != '\n' || input != EOF);
}

void stdclrscr(void)
{
    /* system("cls");   for Windows only */
    system("clear");   /* for Linux command only */
}

void makeStr(char aChar, char aStr[2])
{
    aStr[0] = aChar;
    aStr[1] = '\0';
}

void addContactEntry(phoneBook* simpon)
{
    phoneBookEntry entry;

    scanPhoneBookEntry(&entry);
    addEntryPhoneBook(entry, simpon);
}

int mainSample(void)
{
    phoneBook simpon;
    phoneBookEntry entry;

    initPhoneBook(&simpon);

    stdclrscr();
    printSplashScreen();
    pressAnyKeyToContinue();

    stdclrscr();
    scanPhoneBookEntry(&entry);
    addEntryPhoneBook(entry, &simpon);

    pressAnyKeyToContinue();
    stdclrscr();
    /* printPhoneBookEntry(entry); */
    printPhoneBook(simpon);

    scanPhoneBookEntry(&entry);
    addEntryPhoneBook(entry, &simpon);
    pressAnyKeyToContinue();
    stdclrscr();

    printPhoneBook(simpon);

    pressAnyKeyToContinue();
    stdclrscr();
    printByeMessage();

    newline();
    return 0;
}

void initPhoneBook(phoneBook* simpon)
{
    simpon->count = 0;
}

void addEntryPhoneBook(phoneBookEntry entry, phoneBook* simpon)
{
    stdclrscr();
    printf("Adding a new Contact Entry for Entry Slot #%d", (simpon->count + 1));
    newline();
    printPhoneBookEntry(entry);
    newline();
    if (hasEntrySlot(*simpon)) {
        char msg[MAXSTR] = "";
        char intStr[MAXSTR] = "";

        copyPhoneBookEntry (entry, &simpon->entry[simpon->count++]);
        strcat(msg, "Added Contact Entry Slot #");
        snprintf (intStr, sizeof(intStr), "%d", simpon->count);
        /* itoa(simpon->count, intStr, 10); */
        strcat(msg, intStr);

        printInfoMessage(msg);
    } else {
        printInfoMessage("[simpon] is FULL . . .");
        printInfoMessage("Cannot add a new Contact Entry . . .");
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

void printInfoMessage(char* msg)
{
    printf("INFO: %s\n", msg);
}

boolean hasEntrySlot(phoneBook simpon)
{
    return (simpon.count < MAXENT);
}

void printPhoneBook(phoneBook simpon)
{
    int i;
    stdclrscr();
    printf("Simpon Entries");
    newline();
    for (i = 0; i < simpon.count; i++) {
        printf("#%d - ", (i+1));
        printPhoneBookEntry(simpon.entry[i]);
        newline();
    }
}

void printByeMessage(void)
{
    printf("%s", APP_TAGLINE[0]);
    newline();
    putchar('\t');
    printf("%s", APP_TAGLINE[1]);
}

void pressAnyKeyToContinue()
{
    nnewline(3);
    printf("Press any key to continue . . .");
    getchar();
}

void printSplashScreen()
{
    printf("%s", APP_TITLE);
}

void scanPhoneBookEntry(phoneBookEntry* entry)
{
    printf("firstName=");
    scanf("%s", entry->firstName);
    printf("lastName=");
    scanf("%s", entry->lastName);
    printf("middleName=");
    scanf("%s", entry->mInitial);
    printf("mobileNumber=");
    scanf("%s", entry->mobileNumber);
}

void printPhoneBookEntry(phoneBookEntry entry)
{
    printf("{\n\tfirstName: %s\n", entry.firstName);
    printf("\tlastName: %s\n", entry.lastName);
    printf("\tmiddleName: %s\n", entry.mInitial);
    printf("\tmobileNumber: %s\n}", entry.mobileNumber);
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

void println(char str[MAXSTR])
{
    printf("%s", str);
    newline();
}

void printPhoneBookMenu(void)
{
    int i;
    for (i = 0; i < MNULEN; i++)
        println(MENUS[i]);
}
