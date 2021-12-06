// SEMESTRALKA2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include "structures/heap_monitor.h"

#include "Loader.h"
#include "KriteriumUJNazov.h"
#include "KriteriumUJPocetObyv.h"
#include "KriteriumUJZastavanost.h"
#include "KriteriumUJPrislusnost.h"
#include "KriteriumUJTyp.h"
#include "KriteriumUJPocetObyv.h"
#include "KriteriumUJPocetProdObyv.h"
#include "KriteriumUJCelkovaVymera.h"
#include "KriteriumUJZastavanaPlocha.h"
#include "KriteriumBJPocetIzieb.h"
#include "KriteriumBJPocetOsob.h"
#include "KriteriumBJTyp.h"
#include "KriteriumBJPocet.h"
#include "KriteriumUJPocetBJ.h"
#include "VyberoveKriterium.h"

#include "Triedenie.h"
#include "FilterPodlaHodnoty.h"
#include "FiltrePodlaIntervalu.h"
#include "ZlozenyFilter.h"


#include "structures/table/unsorted_sequence_table.h"



using namespace structures;

SortedSequenceTable<std::string, UzemnaJednotka*> VyhladavanieUJ;
TriediacaStruktura<UzemnaJednotka *, constants::POCET_UJ> TriedenieUJ;
UzemnaJednotka UJednotky[constants::POCET_UJ];


