#include "outputai_v.h"
#include "funkcijos_v.h"
#include "strukturos_v.h"

void vec_atsp_rez(std::vector<std::string> vec_vardai, std::vector<std::string> vec_pavardes, std::vector<double> galutiniai)
{
	std::cout << std::setw(25) << "Vardas" << std::setw(25) << "Pavarde" << std::setw(25) << "Galutinis" << std::endl;
	std::cout << "---------------------------------------------------------------------------------\n";
	for (int i = 0; i < vec_vardai.size(); i++) {

		std::cout << std::setw(25) << vec_vardai[i] << std::setw(25) << vec_pavardes[i] << std::setw(25) << std::fixed << std::setprecision(2) << galutiniai[i] << std::endl;

	}
}

std::vector<vec_studentas> vec_failo_nuskaitymas(std::string failo_pav, std::ifstream& infile)
{
	std::vector<vec_studentas> vec_studentai;

	std::string vardas_i, pavarde_i, vardas, pavarde;

	std::vector<int> patikrinti;

	int rows = 0, cols = 0;
	std::string eilute, reiksme;

	infile.open(failo_pav);


	// while ciklas skirtas suzinoti, kiek failas turi eiluciu ir stulpeliu
	while (std::getline(infile, eilute)) {
		rows++;
		if (rows == 1)
		{
			std::stringstream ss(eilute);
			while (ss >> reiksme)
				cols++;
		}
	}
	infile.close();
	infile.open(failo_pav);

	std::string rez;
	std::vector<std::string> visi_rezultatai;

	std::getline(infile, eilute);
	// nuskaitoma likusi dokumento dalis (be etikeciu, tik duomenys)
	for (int i = 1; i < rows; i++)
	{
		infile >> vardas >> pavarde;

		for (int j = 0; j < cols - 2; j++)
		{
			infile >> rez;
			visi_rezultatai.push_back(rez);

			for (int i = 0; i < visi_rezultatai.size(); i++)
			{
				if (!vec_isNumber(visi_rezultatai[i]))
				{
					std::cout << "Klaida: faile rezultatu vietose yra raides! \n";
				}
				else
				{
					patikrinti.push_back(std::stoi(visi_rezultatai[i]));
				}
				visi_rezultatai.clear();
				std::vector<std::string>().swap(visi_rezultatai);
			}
		}
		vec_studentai.push_back(vec_studentas{ vardas, pavarde, patikrinti });
		patikrinti.clear();
		std::vector<int>().swap(patikrinti);
	}
	infile.close();


	return vec_studentai;
}


void vec_rasymas_i_faila_kursiokiai(std::vector<vec_studentas_sort> vector, std::string failo_pav)
{

	std::ofstream myfile;
	myfile.open(failo_pav);

	if (myfile.fail())
	{
		perror(nullptr);
	}
	for (int i = 0; i < 1; i++)
	{
		myfile << "Vardas" << std::setw(25) << "Pavarde" << std::setw(25) << std::fixed << std::setprecision(2) << "Galutinis(Vid.)" << std::setw(25) << std::fixed << std::setprecision(2) << "Galutinis(Med.)" << "\n";
	}
	for (int i = 0; i < vector.size(); i++)
	{

		myfile << vector[i].vec_vardai << std::setw(25) << vector[i].vec_pavardes << std::setw(25) << vector[i].vec_vidurkiai << std::setw(25) << vector[i].vec_medianos << "\n";
	}

	myfile.close();
	vector.clear();
	std::vector<vec_studentas_sort>().swap(vector);
}

void vec_rasymas_i_faila_nuskriaustieji(std::vector<vec_nuskriaustieji> nus, std::string failo_pav)
{
	std::ofstream myfile;
	myfile.open(failo_pav);
	if (myfile.fail())
	{
		perror(nullptr);
	}

	for (int i = 0; i < 1; i++)
	{
		myfile << "Vardas" << std::setw(25) << "Pavarde" << std::setw(25) << "Galutinis(Vid.)" << "\n";
	}
	for (int i = 0; i < nus.size(); i++)
	{
		myfile << nus[i].vec_vardai << std::setw(25) << nus[i].vec_pavardes << std::setw(25) << nus[i].vec_iverciai << "\n";
	}

}

void vec_rasymas_i_faila_galvociai(std::vector<vec_galvociai> gal, std::string failo_pav)
{
	std::ofstream myfile;
	myfile.open(failo_pav);
	if (myfile.fail())
	{
		perror(nullptr);
	}
	for (int i = 0; i < 1; i++)
	{
		myfile << "Vardas" << std::setw(25) << "Pavarde" << std::setw(25) << "Galutinis(Vid.)" << "\n";
	}

	for (int i = 0; i < gal.size(); i++)
	{
		myfile << gal[i].vec_vardai << std::setw(25) << gal[i].vec_pavardes << std::setw(25) << gal[i].vec_iverciai << "\n";
	}

}

