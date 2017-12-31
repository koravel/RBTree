#pragma once

#include "RBTree.h";

namespace Curse22View
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MyForm : public System::Windows::Forms::Form
	{
		#pragma region InitializePart
	public:
		MyForm(void)
		{
			createTree();
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ComboBox^  ExecuteComboBox;
	private: System::Windows::Forms::Button^  ExecuteButton;





	private: System::Windows::Forms::Label^  InsertDataLabel;
	private: System::Windows::Forms::MaskedTextBox^  DataMaskedTextBox;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		#pragma endregion

		#pragma region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->ExecuteComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->ExecuteButton = (gcnew System::Windows::Forms::Button());
			this->InsertDataLabel = (gcnew System::Windows::Forms::Label());
			this->DataMaskedTextBox = (gcnew System::Windows::Forms::MaskedTextBox());
			this->SuspendLayout();
			// 
			// ExecuteComboBox
			// 
			this->ExecuteComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->ExecuteComboBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->ExecuteComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Search", L"Insert", L"Delete" });
			this->ExecuteComboBox->Location = System::Drawing::Point(12, 680);
			this->ExecuteComboBox->Name = L"ExecuteComboBox";
			this->ExecuteComboBox->Size = System::Drawing::Size(250, 33);
			this->ExecuteComboBox->TabIndex = 1;
			// 
			// ExecuteButton
			// 
			this->ExecuteButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ExecuteButton->Location = System::Drawing::Point(268, 680);
			this->ExecuteButton->Name = L"ExecuteButton";
			this->ExecuteButton->Size = System::Drawing::Size(168, 35);
			this->ExecuteButton->TabIndex = 2;
			this->ExecuteButton->Text = L"Execute";
			this->ExecuteButton->UseVisualStyleBackColor = true;
			this->ExecuteButton->Click += gcnew System::EventHandler(this, &MyForm::ExecuteButton_Click);
			// 
			// InsertDataLabel
			// 
			this->InsertDataLabel->AutoSize = true;
			this->InsertDataLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->InsertDataLabel->Location = System::Drawing::Point(711, 688);
			this->InsertDataLabel->Name = L"InsertDataLabel";
			this->InsertDataLabel->Size = System::Drawing::Size(119, 25);
			this->InsertDataLabel->TabIndex = 7;
			this->InsertDataLabel->Text = L"Insert data:";
			// 
			// DataMaskedTextBox
			// 
			this->DataMaskedTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->DataMaskedTextBox->Location = System::Drawing::Point(836, 684);
			this->DataMaskedTextBox->Name = L"DataMaskedTextBox";
			this->DataMaskedTextBox->Size = System::Drawing::Size(160, 31);
			this->DataMaskedTextBox->TabIndex = 8;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1008, 727);
			this->Controls->Add(this->DataMaskedTextBox);
			this->Controls->Add(this->InsertDataLabel);
			this->Controls->Add(this->ExecuteButton);
			this->Controls->Add(this->ExecuteComboBox);
			this->Name = L"MyForm";
			this->Text = L"RBTree";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		#pragma endregion

		#pragma region RBTree

		RBTree* tree;

		int YNodeArrange = 50;
		int NodeRadius = 30;
		int centerCorrection = NodeRadius / 2;
		int deep;
		int* searchResult;
		
		void createTree()
		{
			tree = new RBTree();
		}

		void treeBypass(Graphics^ g, RBTree::Node* node, int XNodeArrange, int oldX)
		{
			if (node == tree->nullNode)
			{
				return;
			}

			deep++;

			bool isLeftChild = false;
			bool isRoot = node->parent == tree->nullNode;
			if(!isRoot) isLeftChild = tree->isLeftChild(node);

			int rightChildRnage;
			int x, y;

			if (isRoot)
			{
				x = XNodeArrange;
			}
			else if (isLeftChild)
			{
				x = oldX - XNodeArrange;
			}
			else
			{
				x = oldX + XNodeArrange;
			}

			y = YNodeArrange * deep;

			drawNode(g, node, x, y);
			if (!isRoot) drawLine(g, x + centerCorrection, y + centerCorrection, oldX + centerCorrection, YNodeArrange * (deep - 1) + centerCorrection);

			treeBypass(g, node->left_child, XNodeArrange / 2, x);
			treeBypass(g, node->right_child, XNodeArrange / 2, x);
			
			deep--;			
		}

		void drawNode(Graphics^ g, RBTree::Node* node, int x, int y)
		{
			if(node->isBlack)
				g->DrawEllipse(Pens::Black, x, y, NodeRadius, NodeRadius);
			else
				g->DrawEllipse(Pens::Red, x, y, NodeRadius, NodeRadius);
			
			if (node->data != tree->null)
			{
				if (searchResult != tree->null && *searchResult == *(node->data))
					g->DrawEllipse(Pens::Aqua, x, y, NodeRadius, NodeRadius);

				if(*(node->data) <= 9 && *(node->data) >= -9)
					drawString(g, Convert::ToString(*(node->data)), x + 7, y + 6);
				else if (*(node->data) <= 99 && *(node->data) >= -99)
					drawString(g, Convert::ToString(*(node->data)), x + 4, y + 6);
				else if (*(node->data) > 99 || *(node->data) < -99)
					drawString(g, Convert::ToString(*(node->data)), x, y + 6);
			}
			else drawString(g, "NIL", x, y + 4);
		}

		void drawString(Graphics^ g, String^ data, int x, int y)
		{
			System::Drawing::Font^ drawFont = gcnew System::Drawing::Font("Arial", 12);
			SolidBrush^ drawBrush = gcnew SolidBrush(Color::Black);
			PointF drawPoint = PointF((float)x, (float)y);
			g->DrawString(data, drawFont, drawBrush, drawPoint);
		}

		void drawLine(Graphics^ g, int x1, int y1, int x2, int y2)
		{
			g->DrawLine(Pens::Black, (float)x1, (float)y1, (float)x2, (float)y2);
		}

		#pragma endregion

		#pragma region ActionsPart

		bool isDraw;

		private: System::Void ExecuteButton_Click(System::Object^  sender, System::EventArgs^  e)
		{
			int vr;
			if (!Int32::TryParse(DataMaskedTextBox->Text, vr)) return;

			isDraw = true;
			switch (ExecuteComboBox->SelectedIndex)
			{
				case 0:
				{
					searchResult = tree->null;
					RBTree::Node* result = tree->searchElement(Int32::Parse(DataMaskedTextBox->Text));
					if (result->data != tree->null && *(result->data) == Int32::Parse(DataMaskedTextBox->Text)) searchResult = result->data;
					break;
				}
				case 1:
				{
					tree->insertElement(Int32::Parse(DataMaskedTextBox->Text));
					break;
				}
				case 2:
				{
					tree->deleteElement(Int32::Parse(DataMaskedTextBox->Text));
					break;
				}
				default: break;
			}

			this->Invalidate();
		}

		private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
		{
			isDraw = false;

			if (ExecuteComboBox->SelectedIndex == -1) ExecuteComboBox->SelectedIndex = 0;
		}
		private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
		{
			if (isDraw)
			{
				Graphics^ g = this->CreateGraphics();

				deep = 0;
				
				treeBypass(g, tree->root, this->Size.Width / 2, 0);
			}
		}

		#pragma endregion
	};
}

