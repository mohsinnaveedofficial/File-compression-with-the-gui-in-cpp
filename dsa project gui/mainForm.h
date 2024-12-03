#pragma once
#include <string>
#include <msclr/marshal.h>
#include<iostream>
#include<unordered_map>
#include<queue>
#include<fstream>
#include<string>
namespace dsaprojectgui {
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;






	class Node {
	public:
		char ch;
		int freq;
		Node* left, * right;
		Node()
		{

		}
		Node(char c, int f) {
			ch = c;
			freq = f;
			left = right = NULL;
		}


	};

	Node* getnode(Node* left, Node* right, char ch, int freq) {
		Node* newnode = new Node();
		newnode->left = left;
		newnode->right = right;
		newnode->freq = freq;
		newnode->ch = ch;
		return newnode;
	}


	struct comp
	{
		bool operator () (Node* left, Node* right)
		{
			return left->freq > right->freq;
		}
	};

	class huffman {
	public:

		double comptextsize;
		string encodeddata;
		string decodestring;
		huffman() {
			comptextsize = 0;
		}
		void encode(Node* root, string str, unordered_map<char, string>& huffman) {

			if (root == NULL) {
				return;
			}
			if (!root->left && !root->right) {
				huffman[root->ch] = str;
			}

			encode(root->left, str + "0", huffman);
			encode(root->right, str + "1", huffman);


		}
		void decocde(Node* root, int& index, string str) {

			if (root == NULL) {
				return;
			}

			if (!root->left && !root->right) {
				decodestring += root->ch;

			}
			index++;
			if (str[index] == '0') {
				decocde(root->left, index, str);
			}
			else {
				decocde(root->right, index, str);
			}


		}


		void BuildHuffman(string text) {

			unordered_map<char, int>freq;
			for (auto ch : text)
			{
				freq[ch]++;
			}

			priority_queue<Node*, vector<Node*>, comp> pq;
			for (auto pair : freq) {
				pq.push(getnode(NULL, NULL, pair.first, pair.second));
			}


			while (pq.size() > 1) {
				Node* left = pq.top();
				pq.pop();

				Node* right = pq.top();
				pq.pop();

				int sum = left->freq + right->freq;
				pq.push(getnode(left, right, '\0', sum));

			}

			Node* root = pq.top();
			unordered_map <char, string> huffman;
			encode(root, " ", huffman);
			//cout << "Huffman code are " << endl;

			ofstream obj;
			obj.open("savedata.txt", ios::out);


			if (!obj.is_open()) {
				//cout << "Failed to open the file " << endl;
			}
			for (auto pair : huffman) {

				/*cout << pair.second << " " << pair.first << endl;*/
				encodeddata += pair.second + "   " + pair.first;
				encodeddata += "\r\n";
				obj << pair.second << " " << pair.first << endl;
			}




			for (auto pair : freq) {
				comptextsize += pair.second * huffman[pair.first].length();
			}
			/*cout << "\nThe text Orginal Size : " << orgtextsize << " bits" << endl;
			cout << "\nThe text Compressed Size : " << comptextsize << " bits" << endl;
			cout << "\nDifference in bits = " << orgtextsize - comptextsize << " bits" << endl;
			cout << "\nThe data compresed " << (comptextsize / orgtextsize) * 100 << "%" << endl;*/


			//cout << "\ndecode data" << endl;
			string str;
			for (char ch : text) {
				str += huffman[ch];
			}
			int index = 0;
			while (index < int(str.size()) - 1) {
				decocde(root, index, str);
			}




		}


	};



	class file {
	public:
		double orginalsize, compressed;
		string compressedstring;
		string decodestring;
		file() {
			orginalsize = 0.0;
			compressed = 0.0;
			compressedstring = "";
		}
		void readfile(string path) {

			ifstream obj;
			obj.open(path);
			if (!obj.is_open()) {
				//cout << "Failed to open the file " << endl;
			}
			else {
				string line;
				string text;
				while (getline(obj, line)) {
					text += line;

				}
				obj.close();
				orginalsize = text.length() * 8;
				huffman h;
				h.BuildHuffman(text);
				compressed = h.comptextsize;
				compressedstring = h.encodeddata;
				decodestring = h.decodestring;






			}


		}

	};



	