int main()
{
    initHeapMonitor();


    Loader l;
    l.LoadData(UJednotky, &TriedenieUJ, &VyhladavanieUJ);
    std::string zaklad = "A";
    start:
        int volba;
        std::cout << "Pri vyberani filtra mate moznost napisat nedefinovany alebo -1 pri ciselnom filtri\n";
        std::cout << "Vyberte si z nasledujich moznosti: \n";
        std::cout << "1) Vypisanie informacii o uzemnych jednotkach\n";
        std::cout << "2) Zoradenie uzemnych jednotiek\n";
        std::cout << "3) Vypisanie informacii o bytovych jednotkach\n";
        std::cout << "4) Vypisanie informacii o poctoch bytovych jednotiek vo zvolenych uzemnych jednotkach\n";
        std::cout << "5) Zoradenie uzemnych jednotiek podla sumarneho poctu bytovych jednotiek\n";
        std::cout << "6) Vypisanie vyberovych kriterii pre zoskupenia bytovych jednotiek vo zvolenych uzemnych jednotkach\n";
        std::cout << "7) Vypisanie vyberovych kriterii pre uzemne jednotky na zaklade zvolenych zoskupeni bytovych jednotiek\n";
        std::cin >> volba;
        switch (volba)
        {
        case 1:
        {
            std::string vstup;
            std::cout << "1) Vypisanie informacii o uzemnych jednotkach splnajucich Filtre Typ(Obec,Okres,Kraj,Slovensko) Prislusnost(VyssiCelok) a jeden z filtrov: \n1) Nazov\n2) Pocet obyvatelov\n3) Zastavanost\n";
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            } 
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::string nov;
            std::cout << "Zadaj nazov vyssieho celku podla ktoreho sa ma vyhladavat: ";
            std::getline(std::cin, nov);
            bool pouzit_prisl = true;
            if (nov == "nedefinovany")
            {
                pouzit_prisl = false;
            }

            KriteriumUJPrislusnost kriterium_prislusnost;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool> fph_prislusnost(&kriterium_prislusnost, true, pouzit_prisl, nov);

            std::cout << "Vyber si jeden z filtrov: \n1) Nazov\n2) Pocet obyvatelov\n3) Zastavanost\n";
            std::cin >> volba;
            switch (volba)
            {
            case 1:
            {
                std::string vstup;
                std::cout << "Zadaj nazov Obce ktora sa ma vyhladat: ";
                std::getline(std::cin, vstup);
                std::getline(std::cin, vstup);
                bool pouzit = true;
                if (vstup == "nedefinovany")
                {
                    pouzit = false;
                }
                KriteriumUJNazov kujn;
                Kriterium<std::string, UzemnaJednotka*>* pointer_nazov;
                pointer_nazov = &kujn;
                FilterPodlaHodnoty<std::string, UzemnaJednotka*, std::string> fph(pointer_nazov, vstup, pouzit);

                ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
                UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
                UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

                test_zlo_ftr = &fph_kuj;
                zlo_f->pridajFilter(test_zlo_ftr);
                test_zlo_ftr = &fph;
                zlo_f->pridajFilter(test_zlo_ftr);
                test_zlo_ftr = &fph_prislusnost;
                zlo_f->pridajFilter(test_zlo_ftr);

                zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

                for (TableItem<std::string, UzemnaJednotka*>* i : *vyfiltrovanaTab2)
                {
                    std::cout << *(i->accessData());
                }
                delete zlo_f;
                delete vyfiltrovanaTab2;
            }
            break;
            case 2:
            {
                int vstup;
                std::cout << "Zadaj filter pocet obyvatelov: ";
                std::cin >> vstup;
                bool pouzit = true;
                if (vstup == -1)
                {
                    pouzit = false;
                }
                KriteriumUJPocetObyv kujpocetobyv;
                Kriterium<int, UzemnaJednotka*>* pointer;
                pointer = &kujpocetobyv;
                FilterPodlaHodnoty<std::string, UzemnaJednotka*, int> fph(pointer, vstup, pouzit);

                ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
                UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
                UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

                test_zlo_ftr = &fph_kuj;
                zlo_f->pridajFilter(test_zlo_ftr);
                test_zlo_ftr = &fph;
                zlo_f->pridajFilter(test_zlo_ftr);
                test_zlo_ftr = &fph_prislusnost;
                zlo_f->pridajFilter(test_zlo_ftr);

                zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

                for (TableItem<std::string, UzemnaJednotka*>* i : *vyfiltrovanaTab2)
                {
                    std::cout << *(i->accessData());
                }

               delete zlo_f;
               delete vyfiltrovanaTab2;
                break;
            }
            case 3:
            {
                int vstup;
                std::cout << "Zadaj filter zastavanost: ";
                std::cin >> vstup;
                bool pouzit = true;
                if (vstup == -1)
                {
                    pouzit = false;
                }
                KriteriumUJZastavanost kriterium_zastavanost;
                Kriterium<long double, UzemnaJednotka*>* pointer;
                pointer = &kriterium_zastavanost;
                FilterPodlaHodnoty<std::string, UzemnaJednotka*, long double> fph(pointer, vstup, pouzit);

                ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
                UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
                UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

                test_zlo_ftr = &fph_kuj;
                zlo_f->pridajFilter(test_zlo_ftr);
                test_zlo_ftr = &fph;
                zlo_f->pridajFilter(test_zlo_ftr);
                test_zlo_ftr = &fph_prislusnost;
                zlo_f->pridajFilter(test_zlo_ftr);

                zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

                for (TableItem<std::string, UzemnaJednotka*>* i : *vyfiltrovanaTab2)
                {
                    std::cout << *(i->accessData());
                }

                delete zlo_f;
                delete vyfiltrovanaTab2;

                break;
            }
            break;
            }
        }
        break;
        case 2:
        {
            std::string vstup;
            std::cout << "2) Zoradenie uzemnych jednotiek splnajucich Filtre Typ(Obec,Okres,Kraj,Slovensko) Prislusnost(VyssiCelok) a jedno z kriterii: \n1) Nazov\n2) Pocet obyvatelov\n3) Zastavanost\n";
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            }
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::string nov;
            std::cout << "Zadaj nazov vyssieho celku podla ktoreho sa ma vyhladavat: ";
            std::getline(std::cin, nov);
            bool pouzit_prisl = true;
            if (nov == "nedefinovany")
            {
                pouzit_prisl = false;
            }

            KriteriumUJPrislusnost kriterium_prislusnost;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool> fph_prislusnost(&kriterium_prislusnost, true, pouzit_prisl, nov);

            ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
            UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
            UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

            test_zlo_ftr = &fph_kuj;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fph_prislusnost;
            zlo_f->pridajFilter(test_zlo_ftr);
            zlo_f->vyfiltrujTabulku(&VyhladavanieUJ,vyfiltrovanaTab2);

            std::cout << "Vyber si jedno z kriterii: \n1) Nazov\n2) Pocet obyvatelov\n3) Zastavanost\n";
            std::cin >> volba;
            switch (volba)
            {
            case 1:
            {
                std::string order;
                bool vzostupne = true;
                std::cout << "Zoradenie uzemnych jednotiek podla kriteria - Nazov\n";
                std::cout << "Chcete zoradit vzostupne/zostupne: ";
                std::cin >> order;
                if (order == "zostupne")
                {
                    vzostupne = false;
                }
                Triedenie<std::string, UzemnaJednotka*, std::string> t;
                KriteriumUJNazov kujn;
                Kriterium<std::string, UzemnaJednotka*>* pointer;
                pointer = &kujn;
                t.utried(vyfiltrovanaTab2, pointer, vzostupne);

                for (int i = 0; i < (*vyfiltrovanaTab2).size(); i++)
                {
                    std::cout << (*vyfiltrovanaTab2).getItemAtIndex(i).accessData()->getNazov() << " " << pointer->ohodnot((*vyfiltrovanaTab2).getItemAtIndex(i).accessData()) << "\n";
                }
            }
            break;
            case 2:
            {
                std::string order;
                bool vzostupne = true;
                std::cout << "Zoradenie obci podla kriteria - Pocet Obyvatelov\n";
                std::cout << "Chcete zoradit vzostupne/zostupne: ";
                std::cin >> order;
                if (order == "zostupne")
                {
                    vzostupne = false;
                }
                Triedenie<std::string, UzemnaJednotka*, int> t;
                KriteriumUJPocetObyv kujpocetobyv;
                Kriterium<int, UzemnaJednotka*>* pointer;
                pointer = &kujpocetobyv;
                t.utried(vyfiltrovanaTab2, pointer, vzostupne);

                for (int i = 0; i < (*vyfiltrovanaTab2).size(); i++)
                {
                    std::cout << (*vyfiltrovanaTab2).getItemAtIndex(i).accessData()->getNazov() << " " << pointer->ohodnot((*vyfiltrovanaTab2).getItemAtIndex(i).accessData()) << "\n";
                }
                break;
            }
            case 3:
            {
                std::string order;
                bool vzostupne = true;
                std::cout << "Zoradenie obci podla kriteria - Zastavanost\n";
                std::cout << "Chcete zoradit vzostupne/zostupne: ";
                std::cin >> order;
                if (order == "zostupne")
                {
                    vzostupne = false;
                }
                Triedenie<std::string, UzemnaJednotka*, long double> t;
                KriteriumUJZastavanost kujzastavanost;
                Kriterium<long double, UzemnaJednotka*>* pointer;
                pointer = &kujzastavanost;
                t.utried(vyfiltrovanaTab2, pointer, vzostupne);

                for (int i = 0; i < (*vyfiltrovanaTab2).size(); i++)
                {
                    std::cout << (*vyfiltrovanaTab2).getItemAtIndex(i).accessData()->getNazov() << " " << pointer->ohodnot((*vyfiltrovanaTab2).getItemAtIndex(i).accessData()) << "%\n";
                }
                break;
            }
            }
            delete zlo_f;
            delete vyfiltrovanaTab2;
        }
        break;
        case 3:
        {
            std::string vstup;
            std::cout << "3) Vypisanie informacii o zoskupeniach bytovych jednotiek vo zvolenej uzemnej jednotke\n";
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            }
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::string nov;
            std::cout << "Zadaj nazov uzemneho celku: ";
            std::getline(std::cin, nov);
            bool pouzit_prisl = true;
            if (nov == "nedefinovany")
            {
                pouzit_prisl = false;
            }

            KriteriumUJNazov kujn;
            Kriterium<std::string, UzemnaJednotka*>* pointer;
            pointer = &kujn;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, std::string> fph_nazov(pointer, nov, pouzit_prisl);

            ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
            UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
            UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

            test_zlo_ftr = &fph_kuj;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fph_nazov;
            zlo_f->pridajFilter(test_zlo_ftr);
            
            zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

            KriteriumUJPocetObyv k_pocet_obyv;
            KriteriumUJPocetProdObyv k_pocet_prod_obyv;
            KriteriumUJCelkovaVymera k_vymera;
            KriteriumUJZastavanaPlocha k_zastavana_plocha;

            Kriterium<int, UzemnaJednotka*>* pointer_pocet_obyv = &k_pocet_obyv;
            Kriterium<int, UzemnaJednotka*>* pointer_pocet_prod_obyv = &k_pocet_prod_obyv;
            Kriterium<long long, UzemnaJednotka*>* pointer_vymera = &k_vymera;
            Kriterium<long long, UzemnaJednotka*>* pointer_zastavana_plocha = &k_zastavana_plocha;

            KriteriumBJPocet k_bj_pocet;
            KriteriumBJPocetIzieb k_bj_pocet_izieb;
            KriteriumBJPocetOsob k_bj_pocet_osob;
            KriteriumBJTyp k_bj_typ;

            Kriterium<int, BytovaJednotka*>* pointer_bj_pocet = &k_bj_pocet;
            Kriterium<int, BytovaJednotka*>* pointer_bj_pocet_izieb = &k_bj_pocet_izieb;
            Kriterium<int, BytovaJednotka*>* pointer_bj_pocet_osob = &k_bj_pocet_osob;
            Kriterium<std::string, BytovaJednotka*>* pointer_bj_typ = &k_bj_typ;

            for (auto i : *vyfiltrovanaTab2)
            {
                std::cout << pointer->ohodnot(i->accessData()) << " Pocet obyvatelov: " << pointer_pocet_obyv->ohodnot(i->accessData())
                    << " Pocet produktivnych obyvatelov: " << pointer_pocet_prod_obyv->ohodnot(i->accessData()) << " Celkova vymera: "
                    << pointer_vymera->ohodnot(i->accessData()) << " Zastavana plocha: " << pointer_zastavana_plocha->ohodnot(i->accessData()) <<"\n";
                std::cout << "\n    Typ bytovej jednotky        Pocet osob     Pocet miestnosti    Pocet\n";
                auto jedn = i->accessData()->getBJ();
                for (int j = 0; j < constants::POCET_BJ; j++)
                {
                    std::cout << pointer_bj_typ->ohodnot(jedn) << "       " << pointer_bj_pocet_osob->ohodnot(jedn) << "                " << pointer_bj_pocet_izieb->ohodnot(jedn) << "              " << pointer_bj_pocet->ohodnot(jedn) << std::endl;
                    jedn++;
                }

            }
            delete zlo_f;
            delete vyfiltrovanaTab2;
        }
        break;
        case 4:
        {
            std::string vstup;
            std::cout << "4) Vypisanie informacii o poctoch bytovych jednotiek vo zvolennych uzemnych jednotkach\n";
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            }
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::string nov;
            std::cout << "Zadaj nazov vyssieho celku podla ktoreho sa ma vyhladavat: ";
            std::getline(std::cin, nov);
            bool pouzit_prisl = true;
            if (nov == "nedefinovany")
            {
                pouzit_prisl = false;
            }

            KriteriumUJPrislusnost kriterium_prislusnost;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool> fph_prislusnost(&kriterium_prislusnost, true, pouzit_prisl, nov);

            int vstup_pocet_obyv; 
            int vstup_pocet_obyv2;
            std::cout << "Zadaj filter interval (zaciatok a koniec intervalu) pocet obyvatelov: ";
            std::cin >> vstup_pocet_obyv;
            std::cin >> vstup_pocet_obyv2;
            bool pouzit = true;
            if (vstup_pocet_obyv == -1)
            {
                pouzit = false;
            }
            KriteriumUJPocetObyv kujpocetobyv;
            Kriterium<int, UzemnaJednotka*>* pointer;
            pointer = &kujpocetobyv;
            FilterPodlaIntervalu<std::string, UzemnaJednotka*, int> fpintervalu(pointer, vstup_pocet_obyv, vstup_pocet_obyv2, pouzit);

            ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
            UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
            UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

            test_zlo_ftr = &fph_kuj;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fpintervalu;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fph_prislusnost;
            zlo_f->pridajFilter(test_zlo_ftr);

            zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);


            KriteriumBJPocet k_bj_pocet;
            KriteriumBJTyp k_bj_typ;
            KriteriumBJPocetOsob k_bj_pocet_osob;
            KriteriumBJPocetIzieb k_bj_pocet_izieb;

            KriteriumUJNazov k_uj_nazov;
            KriteriumUJPocetObyv k_uj_pocet_obyv;
            KriteriumUJPocetProdObyv k_uj_pocet_prod_obyv;
            KriteriumUJCelkovaVymera k_uj_celkova_vymera;
            KriteriumUJZastavanaPlocha k_uj_zastavana_plocha;

            Kriterium<std::string, UzemnaJednotka*>* pointer_k_uj_nazov = &k_uj_nazov;
            Kriterium<int, UzemnaJednotka*>* pointer_k_uj_pocet_obyv = &k_uj_pocet_obyv;
            Kriterium<int, UzemnaJednotka*>* pointer_k_uj_pocet_prod_obyv = &k_uj_pocet_prod_obyv;
            Kriterium<long long, UzemnaJednotka*>* pointer_k_uj_celkova_vymera = &k_uj_celkova_vymera;
            Kriterium<long long, UzemnaJednotka*>* pointer_k_uj_zastavana_plocha = &k_uj_zastavana_plocha;

            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet = &k_bj_pocet;
            Kriterium<std::string, BytovaJednotka*>* pointer_k_bj_typ = &k_bj_typ;
            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet_osob = &k_bj_pocet_osob;
            Kriterium<int, BytovaJednotka*>* pointer_k_pocet_izieb = &k_bj_pocet_izieb;

            std::string vstup_bj_typ;
            std::cout << "Zadaj filter typ bytovej jednotky: ";
            std::getline(std::cin, vstup_bj_typ);
            std::getline(std::cin, vstup_bj_typ);
            pouzit_typ = true;
            if (vstup_bj_typ == "nedefinovany")
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, std::string> fph_bj_typ(pointer_k_bj_typ, vstup_bj_typ, pouzit_typ);

            int vstup_bj_pocet_osob;
            std::cout << "Zadaj filter pocet osob: ";
            std::cin >> vstup_bj_pocet_osob;

            pouzit_typ = true;
            if (vstup_bj_pocet_osob == -1)
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, int> fph_bj_pocet_osob(pointer_k_bj_pocet_osob, vstup_bj_pocet_osob, pouzit_typ);

            int vstup_bj_pocet_izieb;
            std::cout << "Zadaj filter pocet izieb: ";
            std::cin >> vstup_bj_pocet_izieb;;

            pouzit_typ = true;
            if (vstup_bj_pocet_izieb == -1)
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, int> fph_bj_pocet_izieb(pointer_k_pocet_izieb, vstup_bj_pocet_izieb, pouzit_typ);

            ArrayList<BytovaJednotka*>* vyfiltrovanaTab3 = new ArrayList<BytovaJednotka*>();
            ZlozenyFilter<std::string, BytovaJednotka*>* zlo_f_tri = new ZlozenyFilter<std::string, BytovaJednotka*>();

            UniverzalnyFilter<BytovaJednotka*>* test_zlo_ftr_bj;

            test_zlo_ftr_bj = &fph_bj_typ;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);
            test_zlo_ftr_bj = &fph_bj_pocet_osob;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);
            test_zlo_ftr_bj = &fph_bj_pocet_izieb;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);


            for (auto i : *vyfiltrovanaTab2)
            {
                std::cout << pointer_k_uj_nazov->ohodnot(i->accessData()) << "  Pocet obyvatelov: " << pointer_k_uj_pocet_obyv->ohodnot(i->accessData())
                    << "  Pocet produktivnych obyv: " << pointer_k_uj_pocet_prod_obyv->ohodnot(i->accessData()) << "  Celkova vymera: " <<
                    pointer_k_uj_celkova_vymera->ohodnot(i->accessData()) << "  Zastavana plocha: " << pointer_k_uj_zastavana_plocha->ohodnot(i->accessData()) << std::endl;
                BytovaJednotka* jedn = i->accessData()->getBJ();
                zlo_f_tri->vyfiltrujTabulku(jedn, vyfiltrovanaTab3);
                for (auto au : *vyfiltrovanaTab3)
                {
                    std::cout << "Kriterium pocet bytovych jednotiek: " << pointer_k_bj_pocet->ohodnot(au) << std::endl;
                }
            }
            delete zlo_f;
            delete vyfiltrovanaTab2;
            delete vyfiltrovanaTab3;
            delete zlo_f_tri;
        }
        break;
        case 5:
        {
            std::string vstup;
            std::cout << "5) Zoradenie uzemnych jednotiek podla sumarneho poctu bytovych jednotiek\n";
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            }
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::string nov;
            std::cout << "Zadaj nazov vyssieho celku podla ktoreho sa ma vyhladavat: ";
            std::getline(std::cin, nov);
            bool pouzit_prisl = true;
            if (nov == "nedefinovany")
            {
                pouzit_prisl = false;
            }

            KriteriumUJPrislusnost kriterium_prislusnost;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool> fph_prislusnost(&kriterium_prislusnost, true, pouzit_prisl, nov);

            int vstup_pocet_obyv;
            int vstup_pocet_obyv2;
            std::cout << "Zadaj filter interval (zaciatok a koniec intervalu) pocet obyvatelov: ";
            std::cin >> vstup_pocet_obyv;
            std::cin >> vstup_pocet_obyv2;
            bool pouzit = true;
            if (vstup_pocet_obyv == -1)
            {
                pouzit = false;
            }
            KriteriumUJPocetObyv kujpocetobyv;
            Kriterium<int, UzemnaJednotka*>* pointer;
            pointer = &kujpocetobyv;
            FilterPodlaIntervalu<std::string, UzemnaJednotka*, int> fpintervalu(pointer, vstup_pocet_obyv, vstup_pocet_obyv2, pouzit);

            ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
            UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
            UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

            test_zlo_ftr = &fph_kuj;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fpintervalu;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fph_prislusnost;
            zlo_f->pridajFilter(test_zlo_ftr);

            zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

            KriteriumUJNazov k_uj_nazov;
            KriteriumUJPocetObyv k_uj_pocet_obyv;
            KriteriumUJPocetProdObyv k_uj_pocet_prod_obyv;
            KriteriumUJCelkovaVymera k_uj_celkova_vymera;
            KriteriumUJZastavanaPlocha k_uj_zastavana_plocha;
            KriteriumUJPocetBJ k_uj_pocet_bj;

            Kriterium<std::string, UzemnaJednotka*>* pointer_k_uj_nazov = &k_uj_nazov;
            Kriterium<int, UzemnaJednotka*>* pointer_k_uj_pocet_obyv = &k_uj_pocet_obyv;
            Kriterium<int, UzemnaJednotka*>* pointer_k_uj_pocet_prod_obyv = &k_uj_pocet_prod_obyv;
            Kriterium<long long, UzemnaJednotka*>* pointer_k_uj_celkova_vymera = &k_uj_celkova_vymera;
            Kriterium<long long, UzemnaJednotka*>* pointer_k_uj_zastavana_plocha = &k_uj_zastavana_plocha;
            Kriterium<int, UzemnaJednotka*>* pointer_k_uj_pocet_bj = &k_uj_pocet_bj;

            KriteriumBJPocet k_bj_pocet;
            KriteriumBJTyp k_bj_typ;
            KriteriumBJPocetOsob k_bj_pocet_osob;
            KriteriumBJPocetIzieb k_bj_pocet_izieb;

            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet = &k_bj_pocet;
            Kriterium<std::string, BytovaJednotka*>* pointer_k_bj_typ = &k_bj_typ;
            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet_osob = &k_bj_pocet_osob;
            Kriterium<int, BytovaJednotka*>* pointer_k_pocet_izieb = &k_bj_pocet_izieb;

            std::string vstup_bj_typ;
            std::cout << "Zadaj filter typ bytovej jednotky: ";
            std::getline(std::cin, vstup_bj_typ);
            std::getline(std::cin, vstup_bj_typ);
            pouzit_typ = true;
            if (vstup_bj_typ == "nedefinovany")
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, std::string> fph_bj_typ(pointer_k_bj_typ, vstup_bj_typ, pouzit_typ);

            int vstup_bj_pocet_osob;
            std::cout << "Zadaj filter pocet osob: ";
            std::cin >> vstup_bj_pocet_osob;

            pouzit_typ = true;
            if (vstup_bj_pocet_osob == -1)
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, int> fph_bj_pocet_osob(pointer_k_bj_pocet_osob, vstup_bj_pocet_osob, pouzit_typ);

            int vstup_bj_pocet_izieb;
            std::cout << "Zadaj filter pocet izieb: ";
            std::cin >> vstup_bj_pocet_izieb;;

            pouzit_typ = true;
            if (vstup_bj_pocet_izieb == -1)
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, int> fph_bj_pocet_izieb(pointer_k_pocet_izieb, vstup_bj_pocet_izieb, pouzit_typ);

            ArrayList<BytovaJednotka*>* vyfiltrovanaTab3 = new ArrayList<BytovaJednotka*>();
            ZlozenyFilter<std::string, BytovaJednotka*>* zlo_f_tri = new ZlozenyFilter<std::string, BytovaJednotka*>();

            UniverzalnyFilter<BytovaJednotka*>* test_zlo_ftr_bj;

            test_zlo_ftr_bj = &fph_bj_typ;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);
            test_zlo_ftr_bj = &fph_bj_pocet_osob;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);
            test_zlo_ftr_bj = &fph_bj_pocet_izieb;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);

            int pom = 0;
            for (auto i : *vyfiltrovanaTab2)
            {
                pom = 0;
                BytovaJednotka* jedn = i->accessData()->getBJ();
                zlo_f_tri->vyfiltrujTabulku(jedn, vyfiltrovanaTab3);
                for (auto au : *vyfiltrovanaTab3)
                {
                    pom += pointer_k_bj_pocet->ohodnot(au);
                }
                i->accessData()->setSumPocetBJ(pom);
            }

            bool vzostupne = true;
            std::string order;
            std::cout << "Chcete zoradit vzostupne/zostupne: ";
            std::cin >> order;
            if (order == "zostupne")
            {
                vzostupne = false;
            }

           
            Triedenie<std::string, UzemnaJednotka*, int> t;
            t.utried(vyfiltrovanaTab2, pointer_k_uj_pocet_bj, vzostupne);

            for (auto i : *vyfiltrovanaTab2)
            {
                std::cout << pointer_k_uj_nazov->ohodnot(i->accessData()) << "  Typ: " << i->accessData()->getTypUJnaString()
                    << "  Prislusnost: " << nov << "  Pocet obyvatelov: " <<
                    pointer_k_uj_pocet_obyv->ohodnot(i->accessData()) << "  Pocet bytovych jednotiek: " << pointer_k_uj_pocet_bj->ohodnot(i->accessData()) << std::endl; 
            }

            delete zlo_f;
            delete vyfiltrovanaTab2;
            delete vyfiltrovanaTab3;
            delete zlo_f_tri;

        }
        break;
        case 6:
        {
            std::string vstup;
            std::cout << "6) Vypisanie vyberovych kriterii pre zoskupenia bytovych jednotiek vo zvolenych uzemnych jednotkach\n";
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            }
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::cout << "Zadaj nazov uzemnej jednotky: ";
            std::getline(std::cin, vstup);
            //std::getline(std::cin, vstup);

            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }

            KriteriumUJNazov k_uj_nazov;
            Kriterium<std::string, UzemnaJednotka*>* pointer_nazov = &k_uj_nazov;

            FilterPodlaHodnoty < std::string, UzemnaJednotka*, std::string> fph_kujnazov(pointer_nazov,vstup,pouzit_typ);

            ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
            UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
            UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

            test_zlo_ftr = &fph_kujnazov;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fph_kujnazov;
            zlo_f->pridajFilter(test_zlo_ftr);

            zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

            VyberoveKriterium<BytovaJednotka, BytovaJednotka*, int> vyber_krit(true);

            KriteriumBJPocet k_bj_pocet;
            KriteriumBJTyp k_bj_typ;
            KriteriumBJPocetOsob k_bj_pocet_osob;
            KriteriumBJPocetIzieb k_bj_pocet_izieb;

            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet = &k_bj_pocet;
            Kriterium<std::string, BytovaJednotka*>* pointer_k_bj_typ = &k_bj_typ;
            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet_osob = &k_bj_pocet_osob;
            Kriterium<int, BytovaJednotka*>* pointer_k_pocet_izieb = &k_bj_pocet_izieb;

            BytovaJednotka* pom;
            BytovaJednotka* pom1;
            for (auto i : *vyfiltrovanaTab2)
            {
                pom1 = vyber_krit.najdiMin(i->accessData()->getBJ(), constants::POCET_BJ, pointer_k_bj_pocet);
                pom = vyber_krit.najdiMax(i->accessData()->getBJ(), constants::POCET_BJ, pointer_k_bj_pocet);
                std::cout << i->accessData()->getNazov() << "\n" << "MAX: " << pointer_k_bj_typ->ohodnot(pom) << "  Pocet osob: " 
                    << pointer_k_bj_pocet_osob->ohodnot(pom) << "  Pocet izieb: " << pointer_k_pocet_izieb->ohodnot(pom) << "  PocetBJ: " <<
                    pointer_k_bj_pocet->ohodnot(pom) << std::endl;
                std::cout << "MIN: " << pointer_k_bj_typ->ohodnot(pom1) << "  Pocet osob: "
                    << pointer_k_bj_pocet_osob->ohodnot(pom1) << "  Pocet izieb: " << pointer_k_pocet_izieb->ohodnot(pom1) << "  PocetBJ: " <<
                    pointer_k_bj_pocet->ohodnot(pom1) << std::endl;
            }
            delete zlo_f;
            delete vyfiltrovanaTab2;
        }
        break;
        case 7:
        {

            std::cout << "7) Vypisanie vyberovych kriterii pre uzemne jednotky na zaklade zvolenych zoskupeni bytovych jednotiek\n";
            std::string vstup;
            std::cout << "Zadaj filter Typ(Obec,Okres,Kraj,Slovensko): ";
            std::getline(std::cin, vstup);
            std::getline(std::cin, vstup);
            TypUzemnejJednotky vstup_enum;
            if (vstup == "Obec")
            {
                vstup_enum = OBEC;
            }
            else if (vstup == "Okres")
            {
                vstup_enum = OKRES;
            }
            else if (vstup == "Kraj")
            {
                vstup_enum = KRAJ;
            }
            else if (vstup == "Slovensko")
            {
                vstup_enum = SLOVENSKO;
            }
            else
            {
                vstup_enum = OBEC;
            }

            bool pouzit_typ = true;
            if (vstup == "nedefinovany")
            {
                pouzit_typ = false;
            }
            KriteriumUJTyp kuj_typ;
            Kriterium<TypUzemnejJednotky, UzemnaJednotka*>* pointer_typ;
            pointer_typ = &kuj_typ;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, TypUzemnejJednotky> fph_kuj(pointer_typ, vstup_enum, pouzit_typ);

            std::string nov;
            std::cout << "Zadaj nazov vyssieho celku podla ktoreho sa ma vyhladavat: ";
            std::getline(std::cin, nov);
            bool pouzit_prisl = true;
            if (nov == "nedefinovany")
            {
                pouzit_prisl = false;
            }

            KriteriumUJPrislusnost kriterium_prislusnost;
            FilterPodlaHodnoty<std::string, UzemnaJednotka*, bool> fph_prislusnost(&kriterium_prislusnost, true, pouzit_prisl, nov);

            ZlozenyFilter<std::string, UzemnaJednotka*>* zlo_f = new ZlozenyFilter<std::string, UzemnaJednotka*>();
            UnsortedSequenceTable<std::string, UzemnaJednotka*>* vyfiltrovanaTab2 = new UnsortedSequenceTable<std::string, UzemnaJednotka*>();
            UniverzalnyFilter<UzemnaJednotka*>* test_zlo_ftr;

            test_zlo_ftr = &fph_kuj;
            zlo_f->pridajFilter(test_zlo_ftr);
            test_zlo_ftr = &fph_prislusnost;
            zlo_f->pridajFilter(test_zlo_ftr);

            zlo_f->vyfiltrujTabulku(&VyhladavanieUJ, vyfiltrovanaTab2);

            KriteriumUJNazov k_uj_nazov;
            Kriterium<std::string, UzemnaJednotka*> *pointer_uj_nazov = &k_uj_nazov;

            KriteriumBJPocet k_bj_pocet;
            KriteriumBJTyp k_bj_typ;
            KriteriumBJPocetOsob k_bj_pocet_osob;
            KriteriumBJPocetIzieb k_bj_pocet_izieb;

            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet = &k_bj_pocet;
            Kriterium<std::string, BytovaJednotka*>* pointer_k_bj_typ = &k_bj_typ;
            Kriterium<int, BytovaJednotka*>* pointer_k_bj_pocet_osob = &k_bj_pocet_osob;
            Kriterium<int, BytovaJednotka*>* pointer_k_pocet_izieb = &k_bj_pocet_izieb;

            std::string vstup_bj_typ;
            std::cout << "Zadaj filter typ bytovej jednotky: ";
            std::getline(std::cin, vstup_bj_typ);
            pouzit_typ = true;
            if (vstup_bj_typ == "nedefinovany")
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, std::string> fph_bj_typ(pointer_k_bj_typ, vstup_bj_typ, pouzit_typ);

            int vstup_bj_pocet_osob;
            std::cout << "Zadaj filter pocet osob: ";
            std::cin >> vstup_bj_pocet_osob;

            pouzit_typ = true;
            if (vstup_bj_pocet_osob == -1)
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, int> fph_bj_pocet_osob(pointer_k_bj_pocet_osob, vstup_bj_pocet_osob, pouzit_typ);

            int vstup_bj_pocet_izieb;
            std::cout << "Zadaj filter pocet izieb: ";
            std::cin >> vstup_bj_pocet_izieb;;

            pouzit_typ = true;
            if (vstup_bj_pocet_izieb == -1)
            {
                pouzit_typ = false;
            }

            FilterPodlaHodnoty<std::string, BytovaJednotka*, int> fph_bj_pocet_izieb(pointer_k_pocet_izieb, vstup_bj_pocet_izieb, pouzit_typ);

            BytovaJednotka vyfiltrovanaTab3[constants::POCET_BJ];
            ZlozenyFilter<std::string, BytovaJednotka*>* zlo_f_tri = new ZlozenyFilter<std::string, BytovaJednotka*>();

            UniverzalnyFilter<BytovaJednotka*>* test_zlo_ftr_bj;

            test_zlo_ftr_bj = &fph_bj_typ;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);
            test_zlo_ftr_bj = &fph_bj_pocet_osob;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);
            test_zlo_ftr_bj = &fph_bj_pocet_izieb;
            zlo_f_tri->pridajFilter(test_zlo_ftr_bj);

            int pocet = 0;

            VyberoveKriterium<BytovaJednotka, BytovaJednotka*, int> vyber_krit(true);

            BytovaJednotka* min;
            BytovaJednotka* max;
            for (auto i : *vyfiltrovanaTab2)
            {
                zlo_f_tri->vyfiltrujTabulku(i->accessData()->getBJ(), vyfiltrovanaTab3, pocet);

            }
            min = vyber_krit.najdiMin(vyfiltrovanaTab3, pocet, pointer_k_bj_pocet);
            max = vyber_krit.najdiMax(vyfiltrovanaTab3, pocet, pointer_k_bj_pocet);

            std::cout << min->getNazovUJ() << " " << "MIN: " << pointer_k_bj_pocet->ohodnot(min) << "\n";
            std::cout << max->getNazovUJ() << " " << "MAX: " << pointer_k_bj_pocet->ohodnot(max) << "\n";
            
            delete zlo_f;
            delete vyfiltrovanaTab2;
            delete zlo_f_tri;
        }
        break;
    }
    std::cout << "Chcete pokracovat? [A/N]: ";
    std::cin >> zaklad;
    if(zaklad == "A")
        goto start;
}
