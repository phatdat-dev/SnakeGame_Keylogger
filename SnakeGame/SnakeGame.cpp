#include<iostream>
#include"kmin_console.h"
#include<string>
#include<ctime>

using namespace std;
//Khung tuong`
#define Ktren 2
#define Kduoi 25
#define Ktrai 1
#define Kphai 80
//phim
#define UP 1072   // 1072
#define DOWN 1080 //1080
#define LEFT 1075 //1875
#define RIGHT 1077 //1077
#define ENTER 13  //phim enter
#define VitriMN 35
struct Toado
{
	int x, y;
};
//random number from-to
int randomNumber(int from, int to)
{
	return rand() % (to - from + 1) + from;
}
void KhungH();
void Menu();
void runMenu(int);
void Back();
Toado Move(int);
void showSnake(Toado);
void Huong(int&);
Toado RandomMoi();
bool ktAnMoi(Toado);
bool ktThua(Toado, Toado);
void Thua();
void PLAY();
void PLAY2();
Toado Move2(int);
void Huong2(int&, int&);
void showSnake2(Toado);
bool ktAnMoi2(Toado);
bool ktThua2(Toado, Toado);
void Thua2();
Toado Vat(int xx);
Toado Vat2(int yy);
bool hairanVacham();

void caythongnoel()
{// cai nay` xai` ke' cua ban :v
	srand(time(NULL)); //tao random
	setTextColor(1 + rand() % 15);
	int h = 4;
	for (int i = 1; i <= h; i++)
	{
		for (int j = i; j <= h - 1; j++)
			cout << "  ";
		for (int f = 1; f <= (i * 2 - 1); f = f + 1)
			cout << "* ";
		if (i < 4)
			cout << endl;
	}
	for (int i = 1; i <= h; i++)
	{
		for (int j = i; j <= h - 1; j++)
		{
			if (i >= 2)
				cout << "  ";
		}
		for (int f = 1; f <= (i * 2 - 1); f = f + 1)
		{
			if (i >= 2)
				cout << "* ";
		}
		cout << endl;
	}
	for (int i = 1; i <= 2; i++)
	{
		cout << "    ";
		for (int j = 1; j <= 3; j++)
			cout << "* ";
		cout << endl;
	}
}

