#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

struct userData {
	long long id;
	string userName;
	string password;
};

struct carsData {
	long long id;
	string name;
	string plates;
	string color;
	long long price;
	string status;
};

struct userRentCarsData {
	long long userId;
	long long countNumber;
	vector <int> listCars;
};

//Ham doi mau chu console
void SET_COLOR(int color)
{
	WORD wColor;


	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}

//Tim kiem nhi phan carIdDelete o vi tri nao trong mang carsArr va tra ve vi tri. Neu khong co tra ve -1;
int findBinaryCarsId(int carIdDelete, vector <carsData> carsArr) {
	if (carsArr.empty()) return -1;
	int first = 0;
	int last = carsArr.size() - 1;
	while (first + 1 < last) {
		int mid = (first + last) / 2;
		if (carsArr[mid].id < carIdDelete) first = mid;
		else last = mid;
	}

	if ((carsArr.size() - 1 >= last) && (carsArr[last].id == carIdDelete)) return last;
	if ((carsArr.size() - 1 >= first) && (carsArr[first].id == carIdDelete)) return first;
	return - 1;
}

//Tim kiem nhi phan userId co mat trong vector userRentCarsArr hay chua? neu co tra ve vi tri nguoc lai tra ve -1;
int findBinaryUserRentCar(int userId, vector <userRentCarsData> userRentCarsArr) {
	if (userRentCarsArr.empty()) return -1;

	int first = 0;
	int last = userRentCarsArr.size() - 1;
	while (first + 1 < last) {
		int mid = (first + last) / 2;
		if (userRentCarsArr[mid].userId < userId) first = mid;
		else last = mid;
	}

	if ((userRentCarsArr.size()-1 >= last) && (userRentCarsArr[last].userId == userId)) return last;
	if ((userRentCarsArr.size()-1 >= first) && (userRentCarsArr[first].userId == userId)) return first;
	return -1;
}

//neu user input la kieu int return true nguoc lai return false;
bool checkUserInput(string userInput) {
	
	while (userInput.length() > 0 && userInput[0] == ' ') userInput.erase(0, 1);
	while (userInput.length() > 0 && userInput[userInput.length() - 1] == ' ') userInput.erase(userInput.length() - 1, userInput.length());

	if (userInput.length() == 0) return false;

	int userInputLength = userInput.length() - 1;
	for (int i = 0; i <= userInputLength; i++) {
		if (userInput[i] < '0' || userInput[i] > '9') return false;
	}

	return true;
}

//Chuyen doi string tu nguoi nhap qua so nguyen;
long long convertNumber(string userInput) {
	while (userInput.length() > 0 && userInput[0] == ' ') userInput.erase(0, 1);
	while (userInput.length() > 0 && userInput[userInput.length() - 1] == ' ') userInput.erase(userInput.length() - 1, userInput.length());
	while (userInput.length() > 0 && userInput[0] == '0') userInput.erase(0, 1);

	long long convertNumber = 0;
	int userInputLength = userInput.length() - 1;
	for (int i = 0; i <= userInputLength; i++) {
		long long userInputChar = (long long)(userInput[i]);
		convertNumber = convertNumber * 10 + (userInputChar - (long long)('0'));
	}

	return convertNumber;
}

//Chuyen doi so nguyen sang string;
string convertString(int userString) {
	if (userString == 0) return "0";
	string temp = "";
	while (userString > 0) {
		temp = char(userString % 10 + '0') + temp;
		userString = userString / 10;
	}
	return temp;
}

//Kiem tra lua chon cua nguoi dung trong khoang tu 1 -> choice;
bool checkUserChoice(string userInputLoginMenu, int choice) {
	if (convertNumber(userInputLoginMenu) > choice || convertNumber(userInputLoginMenu) <= 0) return false;
	return true;
}