void vec_failu_generavimas()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 10);

	std::vector<int> kiek_nd_rez;
	int kiek_nd;

	std::cout << "Iveskite, kiek nd ivertinimu sugeneruoti: " << std::endl;
	std::cin >> kiek_nd;
	std::cout << "Pasirinktas nd skaicius: " << kiek_nd << std::endl;

	for (int i = 1; i < kiek_nd + 1; i++)
	{
		kiek_nd_rez.push_back(i);
	}

	////1000 duomenu failo generavimas
	//std::ofstream failas1;
	//failas1.open("stud1000.txt");

	//failas1 << "Vardas" << std::setw(25) << "Pavarde";
	//for (int count = 0; count < kiek_nd; count++) {
	//	failas1 << std::setw(25) << "ND" << kiek_nd_rez[count];
	//}
	//failas1 << std::setw(25) << "EGZ" << std::endl;

	//for (int i = 1; i < 1001; i++)
	//{

	//	failas1 << "Vardas" << i << std::setw(25) << "Pavarde" << i;

	//	for (int j = 0; j < kiek_nd + 1; j++)
	//	{
	//		failas1 << std::setw(25) << dist(mt) << std::setw(25);
	//	}
	//	failas1 << "\n";
	//}
	//failas1.close();

	////10000 duomenu failo generavimas
	//std::ofstream failas2("stud10000.txt");

	//failas2 << "Vardas" << std::setw(25) << "Pavarde";
	//for (int count = 0; count < kiek_nd; count++) {
	//	failas2 << std::setw(25) << "ND" << kiek_nd_rez[count];
	//}
	//failas2 << std::setw(25) << "EGZ" << std::endl;

	//for (int i = 1; i < 10001; i++)
	//{

	//	failas2 << "Vardas" << i << std::setw(25) << "Pavarde" << i;

	//	for (int j = 0; j < kiek_nd + 1; j++)
	//	{
	//		failas2 << std::setw(25) << dist(mt) << std::setw(25);
	//	}
	//	failas2 << "\n";
	//}
	//failas2.close();

	//////100000 duomenu failo generavimas
	//std::ofstream failas3("stud100000.txt");

	//failas3 << "Vardas" << std::setw(25) << "Pavarde";
	//for (int count = 0; count < kiek_nd; count++) {
	//	failas3 << std::setw(25) << "ND" << kiek_nd_rez[count];
	//}
	//failas3 << std::setw(25) << "EGZ" << std::endl;

	//for (int i = 1; i < 100001; i++)
	//{

	//	failas3 << "Vardas" << i << std::setw(25) << "Pavarde" << i;

	//	for (int j = 0; j < kiek_nd + 1; j++)
	//	{
	//		failas3 << std::setw(25) << dist(mt) << std::setw(25);
	//	}
	//	failas3 << "\n";
	//}
	//failas3.close();

	////1000000 duomenu failo generavimas
	//std::ofstream failas4("stud1000000.txt");

	//failas4 << "Vardas" << std::setw(25) << "Pavarde";
	//for (int count = 0; count < kiek_nd; count++) {
	//	failas4 << std::setw(25) << "ND" << kiek_nd_rez[count];
	//}
	//failas4 << std::setw(25) << "EGZ" << std::endl;

	//for (int i = 1; i < 1000001; i++)
	//{

	//	failas4 << "Vardas" << i << std::setw(25) << "Pavarde" << i;

	//	for (int j = 0; j < kiek_nd + 1; j++)
	//	{
	//		failas4 << std::setw(25) << dist(mt) << std::setw(25);
	//	}
	//	failas4 << "\n";
	//}
	//failas4.close();

	//10000000 duomenu failo generavimas
	std::ofstream failas5("stud10000000.txt");

	failas5 << "Vardas" << std::setw(25) << "Pavarde";
	for (int count = 0; count < kiek_nd; count++) {
		failas5 << std::setw(25) << "ND" << kiek_nd_rez[count];
	}
	failas5 << std::setw(25) << "EGZ" << std::endl;

	for (int i = 1; i < 10000001; i++)
	{

		failas5 << "Vardas" << i << std::setw(25) << "Pavarde" << i;
		for (int j = 0; j < kiek_nd + 1; j++)
		{
			failas5 << std::setw(25) << dist(mt) << std::setw(25);
		}
		failas5 << "\n";
	}
	failas5.close();
}