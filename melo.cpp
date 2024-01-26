#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdlib.h>
struct Song {
    char title[100];
    char diskTitle[100];
    char artist[100];
    int releaseYear;
};
struct Disk {
    char title[100];
    int year;
    struct Song songs[10];
    int numSongs;
};
struct Artist {
    char name[100];
    struct Disk disks[5];
    int numDisks;
    struct Song singles[10];
    int numSongs;
};
void printMenu() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf("\n\n\n\t\t\t\t===== ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("���� �������� ��������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf (" =======\n");
    printf("\t\t\t\t| 1. ������ ����������              |\n");
    printf("\t\t\t\t| 2. �������� ����������            |\n");
    printf("\t\t\t\t| 3. ������/�������� ����������    |\n");
    printf("\t\t\t\t| 0. �����                          |\n");
    printf("\t\t\t\t=====================================\n");
}
void printAddMenu() {
    printf("\n\n\t\t\t\t\t=========================\n");
    printf("\t\t\t\t\t|1. ������ ������      |\n");
    printf("\t\t\t\t\t|2. ������ ����         |\n");
    printf("\t\t\t\t\t|3. ������ ����        |\n");
    printf("\t\t\t\t\t|0. � ������� ����      |\n");
    printf("\t\t\t\t\t=========================\n");
}
void printDeleteMenu() {
    printf("\n\n\t\t\t\t=========================\n");
    printf("\t\t\t\t|1. �������� ������    |\n");
    printf("\t\t\t\t|2. �������� ����       |\n");
    printf("\t\t\t\t|3. �������� ����      |\n");
    printf("\t\t\t\t|0. � ������� ����      |\n");
    printf("\t\t\t\t=========================\n");
}
void printEditMenu() {
    printf("\n\n\t\t\t===========================================================\n");
    printf("\t\t\t|1. ��������� ������ ������                               |\n");
    printf("\t\t\t|2. ��������� ���� ����������                             |\n");
    printf("\t\t\t|3. ��������� ���� �����                                 |\n");
    printf("\t\t\t|4. ��������� ���� ����� � �������                       |\n");
    printf("\t\t\t|5. ��������� ���� ������                                |\n");
    printf("\t\t\t|6. ���������� �� ��������                               |\n");
    printf("\t\t\t|7. ���������� �� ����� ������� (���� ���/�����)        |\n");
    printf("\t\t\t|8. ����������� ������                                    |\n");
    printf("\t\t\t|0. � ������� ����                                        |\n");
    printf("\t\t\t===========================================================\n");
}
void addArtist(struct Artist* artists, int* numArt) {
    if (*numArt >= 100) {
        printf("\t\t����������� �-�� ��������� ��� ��������.\n");
        return;
    }
    FILE* f = fopen("music_data.dat", "a+");
    getchar();
    printf("\n\t\t\t\t������ ��'� ���������: ");
    if (fgets(artists[*numArt].name, sizeof(artists[*numArt].name), stdin) == 0 || artists[*numArt].name[0] == '\n') {
        printf("\n\t\t\t�������! ���� ��� ���� ��������� �� ���� ���� ������!\n");
        fclose(f);
        return;
    }
    artists[*numArt].name[strcspn(artists[*numArt].name, "\n")] = '\0';
    (*numArt)++;
    fprintf(f, "\tArtist: %3s\n", artists[*numArt - 1].name);
    printf("\n\t\t\t\t��������� ������ �� ��������.\n");
    fclose(f);
}
void addDisk(struct Artist* artists, int numArt) {
    FILE* f = fopen("music_data.dat", "r+");
    getchar();
    printf("\n������ ��'� ������: ");
    char artName[100];
    if (fgets(artName, sizeof(artName), stdin) == 0 || artName[0] == '\n') {
        printf("\n�������! ���� ���� ��������� �� ���� ���� ������!\n");
        fclose(f);
        return;
    }
    artName[strcspn(artName, "\n")] = '\0';
    int artFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, artName) != 0) {
            artFound = 1;
            break;
        }
    }
    if (artFound) {
        system("cls");
        printf("\n���������� ���������: %s\n", artName);
        fseek(f, 0, 2);
        struct Disk newDisk;
        printf("\n�������� ����� �����: ");
        if (fgets(newDisk.title, sizeof(newDisk.title), stdin) == 0 || newDisk.title[0] == '\n') {
            printf("\n�������! ���� ����� �� ���� ���� ������!\n");
            fclose(f);
            return;
        }
        newDisk.title[strcspn(newDisk.title, "\n")] = '\0';
        printf("\n�������� ���� ������� �����: ");
        if (scanf("%d", &newDisk.year) != 1) {
            printf("\n�������! ���� ��� ���� ������� �� ���� ���� ������!\n");
            fclose(f);
            return;
        }
        getchar();
        fprintf(f, "\tDisk: \"%s\", %d, %s\n", newDisk.title, newDisk.year, artName);
        fflush(f);
        artists[numArt].numDisks++;
        printf("\n���� ���� ������ �� ��������.\n");
    }
    else printf("\n������� �� ���� ��������.\n");
    fclose(f);
}
void addSong(struct Artist* artists, int numArt) {
    FILE* f = fopen("music_data.dat", "r+");
    getchar();
    printf("\n\t������ ��'� ������: ");
    char artName[100];
    if (fgets(artName, sizeof(artName), stdin) == 0 || artName[0] == '\n') {
        printf("\n\t�������! ���� ��� ���� ��������� �� ���� ���� ������!\n");
        fclose(f);
        return;
    }
    artName[strcspn(artName, "\n")] = '\0';
    int artFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, artName) != 0) {
            artFound = 1;
            break;
        }
    }
    if (artFound) {
        system("cls");
        printf("\n\t���������� ���������: %s\n", artName);
        fseek(f, 0, 2);
        struct Song newSong;
        printf("\n\t������ ����� ���: ");
        if (fgets(newSong.title, sizeof(newSong.title), stdin) == 0 || newSong.title[0] == '\n') {
            printf("\n\t�������! ���� ��� ����� ��� �� ���� ���� ������!\n");
            fclose(f);
            return;
        }
        newSong.title[strcspn(newSong.title, "\n")] = '\0';
        printf("\n������ �� �������: ");
        if (scanf("%d", &newSong.releaseYear) != 1) {
            printf("\n\t������� � ������ ���� ������� ���!\n");
            fclose(f);
            return;
        }
        getchar();
        printf("\n\t���� ��� ��� �� ������? (1 - ϳ��� � �������, 0 - �����): ");
        int addToDisk;
        if (scanf("%d", &addToDisk) != 1) {
            printf("\n\t������� � ����� �� ����� ������!\n");
            fclose(f);
            return;
        }
        getchar();
        if (addToDisk) {
            printf("\n\t������ ����� �����: ");
            if (fgets(newSong.diskTitle, sizeof(newSong.diskTitle), stdin) == 0 || newSong.diskTitle[0] == '\n') {
                printf("\n\t�������! ���� ��� ����� �� ���� ���� ������!\n");
                fclose(f);
                return;
            }
            newSong.diskTitle[strcspn(newSong.diskTitle, "\n")] = '\0';
            fprintf(f, "\tSong:  \"%s\", %4d, <%7s>, %5s \n", newSong.title, newSong.releaseYear, newSong.diskTitle, artName);
            printf("\n\tϳ��� ���� ������ �� ��������.\n");
        }
        else {
            fprintf(f, "\tSingle:  \"%s\", %4d, %7s\n", newSong.title, newSong.releaseYear, artName);
            printf("\nϳ���-����� ���� ������ �� ��������.\n");
        }
    }
    else printf("\n������ �� ��������.\n");
    fclose(f);
}
void addInfo(struct Artist* artists, int* numArt, int itemIndex) {

    switch (itemIndex) {
    case 1:
        system("cls");
        addArtist(artists, numArt);
        break;
    case 2:
        system("cls");
        addDisk(artists, *numArt);
        break;
    case 3:
        system("cls");
        addSong(artists, *numArt);
        break;
    case 0:
        system("cls");
        break;
    default:
        printf("������������ ����!\n");
    }
}
void deleteArtist(struct Artist* artists, int* numArt) {
    FILE* f = fopen("music_data.dat", "r");
    char artistName[100];
    getchar();
    printf("\n\t������ ��'� ��������� ��� ���������: ");
    if (fgets(artistName, sizeof(artistName), stdin) == 0 || artistName[0] == '\n') {
        printf("\n\t�������: ��'� ��������� �� ���� ���� ������.\n");
        return;
    }
    artistName[strcspn(artistName, "\n")] = '\0';
    FILE* newFile = fopen("new_music_data.dat", "w");
    int artistFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, artistName) == 0)
            fprintf(newFile, "%s\n", line);
        else artistFound = 1;
    }
    fclose(f);
    fclose(newFile);
    if (!artistFound) {
        printf("\n\t��������� \"%s\" �� �������� � ��� �����.\n", artistName);
        remove("new_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("new_music_data.dat", "music_data.dat");
    for (int i = 0; i < *numArt; i++) {
        if (strcmp(artists[i].name, artistName) == 0) {
            for (int j = i; j < *numArt - 1; j++)
                artists[j] = artists[j + 1];
            (*numArt)--; 
        }
    }
    printf("\n\t��������� \"%s\" �������� � ���� �����.\n", artistName);
    return;
}
void deleteDisk(struct Artist* artists, int* numArt) {
    FILE* f = fopen("music_data.dat", "r");
    getchar();
    char artistName[100];
    char diskName[100];
    printf("\n\t������ ��'� ���������: ");
    if (fgets(artistName, sizeof(artistName), stdin) == 0 || artistName[0] == '\n') {
        printf("\n\t�������: ��'� ��������� �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    artistName[strcspn(artistName, "\n")] = '\0';
    printf("\n\t������ ����� ����� ��� ���������: ");
    if (fgets(diskName, sizeof(diskName), stdin) == 0 || diskName[0] == '\n') {
        printf("\n\t�������: ��'� ��������� �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    diskName[strcspn(diskName, "\n")] = '\0';
    FILE* newFile = fopen("new_music_data.dat", "w");
    int diskFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, artistName) != 0 && strstr(line, diskName) != 0)
            diskFound = 1;
        else fprintf(newFile, "%s\n", line);
    }
    fclose(f);
    fclose(newFile);
    if (!diskFound) {
        printf("\n\t���� \"%s\" ��������� \"%s\" �� �������� � ��� �����.\n", diskName, artistName);
        remove("new_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("new_music_data.dat", "music_data.dat");
    for (int i = 0; i < *numArt; i++) {
        if (strcmp(artists[i].name, artistName) == 0) {
            for (int j = i; j < *numArt - 1; j++)
                artists[j] = artists[j + 1];
            (*numArt)--;
        }
    }
    printf("\n\t���� \"%s\" ��������� \"%s\" �������� � ���� �����.\n", diskName, artistName);
    return;
}
void deleteSong(struct Artist* artists, int* numArtists) {
    FILE* f = fopen("music_data.dat", "r");
    char artistName[100];
    char diskName[100];
    char songName[100];
    int isIndependent;
    getchar();
    printf("\n\t������ ��'� ���������: ");
    if (fgets(artistName, sizeof(artistName), stdin) == 0 || artistName[0] == '\n') {
        printf("\n\t�������: ��'� ��������� �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    artistName[strcspn(artistName, "\n")] = '\0';
    printf("\n\t������ ����� ���: ");
    if (fgets(songName, sizeof(songName), stdin) == 0 || songName[0] == '\n') {
        printf("\n\t�������: ����� ��� �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    songName[strcspn(songName, "\n")] = '\0';
    printf("\n\t�� �� ���������� ����? (1 - ���, 0 - �): ");
    scanf_s("%d", &isIndependent);
    getchar();
    if (!isIndependent) {
        printf("\n\t������ ����� �����: ");
        if (fgets(diskName, sizeof(diskName), stdin) == 0 || diskName[0] == '\n') {
            printf("\n\t�������: ����� ����� �� ���� ���� ������.\n");
            fclose(f);
            return;
        }
        diskName[strcspn(diskName, "\n")] = '\0';
    }
    FILE* newFile = fopen("new_music_data.dat", "w");
    int songFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (isIndependent) {
            if (strstr(line, artistName) != 0 && strstr(line, songName) != 0)
                songFound = 1;
            else fprintf(newFile, "%s\n", line);
        }
        else {
            if (strstr(line, artistName) != 0 && strstr(line, diskName) != 0 && strstr(line, songName) != 0)
                songFound = 1;
            else fprintf(newFile, "%s\n", line);
        }
    }
    fclose(f);
    fclose(newFile);
    if (!songFound) {
        if (isIndependent)
            printf("\n\tϳ��� \"%s\" ��������� \"%s\" �� �������� � ��� �����.\n", songName, artistName);
        else printf("\n\tϳ��� \"%s\" �� ����� \"%s\" ��������� \"%s\" �� �������� � ��� �����.\n", songName, diskName, artistName);
        remove("new_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("new_music_data.dat", "music_data.dat");
    for (int i = 0; i < *numArtists; i++) {
        if (strcmp(artists[i].name, artistName) == 0) {
            if (isIndependent) {
                for (int k = 0; k < artists[i].numSongs; k++) {
                    if (strcmp(artists[i].singles[k].title, songName) == 0) {
                        for (int l = k; l < artists[i].numSongs - 1; l++)
                            artists[i].singles[l] = artists[i].singles[l + 1];
                        artists[i].numSongs--;
                    }
                }
                printf("\n\tϳ��� \"%s\" ��������� \"%s\" �������� � ���� �����.\n", songName, artistName);
                return;
            }
            else {
                for (int j = 0; j < artists[i].numDisks; j++) {
                    if (strcmp(artists[i].disks[j].title, diskName) == 0) {
                        for (int k = 0; k < artists[i].disks[j].numSongs; k++) {
                            if (strcmp(artists[i].disks[j].songs[k].title, songName) == 0) {
                                for (int l = k; l < artists[i].disks[j].numSongs - 1; l++)
                                    artists[i].disks[j].songs[l] = artists[i].disks[j].songs[l + 1];
                                artists[i].disks[j].numSongs--;
                            }
                        }
                    }
                }
                printf("\n\tϳ��� \"%s\" �� ����� \"%s\" ��������� \"%s\" �������� � ���� �����.\n", songName, diskName, artistName);
                return;
            }
        }
    }
}
void deleteInfo(struct Artist* artists, int* numArt, int itemIndex) {
    switch (itemIndex) {
    case 1:
        system("cls");
        deleteArtist(artists, numArt);
        break;
    case 2:
        system("cls");
        deleteDisk(artists, numArt);
        break;
    case 3:
        system("cls");
        deleteSong(artists, numArt);
        break;
    case 0:
        system("cls");
        break;
    default:
        printf("������������ ����. ��������� ��!\n");
    }
}
void viewFile(struct Artist* artists, int numArt) {
    FILE* f = fopen("music_data.dat", "r");
    printf("\n\t\t\t���� ������ �����:\n\n");
    char line[256];
    while (fgets(line, sizeof(line), f) != NULL)
        printf("%s", line);
    fclose(f);
}
void displayArtists() {
    FILE* f = fopen("music_data.dat", "a+");
    char line[256];
    printf("\n\t\t\t\t���������, �� ������� � ��� ���:\n\n");
    printf("\t\t\t\t==================================\n");
    printf("\t\t\t\t| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-30s", "��'� ���������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | \n");
    printf("\t\t\t\t==================================\n");
    while (fgets(line, sizeof(line), f) != 0) {
        if (strstr(line, "Artist") != 0) {
            char* pos = strchr(line, ':');
            if (pos != 0) {
                char* artistName = pos + 2;
                artistName[strcspn(artistName, "\n")] = '\0';
                printf("\t\t\t\t| %-30s |\n", artistName);
            }
        }
    }
    printf("\t\t\t\t==================================\n");
    fclose(f);
}
void displayDisks() {
    FILE* f = fopen("music_data.dat", "a+");
    char line[256];
    printf("\n\t\t\t����� �� �� ���������, �� ������� � ��� ���:\n\n");
    printf("\t\t\t====================================================================================\n");
    printf("\t\t\t| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-40s", "����� �����");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-4s", "г�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-30s", "��'� ���������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" |\n");
    printf("\t\t\t====================================================================================\n");
    while (fgets(line, sizeof(line), f) != 0) {
        if (strstr(line, "Disk") != 0) {
            char* posQuote1 = strchr(line, '"');
            char* posQuote2 = strrchr(line, '"');
            char* posComma1 = strchr(line, ',');
            char* posComma2 = strrchr(line, ',');
            if (posQuote1 != 0 && posQuote2 != 0 && posComma1 != 0 && posComma2 != 0) {
                char* diskTitle = posQuote1 + 1;
                diskTitle[posQuote2 - posQuote1 - 1] = '\0';
                int year = atoi(posComma1 + 2);
                char* artistName = posComma2+2;
                artistName[strcspn(artistName, "\n")] = '\0';
                printf("\t\t\t| %-40s | %-4d | %-30s |\n", diskTitle, year, artistName);
            }
        }
    }
    printf("\t\t\t====================================================================================\n");
    fclose(f);
}
void displaySingles() {
    FILE* f = fopen("music_data.dat", "a+");
    char line[256];
    printf("\n\t\t\t\t������, �� ������� � ��� ���:\n\n");
    printf("\t\t\t==========================================================================\n");
    printf("\t\t\t| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-30s", "����� ���");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-4s", "г�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-30s", "��'� ���������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" |\n");
    printf("\t\t\t==========================================================================\n");
    while (fgets(line, sizeof(line), f) != 0) {
        if (strstr(line, "Single") != 0) {
            line[strcspn(line, "\n")] = '\0';
            char* posColon = strchr(line, ':');
            char* posQuote1 = strchr(line, '"');
            char* posQuote2 = strrchr(line, '"');
            char* posComma1 = strchr(line, ',');
            char* posComma2 = strrchr(line, ',');
            if (posColon != 0 && posQuote1 != 0 && posQuote2 != 0 && posComma1 != 0 && posComma2 != 0) {
                char* songTitle = posQuote1 + 1;
                int quoteCount = 0;
                char* currentPos = line;
                while (currentPos != 0) {
                    currentPos = strchr(currentPos, '"');
                    if (currentPos != 0) {
                        quoteCount++;
                        currentPos++;
                    }
                }
                if (quoteCount == 2) {
                    songTitle[posQuote2 - posQuote1 - 1] = '\0';
                    int year = atoi(posComma1 + 2);
                    char* artistNameStart = posComma2 + 2;
                    char* artistNameEnd = posColon - 1;
                    *posComma2 = '\0';
                    printf("\t\t\t| %-30s | %-4d | %-30s |\n", songTitle, year, artistNameStart);
                }
            }
        }
    }
    printf("\t\t\t==========================================================================\n");
    fclose(f);
}
void displaySongs() {
    FILE* f = fopen("music_data.dat", "a+");
    char line[256];
    printf("\n\t\t\t\tϳ��, �� ������� � ��� ���:\n\n");
    printf("=====================================================================================================================\n");
    printf("| ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-30s", "����� ���");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-4s", "г�");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-40s", "����� �����");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" | ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("%-30s", "��'� ���������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" |\n");
    printf("=====================================================================================================================\n");

    while (fgets(line, sizeof(line), f) != 0) {
        if (strstr(line, "Song") != 0) {
            line[strcspn(line, "\n")] = '\0';
            char* posQuote1 = strchr(line, '"');
            char* posQuote2 = strrchr(line, '"');
            char* posComma1 = strchr(line, ',');
            char* posComma2 = strrchr(line, ',');
            char* posOpenBracket = strchr(line, '<');
            char* posCloseBracket = strrchr(line, '>');
            if (posQuote1 != 0 && posQuote2 != 0 && posComma1 != 0 && posComma2 != 0 && posOpenBracket != 0 && posCloseBracket != 0) {
                char* songTitle = posQuote1 + 1;
                char* albumTitle = posOpenBracket + 1;
                int year = atoi(posComma1 + 2);
                *posComma1 = '\0';
                char* artistName = posComma2 + 2;
                *posComma2 = '\0';
                posQuote2[0] = '\0';
                posOpenBracket[0] = '\0';
                posCloseBracket[0] = '\0';
                printf("| %-30s | %-4d | %-40s | %-30s |\n", songTitle, year, albumTitle, artistName);
            }
        }
    }
    printf("=====================================================================================================================\n");
    fclose(f);
}
void editArtist() {
    FILE* file = fopen("music_data.dat", "r");
    char artistName[100];
    getchar();
    printf("\n\t������ ��'� ��������� ��� �����������: ");
    if (fgets(artistName, sizeof(artistName), stdin) == 0 || artistName[0] == '\n') {
        printf("\n\t�������: ��'� ��������� �� ���� ���� ������.\n");
        fclose(file);
        return;
    }
    artistName[strcspn(artistName, "\n")] = '\0';
    FILE* tempFile = fopen("temp_music_data.dat", "w");
    int artistFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, "Artist") != NULL && strstr(line, artistName) != NULL) {
            artistFound = 1;
            printf("\n\t�������� ��������� \"%s\". �������� ���:\n", artistName);
            printf("\t%s\n", line);
            struct Artist newArtist;
            printf("\n\t������ ��� ��� ��� ���������:\n");
            printf("\t���� ��'� ���������: ");
            fgets(newArtist.name, sizeof(newArtist.name), stdin);
            newArtist.name[strcspn(newArtist.name, "\n")] = '\0';
            fprintf(tempFile, "\tArtist: %s\n", newArtist.name);
        }
        else fprintf(tempFile, "%s\n", line);
    }
    fclose(file);
    fclose(tempFile);
    if (!artistFound) {
        printf("\n\t��������� \"%s\" �� �������� � ��� �����.\n", artistName);
        remove("temp_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("temp_music_data.dat", "music_data.dat");
    printf("\n\t��������� \"%s\" ������������ �� ���������.\n", artistName);
}
void editDisk() {
    FILE* f = fopen("music_data.dat", "r");
    char diskTitle[100];
    int diskYear;
    char artistName[100];
    getchar();
    printf("\n\t������ ����� ����� ��� �����������: ");
    if (fgets(diskTitle, sizeof(diskTitle), stdin) == 0 || diskTitle[0] == '\n') {
        printf("\n\t�������: ����� ����� �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    diskTitle[strcspn(diskTitle, "\n")] = '\0';
    FILE* tempFile = fopen("temp_music_data.dat", "w");
    int diskFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, "Disk") != 0 && strstr(line, diskTitle) != 0) {
            diskFound = 1;
            printf("\n\t�������� ���� \"%s\". �������� ���:\n", diskTitle);
            printf("\t%s\n", line);
            struct Disk newDisk;
            printf("\t������ ����� �����: ");
            fgets(newDisk.title, sizeof(newDisk.title), stdin);
            newDisk.title[strcspn(newDisk.title, "\n")] = '\0';
            printf("\t������ �� �����: ");
            scanf_s("%d", &newDisk.year);
            getchar();
            printf("\t������ ��'� ���������: ");
            fgets(artistName, sizeof(artistName), stdin);
            artistName[strcspn(artistName, "\n")] = '\0';
            fprintf(tempFile, "\tDisk: \"%s\", %d, %s\n", newDisk.title, newDisk.year, artistName);
        }
        else fprintf(tempFile, "%s\n", line);
    }
    fclose(f);
    fclose(tempFile);
    if (!diskFound) {
        printf("\n\t���� \"%s\" �� �������� � ��� �����.\n", diskTitle);
        remove("temp_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("temp_music_data.dat", "music_data.dat");
    printf("\n\t���� \"%s\" ������������ �� ���������.\n", diskTitle);
}
void editSong() {
    FILE* f = fopen("music_data.dat", "r");
    char songTitle[100];
    int songYear;
    char diskTitle[100];
    char artistName[100];
    getchar();
    printf("\n\t������ ����� ��� ��� �����������: ");
    if (fgets(songTitle, sizeof(songTitle), stdin) == 0 || songTitle[0] == '\n') {
        printf("\n\t�������: ����� ��� �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    songTitle[strcspn(songTitle, "\n")] = '\0';
    FILE* tempFile = fopen("temp_music_data.dat", "w");
    int songFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, "Song") != 0 && strstr(line, songTitle) != 0) {
            songFound = 1;
            printf("\n\t�������� ���� \"%s\". �������� ���:\n", songTitle);
            printf("\t%s\n", line);
            struct Song newSong;
            printf("\t������ ����� ���: ");
            fgets(newSong.title, sizeof(newSong.title), stdin);
            newSong.title[strcspn(newSong.title, "\n")] = '\0';
            printf("\t������ �� �������: ");
            scanf("%d", &newSong.releaseYear);
            getchar();
            printf("\t������ ����� �����: ");
            fgets(newSong.diskTitle, sizeof(newSong.diskTitle), stdin);
            newSong.diskTitle[strcspn(newSong.diskTitle, "\n")] = '\0';
            printf("\t������ ��'� ���������: ");
            fgets(newSong.artist, sizeof(newSong.artist), stdin);
            newSong.artist[strcspn(newSong.artist, "\n")] = '\0';
            fprintf(tempFile, "\tSong: \"%s\", %4d, <%7s>, %5s\n", newSong.title, newSong.releaseYear, newSong.diskTitle, newSong.artist);
        }
        else fprintf(tempFile, "%s\n", line);
    }
    fclose(f);
    fclose(tempFile);
    if (!songFound) {
        printf("\n\tϳ��� \"%s\" �� �������� � ��� �����.\n", songTitle);
        remove("temp_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("temp_music_data.dat", "music_data.dat");
    printf("\n\tϳ��� \"%s\" ������������ �� ���������.\n", songTitle);
}
void editSingle() {
    FILE* f = fopen("music_data.dat", "r");
    char singleTitle[100];
    int singleYear;
    char artistName[100];
    getchar();
    printf("\n\t������ ����� ������ ��� �����������: ");
    if (fgets(singleTitle, sizeof(singleTitle), stdin) == 0 || singleTitle[0] == '\n') {
        printf("\n\t�������: ����� ������ �� ���� ���� ������.\n");
        fclose(f);
        return;
    }
    singleTitle[strcspn(singleTitle, "\n")] = '\0';
    FILE* tempFile = fopen("temp_music_data.dat", "w");
    int singleFound = 0;
    char line[256];
    while (fgets(line, sizeof(line), f) != 0) {
        line[strcspn(line, "\n")] = '\0';
        if (strstr(line, "Single") != 0 && strstr(line, singleTitle) != 0) {
            singleFound = 1;
            printf("\n\t�������� ����� \"%s\". �������� ���:\n", singleTitle);
            printf("\t%s\n", line);
            struct Song newSingle;
            printf("\t������ ��� ��� ��� ������:\n");
            printf("\t����� ������: ");
            fgets(newSingle.title, sizeof(newSingle.title), stdin);
            newSingle.title[strcspn(newSingle.title, "\n")] = '\0';
            printf("\t��'� ���������: ");
            fgets(newSingle.artist, sizeof(newSingle.artist), stdin);
            newSingle.artist[strcspn(newSingle.artist, "\n")] = '\0';
            printf("\tг� �������: ");
            scanf_s("%d", &newSingle.releaseYear);
            fprintf(tempFile, "\tSingle: \"%s\", %4d, %7s\n", newSingle.title, newSingle.releaseYear, newSingle.artist);
        }
        else fprintf(tempFile, "%s\n", line);
    }
    fclose(f);
    fclose(tempFile);
    if (!singleFound) {
        printf("\n\t����� \"%s\" �� �������� � ��� �����.\n", singleTitle);
        remove("temp_music_data.dat");
        return;
    }
    remove("music_data.dat");
    rename("temp_music_data.dat", "music_data.dat");
    printf("\n\t����� \"%s\" ������������ �� ���������.\n", singleTitle);
}
void editMenu() {
    int choice;
    printf("\n\n\n\t\t\t\t====== ");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
    printf("���� �����������");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    printf(" ======\n");
    printf("\t\t\t\t|1. ���������� ���������     |\n");
    printf("\t\t\t\t|2. ���������� ����          |\n");
    printf("\t\t\t\t|3. ���������� ����         |\n");
    printf("\t\t\t\t|4. ���������� �����         |\n");
    printf("\t\t\t\t|0. � ������� ����           |\n");
    printf("\t\t\t\t==============================\n");
    printf("\n\n\t\t\t\t������ ��� ����: ");
    scanf_s("%d", &choice);
    switch (choice) {
    case 1:
        editArtist();
        break;
    case 2:
        editDisk();
        break;
    case 3:
        editSong();
        break;
    case 4:
        editSingle();
        break;
    case 0:
        system("cls");
        break;
    default:
        printf("\n\t������� ����.\n");
        break;
    }
}
void edit_viewInfoMenu(struct Artist* artists, int numArt, int itemIndex) {
    switch (itemIndex) {
    case 1:
        system("cls");
        viewFile(artists, numArt);
        break;
    case 2:
        system("cls");
        displayArtists();
        break;
    case 3:
        system("cls");
        displayDisks();
        break;
    case 4:
        system("cls");
        displaySongs();
        break;
    case 5:
        system("cls");
        displaySingles();
        break;
    case 8:
        system("cls");
        editMenu();
        break;
    case 0:
        system("cls");
        break;
    default:
        printf("������������ ����. ��������� ��!\n");
    }
}
void menu(struct Artist* artists, int numArt) {
    int choice;
    int itemIndex;
    do {
        printMenu();
        printf("\n\n\t\t\t\t������ ��� ����: ");
        scanf_s("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            system("cls");
            printAddMenu();
            printf("\n\n\t\t\t\t\t������ ��� ����: ");
            scanf_s("%d", &itemIndex);
            addInfo(artists, &numArt, itemIndex);
            break;
        case 2:
            system("cls");
            printDeleteMenu();
            printf("\n\n\t\t\t\t������ ��� ����: ");
            scanf_s("%d", &itemIndex);
            deleteInfo(artists, &numArt, itemIndex);
            break;
        case 3:
            system("cls");
            printEditMenu();
            printf("\n\n\t\t\t\t������ ��� ����: ");
            scanf_s("%d", &itemIndex);
            edit_viewInfoMenu(artists, numArt, itemIndex);
            break;
        case 0:
            system("cls");
            printf("\n\n\n\n\t\t\t\t\t\t����� �� ��������. \n\n\t\t\t\t����� �� ������������ \"��������� ��������\"!!\n\n\n\n\n");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            break;
        default:
            system("cls");
            printf("\n������������ ����. ��������� �� ���!\n");
        }
    } while (choice != 0);
}
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    struct Artist artists[100]; 
    int numArt = 0;            
    menu(artists, numArt);
    return 0;
}