//Kiem tra ten dang nhap co ton tai hay khong;
bool checkUserNameLogin(string userInput, vector <userData> userArr) {
	if (userInput.length() < 4) {
		printf("Ten dang nhap phai co it nhat 4 ki tu\n");
		return false;
	}
	for (int i = 0; i < userArr.size(); i++)
		if (userInput == userArr[i].userName) return true;
	printf("Ten dang nhap khong ton tai!\n");
	return false;
}

//Kiem tra co ton tai nguoi dung co id la userId trong vector userArr;
bool checkUserId(string userId, vector <userData> userArr) {

	for (int i = 0; i < userArr.size(); i++) {
		if (userId == userArr[i].userName) return true;
	}

	return false;
}

//Kiem tra mat khau cua userId co dung Khong;
bool checkUserPassword(string userId, string userPassword, vector <userData> userArr) {
	if (userPassword.length() < 4) {
		printf("Mat khau phai it nhat 4 ki tu!\n");
		return false;
	}
	for (int i = 0; i < userArr.size(); i++) {
		if (userId == userArr[i].userName && userPassword == userArr[i].password) return true;
	}

	printf("Mat khau bi sai!\n");
	return false;
}

//Nguoi dung nhap mat khau vao va hien dau *, tra ve 1 chuoi la mat khau nguoi dung nhap vao;
string getRenderPassword() {
	string userPassword = "";
	char userChar;

	while (1) {
		userChar = _getch();
		if ((int)(userChar) == 13) break;
		if ((int)(userChar) == 8) {
			if (userPassword.length() > 0) {
				userPassword.erase(userPassword.length() - 1, userPassword.length());
				cout << "\b";
				cout << " ";
				cout << "\b";
			} 
			continue;
		}
		userPassword = userPassword + userChar;
		cout << "*";
	}

	cout << endl;
	return userPassword;

}

//Kiem tra ten dang ki co hop le hay khong;
bool checkUserRegisterName(string userRegisterName, vector <userData> userArr) {
	if (userRegisterName.size() <= 4) {
		printf("Ten dang nhap phai dai hon 4 ki tu\n");
		return false;
	}

	for (int i = 0; i < userArr.size(); i++) {
		if (userRegisterName == userArr[i].userName) {
			printf("Ten nay da ton tai!\n");
			return false;
		}
	}
	return true;
}

//Kiem tra mat khau dang ki co hop le hay khong;
bool checkUserRegisterPassword(string userRegisterPassword) {
	if (userRegisterPassword.size() < 6) {
		printf("Mat khau phai it nhat 6 ki tu\n");
		return false;
	}
	else if (userRegisterPassword.size() > 32) {
		printf("Mat khau nhieu nhat 32 ki tu\n");
		return false;
	}
	return true;
}

//Dieu kien sort vector userArr;
bool conditionUserSort(userData user1, userData user2) {
	return user1.id < user2.id;
}

//Dieu kien sort vector carsArr;
bool conditionCarsSort(carsData car1, carsData car2) {
	return car1.id < car2.id;
}

//Dieu kien sort vector userRentCarsArr;
bool conditionUserRentCarsSort(userRentCarsData userRentCars1, userRentCarsData userRentCars2) {
	return userRentCars1.userId < userRentCars2.userId;
}

//Xem bien so xe co hop le hay khong;
bool checkCarPlatesInput(string carPlatesInput, vector <carsData> carsArr) {
	if (carPlatesInput.size() < 4) {
		printf("Bien so xe phai it nhat 4 ki tu!\n");
		printf("Moi nhap lai bien so xe: ");
		return false;
	}

	for (int i = 0; i < carsArr.size(); i++) {
		if (carPlatesInput == carsArr[i].plates) {
			printf("Bien so xe nay da ton tai!\n");
			printf("Moi nhap lai bien so xe: ");
			return false;
		}
	}
	return true;
}

//Kiem tra xe id la userInput va no phai Avaliable hay khong;
bool checkIdCars(string userInput, vector <carsData> carsArr) {
	int carIdDelete = convertNumber(userInput);

	sort(carsArr.begin(), carsArr.end(), conditionCarsSort);
	int positionCar = findBinaryCarsId(carIdDelete, carsArr);

	if (positionCar != -1 && carsArr[positionCar].status == "Avaliable") return true;
	return false;
}

