#pragma once

namespace blackjack {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Collections::Generic;

    public ref class game_form : public Form {
    private:
        Random^ random;  // Добавляем Random как поле класса
        int playerScore;
        int dealerScore;
        int playerBalance;
        int currentBet;
        List<String^>^ playerCards;
        List<String^>^ dealerCards;
        List<int>^ usedCards;
        bool isAceInPlayerHand;
        bool isAceInDealerHand;

        Label^ labelPlayerScore;
        Label^ labelDealerScore;
        Label^ labelBalance;
        Label^ labelBet;
        Label^ labelPlayerCards;
        Label^ labelDealerCards;

        Button^ buttonHit;
        Button^ buttonStand;
        Button^ buttonMakeBet;

    public:
        game_form(void) {
            random = gcnew Random();  // Инициализируем Random в конструкторе
            InitializeComponent();
            InitializeGame();
        }

    protected:
        ~game_form() {}

    private:
        void InitializeComponent() {
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->BackgroundImage = System::Drawing::Image::FromFile("background.jpg");
            this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
            this->Icon = gcnew System::Drawing::Icon("icon.ico");
            this->Text = L"Blackjack Game";
            this->Size = System::Drawing::Size(575, 450);
            this->MaximizeBox = false;

            labelPlayerScore = gcnew Label();
            labelDealerScore = gcnew Label();
            labelBalance = gcnew Label();
            labelBet = gcnew Label();
            labelPlayerCards = gcnew Label();
            labelDealerCards = gcnew Label();

            buttonHit = gcnew Button();
            buttonStand = gcnew Button();
            buttonMakeBet = gcnew Button();

            SetupUI();
        }

        void SetupUI() {
            auto buttonStyle = gcnew System::Drawing::Font(L"Verdana", 10, FontStyle::Bold);
            auto labelStyle = gcnew System::Drawing::Font(L"Verdana", 12, FontStyle::Bold);
            auto borderColor = System::Drawing::Color::Goldenrod;
            auto backColor = System::Drawing::Color::DarkGreen;
            auto foreColor = System::Drawing::Color::White;

            labelPlayerScore->Text = L"Player Score: 0";
            labelPlayerScore->Location = Point(50, 50);
            labelPlayerScore->Size = System::Drawing::Size(200, 30);
            labelPlayerScore->BackColor = System::Drawing::Color::Transparent;
            labelPlayerScore->ForeColor = System::Drawing::Color::White;
            labelPlayerScore->Font = labelStyle;

            labelDealerScore->Text = L"Dealer Score: 0";
            labelDealerScore->Location = Point(50, 100);
            labelDealerScore->Size = System::Drawing::Size(200, 30);
            labelDealerScore->BackColor = System::Drawing::Color::Transparent;
            labelDealerScore->ForeColor = System::Drawing::Color::White;
            labelDealerScore->Font = labelStyle;

            labelPlayerCards->Text = L"Player Cards: ";
            labelPlayerCards->Location = Point(300, 50);
            labelPlayerCards->Size = System::Drawing::Size(400, 30);
            labelPlayerCards->BackColor = System::Drawing::Color::Transparent;
            labelPlayerCards->ForeColor = System::Drawing::Color::White;
            labelPlayerCards->Font = labelStyle;

            labelDealerCards->Text = L"Dealer Cards: ";
            labelDealerCards->Location = Point(300, 100);
            labelDealerCards->Size = System::Drawing::Size(400, 30);
            labelDealerCards->BackColor = System::Drawing::Color::Transparent;
            labelDealerCards->ForeColor = System::Drawing::Color::White;
            labelDealerCards->Font = labelStyle;

            labelBalance->Text = L"Balance: $1000";
            labelBalance->Location = Point(50, 150);
            labelBalance->Size = System::Drawing::Size(200, 30);
            labelBalance->BackColor = System::Drawing::Color::Transparent;
            labelBalance->ForeColor = System::Drawing::Color::White;
            labelBalance->Font = labelStyle;

            labelBet->Text = L"Current Bet: $0";
            labelBet->Location = Point(50, 200);
            labelBet->Size = System::Drawing::Size(200, 30);
            labelBet->BackColor = System::Drawing::Color::Transparent;
            labelBet->ForeColor = System::Drawing::Color::White;
            labelBet->Font = labelStyle;

            buttonMakeBet->Text = L"Make Bet ($100)";
            buttonMakeBet->Location = Point(50, 300);
            buttonMakeBet->Size = System::Drawing::Size(150, 40);
            buttonMakeBet->Font = buttonStyle;
            buttonMakeBet->BackColor = backColor;
            buttonMakeBet->ForeColor = foreColor;
            buttonMakeBet->FlatStyle = FlatStyle::Flat;
            buttonMakeBet->FlatAppearance->BorderColor = borderColor;
            buttonMakeBet->FlatAppearance->BorderSize = 2;
            buttonMakeBet->Click += gcnew EventHandler(this, &game_form::OnMakeBetClick);

            buttonHit->Text = L"Hit";
            buttonHit->Location = Point(250, 300);
            buttonHit->Size = System::Drawing::Size(100, 40);
            buttonHit->Font = buttonStyle;
            buttonHit->BackColor = backColor;
            buttonHit->ForeColor = foreColor;
            buttonHit->FlatStyle = FlatStyle::Flat;
            buttonHit->FlatAppearance->BorderColor = borderColor;
            buttonHit->FlatAppearance->BorderSize = 2;
            buttonHit->Click += gcnew EventHandler(this, &game_form::OnHitClick);

            buttonStand->Text = L"Stand";
            buttonStand->Location = Point(400, 300);
            buttonStand->Size = System::Drawing::Size(100, 40);
            buttonStand->Font = buttonStyle;
            buttonStand->BackColor = backColor;
            buttonStand->ForeColor = foreColor;
            buttonStand->FlatStyle = FlatStyle::Flat;
            buttonStand->FlatAppearance->BorderColor = borderColor;
            buttonStand->FlatAppearance->BorderSize = 2;
            buttonStand->Click += gcnew EventHandler(this, &game_form::OnStandClick);

            this->Controls->Add(labelPlayerScore);
            this->Controls->Add(labelDealerScore);
            this->Controls->Add(labelBalance);
            this->Controls->Add(labelBet);
            this->Controls->Add(labelPlayerCards);
            this->Controls->Add(labelDealerCards);
            this->Controls->Add(buttonMakeBet);
            this->Controls->Add(buttonHit);
            this->Controls->Add(buttonStand);

            buttonHit->Enabled = false;
            buttonStand->Enabled = false;
        }

        void InitializeGame() {
            playerBalance = 1000;
            currentBet = 0;
            playerScore = 0;
            dealerScore = 0;
            playerCards = gcnew List<String^>();
            dealerCards = gcnew List<String^>();
            usedCards = gcnew List<int>();
            isAceInPlayerHand = false;
            isAceInDealerHand = false;
        }

        int GetUniqueCard() {
            int cardIndex;
            do {
                cardIndex = random->Next(1, 14);  // Используем поле класса random вместо создания нового
            } while (usedCards->Contains(cardIndex));
            usedCards->Add(cardIndex);
            return cardIndex;
        }

        String^ GetCardName(int value) {
            array<String^>^ cardNames = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
            return cardNames[value - 1];
        }

        int GetCardValue(int cardIndex) {
            if (cardIndex == 1) return 11;
            if (cardIndex > 10) return 10;
            return cardIndex;
        }

        void DealInitialCards() {
            DealCardToPlayer();
            DealCardToDealer();
            DealCardToPlayer();
            dealerCards->Add("?");
            UpdateUI();
        }

        void DealCardToPlayer() {
            int cardIndex = GetUniqueCard();
            String^ cardName = GetCardName(cardIndex);
            playerCards->Add(cardName);

            int cardValue = GetCardValue(cardIndex);
            if (cardIndex == 1) {
                isAceInPlayerHand = true;
            }
            playerScore += cardValue;

            if (playerScore > 21 && isAceInPlayerHand) {
                playerScore -= 10;
                isAceInPlayerHand = false;
            }

            UpdateUI();
        }

        void DealCardToDealer() {
            int cardIndex = GetUniqueCard();
            String^ cardName = GetCardName(cardIndex);
            dealerCards->Add(cardName);

            int cardValue = GetCardValue(cardIndex);
            if (cardIndex == 1) {
                isAceInDealerHand = true;
            }
            dealerScore += cardValue;

            if (dealerScore > 21 && isAceInDealerHand) {
                dealerScore -= 10;
                isAceInDealerHand = false;
            }

            UpdateUI();
        }

        void UpdateUI() {
            labelPlayerScore->Text = L"Player Score: " + playerScore;
            labelDealerScore->Text = L"Dealer Score: " + dealerScore;
            labelPlayerCards->Text = L"Player Cards: " + String::Join(" ", playerCards);
            labelDealerCards->Text = L"Dealer Cards: " + String::Join(" ", dealerCards);
            labelBalance->Text = L"Balance: $" + playerBalance;
            labelBet->Text = L"Current Bet: $" + currentBet;
        }

        void OnMakeBetClick(Object^ sender, EventArgs^ e) {
            if (playerBalance >= 100) {
                currentBet += 100;
                playerBalance -= 100;
                buttonHit->Enabled = true;
                buttonStand->Enabled = true;
                buttonMakeBet->Enabled = false;
                DealInitialCards();
                UpdateUI();
            }
            else {
                MessageBox::Show(L"Insufficient funds!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void OnHitClick(Object^ sender, EventArgs^ e) {
            DealCardToPlayer();

            if (playerScore > 21) {
                MessageBox::Show(L"Bust! You lose!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
                ResetGame();
            }
            else if (playerScore == 21) {
                MessageBox::Show(L"Blackjack! You win!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
                playerBalance += (currentBet * 2.5);
                ResetGame();
            }
        }

        void OnStandClick(Object^ sender, EventArgs^ e) {
            dealerCards->RemoveAt(dealerCards->Count - 1);
            DealCardToDealer();

            while (dealerScore < 17) {
                DealCardToDealer();
            }

            if (dealerScore > 21) {
                MessageBox::Show(L"Dealer bust! You win!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
                playerBalance += currentBet * 2;
            }
            else if (playerScore > dealerScore) {
                MessageBox::Show(L"You win!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
                playerBalance += currentBet * 2;
            }
            else if (playerScore == dealerScore) {
                MessageBox::Show(L"Push!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
                playerBalance += currentBet;
            }
            else {
                MessageBox::Show(L"Dealer wins!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }

            ResetGame();
        }

        void ResetGame() {
            playerScore = 0;
            dealerScore = 0;
            currentBet = 0;
            playerCards->Clear();
            dealerCards->Clear();
            usedCards->Clear();
            isAceInPlayerHand = false;
            isAceInDealerHand = false;

            buttonHit->Enabled = false;
            buttonStand->Enabled = false;
            buttonMakeBet->Enabled = true;

            UpdateUI();

            if (playerBalance <= 0) {
                MessageBox::Show(L"Game Over! You're out of money!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
                playerBalance = 1000;
                UpdateUI();
            }
        }
    };
}