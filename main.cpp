//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include   <stdio.h>
#include   <dos.h>

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "trayicon"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
bool WINAPI SystemRestart (DWORD mode)
{   
    BOOL ret;
    OSVERSIONINFO vi;

    vi.dwOSVersionInfoSize = sizeof(vi);
    GetVersionEx (&vi);
    if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT) {
      HANDLE hToken;
      TOKEN_PRIVILEGES tp;

      ret = FALSE;
      if (OpenProcessToken (GetCurrentProcess (),             // open access privilege list.
          TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        tp.PrivilegeCount = 1;
        LookupPrivilegeValue (NULL, SE_SHUTDOWN_NAME,       // Ask the "shutdown" LUID
                              &tp.Privileges[0].Luid);
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; // enable it
        AdjustTokenPrivileges (hToken, FALSE, &tp, 0, NULL, 0);
        ret = (GetLastError () == ERROR_SUCCESS);
      }
    }
    else
      ret = true;

    return (ret ? ExitWindowsEx (mode, 0) : false);
}


//---------------------------------------------------------------------------


void __fastcall TForm1::FormCanResize(TObject *Sender, int &NewWidth,
      int &NewHeight, bool &Resize)
{
Resize = false;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
   Image1->Transparent = true;
   Image1->Picture->Bitmap->TransparentColor = clBtnFace;

   struct  time t;

   gettime(&t);
ComboBox1->ItemIndex = t.ti_hour-1;
ComboBox3->ItemIndex = 0;
ComboBox2->ItemIndex = t.ti_min;
StatusBar1->SimpleText = "Aktualna godzina: ";
if(RadioButton1->Checked)
    GroupBox1->Caption = "O godzinie "+ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text+" wy³¹cz komputer!";
  else
if(RadioButton2->Checked)
    GroupBox1->Caption = "O godzinie "+ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text+" restartuj komputer!";
else
if(RadioButton3->Checked)
    GroupBox1->Caption = "O godzinie "+ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text+" wyloguj!";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
TDateTime dTime = Time();
if(RadioButton1->Checked)
    GroupBox1->Caption = "O godzinie "+ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text+" wy³¹cz komputer!";
  else
if(RadioButton2->Checked)
    GroupBox1->Caption = "O godzinie "+ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text+" restartuj komputer!";
else
if(RadioButton3->Checked)
    GroupBox1->Caption = "O godzinie "+ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text+" wyloguj!";
StatusBar1->SimpleText = "Aktualna godzina: "+TimeToStr(dTime);
if((CheckBox1->Checked == true ) && ((ComboBox1->Text+":"+ComboBox2->Text+":"+ComboBox3->Text)== TimeToStr(dTime)))
  {
    if(RadioButton1->Checked)
      SystemRestart(EWX_POWEROFF | EWX_SHUTDOWN | EWX_FORCE );
    else
    if(RadioButton2->Checked)
      SystemRestart(EWX_REBOOT | EWX_FORCE );
    else
    if(RadioButton3->Checked)
      SystemRestart(EWX_LOGOFF | EWX_FORCE );
  }
}
//---------------------------------------------------------------------------