//Kiem tra nguoi dung xac nhap co hop le hay khong;
bool checkUserConfirm(string userInput) {
	int numberInput = convertNumber(userInput);
	if (numberInput != 1 && numberInput != 2) return false;
	return true;
}

//Kiem tra nguoi dung tra xe co hop le hay khong;
bool checkUserReturn(string userInput, int userId, vector <userRentCarsData> userRentCarsArr) {
	int convertUserInput = convertNumber(userInput);
	int positionUser = -1;
	for (int i = 0; i < userRentCarsArr.size(); i++) {
		if (userRentCarsArr[i].userId == userId) {
			positionUser = i;
			break;
		}
	}

	for (int i = 0; i < userRentCarsArr[positionUser].countNumber; i++) {
		if (convertUserInput == userRentCarsArr[positionUser].listCars[i]) return true;
	}
	return false;
}

//Doc file userFile.txt
void readUserFile(vector <userData>& userArr) {
	fstream userFile;
	userData readFile;
	string temp;

	userFile.open("userFile.txt", ios::in);
	while (!userFile.eof()) {
		if (userFile >> readFile.id) {
			getline(userFile, temp);
			getline(userFile, readFile.userName);
			getline(userFile, readFile.password);

			userArr.push_back(readFile);
		}
		else break;
	}
	userFile.close();
}

//Doc file carsFile.txt
void readCarsFile(vector <carsData>& carsArr) {
	fstream carsFile;
	carsData readFile;
	string temp;

	carsFile.open("carsFile.txt", ios::in);
	while (!carsFile.eof()) {
		if (carsFile >> readFile.id) {
			getline(carsFile, temp);
			getline(carsFile, readFile.name);
			getline(carsFile, readFile.plates);
			getline(carsFile, readFile.color);
			carsFile >> readFile.price;
			getline(carsFile, temp);
			getline(carsFile, readFile.status);

			carsArr.push_back(readFile);
		}
		else break;
	}
	carsFile.close();
}

//Doc file userRentCars.txt
void readUserRentCarsFile(vector <userRentCarsData>& userRentCarsArr) {
	fstream userRentCarsFile;
	userRentCarsData readFile;

	userRentCarsFile.open("userRentCars.txt", ios::in);
	while (!userRentCarsFile.eof()) {
		if (userRentCarsFile >> readFile.userId) {
			userRentCarsFile >> readFile.countNumber;
			for (int i = 0; i < readFile.countNumber; i++) {
				int temp;
				userRentCarsFile >> temp;
				readFile.listCars.push_back(temp);
			}

			userRentCarsArr.push_back(readFile);
		}
		else break;
	}
	userRentCarsFile.close();
}

//Ghi lai file userFile.txt voi vector userArr;
void updateUserFile(vector <userData> userArr) {
	fstream userFile;
	
	userFile.open("userFile.txt", ios::out);
	for (int i = 0; i < userArr.size(); i++) {
		userFile << userArr[i].id << endl;
		userFile << userArr[i].userName << endl;
		if (i != userArr.size() - 1) userFile << userArr[i].password << endl;
		else userFile << userArr[i].password;
	}
	userFile.close();
}

//Ghi lai file carsFile.txt voi vector carsArr;
void updateCarsFile(vector <carsData> carsArr) {
	fstream carsFile;

	carsFile.open("carsFile.txt", ios::out);
	for (int i = 0; i < carsArr.size(); i++) {
		carsFile << carsArr[i].id << endl;
		carsFile << carsArr[i].name << endl;
		carsFile << carsArr[i].plates << endl;
		carsFile << carsArr[i].color << endl;
		carsFile << carsArr[i].price << endl;
		if (i != carsArr.size() - 1) carsFile << carsArr[i].status << endl;
		else carsFile << carsArr[i].status;
	}
	carsFile.close();
}

