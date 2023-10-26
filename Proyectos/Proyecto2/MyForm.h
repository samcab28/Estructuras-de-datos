#pragma once

namespace GraficaProyecto2 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ labelCodigo;
	private: System::Windows::Forms::Label^ labelNombre;
	private: System::Windows::Forms::TextBox^ textBoxCodigo;
	private: System::Windows::Forms::TextBox^ textBoxNombre;
	private: System::Windows::Forms::Button^ botonGuardar;
	private: System::Windows::Forms::Label^ label1;
	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->labelCodigo = (gcnew System::Windows::Forms::Label());
			this->labelNombre = (gcnew System::Windows::Forms::Label());
			this->textBoxCodigo = (gcnew System::Windows::Forms::TextBox());
			this->textBoxNombre = (gcnew System::Windows::Forms::TextBox());
			this->botonGuardar = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// labelCodigo
			// 
			this->labelCodigo->AutoSize = true;
			this->labelCodigo->Location = System::Drawing::Point(13, 28);
			this->labelCodigo->Name = L"labelCodigo";
			this->labelCodigo->Size = System::Drawing::Size(80, 13);
			this->labelCodigo->TabIndex = 0;
			this->labelCodigo->Text = L"Digite el codigo";
			// 
			// labelNombre
			// 
			this->labelNombre->AutoSize = true;
			this->labelNombre->Location = System::Drawing::Point(13, 100);
			this->labelNombre->Name = L"labelNombre";
			this->labelNombre->Size = System::Drawing::Size(83, 13);
			this->labelNombre->TabIndex = 1;
			this->labelNombre->Text = L"Digite el nombre";
			// 
			// textBoxCodigo
			// 
			this->textBoxCodigo->Location = System::Drawing::Point(16, 60);
			this->textBoxCodigo->Name = L"textBoxCodigo";
			this->textBoxCodigo->Size = System::Drawing::Size(142, 20);
			this->textBoxCodigo->TabIndex = 2;
			// 
			// textBoxNombre
			// 
			this->textBoxNombre->Location = System::Drawing::Point(16, 139);
			this->textBoxNombre->Name = L"textBoxNombre";
			this->textBoxNombre->Size = System::Drawing::Size(142, 20);
			this->textBoxNombre->TabIndex = 3;
			// 
			// botonGuardar
			// 
			this->botonGuardar->Location = System::Drawing::Point(16, 176);
			this->botonGuardar->Name = L"botonGuardar";
			this->botonGuardar->Size = System::Drawing::Size(75, 23);
			this->botonGuardar->TabIndex = 4;
			this->botonGuardar->Text = L"guardar";
			this->botonGuardar->UseVisualStyleBackColor = true;
			this->botonGuardar->Click += gcnew System::EventHandler(this, &MyForm::botonGuardar_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(16, 219);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 5;
			this->label1->Text = L"label1";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(397, 440);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->botonGuardar);
			this->Controls->Add(this->textBoxNombre);
			this->Controls->Add(this->textBoxCodigo);
			this->Controls->Add(this->labelNombre);
			this->Controls->Add(this->labelCodigo);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void botonGuardar_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ resp = this->textBoxCodigo -> Text + ";" + textBoxNombre->Text;
		this->label1->Text = "respuesta: " + resp;
	}
};
}

