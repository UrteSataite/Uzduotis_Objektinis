/*
DOKUMENTACIJA
v0.2 uzduotis, realizuota naudojant std::vector tipo konteineri bei ikelta pavyzdini faila.
Pridetas duomenu skaitymas is .txt failo, realizuotas rusiavimas bei duomenu rasymas i .txt faila.
*/

#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <sstream> 

// Aprasomos trys strukturos, talpinancios kintamuosius

struct informacija
{
    std::string vardai;
    std::string pavardes;
    std::string nd1, nd2, nd3, nd4, nd5, nd6, nd7, nd8, nd9, nd10, nd11, nd12, nd13, nd14, nd15;
    std::string egz;
};

struct studentas
{
    std::string vardai;
    std::string pavardes;
    int nd1, nd2, nd3, nd4, nd5, nd6, nd7, nd8, nd9, nd10, nd11, nd12, nd13, nd14, nd15;
    int egz;
};

struct studentas_sort
{
    std::string vardai;
    std::string pavardes;
    double vidurkiai;
    double medianos;
};


double gal_rez(int egr, std::vector<double> nd_rez);
double gal_mediana(int egr, std::vector<double> nd_rez);
void atsp_rez(std::vector<std::string> vardai, std::vector<std::string> pavardes, std::vector<double> galutiniai);

// naudojama palyginimo funckija,kurios reikia sortui

bool compareV(studentas_sort& a, studentas_sort& b) { return a.vardai < b.vardai; }
bool compareP(studentas_sort& a, studentas_sort& b) { return a.pavardes < b.pavardes; }

bool isNumber(std::string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}