//Ghi lai file userRentCars.txt voi vector userRentCarsArr;
void updateUserRentCarsFile(vector <userRentCarsData> userRentCarsArr) {
	fstream userRentCarsFile;

	userRentCarsFile.open("userRentCars.txt", ios::out);
	for (int i = 0; i < userRentCarsArr.size(); i++) {
		userRentCarsFile << userRentCarsArr[i].userId << " " << userRentCarsArr[i].countNumber << " ";
		for (int j = 0; j < userRentCarsArr[i].countNumber; j++)
			if (j != userRentCarsArr[i].countNumber - 1) userRentCarsFile << userRentCarsArr[i].listCars[j] << ' ';
			else userRentCarsFile << userRentCarsArr[i].listCars[j];
		if (i != userRentCarsArr.size() - 1) userRentCarsFile << endl;
	}
	userRentCarsFile.close();
}

//ADD car;
void addCar() {
	system("cls");
	string carNameInput, carPlatesInput, carColor, carRentDay;
	vector <carsData> carsArr;
	fstream carsFile;

	//Lay du lieu tu file carsFile bo vao vector carsArr;
	readCarsFile(carsArr);
	sort(carsArr.begin(), carsArr.end(), conditionCarsSort);

	printf("Nhap thong tin xe muon them:\n");
	printf("1. Loai xe: "); getline(cin, carNameInput);
	printf("2. Bien so xe: "); getline(cin, carPlatesInput);
	while (!checkCarPlatesInput(carPlatesInput, carsArr)) {
		getline(cin, carPlatesInput);
	}
	printf("3. Mau sac: "); getline(cin, carColor);
	printf("4. Gia thue moi ngay: "); getline(cin, carRentDay);
	while (!checkUserInput(carRentDay)) {
		printf("Gia thue xe phai la so nguyen\n");
		printf("Moi nhap lai gia thue xe: "); getline(cin, carRentDay);
	}

	carsData car;
	
	car.id = -1;
	for (int i = 0; i < carsArr.size(); i++) {
		if (carsArr[i].id != i) {
			car.id = i;
			break;
		}
	}
	if (car.id == -1) car.id = carsArr.size();
	car.name = carNameInput;
	car.plates = carPlatesInput;
	car.color = carColor;
	car.price = convertNumber(carRentDay);
	car.status = "Avaliable";
	carsArr.push_back(car);

	//ghi lai danh sach xe sau khi add vao file;
	updateCarsFile(carsArr);
	
	printf("Ban da them xe thanh cong\n");
	system("pause");
}

//View car;
void viewCar() {
	system("cls");
	vector <carsData> carsArr;
	fstream carsFile;

	readCarsFile(carsArr);
	carsFile.close();
	sort(carsArr.begin(), carsArr.end(), conditionCarsSort);

	cout << "||   ";
	cout << setw(13) << left << "So xe"
		<< setw(14) << left << "Ten xe"
		<< setw(18) << left << "Bien so xe"
		<< setw(14) << left << "Mau xe"
		<< setw(19) << left << "Gia thue xe"
		<< setw(15) << left << "Trang thai xe" << "||\n";
	printf("====================================================================================================\n");

	for (int i = 0; i < carsArr.size(); i++) {
		cout << "||   ";
		cout << setw(13) << left << carsArr[i].id ;
		cout << setw(14) << left << carsArr[i].name;
		cout << setw(18) << left << carsArr[i].plates;
		cout << setw(14) << left << carsArr[i].color;
		cout << setw(19) << left << carsArr[i].price;
		cout << setw(15) << left << carsArr[i].status << "||\n";
	}
	system("pause");
}

