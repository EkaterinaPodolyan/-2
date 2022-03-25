#include<iostream>
#include<string>
using namespace std;
/*Есть GCODE Данного формата X(value);Y(value);Z(value).
Он используется для отдачи команд микроконтроллеры, который в свою очередь управляет устройством управления.
Зачастую GCODE выполняется построчно, поэтому если в скрипте оказалась ошибка,
то только на ошибочной строке он остановится.
Дан  GCODE - выведете конечные координаты устройства.
*/
//Насколько я поняла задачу, дают нам строку, а работать надо с числами, до тех пор, пока формат записи не нарушен
/*Я не совсем поняла, каким образом должно всё остановиться в случае, если формат записи нарушен не будет.
Предположим, для этого можно использовать какое-нибудь стоп-слово. Например "HVATIT!" */
class pre_point
{
	int x_prev, y_prev, z_prev;
public:
	pre_point();
	pre_point(int, int, int);
	void SetX(int x) { this->x_prev += x; }
	void SetY(int y) { this->y_prev += y; }
	void SetZ(int z) { this->z_prev += z; }
	void print() { cout << x_prev << ' ' << y_prev << ' ' << z_prev << endl; }
};

pre_point::pre_point()
{
	x_prev = 0;
	y_prev = 0;
	z_prev = 0;
}

pre_point::pre_point(int x_prev, int y_prev, int z_prev)
{
	this->x_prev = x_prev;
	this->y_prev = y_prev;
	this->z_prev = z_prev;
}


bool prevraschalka(string s, int& x, int& y, int& z)
{
	x = 0; y = 0; z = 0;
	//выковыриваем Х
	int koef = 1;
	int index = 0;
	if (s[index] != 'X') { return false; }
	else { index++; }
	if (s[index] == '-') { index++; koef = -1; }
	while (s[index] < 58 && s[index]>47)
	{
		x = x * 10 + int(s[index]) - int('0');
		index++;
	}
	x *= koef;
	if (s[index] != ';') { return false; }
	else { index++; }
	//теперь Y
	if (s[index] != 'Y') { return false; }
	else { index++; }
	koef = 1;
	if (s[index] == '-') { index++; koef = -1; }
	while (s[index] < 58 && s[index]>47)
	{
		y = y * 10 + int(s[index]) - int('0');
		++index;
	}
	y *= koef;
	if (s[index] != ';') { return false; }
	else { index++; }
	//и, наконец, Z
	if (s[index] != 'Z') { return false; }
	else { index++; }
	koef = 1;
	if (s[index] == '-') { index++;  koef = -1; }
	while (s[index] < 58 && s[index]>47)
	{
		z = z * 10 + int(s[index]) - int('0');
		index++;
	}
	z *= koef;
	if (s[index] != ';') { return false; }
	else { return true; }
}

int main() {
	setlocale(LC_ALL, "rus");
	/*насколько я понимаю, первая строчка - исходное положение, и, поскольку она записана в другом формате,
значит её запрашивают отдельно. Обозначу ее x_prev, y_prev, z_prev;
*/
	int x_prev, y_prev, z_prev;
	cout << "введите координаты исходного положения: " << endl << "x = ";
	cin >> x_prev;
	cout << endl << "y = ";
	cin >> y_prev;
	cout << endl << "z = ";
	cin >> z_prev;
	pre_point prev(x_prev, y_prev, z_prev);
	cout << endl;

	int x = 0, y = 0, z = 0;
	//теперь вводим GCODE. Для этого заведем массив  строк
	int i = 0;
	string str;
	while (1) {
		cout << "введите GCODE в формате X(value);Y(value);Z(value);" << endl;
		//поскольку запись без пробелов, считаем ее cin -ом
		cin >> str;
		if (str == "HVATIT!")
		{
			prev.print(); 
			return 0;
		}
		/*координаты в числовом эквиваленте после функции-превращалки*/
		if (prevraschalka(str, x, y, z))
		{
			prev.SetX(x);
			prev.SetY(y);
			prev.SetZ(z);
		}
		if (!prevraschalka(str, x, y, z)) 
		{ 
		cout << endl << endl; 
		prev.print(); 
		cout << "ERROR SCRIPT" << endl; 
		return 0; 
		}
	}
}
