#pragma once

namespace blackjack {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class game_form : public System::Windows::Forms::Form {
	public:
		game_form(void) {
			InitializeComponent();
			System::IO::FileStream^ fs = gcnew System::IO::FileStream("icon.ico", System::IO::FileMode::Open);
			this->Icon = gcnew System::Drawing::Icon(fs); // Set the icon from the file stream
			fs->Close();
		}

	protected:
		~game_form() {
			if (components) {
				delete components;
			}
		}

	private:
		System::Windows::Forms::Label^ labelDealerCards;
		System::Windows::Forms::Label^ labelBet;
		System::Windows::Forms::Label^ labelPlayerCards;
		System::Windows::Forms::Button^ buttonDouble;
		System::Windows::Forms::Button^ buttonHit;
		System::Windows::Forms::Button^ buttonMakeBet;
		System::Windows::Forms::Button^ buttonStand;
		System::Windows::Forms::Panel^ gamePanel;
		System::Windows::Forms::Label^ main_label;
		System::Windows::Forms::Button^ check_balance_button;
		System::Windows::Forms::Button^ start_button;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void) {
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->main_label = (gcnew System::Windows::Forms::Label());
			this->check_balance_button = (gcnew System::Windows::Forms::Button());
			this->start_button = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// main_label
			// 
			this->main_label->AutoSize = true;
			this->main_label->Font = (gcnew System::Drawing::Font(L"Arial", 36, System::Drawing::FontStyle::Bold));
			this->main_label->Location = System::Drawing::Point(170, 62);
			this->main_label->Name = L"main_label";
			this->main_label->Size = System::Drawing::Size(587, 84);
			this->main_label->TabIndex = 0;
			this->main_label->Text = L"Blackjack Game";
			this->main_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// check_balance_button
			// 
			this->check_balance_button->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->check_balance_button->Location = System::Drawing::Point(320, 300);
			this->check_balance_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->check_balance_button->Name = L"check_balance_button";
			this->check_balance_button->Size = System::Drawing::Size(225, 62);
			this->check_balance_button->TabIndex = 1;
			this->check_balance_button->Text = L"Check Balance";
			this->check_balance_button->UseVisualStyleBackColor = true;
			this->check_balance_button->Click += gcnew System::EventHandler(this, &game_form::check_balance_button_Click);
			// 
			// start_button
			// 
			this->start_button->Font = (gcnew System::Drawing::Font(L"Arial", 12, System::Drawing::FontStyle::Bold));
			this->start_button->Location = System::Drawing::Point(320, 400);
			this->start_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->start_button->Name = L"start_button";
			this->start_button->Size = System::Drawing::Size(225, 62);
			this->start_button->TabIndex = 2;
			this->start_button->Text = L"Start Game";
			this->start_button->UseVisualStyleBackColor = true;
			this->start_button->Click += gcnew System::EventHandler(this, &game_form::start_button_Click);
			// 
			// game_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(920, 768);
			this->Controls->Add(this->main_label);
			this->Controls->Add(this->check_balance_button);
			this->Controls->Add(this->start_button);
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"game_form";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"BlackJack Game";
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private:
		void InitializeGamePanel() {
			// Создаем панель для игры
			this->gamePanel = gcnew System::Windows::Forms::Panel();
			this->gamePanel->Size = System::Drawing::Size(this->ClientSize.Width, this->ClientSize.Height); // Размер панели - на весь экран
			this->gamePanel->Location = System::Drawing::Point(0, 0);
			this->gamePanel->BackgroundImage = System::Drawing::Image::FromFile("background.jpg");
			this->gamePanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;// Панель начинается с верхнего левого угла
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimumSize = System::Drawing::Size(this->Width, this->Height);
			this->MaximumSize = System::Drawing::Size(this->Width, this->Height);
			this->Controls->Add(this->gamePanel); // Добавляем панель на форму

			// Создаем элементы внутри gamepanel
			this->labelDealerCards = (gcnew System::Windows::Forms::Label());
			this->labelBet = (gcnew System::Windows::Forms::Label());
			this->labelPlayerCards = (gcnew System::Windows::Forms::Label());
			this->buttonDouble = (gcnew System::Windows::Forms::Button());
			this->buttonHit = (gcnew System::Windows::Forms::Button());
			this->buttonStand = (gcnew System::Windows::Forms::Button());
			this->buttonMakeBet = (gcnew System::Windows::Forms::Button());

			// Устанавливаем размеры и расположение элементов относительно панели

			// labelDealerCards
			this->labelDealerCards->AutoSize = true;
			this->labelDealerCards->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->labelDealerCards->Location = System::Drawing::Point(20, 20);
			this->labelDealerCards->Text = L"Dealer's Cards";
			this->labelDealerCards->BackColor = System::Drawing::Color::Transparent;

			// labelBet
			this->labelBet->AutoSize = true;
			this->labelBet->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->labelBet->Location = System::Drawing::Point(440, 300); // Небольшой отступ вниз от предыдущей метки
			this->labelBet->Text = L"Your Bet: $$$";
			this->labelBet->BackColor = System::Drawing::Color::Transparent;

			// labelPlayerCards
			this->labelPlayerCards->AutoSize = true;
			this->labelPlayerCards->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->labelPlayerCards->Location = System::Drawing::Point(20, 350); // Небольшой отступ вниз
			this->labelPlayerCards->Text = L"Your Cards";
			this->labelPlayerCards->BackColor = System::Drawing::Color::Transparent;

			// buttonDouble
			this->buttonDouble->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->buttonDouble->Size = System::Drawing::Size(150, 40);
			this->buttonDouble->Location = System::Drawing::Point(20, 400);
			this->buttonDouble->Text = L"Double";
			this->buttonDouble->UseVisualStyleBackColor = true;
			this->buttonDouble->BackColor = System::Drawing::Color::LightGreen; // Цвет фона
			this->buttonDouble->ForeColor = System::Drawing::Color::White;     // Цвет текста
			this->buttonDouble->FlatStyle = System::Windows::Forms::FlatStyle::Flat; // Убирает объемный стиль
			this->buttonDouble->FlatAppearance->BorderSize = 2;  // Толщина рамки
			this->buttonDouble->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;

			// buttonHit
			this->buttonHit->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->buttonHit->Size = System::Drawing::Size(150, 40);
			this->buttonHit->Location = System::Drawing::Point(230, 400); // Размещаем рядом с предыдущей кнопкой
			this->buttonHit->Text = L"Hit";
			this->buttonHit->UseVisualStyleBackColor = true;
			this->buttonHit->BackColor = System::Drawing::Color::LightGreen; // Цвет фона
			this->buttonHit->ForeColor = System::Drawing::Color::White;     // Цвет текста
			this->buttonHit->FlatStyle = System::Windows::Forms::FlatStyle::Flat; // Убирает объемный стиль
			this->buttonHit->FlatAppearance->BorderSize = 2;  // Толщина рамки
			this->buttonHit->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;

			// buttonStand
			this->buttonStand->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->buttonStand->Size = System::Drawing::Size(150, 40);
			this->buttonStand->Location = System::Drawing::Point(440, 400); // Размещаем рядом с предыдущей кнопкой
			this->buttonStand->Text = L"Stand";
			this->buttonStand->UseVisualStyleBackColor = true;
			this->buttonStand->BackColor = System::Drawing::Color::LightGreen; // Цвет фона
			this->buttonStand->ForeColor = System::Drawing::Color::White;     // Цвет текста
			this->buttonStand->FlatStyle = System::Windows::Forms::FlatStyle::Flat; // Убирает объемный стиль
			this->buttonStand->FlatAppearance->BorderSize = 2;  // Толщина рамки
			this->buttonStand->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;

			// buttonMakeBet
			this->buttonMakeBet->Font = (gcnew System::Drawing::Font(L"Futura", 10, System::Drawing::FontStyle::Bold));
			this->buttonMakeBet->Size = System::Drawing::Size(150, 40);
			this->buttonMakeBet->Location = System::Drawing::Point(440, 325); // Размещаем рядом с предыдущей кнопкой
			buttonMakeBet->Text = L"Make Bet";
			this->buttonMakeBet->UseVisualStyleBackColor = true;
			this->buttonMakeBet->BackColor = System::Drawing::Color::LightGreen; // Цвет фона
			this->buttonMakeBet->ForeColor = System::Drawing::Color::White;     // Цвет текста
			this->buttonMakeBet->FlatStyle = System::Windows::Forms::FlatStyle::Flat; // Убирает объемный стиль
			this->buttonMakeBet->FlatAppearance->BorderSize = 2;  // Толщина рамки
			this->buttonMakeBet->FlatAppearance->BorderColor = System::Drawing::Color::DarkGreen;

			// Добавляем элементы в панель
			this->gamePanel->Controls->Add(this->labelDealerCards);
			this->gamePanel->Controls->Add(this->labelBet);
			this->gamePanel->Controls->Add(this->labelPlayerCards);
			this->gamePanel->Controls->Add(this->buttonDouble);
			this->gamePanel->Controls->Add(this->buttonHit);
			this->gamePanel->Controls->Add(this->buttonStand);
			this->gamePanel->Controls->Add(this->buttonMakeBet);//батон 123
		}


		System::Void check_balance_button_Click(System::Object^ sender, System::EventArgs^ e) {
			MessageBox::Show("Your balance is: $$$", "Balance", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}

		System::Void start_button_Click(System::Object^ sender, System::EventArgs^ e) {
			this->main_label->Visible = false;
			this->check_balance_button->Visible = false;
			this->start_button->Visible = false;
			InitializeGamePanel();
		}
	};
}