//delete car;
void deleteCar() {
	system("cls");

	string userInput;
	vector <carsData> carsArr;
	fstream carsFile;

	readCarsFile(carsArr);
	sort(carsArr.begin(), carsArr.end(), conditionCarsSort);

	printf("Danh sach xe chua duoc thue:\n");
	cout << "||   ";
	cout << setw(13) << left << "So xe"
		<< setw(14) << left << "Ten xe"
		<< setw(18) << left << "Bien so xe"
		<< setw(14) << left << "Mau xe"
		<< setw(19) << left << "Gia thue xe"
		<< setw(15) << left << "Trang thai xe" << "||\n";
	printf("====================================================================================================\n");
	
	bool isTrue = false;
	if (carsArr.empty()) isTrue = false;
	for (int i = 0; i < carsArr.size(); i++) 
		if (carsArr[i].status == "Avaliable") {
			isTrue = true;
			cout << "||   ";
			cout << setw(13) << left << carsArr[i].id;
			cout << setw(14) << left << carsArr[i].name;
			cout << setw(18) << left << carsArr[i].plates;
			cout << setw(14) << left << carsArr[i].color;
			cout << setw(19) << left << carsArr[i].price;
			cout << setw(15) << left << carsArr[i].status << "||\n";
		}
	if (!isTrue) {
		printf("Khong co xe nao co the xoa!\n");
		system("pause");
		return;
	}

	printf("Nhap so xe ban muon xoa: "); getline(cin, userInput);
	while (!checkUserInput(userInput) || !checkIdCars(userInput, carsArr)) {
		printf("So xe nhap khong hop le!\n");
		printf("Vui long nhap lai so xe: "); getline(cin, userInput);
	}

	long long userConvertNumber = convertNumber(userInput);

	//Tim vi tri cua car tren carsArr va xoa phan tu do khoi vector;
	long long carPosDelete = findBinaryCarsId(userConvertNumber, carsArr);
	long long carIdDelete = carsArr[carPosDelete].id;
	carsArr.erase(carsArr.begin() + carPosDelete);

	//ghi lai danh sach xe sau khi xoa;
	updateCarsFile(carsArr);
	
	printf("Ban da xoa xe so %lld thanh cong!\n", carIdDelete);
	system("pause");
}