int main()
{
    std::ofstream myfile;
    std::fstream infile;

    int sk, egr, tmp, tmp2;

    std::vector<double> nd_rez;
    std::vector<std::string> vardai;
    std::vector<std::string> pavardes;
    std::vector<double> galutiniai;
    std::vector<double> galutiniai2;


    std::string nd1_i, nd2_i, nd3_i, nd4_i, nd5_i, nd6_i, nd7_i, nd8_i, nd9_i, nd10_i, nd11_i, nd12_i, nd13_i, nd14_i, nd15_i, egz_i;
    std::string nd1, nd2, nd3, nd4, nd5, nd6, nd7, nd8, nd9, nd10, nd11, nd12, nd13, nd14, nd15, egz;

    std::string vardas, pavarde, vardas_i, pavarde_i;

    char mv;

    int egzaminai;

    std::string opt;

    std::cout << "Ar norite nuskaityti is failo duomenis ar ivesti ? (N-nuskaityti/I-ivesti)\n";
    std::cin >> opt;

    if (opt == "N")
    {
        infile.open("studentai10000.txt");

        int k = -1;

        std::vector<studentas> studentai;
        std::vector<informacija> info;
        std::vector<std::string> patikrinimas;
        std::vector<int> patikrinti;
        int egz_rezul;

        if (infile.fail())
        {
            perror(nullptr);
            return 1;
        }
        else {

            // tikrinama, ar failo duomenys yra is tikruju skaiciai, o ne raides
            while (k != 0 && infile >> vardas_i >> pavarde_i >> nd1_i >> nd2_i >> nd3_i >> nd4_i >> nd5_i >> nd6_i >> nd7_i >> nd8_i >> nd9_i >> nd10_i >> nd11_i >> nd12_i >> nd13_i >> nd14_i >> nd15_i >> egz_i)
            {

                info.push_back(informacija{ vardas_i, pavarde_i, nd1_i, nd2_i, nd3_i, nd4_i, nd5_i, nd6_i, nd7_i, nd8_i, nd9_i, nd10_i, nd11_i, nd12_i, nd13_i, nd14_i, nd15_i, egz_i });
                k++;

            }

            while (infile >> vardas >> pavarde >> nd1 >> nd2 >> nd3 >> nd4 >> nd5 >> nd6 >> nd7 >> nd8 >> nd9 >> nd10 >> nd11 >> nd12 >> nd13 >> nd14 >> nd15 >> egz)
            {
                patikrinimas.push_back(nd1);
                patikrinimas.push_back(nd2);
                patikrinimas.push_back(nd3);
                patikrinimas.push_back(nd4);
                patikrinimas.push_back(nd5);
                patikrinimas.push_back(nd6);
                patikrinimas.push_back(nd7);
                patikrinimas.push_back(nd8);
                patikrinimas.push_back(nd9);
                patikrinimas.push_back(nd10);
                patikrinimas.push_back(nd11);
                patikrinimas.push_back(nd12);
                patikrinimas.push_back(nd13);
                patikrinimas.push_back(nd14);
                patikrinimas.push_back(nd15);
                patikrinimas.push_back(egz);

                for (int i = 0; i < patikrinimas.size(); i++)
                {
                    if (!isNumber(patikrinimas.at(i)))
                    {
                        patikrinti.push_back(0);
                    }
                    else
                    {
                        patikrinti.push_back(std::stoi(patikrinimas.at(i)));
                    }
                }

                studentai.push_back(studentas{ vardas, pavarde, patikrinti.at(0), patikrinti.at(1), patikrinti.at(2), patikrinti.at(3), patikrinti.at(4), patikrinti.at(5), patikrinti.at(6), patikrinti.at(7), patikrinti.at(8), patikrinti.at(9), patikrinti.at(10), patikrinti.at(11), patikrinti.at(12), patikrinti.at(13), patikrinti.at(14), patikrinti.at(15) });
                k++;
                patikrinimas.clear();
            }

        }

        infile.close();



        /* V0.2 ANTRAS PUNKTAS PRASIDEDA*/

        std::vector<double> nd_rezul;
        std::vector<double> egz_rez;
        std::vector<double> vidurkiai;
        std::vector<double> medianos;
        for (int i = 0; i < studentai.size(); i++)
        {

            std::cout << "SKAICIUOJAMA MEDIANA IR VIDURKIS" << "\n";
            nd_rezul.push_back(studentai[i].nd1);
            nd_rezul.push_back(studentai[i].nd2);
            nd_rezul.push_back(studentai[i].nd3);
            nd_rezul.push_back(studentai[i].nd4);
            nd_rezul.push_back(studentai[i].nd5);
            nd_rezul.push_back(studentai[i].nd6);
            nd_rezul.push_back(studentai[i].nd7);
            nd_rezul.push_back(studentai[i].nd8);
            nd_rezul.push_back(studentai[i].nd9);
            nd_rezul.push_back(studentai[i].nd10);
            nd_rezul.push_back(studentai[i].nd11);
            nd_rezul.push_back(studentai[i].nd12);
            nd_rezul.push_back(studentai[i].nd13);
            nd_rezul.push_back(studentai[i].nd14);
            nd_rezul.push_back(studentai[i].nd15);
            egz_rez.push_back(studentai[i].egz);

            vidurkiai.push_back(gal_rez(egz_rez[i], nd_rezul));

            medianos.push_back(gal_mediana(egz_rez[i], nd_rezul));
        }


        std::vector<studentas_sort> stud_rus;


        for (int i = 0; i < studentai.size(); i++)
        {
            stud_rus.push_back(studentas_sort{ studentai[i].vardai, studentai[i].pavardes, vidurkiai[i],medianos[i] });
        }

        // rusiavimas
        std::string var;
        std::cout << "Rusiuoti pagal pavardes ar vardus ? (V/P)";
        std::cin >> var;

        if (var == "V")
        {
            std::sort(stud_rus.begin(), stud_rus.end(), compareV);
        }
        else if (var == "P")
        {
            std::sort(stud_rus.begin(), stud_rus.end(), compareP);
        }

        // skaitymas i faila
        myfile.open("kursiokai.txt");

        if (myfile.fail())
        {
            perror(nullptr);
            return 1;
        }
        else
        {
            for (int i = 0; i < info.size(); i++)
            {
                myfile << "Vardas" << std::setw(25) << "Pavarde" << std::setw(25) << "Galutinis(Vid.)" << std::setw(25) << "Galutinis(Med.)" << "\n";
            }

            for (int i = 0; i < studentai.size(); i++)
            {
                myfile << stud_rus[i].vardai << std::setw(25) << stud_rus[i].pavardes << std::setw(25) << stud_rus[i].vidurkiai << std::setw(25) << stud_rus[i].medianos << "\n";
            }
        }

        myfile.close();

        /* V0.2 ANTRAS PUNKTAS PASIBAIGIA*/

    }
    else if (opt == "I")
    {


        std::cout << "Iveskite studentu skaiciu: \n";
        std::cin >> sk;

        if (sk > 0)
        {
            for (int i = 0; i < sk; i++) {

                std::cout << "Iveskite studento varda: \n";
                std::cin >> vardas;
                if (std::isdigit(vardas[i]))
                {
                    std::cout << "Klaida: vardas negali buti skaicius\n";
                }
                else {
                    vardai.push_back(vardas);

                    std::cout << "Iveskite studento pavarde: \n";
                    std::cin >> pavarde;
                    if (std::isdigit(pavarde[i]))
                    {
                        std::cout << "Klaida: pavarde negali buti skaicius \n";
                    }
                    else
                    {
                        pavardes.push_back(pavarde);

                        std::cout << "Ar balus sugeneruoti automatiskai? (T/N) \n";
                        std::string ats;
                        std::cin >> ats;

                        if (ats == "T") {

                            while (true) {

                                int max = 10;
                                srand(time(0));
                                tmp = rand() % max;
                                nd_rez.push_back(tmp);

                                std::cout << "SUGENERUOTAS NAMU DARBU BALAS  " << tmp << "\n";


                                std::cout << "Ar jau ivesti visi rezulatatai (T/N)? \n";
                                std::string tn;
                                std::cin >> tn;

                                if (tn == "T") {
                                    break;
                                }
                            }
                        }
                        else if (ats == "N") {

                            while (true) {
                                std::cout << "Iveskite namu darbu rezultatus \n";
                                std::cin >> tmp;
                                if (tmp > 0 && tmp <= 10)
                                {
                                    nd_rez.push_back(tmp);
                                    std::cout << "Ar jau ivesti visi rezulatatai (T/N)? \n";
                                    std::string tn;
                                    std::cin >> tn;

                                    if (tn == "T") {
                                        break;
                                    }
                                }
                                else {
                                    std::cout << "Klaida: rezultatas turi buti pateiktas 10-baleje sistemoje.\n";
                                }
                            }
                        }
                        else
                        {
                            std::cout << "Klaida: reikia pasirinkti T arba N";
                        }

                        std::cout << "Ar egzamino bala sugeneruoti automatiskai? (T/N) \n";
                        std::string ats2;
                        std::cin >> ats2;

                        if (ats2 == "T")
                        {
                            int max = 10;
                            srand(time(0));
                            egr = rand() % max;
                            std::cout << "SUGENERUOTAS EGZAMINO BALAS  " << egr << "\n";
                        }
                        else if (ats == "N")
                        {
                            std::cout << "Iveskite egzamino rezultata: \n";
                            std::cin >> egr;
                            if (egr < 0 || egr > 11)
                            {
                                std::cout << "Klaida: rezultatas turi buti pateiktas 10-baleje sistemoje.\n";
                            }
                        }
                        else
                        {
                            std::cout << "Klaida: reikia pasirinkti T arba N";
                        }

                        galutiniai.push_back(gal_rez(egr, nd_rez));

                        galutiniai2.push_back(gal_mediana(egr, nd_rez));

                        nd_rez.clear();

                    }

                }
            }
        }
        else {
            std::cout << "Studentu skaicius turi buti teigiamas skaicius \n";
        }
        std::cout << "Mediana ar Vidurkis (M/V): \n";
        std::cin >> mv;

        if (std::strcmp(&mv, "M"))
        {
            atsp_rez(vardai, pavardes, galutiniai2);
        }
        else
        {
            atsp_rez(vardai, pavardes, galutiniai);
        }
    }
}