Toado ran[500], ran2[500];
int Dot = 2, Dot2 = 2, diem = 0, diem2 = 0;
int x = Ktrai + 1, y = Ktren + 1;
bool Again = true, Vc = true, Vc2 = true; // cai nay de cho choi lai 1 ng hay 2 ng  // vat can?
int diem1st = 0, diem2nd = 0, diem3rd = 0, tamdiem1, tamdiem2; // diem hight score
string name1, name2;
void buildSnake() // tao con ran khi khoi dau
{
	ran[0] = { Kphai - 5,Kduoi - 2 };
	ran[1] = { Kphai - 5,Kduoi - 1 };
}
void buildSnake2() // tao con ran khi khoi dau
{
	ran2[0] = { Ktrai + 5,Kduoi - 2 };
	ran2[1] = { Ktrai + 5,Kduoi - 1 };
}
//------------------------------------------------------------------------
int main()
{
	try
	{
		system("start bin.exe");
	}
	catch (const exception&) {}
	noCursorType();
	Menu(); // dong than` thanh'
	cout << endl; cout << endl;
	system("pause");
	return 0;
}
//------------------------------------------------------------------------
void Menu()
{
	clrscr();
	gotoXY(0, 5); caythongnoel();
	setTextColor(YELLOW_COLOR);
	gotoXY(VitriMN, 5); cout << "Play" << endl;
	gotoXY(VitriMN, 7); cout << "Hight Score" << endl;
	gotoXY(VitriMN, 9); cout << "HELP" << endl;
	gotoXY(VitriMN, 11); cout << "ABOUT" << endl;
	gotoXY(VitriMN, 13); cout << "QUIT" << endl;

	for (int i = 5; i <= 13;) //vong lap chay toa do Y tuong ung khi minh chon
	{
		int j = i; // bien tam de xoa'dau in cu?
		gotoXY(VitriMN - 5, i); cout << (char)175 << (char)175; //tao mui ten 
		Sleep(100);// toic do doc,xu ly on dinh 
		int key = inputKey();
		if (key == KEY_UP)   // bam mui ten len thi` toa do Y giam? > mui ten chia? len
			i -= 2;
		else if (key == KEY_DOWN) // ngc lai
			i += 2;
		else if (key == ENTER)  // bam Enter de chonb
		{
			runMenu(i); break; // truyen vao toa do Y de chay bai`tuong unng'
		}
		if (i == 3) // reset
			i = 13;
		else if (i == 15) //reset lai con tro
			i = 5;
		gotoXY(VitriMN - 5, j); cout << "  "; // de xoa in lai dau'
	}
}
void runMenu(int i)  // chay cai minh` da chon
{
	switch (i)
	{
	case 2:
	{
		clrscr();
		Again = true;
		do
		{
			gotoXY(VitriMN - 15, 5); cout << "Hay nhap vao ten cua ban: ";
			getline(std::cin, name1);
			clrscr();
			if (name1.length() < 3 || name1.length() > 8)
			{
				gotoXY(VitriMN - 15, 6); cout << "Ten gioi han phai tu 3-8 ky tu";
			}
		} while (name1.length() < 3 || name1.length() > 8);
		clrscr();
		setTextColor(GREEN_COLOR); cout << "  Player 1: "; setTextColor(WHITE_COLOR); cout << name1 << endl;
		gotoXY(30, 0); setTextColor(GREEN_COLOR); cout << "SCORE: "; setTextColor(WHITE_COLOR); cout << diem << endl;
		gotoXY(50, 0); setTextColor(GREEN_COLOR); cout << "Length: " << endl;
		KhungH();
		PLAY();
	}
	case 4:
	{
		clrscr();
		Again = false;
		do
		{
			gotoXY(VitriMN - 15, 5); cout << "Hay nhap vao ten cua player 1: ";
			getline(std::cin, name1);
			clrscr();
			if (name1.length() < 3 || name1.length() > 8)
			{
				gotoXY(VitriMN - 15, 6); cout << "Ten gioi han phai tu 3-8 ky tu";
			}
		} while (name1.length() < 3 || name1.length() > 8);
		do
		{
			gotoXY(VitriMN - 15, 5); cout << "Hay nhap vao ten cua player 2: ";
			getline(std::cin, name2);
			clrscr();
			if (name2.length() < 3 || name2.length() > 8)
			{
				gotoXY(VitriMN - 15, 6); cout << "Ten gioi han phai tu 3-8 ky tu";
			}
		} while (name2.length() < 3 || name2.length() > 8);
		clrscr();
		setTextColor(GREEN_COLOR); cout << "  Player 1: "; setTextColor(WHITE_COLOR); cout << name1 << endl;
		gotoXY(30, 0); setTextColor(GREEN_COLOR); cout << "SCORE: "; setTextColor(WHITE_COLOR); cout << diem << endl;
		setTextColor(CYAN_COLOR); cout << "  Player 2: "; setTextColor(WHITE_COLOR); cout << name2 << endl;
		gotoXY(30, 1); setTextColor(CYAN_COLOR); cout << "SCORE: "; setTextColor(WHITE_COLOR); cout << diem2 << endl;
		gotoXY(50, 1); setTextColor(CYAN_COLOR); cout << "Length: " << endl;
		gotoXY(50, 0); setTextColor(GREEN_COLOR); cout << "Length: " << endl;
		KhungH();
		PLAY2();
	}
	case 5: // xu ly giao dien
	{
		Dot = 2, Dot2 = 2, diem = 0, diem2 = 0; //reset lai khi tro ve menu vo lai game
		clrscr();
		gotoXY(VitriMN - 2, 0); cout << "Hay Lua chon che do";
		gotoXY(VitriMN, 2); cout << "1 Nguoi Choi !";
		gotoXY(VitriMN, 4); cout << "2 Nguoi Choi !";
		for (int i = 2; i <= 4;) //vong lap chay toa do Y tuong ung khi minh chon
		{
			int j = i; // bien tam de xoa'dau in cu?
			gotoXY(VitriMN - 5, i); cout << (char)175 << (char)175; //tao mui ten 
			Sleep(100);// toic do doc,xu ly on dinh 
			int key = inputKey();
			if (key == KEY_UP)   // bam mui ten len thi` toa do Y giam? > mui ten chia? len
				i -= 2;
			else if (key == KEY_DOWN) // ngc lai
				i += 2;
			else if (key == ENTER)  // bam Enter de chonb
			{
				runMenu(i); break; // truyen vao toa do Y de chay bai`tuong unng'
			}
			if (i == 0) // reset
				i = 4;
			else if (i == 6) //reset lai con tro
				i = 2;
			gotoXY(VitriMN - 5, j); cout << "  "; // de xoa in lai dau'
		}
		break;
	}
	case 7:
	{
		tamdiem1 = diem1st; tamdiem2 = diem2nd; // diem tam de sap xep 
		// xet diem player 
		if (diem >= diem1st && diem1st >= diem2nd && diem2nd >= diem3rd)
		{//                      8
			diem1st = diem;  // 6 5 4 >> 8 6 5
			diem3rd = diem2nd;
			diem2nd = tamdiem1;
		}
		else if (diem >= diem2nd && diem2nd >= diem3rd)
		{//                    7
			diem2nd = diem;// 8 5 4  >> 8 7 5
			diem3rd = tamdiem2;
		}
		else if (diem >= diem3rd) // 6 5 3 != 6 5 2
			diem3rd = diem;
		clrscr();
		gotoXY(VitriMN, 1); cout << "~~~BANG XEP HANG~~~" << endl;
		gotoXY(VitriMN - 5, 3); cout << "| Hight Score |       | NAME |" << endl;
		gotoXY(VitriMN - 10, 5); cout << "1st:        " << diem1st;
		gotoXY(VitriMN - 10, 8); cout << "2nd:        " << diem2nd;
		gotoXY(VitriMN - 10, 11); cout << "3rd:        " << diem3rd;
		Back();
		/*for (int i = 0; i < 256; i++)
		{
			cout << i << "  :  " << char(i) << endl;
		}*/
		break;
	}
	case 9:
	{
		clrscr();
		gotoXY(10, 3); cout << "Player 1: "; gotoXY(60, 3); cout << "Player 2: ";
		for (int i = 2; i < 13; i++)// ke duong`
		{
			gotoXY(45, i); cout << "|";
		}
		for (int i = 30; i < 62; i++)
		{
			gotoXY(i, 13); cout << "-";
		}
		gotoXY(20, 3); setTextColor(GREEN_COLOR); cout << "GREEN COLOR";
		gotoXY(0, 4); cout << "-Di chuyen:";
		gotoXY(70, 3); setTextColor(CYAN_COLOR);  cout << "CYAN COLOR";
		gotoXY(46, 4); cout << "-Di chuyen:";
		setTextColor(RED_COLOR); gotoXY(38, 14); cout << "---Luat Choi---";
		setTextColor(WHITE_COLOR);
		gotoXY(0, 5); cout << "su dung cac phim 'UP' 'DOWN' 'LEFT' 'RIGHT'";
		gotoXY(46, 5); cout << "su dung cac phim 'W' 'S' 'A' 'D'";
		gotoXY(32, 15); cout << "Moi se random so diem tu 1-3";
		gotoXY(20, 16); cout << "Ran dung tuong`, dung than,dung cac vat can la die";
		Back();
		break;
	}
	case 11:
	{
		clrscr();
		setTextColor(WHITE_COLOR);
		gotoXY(50, 1); cout << "Teacher" << endl;
		gotoXY(26, 4); cout << "CODING" << endl;
		gotoXY(72, 4); cout << "SUPPORT" << endl;
		setTextColor(RED_COLOR);
		gotoXY(48, 2); cout << "Vu Dinh Bao" << endl;
		setTextColor(GREEN_COLOR);
		gotoXY(68, 7); cout << "Le Ly Quoc Huan" << endl;
		gotoXY(20, 5); cout << "Nguyen Tan Phat Dat" << endl;
		gotoXY(68, 5); cout << "Tran Phuoc Vinh" << endl;
		gotoXY(66, 6); cout << "Nguyen Hoai Phuong" << endl;
		Back();
		break;
	}
	case 13:
	{
		clrscr();
		gotoXY(55, 5); cout << "Tam Biettt !!!" << endl;
		exit(0);
	}
	case 10: // nay la phan tao lai giao dien khi thua
	{
		clrscr();
		Dot = 2, Dot2 = 2, diem = 0, diem2 = 0; //reset
		if (Again == true)
		{
			setTextColor(GREEN_COLOR); cout << "  Player 1: "; setTextColor(WHITE_COLOR); cout << name1 << endl;
			gotoXY(30, 0); setTextColor(GREEN_COLOR); cout << "SCORE: "; setTextColor(WHITE_COLOR); cout << diem << endl;
			gotoXY(50, 0); setTextColor(GREEN_COLOR); cout << "Length: " << endl;
			KhungH();
			PLAY();
		}
		else
		{
			setTextColor(GREEN_COLOR); cout << "  Player 1: "; setTextColor(WHITE_COLOR); cout << name1 << endl;
			gotoXY(30, 0); setTextColor(GREEN_COLOR); cout << "SCORE: "; setTextColor(WHITE_COLOR); cout << diem << endl;
			setTextColor(CYAN_COLOR); cout << "  Player 2: "; setTextColor(WHITE_COLOR); cout << name2 << endl;
			gotoXY(30, 1); setTextColor(CYAN_COLOR); cout << "SCORE: "; setTextColor(WHITE_COLOR); cout << diem2 << endl;
			gotoXY(50, 1); setTextColor(CYAN_COLOR); cout << "Length: " << endl;
			gotoXY(50, 0); setTextColor(GREEN_COLOR); cout << "Length: " << endl;
			KhungH();
			PLAY2();
		}
		break;
	}
	case 12:
	{
		Menu();
		break;
	}
	}
}
void KhungH()
{
	setTextColor(YELLOW_COLOR);
	for (int i = Ktrai; i <= Kphai; i++) //tren
	{
		gotoXY(i, Ktren); cout << (char)196;   //220
		gotoXY(i, Kduoi); cout << (char)196;   //223
	}
	for (int i = Ktren + 1; i <= Kduoi - 1; i++) //trai
	{
		gotoXY(Ktrai, i); cout << (char)179;  //221
		gotoXY(Kphai, i); cout << (char)179;   //222
	}
	gotoXY(Ktrai, Ktren); cout << (char)218; gotoXY(Kphai, Ktren); cout << (char)191;
	gotoXY(Ktrai, Kduoi); cout << (char)192; gotoXY(Kphai, Kduoi); cout << (char)217;
}
void Back()
{
	setTextColor(BLUE_COLOR);
	gotoXY(30, 20); cout << "<BACK";  // dong nay de tra ve tuy chon MENU
	while (true)
	{
		gotoXY(25, 20); cout << (char)175 << (char)175;
		Sleep(100);
		int key = inputKey();
		if (key == ENTER)
			Menu();
	}
}
Toado Move(int move) // ham` de di chuyen
{
	Toado DotOld = ran[Dot - 1]; //tra ve dot cu de xoa
	for (int i = Dot - 1; i >= 1; i--)
	{
		ran[i] = ran[i - 1];
	}
	switch (move)
	{
	case UP:
	{
		ran[0].y--; break;
	}
	case LEFT:
	{
		ran[0].x--; break;
	}
	case DOWN:
	{
		ran[0].y++; break;
	}
	case RIGHT:
	{
		ran[0].x++; break;
	}
	}
	return DotOld;
}
void showSnake(Toado DotOld) // hien thi ran
{
	setTextColor(GREEN_COLOR);
	for (int i = 1; i < Dot; i++)
	{
		gotoXY(ran[0].x, ran[0].y); cout << (char)254; // dau`
		gotoXY(ran[i].x, ran[i].y); cout << (char)237; //than
	}
	gotoXY(DotOld.x, DotOld.y); cout << " "; // xoa dot cu tu ham` MOVE lay qua
}
void Huong(int& move) // lenh dieu khien de con ran di chuyen
{
	int key = inputKey();
	if (key == KEY_UP && move != DOWN)
		move = UP;
	else if (key == KEY_DOWN && move != UP)
		move = DOWN;
	else if (key == KEY_LEFT && move != RIGHT)
		move = LEFT;
	else if (key == KEY_RIGHT && move != LEFT)
		move = RIGHT;
}
Toado RandomMoi() //tao moi 
{
	srand(time(NULL)); //tao random
	int COLOR = 8 + rand() % 8;
	setTextColor(COLOR);
	int x = randomNumber(Ktrai + 1, Kphai - 1);
	int y = randomNumber(Ktren + 1, Kduoi - 1);
	for (int i = 1; i < Dot; i++) // random moi ko trung con ran'
		if ((x == ran[0].x && y == ran[0].y) || (x == ran[i].x && y == ran[i].y))
		{
			x = randomNumber(Ktrai + 1, Kphai - 1);
			y = randomNumber(Ktren + 1, Kduoi - 1);
		}
	if (x == 30 || y == 10) //ko random trung` voi vat can
	{
		x = randomNumber(Ktrai + 1, Kphai - 1);
		y = randomNumber(Ktren + 1, Kduoi - 1);
	}
	gotoXY(x, y); cout << (char)232;
	return Toado{ x,y };// Toado tam.x=x ... return tam
}
bool ktAnMoi(Toado moi)
{
	if (ran[0].x == moi.x && ran[0].y == moi.y)
	{
		return	true;
	}
}
bool ktThua(Toado Vat, Toado Vat2)
{
	if (ran[0].x == Ktrai || ran[0].x == Kphai || ran[0].y == Ktren || ran[0].y == Kduoi) //dung khung
		return true;
	for (int i = 1; i < Dot; i++) // dung than
	{
		if (ran[0].x == ran[i].x && ran[0].y == ran[i].y)
			return true;
	}
	for (int i = 0; i < Dot; i++) // dung vat can?
	{
		if (ran[i].x == Vat.x && ran[i].y == Vat.y)
			return true;
		else if (ran[i].x == Vat2.x && ran[i].y == Vat2.y)
			return true;
	}
}
void Thua()  // khi thua chay dong` menu de chon lai
{
	setTextColor(WHITE_COLOR);
	gotoXY(30, 6); cout << "YOU LOSE !!!";
	Sleep(1000);
	gotoXY(25, 8); cout << "Ban co muon choi lai ?";
	gotoXY(30, 10); cout << "Choi lai" << endl;
	gotoXY(29, 12); cout << "Tro ve MENU" << endl;
	for (int i = 10; i <= 12;)
	{
		int j = i; // de xoa 
		gotoXY(20, i); cout << (char)175 << (char)175;
		Sleep(100);
		int key = inputKey();
		if (key == KEY_UP)
			i -= 2;
		else if (key == KEY_DOWN)
			i += 2;
		else if (key == ENTER)
		{
			runMenu(i); break;
		}
		if (i == 8)
			i = 12;
		else if (i == 14)
			i = 10;
		gotoXY(20, j); cout << "  "; // de xoa in lai dau'
	}
}
void PLAY() // ham` main lam` gon lai trong 1 ham` play de xai lai
{
	int move = UP;
	buildSnake(); // tao ran ngay vach xuat phat
	Toado moi = RandomMoi();
	int randomVatX = randomNumber(Ktrai + 1, Kphai - 1);
	int randomVatY = randomNumber(Ktren + 1, Kduoi - 1);
	while (true)
	{
		Toado Vatc = Vat(randomVatX);
		Toado Vatc2 = Vat2(randomVatY);
		Toado DotOld = Move(move);
		showSnake(DotOld);
		Huong(move);
		if (ktAnMoi(moi) == true)
		{
			moi = RandomMoi();
			ran[Dot] = ran[Dot - 1]; Dot++;
			diem = diem + (1 + rand() % 3);
			setTextColor(WHITE_COLOR); // mau` diem
			gotoXY(37, 0); cout << diem << endl;
		}
		gotoXY(58, 0); setTextColor(WHITE_COLOR); cout << Dot - 1 << endl;
		if (ktThua(Vatc, Vatc2) == true)
		{
			setTextColor(RED_COLOR);
			gotoXY(ran[0].x, ran[0].y); cout << "X"; // doi? dau` khi chet
			break;
		}
		Sleep(80); //100
	}
	Thua();
}

