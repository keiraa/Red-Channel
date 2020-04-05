#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include <fstream>
#include <Windows.h>
#include <cwchar>

using namespace cv;
using namespace std;

CONSOLE_FONT_INFOEX cfi;


int count_dir(const char* path) {
    struct dirent* entry;
    DIR* dir = opendir(path);
    int i = 0;

    if (dir == NULL) {
        cout << "\n!!!!!!!!!!!!! Can't Find Path !!!!!!!!!!!!!\n";
        cout << "\n<<<<<<<<<<<<< Sorry Try Again >>>>>>>>>>>>";
        exit(10);
    }
    if ((entry = readdir(dir)) == NULL)
    {
        return 0;
    }
    while ((entry = readdir(dir)) != NULL) {
        i++;
    }
    closedir(dir);
    return i;
}


int RecordVid(string path)
{
    Mat frame;
    time_t start, end;

    VideoCapture vid(0);

    if (!vid.isOpened())
    {
        cerr << "Error! Camera not Connected\n";
        return -1;
    }


    vid >> frame;

    if (frame.empty()) {
        cerr << "ERROR! Camera returned Blank Frames\n";
        return -1;
    }


    //Initializing Video Writer
    VideoWriter output;

    //Attributes of Video Writer
    bool isColor = (frame.type() == CV_8UC3);
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
    string filename;
    char last = path.back();
    char num;

    const char* save = path.c_str();
    int i = count_dir(save);
    i--;

    ofstream ofile("num.txt");
    ofile << i;
    ofile.close();

    ifstream myfile("num.txt");
    myfile >> num;
    myfile.close();

    int number = (int)num;
    number++;

    ofstream myfile1("num.txt");
    myfile1 << (char)number;
    myfile1.close();

    if (num == '0')
    {
        filename = "\\live.avi";
    }
    else
    {
        filename = "\\live";
        string s = "(";
        s += num;
        s += ')';
        filename.append(s);
        filename.append(".avi");
    }
    path.append(filename);

    output.open(path, codec, 10, frame.size(), isColor);

    if (!output.isOpened()) {
        cerr << "Could not open the output video file\n";
        return -1;
    }

    time(&start);

    while (vid.read(frame))
    {
        Mat GaussBlur, res;
        vector<Mat> planes;
        split(frame, planes);

        for (int i = 0; i < 2; i++)
        {
            planes[i] = Mat::zeros(frame.size(), planes[0].type());
        }
        cv::merge(planes, res);

        GaussianBlur(res, GaussBlur, Size(5, 5), true);

        output.write(GaussBlur);

        //imshow("Cam Feed", GaussBlur);
        if (waitKey(50) == 27)
            break;

        time(&end);
        double elapsed = difftime(end, start);
        if (elapsed == 11)
        {
            break;
        }
    }
    return 0;
}



void list_dir(const char* path) {
    struct dirent* entry;
    DIR* dir = opendir(path);

    if (dir == NULL) {
        cout << "Wrong path\n";
        return;
    }
    if ((entry = readdir(dir)) == NULL)
    {
        cout << "No Recorder Videos at Present\n";
    }
    else
    {
        cout << "The Video List is as Follows: \n";
    }
    while ((entry = readdir(dir)) != NULL) {
        cout << entry->d_name << endl;
    }
    closedir(dir);
}