	/// <summary>
	/// Summary for mainForm
	/// </summary>
	public ref class mainForm : public System::Windows::Forms::Form
	{
	public:
		mainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~mainForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TableLayoutPanel^ tableLayoutPanel1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ orginalsizetextbox;
	private: System::Windows::Forms::TextBox^ precen;



	private: System::Windows::Forms::TextBox^ diff;

	private: System::Windows::Forms::TextBox^ compsizetextbox;
	private: System::Windows::Forms::TextBox^ encoded;
	private: System::Windows::Forms::TextBox^ decode;

	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(mainForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->precen = (gcnew System::Windows::Forms::TextBox());
			this->diff = (gcnew System::Windows::Forms::TextBox());
			this->compsizetextbox = (gcnew System::Windows::Forms::TextBox());
			this->orginalsizetextbox = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->encoded = (gcnew System::Windows::Forms::TextBox());
			this->decode = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Fax", 19.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(462, 25);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(304, 38);
			this->label1->TabIndex = 0;
			this->label1->Text = L"File Compressor";
			this->label1->Click += gcnew System::EventHandler(this, &mainForm::label1_Click);
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(53, 122);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(265, 44);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Browse File";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &mainForm::button1_Click);
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
				227)));
			this->tableLayoutPanel1->Controls->Add(this->precen, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->diff, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->compsizetextbox, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->orginalsizetextbox, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->textBox1, 0, 0);
			this->tableLayoutPanel1->Controls->Add(this->textBox3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->textBox4, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->textBox2, 0, 1);
			this->tableLayoutPanel1->Location = System::Drawing::Point(53, 218);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 4;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 41)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 32)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(447, 171);
			this->tableLayoutPanel1->TabIndex = 2;
			// 
			// precen
			// 
			this->precen->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->precen->Location = System::Drawing::Point(223, 142);
			this->precen->Name = L"precen";
			this->precen->Size = System::Drawing::Size(197, 24);
			this->precen->TabIndex = 7;
			// 
			// diff
			// 
			this->diff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->diff->Location = System::Drawing::Point(223, 101);
			this->diff->Name = L"diff";
			this->diff->Size = System::Drawing::Size(197, 24);
			this->diff->TabIndex = 6;
			// 
			// compsizetextbox
			// 
			this->compsizetextbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->compsizetextbox->Location = System::Drawing::Point(223, 52);
			this->compsizetextbox->Name = L"compsizetextbox";
			this->compsizetextbox->Size = System::Drawing::Size(197, 24);
			this->compsizetextbox->TabIndex = 5;
			// 
			// orginalsizetextbox
			// 
			this->orginalsizetextbox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->orginalsizetextbox->Location = System::Drawing::Point(223, 3);
			this->orginalsizetextbox->Name = L"orginalsizetextbox";
			this->orginalsizetextbox->Size = System::Drawing::Size(197, 24);
			this->orginalsizetextbox->TabIndex = 4;
			this->orginalsizetextbox->TextChanged += gcnew System::EventHandler(this, &mainForm::textBox5_TextChanged);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox1->Location = System::Drawing::Point(3, 3);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(196, 24);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"Orginal File Size ";
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &mainForm::textBox1_TextChanged);
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox3->Location = System::Drawing::Point(3, 101);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(196, 24);
			this->textBox3->TabIndex = 2;
			this->textBox3->Text = L"Difference";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &mainForm::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox4->Location = System::Drawing::Point(3, 142);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(196, 24);
			this->textBox4->TabIndex = 3;
			this->textBox4->Text = L"Precentage";
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->Location = System::Drawing::Point(3, 52);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(196, 24);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"Compressed File Size ";
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &mainForm::textBox2_TextChanged);
			// 
			// encoded
			// 
			this->encoded->AllowDrop = true;
			this->encoded->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->encoded->BackColor = System::Drawing::SystemColors::Window;
			this->encoded->Cursor = System::Windows::Forms::Cursors::No;
			this->encoded->ForeColor = System::Drawing::SystemColors::WindowText;
			this->encoded->Location = System::Drawing::Point(784, 170);
			this->encoded->Multiline = true;
			this->encoded->Name = L"encoded";
			this->encoded->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->encoded->Size = System::Drawing::Size(569, 518);
			this->encoded->TabIndex = 3;
			// 
			// decode
			// 
			this->decode->Cursor = System::Windows::Forms::Cursors::No;
			this->decode->Location = System::Drawing::Point(53, 483);
			this->decode->Multiline = true;
			this->decode->Name = L"decode";
			this->decode->ScrollBars = System::Windows::Forms::ScrollBars::Both;
			this->decode->Size = System::Drawing::Size(474, 172);
			this->decode->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(794, 141);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(126, 25);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Encoded Data";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 10.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(63, 455);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(129, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Decoded Data";
			// 
			// mainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->BackColor = System::Drawing::SystemColors::GradientActiveCaption;
			this->ClientSize = System::Drawing::Size(1377, 700);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->decode);
			this->Controls->Add(this->encoded);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(1395, 747);
			this->Name = L"mainForm";
			this->Text = L"mainForm";
			this->Load += gcnew System::EventHandler(this, &mainForm::mainForm_Load);
			this->tableLayoutPanel1->ResumeLayout(false);
			this->tableLayoutPanel1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void mainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) {


	}

	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ filedialog = gcnew OpenFileDialog();

		filedialog->Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
		filedialog->Title = "Please select the text file";

		if (filedialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			String^ filepath = filedialog->FileName;

			using namespace System::Runtime::InteropServices;
			IntPtr ptr = Marshal::StringToHGlobalAnsi(filepath);
			std::string stdFilePath = static_cast<char*>(ptr.ToPointer());
			Marshal::FreeHGlobal(ptr); 

			try {
				file f;
				f.readfile(stdFilePath);
				MessageBox::Show("Selected File: " + filepath);
				orginalsizetextbox->Text = f.orginalsize.ToString();
				compsizetextbox->Text = f.compressed.ToString();
				diff->Text = (f.orginalsize - f.compressed).ToString();
				precen->Text = ((f.compressed / f.orginalsize) * 100).ToString("F2") + "%";

				String^ systemcompstring = gcnew String(f.compressedstring.c_str());
				encoded->Text = systemcompstring;

				String^ systemdecodestr = gcnew String(f.decodestring.c_str());
				decode->Text = systemdecodestr;
				MessageBox::Show("The File is Saved \nC:\\Users\\Mohsin\\source\\repos\\dsa project gui\\dsa project gui\\savedata.txt");

				
			}
			catch (const std::exception& ex) {
				MessageBox::Show("Error: " + gcnew String(ex.what()));
			}
		}
		else {
			MessageBox::Show("Unable to select the file");
		}
	}


	};
	













}