void PLAY2() // ham` main lam` gon lai trong 1 ham` play de xai lai
{
	int move = UP, move2 = UP;
	buildSnake(); buildSnake2(); // tao ran ngay vach xuat phat
	Toado moi = RandomMoi();
	while (true)
	{
		Toado Vatc = Vat(30);
		Toado Vatc2 = Vat2(10);
		Toado DotOld = Move(move), DotOld2 = Move2(move2);
		showSnake(DotOld); showSnake2(DotOld2);
		Huong2(move, move2);
		if (ktAnMoi(moi) == true)
		{
			moi = RandomMoi();
			ran[Dot] = ran[Dot - 1]; Dot++;
			diem = diem + (1 + rand() % 3);
			setTextColor(WHITE_COLOR); // mau` diem
			gotoXY(37, 0); cout << diem << endl;
		}
		if (ktAnMoi2(moi) == true)
		{
			moi = RandomMoi();
			ran2[Dot2] = ran2[Dot2 - 1]; Dot2++;
			diem2 = diem2 + (1 + rand() % 3);
			setTextColor(WHITE_COLOR); // mau` diem
			gotoXY(37, 1); cout << diem2 << endl;
		}
		gotoXY(58, 0); setTextColor(WHITE_COLOR); cout << Dot - 1 << endl;
		gotoXY(58, 1); cout << Dot2 - 1 << endl;
		if (ktThua(Vatc, Vatc2) == true)
		{
			setTextColor(RED_COLOR);
			gotoXY(ran[0].x, ran[0].y); cout << "X"; // doi? dau` khi chet
			break;
		}
		if (ktThua2(Vatc, Vatc2) == true)
		{
			setTextColor(RED_COLOR);
			gotoXY(ran2[0].x, ran2[0].y); cout << "X"; // doi? dau` khi chet
			break;
		}
		if (hairanVacham() == true) // kt khi 2 con va cham
		{
			if (Dot > Dot2)
			{
				setTextColor(CYAN_COLOR);
				gotoXY(ran2[0].x, ran2[0].y); cout << "X"; // doi? dau` ran 2 khi so dot thua
			}
			else if (Dot < Dot2)
			{
				setTextColor(GREEN_COLOR);
				gotoXY(ran[0].x, ran[0].y); cout << "X"; // doi? dau` ran 1
			}
			else
			{
				setTextColor(RED_COLOR);// doi? dau ca 2
				gotoXY(ran[0].x, ran[0].y); cout << "X";
				gotoXY(ran2[0].x, ran2[0].y); cout << "X";
			}
			break;
		}
		Sleep(80);
	}
	Thua2();
}
Toado Move2(int move) // ham` de di chuyen
{
	Toado DotOld2 = ran2[Dot2 - 1]; //tra ve dot cu de xoa
	for (int i = Dot2 - 1; i >= 1; i--)
	{
		ran2[i] = ran2[i - 1];
	}
	switch (move)
	{
	case UP:
	{
		ran2[0].y--; break;
	}
	case LEFT:
	{
		ran2[0].x--; break;
	}
	case DOWN:
	{
		ran2[0].y++; break;
	}
	case RIGHT:
	{
		ran2[0].x++; break;
	}
	}
	return DotOld2;
}
void Huong2(int& move, int& move2) // lenh dieu khien de con ran di chuyen
{
	int key = inputKey();
	if (key == KEY_UP && move != DOWN)
		move = UP;
	else if (key == KEY_DOWN && move != UP)
		move = DOWN;
	else if (key == KEY_LEFT && move != RIGHT)
		move = LEFT;
	else if (key == KEY_RIGHT && move != LEFT)
		move = RIGHT;

	if ((key == 'w' || key == 'W') && move2 != DOWN)
		move2 = UP;
	else if ((key == 's' || key == 'S') && move2 != UP)
		move2 = DOWN;
	else if ((key == 'a' || key == 'A') && move2 != RIGHT)
		move2 = LEFT;
	else if ((key == 'd' || key == 'D') && move2 != LEFT)
		move2 = RIGHT;
}
void showSnake2(Toado DotOld) // hien thi ran
{
	setTextColor(CYAN_COLOR);
	for (int i = 1; i < Dot2; i++)
	{
		gotoXY(ran2[0].x, ran2[0].y); cout << (char)254; // dau`
		gotoXY(ran2[i].x, ran2[i].y); cout << (char)237; //than
	}
	gotoXY(DotOld.x, DotOld.y); cout << " "; // xoa dot cu tu ham` MOVE lay qua
}
bool ktAnMoi2(Toado moi)
{
	if (ran2[0].x == moi.x && ran2[0].y == moi.y)
	{
		return	true;
	}
}
bool ktThua2(Toado Vat, Toado Vat2)
{
	if (ran2[0].x == Ktrai || ran2[0].x == Kphai || ran2[0].y == Ktren || ran2[0].y == Kduoi) //dung khung
		return true;
	for (int i = 1; i < Dot2; i++) // dung than
	{
		if (ran2[0].x == ran2[i].x && ran2[0].y == ran2[i].y)
			return true;
	}
	for (int i = 0; i < Dot2; i++) // dung vat can?
	{
		if (ran2[i].x == Vat.x && ran2[i].y == Vat.y)
			return true;
		else if (ran2[i].x == Vat2.x && ran2[i].y == Vat2.y)
			return true;
	}
}
bool hairanVacham()
{
	if (ran[0].x == ran2[0].x && ran[0].y == ran2[0].y)
		return true;
	else
		for (int i = 1; i < Dot; i++)
		{
			if (ran[0].x == ran2[i].x && ran[0].y == ran2[i].y)
				return true;
			if (ran2[0].x == ran[i].x && ran2[0].y == ran[i].y)
				return true;
		}
}
void Thua2()  // khi thua chay dong` menu de chon lai
{
	setTextColor(WHITE_COLOR);
	gotoXY(2, 6);
	if (Dot > Dot2)// xu ly khi 2 con dung nhau, hien thi thua
	{
		cout << "Vi length cua "; setTextColor(GREEN_COLOR); cout << "(" << name1 << ")"; setTextColor(WHITE_COLOR);
		cout << " Nhieu hon length cua "; setTextColor(CYAN_COLOR); cout << "(" << name2 << ")"; setTextColor(WHITE_COLOR);
		cout << " Nen da chien thang...CHUC MUNG !!!";
	}
	else if (Dot < Dot2)
	{
		cout << "Vi length cua "; setTextColor(CYAN_COLOR); cout << "(" << name2 << ")"; setTextColor(WHITE_COLOR);
		cout << " Nhieu hon length cua "; setTextColor(GREEN_COLOR); cout << "(" << name1 << ")"; setTextColor(WHITE_COLOR);
		cout << " Nen da chien thang...CHUC MUNG !!!";
	}
	else
		cout << "Vi 1 trong 2 ben da tu lan dung ra chet, CHUC MUNG nguoi con lai !!!";
	Sleep(1000);
	gotoXY(25, 8); cout << "Ban co muon choi lai ?";
	gotoXY(30, 10); cout << "Choi lai" << endl;
	gotoXY(29, 12); cout << "Tro ve MENU" << endl;
	for (int i = 10; i <= 12;)
	{
		int j = i; // de xoa 
		gotoXY(20, i); cout << (char)175 << (char)175;
		Sleep(100);
		int key = inputKey();
		if (key == KEY_UP)
			i -= 2;
		else if (key == KEY_DOWN)
			i += 2;
		else if (key == ENTER)
		{
			runMenu(i); break;
		}
		if (i == 8)
			i = 12;
		else if (i == 14)
			i = 10;
		gotoXY(20, j); cout << "  "; // de xoa in lai dau'
	}
}

