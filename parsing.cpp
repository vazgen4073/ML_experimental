#pragma once
#include "parsing.h"
#include <string.h>
parsing::parsing()
{
}

void parsing::find_word_inline(string& line, char word[100], short& z, bool& findbool)
{
    char char_word[1000];

    strcpy(char_word, line.c_str());
    short lenght = strlen(char_word);
    for (short i = 0; i < lenght; i++) {
        if (char_word[i] == '>') //(char_word[i] >= '0'|| char_word[i] <= '9')    //(char_word[i] == '>')
        {
            short k = i;
            while (!(char_word[k] == '\0')) {
                word[z++] = char_word[k++];
            }
            word[z++] = '\0';
            findbool = true;
            break;
        }
    }
}

void parsing::write(int& data_name_number, string Path_to_data1, string Path_to_data2)
{

    string name_number = to_string(data_name_number);
    ofstream out, out1;
    //out1.open("myfile1.txt");
    out.open(Path_to_data1 + name_number + Path_to_data2, ios::app);
    if (!out)
        exit(1);

    char url[MAX_LINE] = "https://www.investing.com/currencies/eur-usd"; //// "http://www.earthcalendar.net/index.php";
    char destination[MAX_LINE] = "index.html"; //"D:\myfile.html.txt";//"index.html";
    char buffer[MAX_LINE];

    HRESULT dl;

    typedef HRESULT(WINAPI * URLDownloadToFileA_t)(LPUNKNOWN pCaller, LPCSTR szURL, LPCSTR szFileName, DWORD dwReserved, void* lpfnCB);
    URLDownloadToFileA_t xURLDownloadToFileA;
    xURLDownloadToFileA = (URLDownloadToFileA_t)GetProcAddress(LoadLibraryA("urlmon"), "URLDownloadToFileA");

    dl = xURLDownloadToFileA(NULL, url, destination, 0, NULL);

    sprintf(buffer, "Downloading File From: %s, To: %s", url, destination);

    if (dl == S_OK) {
        sprintf(buffer, "", destination); //File Successfully Downloaded To: %s
        printf(buffer);
        struct tm *local, *gm;
        time_t t;
        t = time(NULL);
        local = localtime(&t);

        //out << endl << "EUR-USD " << asctime(local);
        //cout << "EUR-USD " << asctime(local) << endl;
    } else if (dl == E_OUTOFMEMORY) {
        sprintf(buffer, "Failed To Download File Reason: Insufficient Memory");
        printf(buffer);
        this_thread::sleep_for(chrono::milliseconds(30000));
    } else {
        sprintf(buffer, "Failed To Download File Reason: Unknown");
        printf(buffer);
        //return 0;
        this_thread::sleep_for(chrono::milliseconds(30000));
    }
    void func();
    ///////////////////////////////////////////
    //char ham[100] = "id = \"last_last\"";
    ///////////////////////////////////////////
    char found_word[100];
    char line_temp[3000];
    char found_word_without_simbols[100];

    string line;

    bool turn_on__function_find_word_inline = false;
    bool key_for_line = false;
    bool turn_on_break_in_line_133 = false;

    short r = 0; //counter for  found_word_without_simbols  array
    short z = 0; //counter in function  find_word_inline

    ifstream fin("index.html");

    if (!(fin.is_open())) {
        cout << "File path is Worng!" << endl;
        exit(1);
    }

    //ifstream fin1("myfile1.txt");
    while (fin) {

        fin >> line;
        //	out1 << line << endl;
        strcpy(line_temp, line.c_str());
        key_for_line = strstr(line_temp, "id=\"last_last\""); //  for   m.    "pid-945629-last\">" );  //"id=\"last_last\"");

        line_temp[0] = '\0';

        if (turn_on__function_find_word_inline) {
            cout << line_temp << endl;
            find_word_inline(line, found_word, z, turn_on_break_in_line_133);
        }
        if (turn_on_break_in_line_133)
            break;
        if (key_for_line) {
            turn_on__function_find_word_inline = true;
        }
    }

    //	cout << found_word << endl;

    int te_lengh;
    te_lengh = strlen(found_word);

    for (int i = 0; i < te_lengh; i++) //ardyunq   aranc  avelord  nshanneri
    {

        int temppo = int(found_word[i]);
        if ((temppo >= 48) && (temppo <= 57) || temppo == 44 || temppo == 46) {

            if ((found_word[i] == ','))
                //
                continue;
            //
            else
                //
                found_word_without_simbols[r++] = found_word[i];
            //
        }
    }

    found_word_without_simbols[r] = '\0'; //  end of  line '\0'

    /*struct tm* local, * gm;
		time_t t;
		t = time(NULL);
		local = localtime(&t);
		printf("Local time and date: %s", asctime(local));
		gm = gmtime(&t);
		printf("Greenwich mean time and date: %s", asctime(gm));
		*/

    char* p;
    p = found_word_without_simbols;
    double result;
    result = (double)strtod(p, NULL); //convert

    //cout << "  BTC-USD " << result << endl;

    out << result << endl; // << "--------------------------";
    //cout << endl << result << endl << "---------" << endl;

    this_thread::sleep_for(chrono::milliseconds(4800));
    //system("cls");
    cout << endl
         << result << endl;
}

parsing::~parsing()
{
}