//rent car;
void rentCar(long long userId) {
	system("cls");

	vector <userRentCarsData> userRentCarsArr;
	vector <carsData> carsArr;
	fstream userRentCarsFile, carsFile;

	//lay danh sach cau truc du lieu user thue xe;
	readUserRentCarsFile(userRentCarsArr);
	
	//lay danh sach xe trong file carsFile;
	readCarsFile(carsArr);
	sort(carsArr.begin(), carsArr.end(), conditionCarsSort);

	bool isTrue = false;
	if (carsArr.empty()) isTrue = false;
	printf("Danh sach xe co the thue:\n");
	cout << "||   ";
	cout << setw(13) << left << "So xe"
		<< setw(14) << left << "Ten xe"
		<< setw(18) << left << "Bien so xe"
		<< setw(14) << left << "Mau xe"
		<< setw(19) << left << "Gia thue xe"
		<< setw(15) << left << "Trang thai xe" << "||\n";
	printf("====================================================================================================\n");

	for (int i = 0; i < carsArr.size(); i++)
		if (carsArr[i].status == "Avaliable") {
			isTrue = true;
			cout << "||   ";
			cout << setw(13) << left << carsArr[i].id;
			cout << setw(14) << left << carsArr[i].name;
			cout << setw(18) << left << carsArr[i].plates;
			cout << setw(14) << left << carsArr[i].color;
			cout << setw(19) << left << carsArr[i].price;
			cout << setw(15) << left << carsArr[i].status << "||\n";
		}
	if (!isTrue) {
		printf("Khong co xe nao co the thue!\n");
		system("pause");
		return;
	}

	string userInputCar, userInputDays;
	printf("Nhap so xe ban muon thue: "); getline(cin, userInputCar);
	while (!checkUserInput(userInputCar) || !checkIdCars(userInputCar, carsArr)) {
		printf("So xe khong hop le!\n");
		printf("Vui long nhap lai so xe: "); getline(cin, userInputCar);
	}
	printf("Nhap so ngay ban muon thue: "); getline(cin, userInputDays);
	while (!checkUserInput(userInputDays)) {
		printf("So ngay khong hop le!\n");
		printf("Vui long nhap lai so ngay: "); getline(cin, userInputDays);
	}

	long long numberCar = convertNumber(userInputCar);
	long long numberDays = convertNumber(userInputDays);
	
	//Tim vi tri cua xe numberCar trong carsArr, vi tri chac chan co vi userInput da check;
	long long positionCar = findBinaryCarsId(numberCar, carsArr);

	string userInput;
	printf("So tien ban phai tra khi thue xe %lld trong %lld ngay la: %lld\n", numberCar, numberDays, carsArr[positionCar].price*numberDays);
	printf("Ban co xac nhan thue xe ?\n");
	printf("1. Co\n");
	printf("2. Khong\n");
	printf("Nhap y kien xac nhan cua ban: "); getline(cin, userInput);
	while (!checkUserInput(userInput) || !checkUserConfirm(userInput)) {
		printf("Du lieu khong hop le!\n");
		printf("Vui long nhap lai y kien xac nhan: "); getline(cin, userInput);
	}

	long long confirmInput = convertNumber(userInput);
	if (confirmInput == 2) {
		printf("Thue xe khong thanh cong\n");
		system("pause");
		return;
	}
	else {

		//Tim vi tri user thue xe tren userRentCarsArr;
		sort(userRentCarsArr.begin(), userRentCarsArr.end(), conditionUserRentCarsSort);
		int positionUser = findBinaryUserRentCar(userId, userRentCarsArr);
			
		if (positionUser == -1) {
			userRentCarsData temp;
			temp.userId = userId;
			temp.countNumber = 1;
			temp.listCars.push_back(positionCar);
			userRentCarsArr.push_back(temp);
		}
		else {
			userRentCarsArr[positionUser].countNumber++;
			userRentCarsArr[positionUser].listCars.push_back(numberCar);
		}
		printf("Ban da thue xe thanh cong!\n");

		//ghi lai danh sach user thue xe;
		updateUserRentCarsFile(userRentCarsArr);
		
		//cap nhat lai trang thai xe;
		carsArr[positionCar].status = "Rented";

		//Ghi lai danh sach xe;
		updateCarsFile(carsArr);
	}
	system("pause");
}