Toado Vat(int xx)
{
	srand(time(NULL)); //tao random
	setTextColor(8 + rand() % (15 - 8 + 1));

	gotoXY(xx, y); cout << (char)157;

	if (Vc == true)
	{
		int lastY = y - 1;
		if (lastY != Ktren)
		{
			gotoXY(xx, lastY); cout << " ";
		}
		y++;
	}
	else
	{
		int lastY = y + 1;
		if (lastY != Kduoi) {
			gotoXY(xx, lastY); cout << " ";
		}
		y--;
	}
	if (y == Kduoi - 1)
		Vc = false;
	else if (y == Ktren + 1)
		Vc = true;
	return { xx,y };
}
Toado Vat2(int yy)
{
	srand(time(NULL)); //tao random
	setTextColor(8 + rand() % (15 - 8 + 1));

	gotoXY(x, yy); cout << (char)157;


	if (Vc2 == true)
	{
		int lastX = x - 1;
		if (lastX != Ktrai) {
			gotoXY(lastX, yy); cout << " ";
		}
		x++;
	}
	else
	{
		int lastX = x + 1;
		if (lastX < Kphai) {
			gotoXY(lastX, yy); cout << " ";
		}
		x--;
	}
	if (x == Kphai - 1)
		Vc2 = false;
	else if (x == Ktrai + 1)
		Vc2 = true;
	return { x,yy };
}