class loginUser
{
private:
    string username;
    string password;
    bool loginFlag = false;


public:
    loginUser()
    {
        cfi.cbSize = sizeof(cfi);
        cfi.nFont = 0;
        cfi.dwFontSize.X = 15;
        cfi.dwFontSize.Y = 40;
        cfi.FontFamily = FF_SWISS;
        cfi.FontWeight = FW_BOLD;

        wcscpy_s(cfi.FaceName, L"Cooper Black");
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
        cout << "--------------------------------The Red Channel--------------------------------\n\n";


        cout << "\n>  Hello User, Welcome to the Red Channel\n";
        cout << ">  You Should Login in order to use this App's Features!\n";
        cout << "\n>  Login Below Here!\n";
    }
    bool login()
    {
        if (loginFlag)
        {
            cout << " >>>>>>>>> OOPS! You are Logged In Already <<<<<<<<<\n";
        }
        else
        {
            cout << "      Enter the Required Credentials to Log In   \n";
        EnterU:
            cout << ">  Username: ";
            cin >> username;
            cout << "\n";
            if (username == "user")
            {
            EnterP:
                cout << ">  Password: ";
                cin >> password;
                cout << "\n";
                if (password == "password")
                {
                    cout << "\n ::::::::: Login Successful :::::::::\n";
                    loginFlag = true;
                    return loginFlag;
                }
                else
                {
                    string option;
                    cout << "!!!!!!!!!! OOPS! Password Does'nt Match !!!!!!!!!!\n";
                    cout << "    <> Wanna Try Again? <>\n    Yes or No\n";
                    cin >> option;
                    if (option == "Yes" || option == "yes" || option == "YES")
                    {
                        goto EnterP;
                    }
                    else
                    {
                        cout << "\n!!!!!!!!! Can't Login without Correct Password! Please Verify and visit Again !!!!!!!!!\n";
                        exit(10);
                    }
                }
            }
            else
            {
                string option;
                cout << "The Username Does'nt Exist\n";
                cout << "Wanna Try Again?\n Yes or No\n";
                cin >> option;
                cout << "\n";
                if (option == "Yes" || option == "yes" || option == "YES")
                {
                    goto EnterU;
                }
                else
                {
                    cout << "\n!!!!!!!!! Can't Find the Username! Please Verify and Visit again !!!!!!!!!\n";
                    exit(10);
                }
            }
        }
    }
    bool islogined()
    {
        return loginFlag;
    }
    void logout()
    {
        loginFlag = false;
        cout << "\n<<<<<<<<<<   Yay! You have been Successfully Logged out   >>>>>>>>>>\n";
        string option;
        cout << "!!!!!!!! Can't Go any further! Login if you Wanna Continue !!!!!!!! \n";
        cout << "    Do You Wanna Login Again?\n    Yes or No\n";
        cin >> option;
        cout << "\n";
        if (option == "Yes" || option == "yes" || option == "YES")
        {
            login();
        }
        else
        {
            cout << ">>>>>>>>> Thank You! Hope we see you Again <<<<<<<<<\n";
            exit(10);
        }
    }

    void features()
    {
        string save;
        cout << "\n\n %%% Please Enter the Path where you like to save your Stuff: \n";
        cout << "Note: Don't end with a \\ \n";
        cout << "Path : ";
        cin >> save;
        cout << "\n";
        const char* path = save.c_str();
        while (1)
        {
            if (loginFlag)
            {
                int option;
                cout << "\n <<<<<<<<  Enter the Option You Wanna DO:  >>>>>>>>\n";
                cout << "   (1) Record\n   (2) Show Videos \n   (3) LogOut\n   (4) exit\n";
                cin >> option;
                cout << "\n";
                switch (option)
                {
                case 1:
                    RecordVid(save);
                    break;
                case 2:
                    list_dir(path);
                    break;
                case 3:
                    logout();
                    break;
                case 4:
                    exit(10);
                    break;
                }
            }
            else
            {

            }
        }
    }
};


int main() {
    bool loginFlag;
    string opt;
    //list_dir("E:\Video");
    loginUser User;
    cout << "\n";
    loginFlag = false;
    cout << "\n       Are You an Authorized user?\n       Yes or No\n";
    cin >> opt;
    cout << "\n";
    if (opt == "Yes" || opt == "yes" || opt == "YES")
    {
        cout << "\n:::::: Awesome! Go Ahead an login!... ::::::\n";
        loginFlag = User.login();
    }
    else
    {
        cout << "!!!!!!!!! Can't Go Any Further! Login to gain Access. !!!!!!!!!\n";
    }


    if (loginFlag)
    {
        cout << ":::::::::::::: OOOH! Lets Explore the Features Ahead ::::::::::::::";
        User.features();
    }

}