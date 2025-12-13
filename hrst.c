#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// ----- CONSTANTS -----
#define MAX_NAME_LEN 50
#define MAX_PROFILES 100
#define MAX_LINE 256
#define MAX_ROUNDS 20
#define MAX_HISTORY 200
#define MAX_MOVE_LEN 5

#define PROFILE_FILE "profiles.dat"
#define HIGHSCORE_FILE "highscores.txt"
#define STATS_FILE "gamestats.txt"

// ----- STRUCTS -----

typedef struct {
    char name[MAX_NAME_LEN];
    int gamesPlayed;
    int wins;
    int losses;
} Profile;

typedef struct {
    char playerName[MAX_NAME_LEN];
    int roundsPlayed;
    int wins;
    int losses;
    char movesHistory[MAX_HISTORY][MAX_MOVE_LEN];      // player moves
    char compMovesHistory[MAX_HISTORY][MAX_MOVE_LEN];  // computer moves
} GameSession;

// ----- FUNCTION PROTOTYPES -----

// Input and output
int readLine(char *buffer, int length);
int getIntInRange(const char *prompt, int min, int max);
int confirmYesNo(const char *prompt);
void toUpperStr(char *str);
void pauseProgram();
void printHeader(const char *title);
void printFooter();
void printDivider();
void printEmptyLines(int count);

// Profile management
int loadProfiles(Profile profiles[], int maxProfiles);
int saveProfiles(Profile profiles[], int count);
int findProfileIndex(Profile profiles[], int count, const char *name);
void addNewProfile(Profile profiles[], int *count);
void renameProfile(Profile profiles[], int count);
void deleteProfile(Profile profiles[], int *count);
void showProfiles(Profile profiles[], int count);
void viewProfileDetails(Profile *p);
void updateProfileStats(Profile *p, GameSession *session);

// Game logic
void playGame(Profile profiles[], int profCount);
int isValidBasicMove(const char *move);
int isValidAdvancedMove(const char *move);
int isValidMove(const char *move, int mode);
const char *mapAdvancedMove(const char *input);
const char *computerMove(int mode);
void printRoundResult(const char *playerMove, const char *compMove, int *win, int *loss);

// Scoreboard
void saveScoreToFile(GameSession *session);
void displayScoreboard();

// Stats Logging
void saveGameStats(GameSession *session, int mode);
void viewGameStats();

// Menu and interface
void mainMenu(Profile profiles[], int *profCount);
void profilesMenu(Profile profiles[], int *profCount);
void gameMenu(Profile profiles[], int profCount);
void scoreboardMenu();
void statsMenu();
void instructionsMenu();

// Helper for long line printing and delays
void waitSeconds(int seconds);


// ----- MAIN FUNCTION -----
int main() {
    srand((unsigned int)time(NULL)); // Seed for random

    Profile profiles[MAX_PROFILES];
    int profileCount = 0;

    profileCount = loadProfiles(profiles, MAX_PROFILES);

    printHeader("Welcome to Cham Cham Cham!");

    mainMenu(profiles, &profileCount);

    return 0;
}


// INPUT / OUTPUT HELPERS

int readLine(char *buffer, int length) {
    if (fgets(buffer, length, stdin)) {
        buffer[strcspn(buffer, "\n")] = '\0'; // strip newline
        return 1;
    }
    return 0;
}

int getIntInRange(const char *prompt, int min, int max) {
    char line[MAX_LINE];
    int value;
    while (1) {
        printf("%s", prompt);
        if (!readLine(line, MAX_LINE)) {
            printf("Error reading input, please try again.\n");
            continue;
        }
        if (sscanf(line, "%d", &value) != 1) {
            printf("Invalid number, please enter a valid integer.\n");
            continue;
        }
        if (value < min || value > max) {
            printf("Please enter a number between %d and %d.\n", min, max);
            continue;
        }
        return value;
    }
}

int confirmYesNo(const char *prompt) {
    char line[MAX_LINE];
    while (1) {
        printf("%s (y/n): ", prompt);
        if (!readLine(line, MAX_LINE)) continue;
        if (strlen(line) == 0) continue;
        char c = (char)tolower(line[0]);
        if (c == 'y') return 1;
        if (c == 'n') return 0;
        printf("Please answer 'y' or 'n'.\n");
    }
}

void toUpperStr(char *str) {
    for (; *str; str++) {
        *str = (char)toupper(*str);
    }
}