//return car;
void returnCar(long long userId) {
	system("cls");
	vector <userRentCarsData> userRentCarsArr;
	vector <carsData> carsArr;
	fstream userRentCarsFile, carsFile;

	//Lay du lieu trong file userRentCars bo vao vector userRentCarsArr;
	readUserRentCarsFile(userRentCarsArr);
	sort(userRentCarsArr.begin(), userRentCarsArr.end(), conditionUserRentCarsSort);

	//lay du lieu tu file carsFile bo vao vector carsArr;
	readCarsFile(carsArr);
	sort(carsArr.begin(), carsArr.end(), conditionCarsSort);
	
	long long positionUserId = findBinaryUserRentCar(userId, userRentCarsArr);
	/*for (int i = 0; i < userRentCarsArr.size(); i++) {
		if (userId == userRentCarsArr[i].userId) {
			positionUserId = i;
			break;
		}
	}*/
	if (positionUserId == -1) {
		printf("Ban khong co xe de tra!\n");
		system("pause");
		return;
	}

	bool isTrue = false;
	if (userRentCarsArr[positionUserId].listCars.empty()) isTrue = false;
	printf("Danh sach xe ban da thue:\n");
	cout << "||   ";
	cout << setw(13) << left << "So xe"
		 << setw(14) << left << "Ten xe"
		 << setw(18) << left << "Bien so xe"
		 << setw(14) << left << "Mau xe"
		 << setw(19) << left << "Gia thue xe"
		 << setw(15) << left << "Trang thai xe" << "||\n";
	printf("====================================================================================================\n");

	for (int i = 0; i < userRentCarsArr[positionUserId].countNumber; i++) {
		long long userRentCarsId = userRentCarsArr[positionUserId].listCars[i];
		
		for(int j = 0; j<carsArr.size(); j++) 
			if (carsArr[j].id == userRentCarsId) {
				isTrue = true;
				cout << "||   ";
				cout << setw(13) << left << carsArr[j].id;
				cout << setw(14) << left << carsArr[j].name;
				cout << setw(18) << left << carsArr[j].plates;
				cout << setw(14) << left << carsArr[j].color;
				cout << setw(19) << left << carsArr[j].price;
				cout << setw(15) << left << carsArr[j].status << "||\n";
			}
	}
	if (!isTrue) {
		printf("Ban khong co xe de tra!\n");
		system("Pause");
		return;
	}

	string userInput;
	printf("Nhap so xe ma ban muon tra: "); getline(cin, userInput);
	while (!checkUserInput(userInput) || !checkUserReturn(userInput, userId, userRentCarsArr)) {
		printf("So xe khong hop le!\n");
		printf("Yeu cau nhap lai so xe: "); getline(cin, userInput);
	}


	long long carIdReturn = convertNumber(userInput);
	long long positionCarReturn = -1;
	for (int i = 0; i < userRentCarsArr[positionUserId].countNumber; i++) {
		if (carIdReturn == userRentCarsArr[positionUserId].listCars[i]) {
			positionCarReturn = i;
			break;
		}
	}
	userRentCarsArr[positionUserId].listCars.erase(userRentCarsArr[positionUserId].listCars.begin() + positionCarReturn);
	userRentCarsArr[positionUserId].countNumber--;
	if (userRentCarsArr[positionUserId].countNumber == 0) userRentCarsArr.erase(userRentCarsArr.begin() + positionUserId);

	//update lai tep userRentCars;
	updateUserRentCarsFile(userRentCarsArr);

	//cap nhat lai trang thai cua carIdReturn trong carsArr va ghi vao tep
	int positionCar = findBinaryCarsId(carIdReturn, carsArr);
	carsArr[positionCar].status = "Avaliable";
	updateCarsFile(carsArr);

	printf("Ban da tra xe thanh cong!\n");
	system("pause");
}

//Menu chinh dung de chon chuc nang;
void mainMenu(long long userId) {
	while (1) {
		system("cls");
		printf("==========================================================\n");
		printf("*       Chao mung ban den voi ung dung cho thue xe       *\n");
		printf("*                  1. Them xe                            *\n");
		printf("*                  2. Xem danh sach xe                   *\n");
		printf("*                  3. Xoa xe                             *\n");
		printf("*                  4. Thue xe                            *\n");
		printf("*                  5. Tra lai xe                         *\n");
		printf("*                  6. Dang xuat                          *\n");
		printf("==========================================================\n");

		string userInput;
		printf("Chon tinh nang ban muon thuc hien: "); getline(cin, userInput);
		while (!checkUserInput(userInput) || !checkUserChoice(userInput, 6)) {
			printf("Vui long nhap dung chuc nang: "); getline(cin, userInput);
		}
		long long userConvert = convertNumber(userInput);

		switch (userConvert) {
			case 1: {
				addCar();
				break;
			}
			case 2: {
				viewCar();
				break;
			}
			case 3: {
				deleteCar();
				break;
			}
			case 4: {
				rentCar(userId);
				break;
			}
			case 5: {
				returnCar(userId);
				break;
			}
			case 6: {
				return;
			}
			default: return;
		}
	}
}

