#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>

using namespace std;

int menu() {
	int x;
	system("cls");
	cout << "=============== Welcome ===============\n";
	cout << "[1] - Adicionar Novo Filme\n";
	cout << "[2] - Visualizar Filmes\n";
	cout << "[3] - Buscar Filme\n";
	cout << "[4] - Editar Filme\n";
	cout << "[5] - Excluir Filme\n";
	cout << "[6] - Sair\n";
	cout << "Opcao: ";
	cin >> x;

	while ((x != 1) && (x != 2) && (x != 3) && (x != 4) && (x != 5) && (x != 6)) {
		cout << "Opcao invalida, digite novamente: ";
		cin >> x;
	}

	return x;
}

bool verificar(string Cod) {
	ifstream leer("BD.txt", ios::in);
	string filme, cod, diretor;
	leer >> filme;
	while (!leer.eof()) {
		leer >> diretor;
		leer >> cod;
		if (cod == Cod) {
			leer.close();
			return false;
		}
		leer >> filme;
	}
	leer.close();
	return true;
}

void adicionar(ofstream& es) {
	system("cls");
	string filme, cod, diretor;
	int linha = 0;

	es.open("BD.txt", ios::out | ios::app);
	cout << "Filme: ";
	cin >> filme;
	cout << "Diretor: ";
	cin >> diretor;
	cout << "ID: ";
	cin >> cod;
	if (verificar(cod))
		es << filme << " " << diretor << " " << cod << "\n";
	es.close();
}

void leitura(ifstream& Let) {
	system("cls");
	string filme, cod, diretor;
	Let.open("BD.txt", ios::in);
	if (Let.is_open()) {
		cout << "================= Data Base =================\n";
		Let >> filme;
		while (!Let.eof()) {
			Let >> diretor;
			Let >> cod;
			cout << "Nome    :" << filme << "\n";
			cout << "Diretor :" << diretor << "\n";
			cout << "ID      :" << cod << "\n";
			cout << "______________________________________________\n";
			Let >> filme;
		}

		Let.close();
	}
	else
		cout << "Erro na busca do arquivo!" << "\n";
	system("pause");
}

void buscar(ifstream& Let) {
	system("cls");
	Let.open("BD.txt", ios::in);
	string filme, diretor, cod, codeaux;
	bool encontrado = false;
	cout << "Digite o código: ";
	cin >> codeaux;
	Let >> filme;
	while (!Let.eof() && !encontrado) {
		Let >> diretor;
		Let >> cod;
		if (cod == codeaux) {
			cout << "Nome    :" << filme << "\n";
			cout << "Diretor :" << diretor << "\n";
			cout << "ID      :" << cod << "\n";
			cout << "______________________________________________\n";
			encontrado = true;
		}
		Let >> filme;
	}
	Let.close();

	if (!encontrado)
		cout << "Nao Encontrado!" << "\n";
	system("pause");
}

void editar(ifstream& Let) {
	system("cls");
	string filme, diretor, cod, codeaux, filmeaux, diretoraux;
	Let.open("BD.txt", ios::in);
	ofstream aux("auxiliar.txt", ios::out);
	if (Let.is_open()) {
		cout << "Codigo: ";
		cin >> codeaux;
		Let >> filme;
		while (!Let.eof()) {
			Let >> diretor;
			Let >> cod;
			if (cod == codeaux) {
				cout << "Novo Filme: ";
				cin >> filmeaux;
				cout << "Novo Diretor: ";
				cin >> diretoraux;
				aux << filmeaux << " " << diretoraux << " " << cod << "\n";
			}
			else {
				aux << filme << " " << diretor << " " << cod << "\n";
			}
			Let >> filme;
		}
		Let.close();
		aux.close();
	}
	else
		cout << "Falha na execucao da edicao!\n";
	remove("BD.txt");
	rename("auxiliar.txt", "BD.txt");
}

void excluir(ifstream& Let) {
	system("cls");
	string filme, diretor, cod, codeaux;
	Let.open("BD.txt", ios::in);
	ofstream aux("auxiliar.txt", ios::out);
	if (Let.is_open()) {
		cout << "Codigo: ";
		cin >> codeaux;
		Let >> filme;
		while (!Let.eof()) {
			Let >> diretor;
			Let >> cod;
			if (cod == codeaux) {
				cout << "Item Eliminado com Sucesso!\n ";
				Sleep(1500);
			}
			else {
				aux << filme << " " << diretor << " " << cod << "\n";
			}
			Let >> filme;
		}
		Let.close();
		aux.close();
	}
	else
		cout << "Falha na execucao da edicao!\n";
	remove("BD.txt");
	rename("auxiliar.txt", "BD.txt");
}

int main() {
	ofstream Esc;
	ifstream Let;
	int op;
	do {
		system("cls");
		op = menu();
		switch (op) {
		case 1:
			adicionar(Esc);
			break;
		case 2:
			leitura(Let);
			break;
		case 3:
			buscar(Let);
			break;
		case 4:
			editar(Let);
			break;
		case 5:
			excluir(Let);
			break;
		}
	} while (op != 6);

	return 0;

}