void pauseProgram() {
    printf("Press Enter to continue...");
    fflush(stdout);
    char temp[16];
    fgets(temp, sizeof(temp), stdin);
}

void printHeader(const char *title) {
    printDivider();
    printf("  %s\n", title);
    printDivider();
}

void printFooter() {
    printDivider();
}

void printDivider() {
    printf("----------------------------------------\n");
}

void printEmptyLines(int count) {
    for (int i = 0; i < count; i++) {
        printf("\n");
    }
}


// PROFILE MANAGEMENT

int loadProfiles(Profile profiles[], int maxProfiles) {
    FILE *fp = fopen(PROFILE_FILE, "rb");
    if (!fp) return 0; // no file yet

    int count = 0;
    while (count < maxProfiles && fread(&profiles[count], sizeof(Profile), 1, fp) == 1) {
        count++;
    }
    fclose(fp);
    return count;
}

int saveProfiles(Profile profiles[], int count) {
    FILE *fp = fopen(PROFILE_FILE, "wb");
    if (!fp) {
        printf("Error: Could not save profiles.\n");
        return 0;
    }
    fwrite(profiles, sizeof(Profile), count, fp);
    fclose(fp);
    return 1;
}

int findProfileIndex(Profile profiles[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(profiles[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void addNewProfile(Profile profiles[], int *count) {
    if (*count >= MAX_PROFILES) {
        printf("Profile limit reached, cannot add more.\n");
        pauseProgram();
        return;
    }
    char name[MAX_NAME_LEN];
    printf("Enter new player name: ");
    if (!readLine(name, MAX_NAME_LEN)) {
        printf("Input error.\n");
        pauseProgram();
        return;
    }
    if (strlen(name) == 0) {
        printf("Name cannot be empty.\n");
        pauseProgram();
        return;
    }
    if (findProfileIndex(profiles, *count, name) != -1) {
        printf("Profile with this name already exists.\n");
        pauseProgram();
        return;
    }
    Profile newProfile = {0};
    strncpy(newProfile.name, name, MAX_NAME_LEN - 1);
    newProfile.gamesPlayed = 0;
    newProfile.wins = 0;
    newProfile.losses = 0;

    profiles[*count] = newProfile;
    (*count)++;

    if (!saveProfiles(profiles, *count)) {
        printf("Failed to save profiles.\n");
    } else {
        printf("Profile '%s' added successfully.\n", name);
    }
    pauseProgram();
}

void renameProfile(Profile profiles[], int count) {
    if (count == 0) {
        printf("No profiles available.\n");
        pauseProgram();
        return;
    }
    showProfiles(profiles, count);
    int choice = getIntInRange("Select profile number to rename: ", 1, count);
    int idx = choice - 1;
    printf("Current name: %s\n", profiles[idx].name);
    printf("Enter new name: ");
    char newName[MAX_NAME_LEN];
    if (!readLine(newName, MAX_NAME_LEN)) {
        printf("Input error.\n");
        pauseProgram();
        return;
    }
    if (strlen(newName) == 0) {
        printf("Name cannot be empty.\n");
        pauseProgram();
        return;
    }
    if (findProfileIndex(profiles, count, newName) != -1) {
        printf("Another profile with this name exists.\n");
        pauseProgram();
        return;
    }
    strncpy(profiles[idx].name, newName, MAX_NAME_LEN - 1);

    if (!saveProfiles(profiles, count)) {
        printf("Failed to save profiles.\n");
    } else {
        printf("Profile renamed successfully.\n");
    }
    pauseProgram();
}

void deleteProfile(Profile profiles[], int *count) {
    if (*count == 0) {
        printf("No profiles to delete.\n");
        pauseProgram();
        return;
    }
    showProfiles(profiles, *count);
    int choice = getIntInRange("Select profile number to delete: ", 1, *count);
    int idx = choice - 1;
    printf("Are you sure you want to delete '%s'? This cannot be undone.\n", profiles[idx].name);
    if (confirmYesNo("Confirm deletion")) {
        // Shift profiles down
        for (int i = idx; i < (*count) - 1; i++) {
            profiles[i] = profiles[i + 1];
        }
        (*count)--;
        if (!saveProfiles(profiles, *count)) {
            printf("Failed to save profiles.\n");
        } else {
            printf("Profile deleted.\n");
        }
    } else {
        printf("Deletion canceled.\n");
    }
    pauseProgram();
}

void showProfiles(Profile profiles[], int count) {
    if (count == 0) {
        printf("No profiles available.\n");
        return;
    }
    printHeader("Player Profiles");
    for (int i = 0; i < count; i++) {
        printf("%d) %s  | Games Played: %d  Wins: %d  Losses: %d\n",
               i + 1,
               profiles[i].name,
               profiles[i].gamesPlayed,
               profiles[i].wins,
               profiles[i].losses);
    }
    printFooter();
}

void viewProfileDetails(Profile *p) {
    if (!p) return;
    printHeader("Profile Details");
    printf("Name        : %s\n", p->name);
    printf("Games Played: %d\n", p->gamesPlayed);
    printf("Wins        : %d\n", p->wins);
    printf("Losses      : %d\n", p->losses);
    printFooter();
    pauseProgram();
}

void updateProfileStats(Profile *p, GameSession *session) {
    if (!p || !session) return;
    p->gamesPlayed += session->roundsPlayed;
    p->wins += session->wins;
    p->losses += session->losses;
}

// GAME LOGIC

int isValidBasicMove(const char *move) {
    if (!move || strlen(move) != 1) return 0;
    char c = (char)toupper(move[0]);
    return (c == 'L' || c == 'R' || c == 'U' || c == 'D');
}

int isValidAdvancedMove(const char *move) {
    if (!move || strlen(move) != 1) return 0;
    char c = (char)toupper(move[0]);
    return (c == 'A' || c == 'B' || c == 'C' || c == 'E');
}

int isValidMove(const char *move, int mode) {
    if (mode == 1) {
        return isValidBasicMove(move);
    } else if (mode == 2) {
        if (isValidAdvancedMove(move)) return 1;
        if (strlen(move) == 2) {
            char tmp[3];
            strncpy(tmp, move, 2);
            tmp[2] = '\0';
            toUpperStr(tmp);
            return (strcmp(tmp, "LU") == 0 || strcmp(tmp, "LD") == 0 || strcmp(tmp, "RU") == 0 || strcmp(tmp, "RD") == 0);
        }
    }
    return 0;
}

const char *mapAdvancedMove(const char *input) {
    static char move[3];
    if (!input) return NULL;
    char c = (char)toupper(input[0]);
    switch (c) {
        case 'A': strcpy(move, "LU"); break;
        case 'B': strcpy(move, "LD"); break;
        case 'C': strcpy(move, "RU"); break;
        case 'E': strcpy(move, "RD"); break;
        default: return NULL;
    }
    return move;
}

const char *computerMove(int mode) {
    static const char *basicMoves[4] = {"L", "R", "U", "D"};
    static const char *advMoves[4] = {"LU", "LD", "RU", "RD"};
    int choice = rand() % 4;
    if (mode == 1) {
        return basicMoves[choice];
    } else {
        return advMoves[choice];
    }
}

void printRoundResult(const char *playerMove, const char *compMove, int *win, int *loss) {
    if (strcmp(playerMove, compMove) == 0) {
        printf("You LOSE this round!\n");
        (*loss)++;
    } else {
        printf("You WIN this round!\n");
        (*win)++;
    }
}

void playGame(Profile profiles[], int profCount) {
    if (profCount == 0) {
        printf("No profiles available. Please add one first.\n");
        pauseProgram();
        return;
    }
    showProfiles(profiles, profCount);
    int idx = getIntInRange("Select your profile number: ", 1, profCount) - 1;

    Profile *playerProfile = &profiles[idx];

    printf("Welcome %s!\n", playerProfile->name);

    int mode = 1;
    if (confirmYesNo("Use Advanced mode (A/B/C/E)?")) {
        mode = 2;
    }

    int rounds = getIntInRange("Enter number of rounds (1-20): ", 1, MAX_ROUNDS);

    GameSession session = {0};
    strncpy(session.playerName, playerProfile->name, MAX_NAME_LEN - 1);
    session.roundsPlayed = rounds;
    session.wins = 0;
    session.losses = 0;

    printEmptyLines(1);

    for (int r = 0; r < rounds; r++) {
        printf("Round %d\n", r + 1);

        char input[MAX_MOVE_LEN];
        while (1) {
            if (mode == 1) {
                printf("Enter your move (L,R,U,D): ");
            } else {
                printf("Enter your move (A=LU, B=LD, C=RU, E=RD or full LU/LD/RU/RD): ");
            }
            if (!readLine(input, MAX_MOVE_LEN)) {
                printf("Input error, try again.\n");
                continue;
            }
            if (!isValidMove(input, mode)) {
                printf("Invalid move, please try again.\n");
                continue;
            }
            break;
        }

        char playerMove[MAX_MOVE_LEN] = {0};
        if (mode == 1) {
            playerMove[0] = (char)toupper(input[0]);
            playerMove[1] = '\0';
        } else {
            if (isValidAdvancedMove(input)) {
                const char *mapped = mapAdvancedMove(input);
                if (mapped) {
                    strncpy(playerMove, mapped, MAX_MOVE_LEN - 1);
                }
            } else {
                strncpy(playerMove, input, MAX_MOVE_LEN - 1);
                toUpperStr(playerMove);
            }
        }

        const char *compMove = computerMove(mode);

        printf("Computer chose: %s\n", compMove);

        strncpy(session.movesHistory[r], playerMove, MAX_MOVE_LEN - 1);
        strncpy(session.compMovesHistory[r], compMove, MAX_MOVE_LEN - 1);

        printRoundResult(playerMove, compMove, &session.wins, &session.losses);

        printEmptyLines(1);
    }

    printDivider();
    printf("Game over! %s's Results:\n", session.playerName);
    printf("Rounds Played: %d\n", session.roundsPlayed);
    printf("Wins: %d\n", session.wins);
    printf("Losses: %d\n", session.losses);
    printDivider();

    if (session.wins > session.losses) {
    printf("You won the game! Congratulations!\n");
    saveScoreToFile(&session);
    } else if (session.wins < session.losses) {
        printf("You lost the game. Better luck next time!\n");
    } else {
        printf("The game was a draw!\n");
    }

    updateProfileStats(playerProfile, &session);
    saveProfiles(profiles, profCount);
    saveGameStats(&session, mode);

    pauseProgram();
}

// SCOREBOARD

void saveScoreToFile(GameSession *session) {
    FILE *fp = fopen(HIGHSCORE_FILE, "a");
    if (!fp) {
        printf("Error saving score.\n");
        return;
    }
    fprintf(fp, "%s %d %d %d\n", session->playerName, session->roundsPlayed, session->wins, session->losses);
    fclose(fp);
}

// Global ScoreEntry struct so comparator can see it
typedef struct {
    char name[MAX_NAME_LEN];
    int gamesPlayed;
    int wins;
    int losses;
} ScoreEntry;

/* FIXED comparator – place OUTSIDE any function */
int compare(const void *a, const void *b) {
    const ScoreEntry *sa = (const ScoreEntry *)a;
    const ScoreEntry *sb = (const ScoreEntry *)b;

    /* wins descending */
    if (sa->wins < sb->wins) return 1;
    if (sa->wins > sb->wins) return -1;

    /* tie-breaker: name ascending */
    return strcmp(sa->name, sb->name);
}

void displayScoreboard() {
    FILE *fp = fopen(HIGHSCORE_FILE, "r");
    if (!fp) {
        printf("No scores available yet.\n");
        pauseProgram();
        return;
    }


    ScoreEntry scores[200];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        char name[MAX_NAME_LEN];
        int games, wins, losses;

        if (sscanf(line, "%49s %d %d %d", name, &games, &wins, &losses) != 4) {
            continue;
        }

        int found = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(scores[i].name, name) == 0) {
                scores[i].gamesPlayed += games;
                scores[i].wins += wins;
                scores[i].losses += losses;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (count >= 200) break;
            strncpy(scores[count].name, name, MAX_NAME_LEN - 1);
            scores[count].name[MAX_NAME_LEN - 1] = '\0';
            scores[count].gamesPlayed = games;
            scores[count].wins = wins;
            scores[count].losses = losses;
            count++;
        }
    }
    fclose(fp);

    if (count == 0) {
        printf("No valid scores found.\n");
        pauseProgram();
        return;
    }

    qsort(scores, count, sizeof(ScoreEntry), compare);

    printHeader("Scoreboard");
    printf("%-20s | %-12s | %-6s | %-6s\n", "Player Name", "Games Played", "Wins", "Losses");
    printDivider();
    for (int i = 0; i < count; i++) {
        printf("%-20s | %-12d | %-6d | %-6d\n",
               scores[i].name,
               scores[i].gamesPlayed,
               scores[i].wins,
               scores[i].losses);
    }
    printFooter();

    pauseProgram();
}

// GAME STATS LOGGING

void saveGameStats(GameSession *session, int mode) {
    FILE *fp = fopen(STATS_FILE, "a");
    if (!fp) return;

    fprintf(fp, "Player: %s | Mode: %s | Rounds: %d | Wins: %d | Losses: %d\n",
            session->playerName,
            mode == 1 ? "Basic" : "Advanced",
            session->roundsPlayed,
            session->wins,
            session->losses);
    fprintf(fp, "Moves (Player vs Computer):\n");
    for (int i = 0; i < session->roundsPlayed; i++) {
      fprintf(fp, "%s %d %d %d\n", session->playerName, 1, session->wins, session->losses);
    }
    fprintf(fp, "-----\n");

    fclose(fp);
}

void viewGameStats() {
    FILE *fp = fopen(STATS_FILE, "r");
    if (!fp) {
        printf("No game stats recorded yet.\n");
        pauseProgram();
        return;
    }
    printHeader("Game Stats History");
    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, fp)) {
        printf("%s", line);
    }
    printFooter();
    fclose(fp);
    pauseProgram();
}