//form dang ki tai khoan;
void userRegister() {
	system("cls");
	vector <userData> userArr;
	fstream userFile;

	readUserFile(userArr);

	string userId, userPassword;
	SET_COLOR(11);
	printf("Nhap ten dang ki: "); 
	
	SET_COLOR(7);
	getline(cin, userId);
	SET_COLOR(11);
	
	while (!checkUserRegisterName(userId, userArr)) {
		printf("Nhap lai ten dang ki: "); 
		SET_COLOR(7);
		getline(cin, userId);
		SET_COLOR(11);
	}
	printf("Nhap mat khau dang ki: "); 
	SET_COLOR(7);
	userPassword = getRenderPassword();
	SET_COLOR(11);

	while (!checkUserRegisterPassword(userPassword)) {
		printf("Nhap lai mat khau dang ki: "); 
		SET_COLOR(7);
		userPassword = getRenderPassword();
		SET_COLOR(11);
	}

	sort(userArr.begin(), userArr.end(), conditionUserSort);
	userData newUser;
	newUser.id = -1;

	for (int i = 0; i < userArr.size(); i++) {
		if (userArr[i].id != i) {
			newUser.id = i;
			break;
		}
	}

	if (newUser.id == -1) newUser.id = userArr.size();
	newUser.userName = userId;
	newUser.password = userPassword;
	userArr.push_back(newUser);

	//update lai tep userFile
	updateUserFile(userArr);
	
	SET_COLOR(2);
	printf("Dang ki thanh cong!\n");
	SET_COLOR(7);
	system("pause");
	mainMenu(newUser.id);
}

//form dang nhap;
void userLogin() {
	vector <userData> userArr;
	string userName, userPassword;
	fstream userFile;

	system("cls");

	readUserFile(userArr);

	SET_COLOR(11);
	printf("Nhap ten dang nhap: ");
	SET_COLOR(7);
	getline(cin, userName);
	SET_COLOR(11);
	while (!checkUserNameLogin(userName, userArr)) {
		printf("Vui long nhap lai ten dang nhap (bam 2 de dang ki): ");
		SET_COLOR(7);
		getline(cin, userName);
		SET_COLOR(11);
		if (checkUserInput(userName)) {
			if (convertNumber(userName) == 2) {
				userRegister();
				return;
			}
		}
	}


	int count = 4;
	printf("Nhap mat khau: ");
	SET_COLOR(7);
	userPassword = getRenderPassword();
	SET_COLOR(11);
	while (!checkUserPassword(userName, userPassword, userArr)) {
		count--;
		printf("Con %d lan nhap\n", count);
		printf("Nhap lai mat khau (bam 2 de dang ki): ");
		SET_COLOR(7);
		userPassword = getRenderPassword();
		SET_COLOR(11);
		if (checkUserInput(userPassword)) {
			if (convertNumber(userPassword) == 2) {
				userRegister();
				return;
			}
		}
		if (count == 0) return;
	}

	long long userId = -1;
	for(int i = 0; i<userArr.size(); i++)
		if (userName == userArr[i].userName) {
			userId = userArr[i].id;
			break;
		}

	if (checkUserPassword(userName, userPassword, userArr)) {
		SET_COLOR(2);
		printf("Dang nhap thanh cong!\n");
		SET_COLOR(7);
		system("pause");
		mainMenu(userId);
	}
}

//menu dung de login, register
void LoginMenu() {
	while (1) {
		system("cls");
		printf("==========================================================\n");
		printf("*       Chao mung ban den voi ung dung cho thue xe       *\n");
		printf("*                  1. Dang nhap                          *\n");
		printf("*                  2. Dang ki                            *\n");
		printf("*                  3. Thoat                              *\n");
		printf("==========================================================\n");

		string userInput;
		printf("Chon tinh nang ban muon thuc hien: "); getline(cin, userInput);
		while (!checkUserInput(userInput) || !checkUserChoice(userInput, 3)) {
			printf("Vui long nhap dung chuc nang: "); getline(cin, userInput);
		}
		long long userConvert = convertNumber(userInput);
		switch (userConvert) {
			case 1: {
				userLogin();
				break;
			}
			case 2: {
				userRegister();
				break;
			}
			case 3: {
				return;
			}
			default: return;
		}
	}
}

int main() {
	
	LoginMenu();

	return 0;
}
