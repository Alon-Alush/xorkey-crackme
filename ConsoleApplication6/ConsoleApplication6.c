#include <stdint.h>
#include <stdio.h>
#include <windows.h>
unsigned int crcdata(unsigned char* data, size_t bytesRead)
{
    unsigned int crc = 0xFFFFFFFF;
    for (size_t i = 0; i < bytesRead; i++) {
        crc ^= data[i];

        
        for (int j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else {
                crc >>= 1;
            }
        }
    }

    return ~crc; // Invert the CRC result
}

int main() {
    HANDLE hConsole;
    

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    

    char path[MAX_PATH];
    DWORD bytesRead;
    unsigned char data[10240];

    GetModuleFileNameA(NULL, path, MAX_PATH);
    HANDLE hFile = CreateFileA(
        path,
        GENERIC_READ,
        FILE_SHARE_READ,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    DWORD result = (ReadFile(hFile, data, sizeof(data), &bytesRead, NULL));
    if (result == 0) {
        return 1;
    }

    uint8_t xorkey = 0x69;
    char patchmsg[] = { 0x39,0x08,0x1d,0x0a,0x01,0x49,0x0d,0x0c,0x1d,0x0c,0x0a,0x1d,0x0c,0x0d,0x48,0x49,0x30,0x06,0x1c,0x1b,0x49,0x19,0x1b,0x06,0x0e,0x1b,0x08,0x04,0x49,0x01,0x08,0x1a,0x49,0x0b,0x0c,0x0c,0x07,0x49,0x00,0x07,0x1f,0x08,0x05,0x00,0x0d,0x08,0x1d,0x0c,0x0d,0x47, '\n', '\0' };
    for (size_t i = 0; i < 50; i++)
    {
        patchmsg[i] ^= xorkey;

    }
    CloseHandle(hFile);
    unsigned int crchash = crcdata(data, bytesRead);
    unsigned int shorthash = (crchash / 10 % 100);
    if (shorthash != 20) {
        printf(patchmsg, "\n");
        system("pause");
        return 0;
    }
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf(
        "Made by alonalush5@gmail.com \n"
        " __   ______  _____  \n"
        " \\ \\ / / __ \\|  __ \\ \t     8 8 8 8                     ,ooo.  \n"
        "  \\ V / |  | | |__) | \t     8a8 8a8                    oP   ?b \n"
        "   > <| |  | |  _  /  \t    d888a888zzzzzzzzzzzzzzzzzzzz8     8b \n"
        "  / . \\ |__| | | \\ \\ \t     `\"\"^\"\"'                    ?o___oP' \n"
        " /_/ \\_\\____/|_|  \\_\\\n"
    );
        
    printf("------------------------------------------------------------------------- \n");
    printf("Welcome to my first crackme, boys! \n");
    char UserInput[32];
    
    printf("Enter the password:\n");
    char TheKey[] = { 0x28, 0x5, 0x6, 0x7, 0x49, 0x28, 0x5, 0x1c, 0x1a, 0x1, '\n', '\0' };
    char BadMsg[] = { 0x3e, 0x1b, 0x06, 0x07, 0x0e, 0x49, 0x02, 0x0c, 0x10, 0x48, '\n', '\0' };
    char NiceMsg[] = { 0x3e,0x0c,0x05,0x05,0x49,0x0d,0x06,0x07,0x0c,0x48, '\n', '\0' };
    fgets(UserInput, sizeof(UserInput), stdin);

    /// XOR routine
    for (size_t i = 0; i < strlen(NiceMsg) - 1; i++)
    {
        NiceMsg[i] ^= xorkey;

    }
    for (size_t i = 0; i < strlen(UserInput) -1; i++)
    {
        UserInput[i] ^= xorkey;
    }
    for (size_t i = 0; i < strlen(BadMsg) - 1; i++)
    {
        BadMsg[i] ^= xorkey;
    }

    if (!strcmp(UserInput, TheKey) && sizeof(UserInput) == 32 && strlen(UserInput) == 11 && strlen(UserInput) -1 == 10 && sizeof(UserInput) + 5 == 37) {
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf(NiceMsg);
        printf(
            "                                       /;    ;\\\n"
            "                                   __  \\\\____//\n"
            "                                  /{_\\_/   `'\\____\n"
            "                                  \\___   (o)  (o  }\n"
            "       _____________________________/          :--'  \n"
            "   ,-,'`@@@@@@@@       @@@@@@         \\_    `__\\\n"
            "  ;:(  @@@@@@@@@        @@@             \\___(o'o)\n"
            "  :: )  @@@@          @@@@@@        ,'@@(  `===='       \n"
            "  :: : @@@@@:          @@@@         `@@@:\n"
            "  :: \\  @@@@@:       @@@@@@@)    (  '@@@'\n"
            "  ;; /\\      /`,    @@@@@@@@@\\   :@@@@@)\n"
            "  ::/  )    {_----------------:  :~`,~~;\n"
            "  ;;'`; :   )                  :  / `; ;\n"
            "  ;;;; : :   ;                  :  ;  ; :\n"
            "  `'`' / :  :                   :  :  : :\n"
            "      )_ \\__;      \";\"          :_ ;  \\_\\       `,','\n"
            "      :__\\  \\    * `,'*         \\  \\  :  \\   *  8`;'*  *\n"
            "          `^'     \\ :/           `^'  `-^-'   \\v/ :  \\/  \n"
        );

        system("pause");
    }
    else {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
        printf(BadMsg);
        printf(
            "     .-\"\"\"\"\"\"-.\n"
            "   .'  \\\\  //  '.\n"
            "  /   O      O   \\\n"
            " :                :\n"
            " |                |  angry\n"
            " :       __       :\n"
            "  \\  .-\"`  `\"-.  /\n"
            "   '.          .'\n"
            "jgs  '-......-' \n"
        );
        system("pause");
        return 0;
    }
}