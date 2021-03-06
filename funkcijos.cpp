#include "funkcijos.h"
#include "strukturos.h"
#include "outputai.h"

// Funkcijos, reikalingos sort veikimui. Palyginami vidurkiai, vardai, pavardes
bool compareAVG(studentas_sort* a, studentas_sort* b) { return a->vidurkiai < b->vidurkiai; };

// 2 stratedijos igyvendinimo dalis. Funkcija grazina tuos listo elementus, kuriu vidurkis mazesnis nei 5
bool listo_salyga(const studentas_sort& listas)
{
	return listas.vidurkiai < 5;
}

// Funkcija, skaiciuojanti galutines medianos reiksmes
double medianos_skaiciavimas(int egr, std::list<int> nd_rez)
{
	std::vector<double> eilute;
	for (auto const& i : eilute) {
		eilute.push_back(i);
	}

	eilute.push_back(egr);

	if (eilute.size() % 2 == 0)
	{
		return (eilute[eilute.size() / 2 - 1] + eilute[eilute.size() / 2]) / 2;
	}
	else
	{
		return eilute[eilute.size() / 2];
	}
}

// Funkcija, skaiciuojanti vidurki ir galutini bala
double balo_skaiciavimas(int egr, std::list<int> nd_rez)
{
	double vidurkis, galutinis1;

	vidurkis = accumulate(nd_rez.begin(), nd_rez.end(), 0.000) / nd_rez.size();
	galutinis1 = (0.4 * vidurkis) + (0.6 * egr);

	return galutinis1;
}

// Funckija, irasanti vidurkiu reiksmes studentams
std::list<double> vidurkiai_funkcija(std::list<studentas> studentai)
{
	std::list<double> vidurkiai;
	for (auto const& i : studentai)
	{
		std::cout << "Skaiciuojamas vidurkis \n";
		vidurkiai.push_back(balo_skaiciavimas(i.iverciai.back(), i.iverciai));
	}

	return vidurkiai;
}

// Funckija, irasanti medianos reiksmes studentams 
std::list<double> medianos_funkcija(std::list<studentas> studentai)
{
	std::list<double> medianos;
	for (auto const& i : studentai)
	{
		std::cout << "Skaiciuojama mediana \n";
		medianos.push_back(medianos_skaiciavimas(i.iverciai.back(), i.iverciai));
	}

	return medianos;
}

// Programos testavimo funkcija
void testas_list(std::string failo_pav, int irasu_sk, int testas)
{
	std::list<studentas_sort> stud_sort;

	// Patikrinimas, ar egzistuoja norimas testuoti failas. 
	std::ifstream infile(failo_pav);
	if (infile.fail()) {
		std::cout << "KLAIDA: failas tokiu pavadinimu neegzistuoja! \n" << std::endl;
	}
	else {

		std::ifstream infile;

		auto startas = std::chrono::high_resolution_clock::now();

		// Failo nuskaitymas
		auto start1 = std::chrono::high_resolution_clock::now();

		std::list<studentas> studentai = failo_nuskaitymas(failo_pav, infile);

		auto end1 = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> diff = end1 - start1;

		std::cout << "Failo is " << irasu_sk << " irasu nuskaitymas laikas " << diff.count() << " s\n";

		// Duomenu surasymas i stud_sort lista
		for (auto const& i : studentai)
		{
			stud_sort.push_back(studentas_sort{ i.vardai, i.pavardes, balo_skaiciavimas(i.iverciai.back(), i.iverciai) ,  medianos_skaiciavimas(i.iverciai.back(), i.iverciai) });
		}

		// Issrusiuojama didejimo tvarka
		auto start2 = std::chrono::high_resolution_clock::now();

		stud_sort.sort(CompareAvg());

		auto end2 = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> diff1 = end2 - start2;

		std::cout << "Failo is " << irasu_sk << " irasu isrusiavimo didejimo tvarka laikas " << diff1.count() << " s\n";

		//Suskirstoma dvi grupes: i nuskriaustuosius ir galvocius. Nuskriaustieji perkeliami i kita lista, istrinami is stud_sort

		std::list<nuskriaustieji> nus;

		auto start3 = std::chrono::high_resolution_clock::now();

		for (auto& it : stud_sort) {
			if (it.vidurkiai < 5)
			{
				nus.push_back(nuskriaustieji{ it.vardai, it.pavardes, it.vidurkiai });
			}
		}

		stud_sort.remove_if(listo_salyga);

		auto end3 = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> diff2 = end3 - start3;

		std::cout << "Failo is " << irasu_sk << " irasu padalijimo i dvi grupes laikas " << diff2.count() << " s\n";

		//Rasymas i faila nuskriaustuju
		auto start4 = std::chrono::high_resolution_clock::now();
		rasymas_i_faila_nuskriaustieji(nus, "nuskriaustieji.txt");
		auto end4 = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> diff3 = end4 - start4;

		std::cout << "Failo is " << irasu_sk << " Nuskriaustuju irasymo laikas " << diff3.count() << " s\n";

		//Rasymas i faila galvociu
		auto start5 = std::chrono::high_resolution_clock::now();
		rasymas_i_faila_galvociai(stud_sort, "galvociai.txt");
		auto end5 = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> diff4 = end5 - start5;

		std::cout << "Failo is " << irasu_sk << " Galvociu irasymo laikas " << diff4.count() << " s\n";

		auto endas = std::chrono::high_resolution_clock::now();

		// Suskaiciuojamas bendras testo laikas
		std::chrono::duration<double> diff5 = endas - startas;

		std::cout << "Failo is " << irasu_sk << " Testo nr " << testas << " rezultatas " << diff5.count() << " s\n";

		std::cout << " " << std::endl;

		nus.clear();

		std::list<nuskriaustieji>().swap(nus);
		studentai.clear();
		std::list<studentas>().swap(studentai);
		stud_sort.clear();
		std::list<studentas_sort>().swap(stud_sort);
	}
}

bool isNumber(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;
	return true;
}