// Double funkcija, apskaiciuojanti kiekvieno studento nd pazymiu vidurki ir grazinanti galutini bala, apskaiciuota pagal salygoje nurodyta formule
double gal_rez(int egr, std::vector<double> nd_rez)
{
    double vidurkis, galutinis1;

    vidurkis = accumulate(nd_rez.begin(), nd_rez.end(), 0.000) / nd_rez.size();
    galutinis1 = (0.4 * vidurkis) + (0.6 * egr);

    return galutinis1;
}

// Double funkcija, apskaiciuojanti ir grazianti nd bei egzamino pazymiu mediana
double gal_mediana(int egr, std::vector<double> nd_rez)
{
    std::vector<double> eilute;
    for (int i = 0; i < nd_rez.size(); i++) {
        eilute.push_back(nd_rez.at(i));
    }

    eilute.push_back(egr);

    std::sort(eilute.begin(), eilute.end());

    if (eilute.size() % 2 == 0)
    {
        return (eilute[eilute.size() / 2 - 1] + eilute[eilute.size() / 2]) / 2;
    }
    else
    {
        return eilute[eilute.size() / 2];
    }
}

// Void funkcija, spausdinanti rezulatatu lentele
void atsp_rez(std::vector<std::string> vardai, std::vector<std::string> pavardes, std::vector<double> galutiniai)
{
    std::cout << std::setw(25) << "Vardas" << std::setw(25) << "Pavarde" << std::setw(25) << "Galutinis" << std::endl;
    std::cout << "---------------------------------------------------------------------------------\n";
    for (int i = 0; i < vardai.size(); i++) {

        std::cout << std::setw(25) << vardai.at(i) << std::setw(25) << pavardes.at(i) << std::setw(25) << galutiniai.at(i) << std::endl;

    }
}