// MENU

void mainMenu(Profile profiles[], int *profCount) {
    while (1) {
        printHeader("Main Menu");
        printf("1) Play Game\n");
        printf("2) Profiles Management\n");
        printf("3) Scoreboard\n");
        printf("4) View Game Stats\n");
        printf("5) Instructions\n");
        printf("0) Exit\n");
        printDivider();
        int choice = getIntInRange("Enter your choice: ", 0, 5);

        switch (choice) {
            case 1:
                playGame(profiles, *profCount);
                break;
            case 2:
                profilesMenu(profiles, profCount);
                break;
            case 3:
                scoreboardMenu();
                break;
            case 4:
                statsMenu();
                break;
            case 5:
                instructionsMenu();
                break;
            case 0:
                printf("Thank you for playing Cham Cham Cham!\n");
                return;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}

void profilesMenu(Profile profiles[], int *profCount) {
    while (1) {
        printHeader("Profiles Management");
        printf("1) List Profiles\n");
        printf("2) Add New Profile\n");
        printf("3) Rename Profile\n");
        printf("4) Delete Profile\n");
        printf("5) View Profile Details\n");
        printf("0) Return to Main Menu\n");
        printDivider();

        int choice = getIntInRange("Enter choice: ", 0, 5);
        switch (choice) {
            case 1:
                showProfiles(profiles, *profCount);
                pauseProgram();
                break;
            case 2:
                addNewProfile(profiles, profCount);
                break;
            case 3:
                renameProfile(profiles, *profCount);
                break;
            case 4:
                deleteProfile(profiles, profCount);
                break;
            case 5:
                if (*profCount == 0) {
                    printf("No profiles available.\n");
                    pauseProgram();
                } else {
                    showProfiles(profiles, *profCount);
                    int sel = getIntInRange("Select profile number to view: ", 1, *profCount);
                    viewProfileDetails(&profiles[sel - 1]);
                }
                break;
            case 0:
                return;
            default:
                printf("Invalid choice, try again.\n");
        }
    }
}

void scoreboardMenu() {
    displayScoreboard();
}

void statsMenu() {
    viewGameStats();
}

void instructionsMenu() {
    printHeader("Instructions");
    printf("Welcome to Cham Cham Cham!\n\n");
    printf("Basic mode moves:\n");
    printf("L - Left\n");
    printf("R - Right\n");
    printf("U - Up\n");
    printf("D - Down\n\n");

    printf("Advanced mode moves:\n");
    printf("A - LU (Left-Up)\n");
    printf("B - LD (Left-Down)\n");
    printf("C - RU (Right-Up)\n");
    printf("E - RD (Right-Down)\n");
    printf("Or directly input two-letter moves LU, LD, RU, RD.\n\n");

    printf("How to play:\n");
    printf("- Choose your profile or create one.\n");
    printf("- Choose basic or advanced mode.\n");
    printf("- Enter moves each round.\n");
    printf("- You win the round if your move differs from the computer's move.\n");
    printf("- The game ends after selected rounds.\n\n");

    printf("Good luck and have fun!\n");
    printFooter();
    pauseProgram();
}

// EXTRA HELPERS


void waitSeconds(int seconds) {
    time_t start = time(NULL);
    while (time(NULL) - start < seconds) {
        // just wait
    }
}
