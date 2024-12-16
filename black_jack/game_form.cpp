#include "game_form.h"

using namespace System;
using namespace System::Windows::Forms;



[STAThreadAttribute]

int main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	blackjack::game_form mainForm;
	Application::Run(% mainForm);
}