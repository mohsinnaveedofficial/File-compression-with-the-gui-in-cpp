#include "mainForm.h"
#include<iostream>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<string>
using namespace System;
using namespace System::Windows::Forms;
using namespace dsaprojectgui;
using namespace std;







[STAThread]
int main() {
    // Enable Windows Forms visual styles
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    // Run the main form
    Application::Run(gcnew mainForm());




    return 0;


}