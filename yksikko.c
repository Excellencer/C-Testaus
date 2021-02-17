/* 
Moodle ryhmä 42 : SVN ryhmä 29
Kalle Liljeström	- 
Marcus Palmu 		- 
Miro Lähde			- 
*/
/**********************************************************************************
 * Yksikkötestit tietorakenne.c ja tiedostonkäsittely.c moduleille poislukien 
 * Lue, Muistinvapautus ja Listanvapautus aliohjelmat. Ohjelman kaatavat testit
 * ovat kommentoitu pois ohjelman suorituksesta. Luo tiedoston "Test-Results.xml"
 * testitulosten pohjalta. 
 * Vaadittavat .c tiedostot: tietorakenne, tiedostonkäsittely
 * Vaadittavat .txt tiedostot: lokiTest, templokiTest, paalokiTest1, paalokiTest2
 * 
 *********************************************************************************/
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "CUnit/Console.h"

#include <stdio.h>
#include <stdlib.h>
#include "tietorakenne.h"
#include "tiedostonkasittely.h"

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

/************************OMAT ALIOHJELMAT JA TYNGÄT**********************************************/

/* Vertaa kahden tiedoston sisältöä, palauttaa: samat = 0, eri = -1 */
int vertaaTDO(FILE *fP1, FILE *fP2)
{
	int rivi = 1, sara = 0;
	char s1, s2;

	do
	{
		s1 = fgetc(fP1);
		s2 = fgetc(fP2);

		if (s1 == '\n')
		{
			rivi++;
			sara = 0;
		}

		if (s1 != s2)
			return -1;

		sara++;
	} while (s1 != EOF && s2 != EOF);

	if (s1 == EOF && s2 == EOF)
		return 0;
	else
		return -1;
}

/* Tynkä PVM funktiosta */
char *PVM(char *pvm)
{
	char s[] = "16.04.2019 10:42";
	strcpy(pvm, s);
	return pvm;
}

/* Korjattu versio "Muistinvapautus" -aliohjelmasta, ei kuulu testattaviin */
Pullo *MuistinvapautusFix(Pullo *pEka)
{
	Pullo *del = pEka;
	while (del != NULL)
	{
		pEka = del->pSeuraava;
		/* Lisätty rivi alla */
		free(del->sTyyppi);
		free(del);
		del = pEka;
	}

	return pEka;
}
/***************************TESTIT******************************************************************/

/* Lisays -aliohjelman testaus */
void test_lisays(void)
{
	/* Luodaan tarvittavat parametrit testaamiseen */
	Pullo *pTA1 = NULL, *pTA2 = NULL, *pTA3 = NULL, *pTA4 = NULL, *pTest, *pVertaus;
	char s1[255] = "pullo 1.50 0.40";
	char s2[6] = "Pullo";
	char s3[255] = "pullo 1.50 0.40";

	/* Luodaan "Pullo" alkio testattavaksi */
	if ((pTest = (Pullo *)malloc(sizeof(Pullo))) == NULL)
	{
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
	if ((pTest->sTyyppi = malloc(strlen(s2) + 1)) == NULL)
	{
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
	strcpy(pTest->sTyyppi, s2);
	pTest->fTilavuus = 1.50;
	pTest->fPantti = 0.40;
	pTest->pSeuraava = NULL;

	/* Testitapaukset */
	pTA1 = Lisays(pTA1, s1);
	CU_ASSERT_PTR_NOT_NULL(pTA1);

	pVertaus = pTest;
	pTest = Lisays(pTest, s3);
	CU_ASSERT_PTR_EQUAL(pTest, pVertaus);

	/* Alla olevat testitapaukset aiheuttavat ohjelman kaatumisen: korjattava! */
	/*
	char s4[255] = "pullo 1,50 0,40";
	pTA2 = Lisays(pTA2, s4);
	CU_ASSERT_PTR_NOT_NULL(pTA2);
	
	char s5[255] = "pullo";
	Lisays(pTA3, s5);
	CU_ASSERT_PTR_NOT_NULL(pTA3);

	char s6[255] = "pullo 1.5.0 0.A0";
	Lisays(pTA4, s6);
	CU_ASSERT_PTR_NOT_NULL(pTA4);
*/
	/* Muistinvapautus */
	pTA1 = MuistinvapautusFix(pTA1);
	pTA2 = MuistinvapautusFix(pTA2);
	pTA3 = MuistinvapautusFix(pTA3);
	pTA4 = MuistinvapautusFix(pTA4);
	pTest = MuistinvapautusFix(pTest);
}
/* Tiettyalkio -aliohjelman testaus */
void test_tietty(void)
{
	Pullo *pA = NULL, *ptr, *pUusi, *p2, *pL;
	char str1[20] = "tölkki";
	int i = 0, k;

	/* Luodaan linkitetty lista */
	for (k = 0; k < 4; k++)
	{
		if ((pUusi = (Pullo *)malloc(sizeof(Pullo))) == NULL)
		{
			perror("Muistin varaaminen epäonnistui.");
			exit(1);
		}
		if ((pUusi->sTyyppi = malloc(strlen(str1) + 1)) == NULL)
		{
			perror("Muistin varaaminen epäonnistui.");
			exit(1);
		}
		strcpy(pUusi->sTyyppi, str1);
		pUusi->fTilavuus = 1.50;
		pUusi->fPantti = 0.40;

		pUusi->pSeuraava = NULL;

		if (pA == NULL)
		{
			pA = pUusi;
		}
		else
		{

			ptr = pA;
			while (ptr->pSeuraava != NULL)
			{
				ptr = ptr->pSeuraava;
			}
			ptr->pSeuraava = pUusi;
		}

		/* Otetaan listan toisen ja viimeisen alkion osoitteet pointtereihin */
		if (++i == 2)
		{
			p2 = pUusi;
		}
		else if (i == 4)
		{
			pL = pUusi;
		}
	}

	/* Testitapaukset */
	CU_ASSERT_PTR_EQUAL(Tiettyalkio(pA, 1), pA);
	CU_ASSERT_PTR_EQUAL(Tiettyalkio(pA, 2), p2);
	CU_ASSERT_PTR_EQUAL(Tiettyalkio(pA, 4), pL);

	/* Muistinvapautus */
	pA = MuistinvapautusFix(pA);
}
/* Palautus -aliohjelman testaus */
void test_palautus(void)
{
	Solmu *pA1 = NULL, *pA2 = NULL, *pATest = NULL, *ptr, *pUusi, *pVertaus;
	int i = 0, k;

	/* Luodaan linkitetty lista */
	for (k = 0; k < 5; k++)
	{
		if ((pUusi = (Solmu *)malloc(sizeof(Solmu))) == NULL)
		{
			perror("Muistin varaaminen epäonnistui.");
			exit(1);
		}

		/* Asetetaan erilaisia arvoja listan eri alkioille */
		if (++i == 1)
		{
			pUusi->iNro = 1;
		}
		else if (i == 2)
		{
			pUusi->iNro = 100;
		}
		else if (i == 3)
		{
			pUusi->iNro = 33;
		}
		else if (i == 4)
		{
			pUusi->iNro = 100;
		}
		else if (i == 5)
		{
			pUusi->iNro = 100;
		}

		pUusi->pSeuraava = NULL;

		if (pATest == NULL)
		{
			pATest = pUusi;
		}
		else
		{
			ptr = pATest;
			while (ptr->pSeuraava != NULL)
			{
				ptr = ptr->pSeuraava;
			}
			ptr->pSeuraava = pUusi;
		}
	}

	/* Testitapaukset */
	pA1 = Palautus(pA1, 1);
	CU_ASSERT_PTR_NOT_NULL(pA1);
	pA2 = Palautus(pA2, 100);
	CU_ASSERT_PTR_NOT_NULL(pA2);
	pVertaus = pATest;
	pATest = Palautus(pATest, 33);
	CU_ASSERT_PTR_EQUAL(pVertaus, pATest);

	/* Muistinvapautus */
	Listanvapautus(pA1);
	Listanvapautus(pA2);
	Listanvapautus(pATest);
}
/* KPL -aliohjelman testaus */
void test_kpl(void)
{
	Solmu *pA1 = NULL, *pATest = NULL, *ptr, *pUusi;
	int i = 0, k;

	/* Luodaan linkitetty lista */
	for (k = 0; k < 5; k++)
	{
		if ((pUusi = (Solmu *)malloc(sizeof(Solmu))) == NULL)
		{
			perror("Muistin varaaminen epäonnistui.");
			exit(1);
		}

		/* Asetetaan erilaisia arvoja listan eri alkioille */
		if (++i == 1)
		{
			pUusi->iNro = 1;
		}
		else if (i == 2)
		{
			pUusi->iNro = 100;
		}
		else if (i == 3)
		{
			pUusi->iNro = 33;
		}
		else if (i == 4)
		{
			pUusi->iNro = 100;
		}
		else if (i == 5)
		{
			pUusi->iNro = 100;
		}

		pUusi->pSeuraava = NULL;

		if (pATest == NULL)
		{
			pATest = pUusi;
		}
		else
		{
			ptr = pATest;
			while (ptr->pSeuraava != NULL)
			{
				ptr = ptr->pSeuraava;
			}
			ptr->pSeuraava = pUusi;
		}
	}
	/* Testitapaukset */
	CU_ASSERT_EQUAL(KPL(pATest, 4), 0);
	CU_ASSERT_EQUAL(KPL(pATest, 100), 3);
	CU_ASSERT_EQUAL(KPL(pA1, 1), 0);

	/* Muistinvapautus */
	Listanvapautus(pATest);
}
/* Maara -aliohjelman testaus */
void test_maara(void)
{
	/* Luodaan tiedosto, jossa 3 laskettavaa riviä */
	FILE *temptiedosto;
	if ((temptiedosto = fopen("tilapaistiedosto.txt", "w")) != NULL)
	{
		fprintf(temptiedosto, "Otsikko\n\nkalle\nmarcus\nmiro");
	}
	else
	{
		printf("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	fclose(temptiedosto);

	CU_ASSERT_EQUAL(Maara(), 3);

	/* Luodaan tiedosto, jossa 100 laskettavaa riviä */
	FILE *temptiedosto2;
	if ((temptiedosto2 = fopen("tilapaistiedosto.txt", "w")) != NULL)
	{
		fprintf(temptiedosto2, "Otsikko\n\n");
		for (int i = 0; i < 100; i++)
		{
			fprintf(temptiedosto2, "kalle\n");
		}
	}
	else
	{
		printf("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	fclose(temptiedosto2);

	CU_ASSERT_EQUAL(Maara(), 100);

	/* Luodaan tiedosto, jossa 0 laskettavaa riviä */
	FILE *temptiedosto3;
	if ((temptiedosto3 = fopen("tilapaistiedosto.txt", "w")) != NULL)
	{
		fprintf(temptiedosto3, "Otsikko\n\n");
	}
	else
	{
		printf("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	fclose(temptiedosto3);

	CU_ASSERT_EQUAL(Maara(), 0);
}
/* Loki -aliohjelman testaus */
void test_loki(void)
{
	/* Ajetaan ohjelma ja verrataan syntynyttä tiedostoa oikeanlaiseen tiedostoon */
	Loki();
	FILE *tdo1;
	if ((tdo1 = fopen("tilapaistiedosto.txt", "r")) == NULL)
	{
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Oikeanlainen tiedosto, "lokiTest.txt" */
	FILE *tdo2;
	if ((tdo2 = fopen("lokiTest.txt", "r")) == NULL)
	{
		perror("\nTiedoston lokiTest.txt avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Virhe, jos tiedostot eivät ole samanlaiset */
	if (vertaaTDO(tdo1, tdo2) == 0)
	{
		CU_PASS();
	}
	else
	{
		CU_FAIL();
	}

	/* Muistinvapautus */
	fclose(tdo1);
	fclose(tdo2);
}
/* Temploki -aliohjelman testaus */
void test_temploki(void)
{
	/* Luodaan testialkio */
	Pullo *pUusi;
	char s[] = "tölkki";

	if ((pUusi = (Pullo *)malloc(sizeof(Pullo))) == NULL)
	{
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}
	if ((pUusi->sTyyppi = malloc(strlen(s) + 1)) == NULL)
	{
		perror("Muistin varaaminen epäonnistui.");
		exit(1);
	}

	strcpy(pUusi->sTyyppi, s);
	pUusi->fTilavuus = 1.50;
	pUusi->fPantti = 0.40;
	pUusi->pSeuraava = NULL;

	/* Ajetaan ohjelma ja verrataan syntynyttä tiedostoa oikeanlaiseen tiedostoon */
	Temploki(pUusi);
	FILE *tdo1;
	if ((tdo1 = fopen("tilapaistiedosto.txt", "r")) == NULL)
	{
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Oikeanlainen tiedosto, "templokiTest.txt" */
	FILE *tdo2;
	if ((tdo2 = fopen("templokiTest.txt", "r")) == NULL)
	{
		perror("\nTiedoston templokiTest.txt avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Virhe, jos tiedostot eivät ole samanlaiset */
	if (vertaaTDO(tdo1, tdo2) == 0)
	{
		CU_PASS();
	}
	else
	{
		CU_FAIL();
	}

	/* Muistinvapautus */
	fclose(tdo1);
	fclose(tdo2);
	MuistinvapautusFix(pUusi);
}
/* Paaloki -aliohjelman testaus */
void test_paaloki(void)
{
	/* Tyhjennetään lokitiedosto.txt */
	FILE *temptiedosto;
	if ((temptiedosto = fopen("lokitiedosto.txt", "w")) == NULL)
	{
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}
	fclose(temptiedosto);

	/* Ajetaan ohjelma ja verrataan syntynyttä tiedostoa oikeanlaiseen tiedostoon */
	Paaloki(23, 12.12);
	FILE *tdo1;
	if ((tdo1 = fopen("lokitiedosto.txt", "r")) == NULL)
	{
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Oikeanlainen tiedosto, "paalokiTest1.txt" */
	FILE *tdo2;
	if ((tdo2 = fopen("paalokiTest1.txt", "r")) == NULL)
	{
		perror("\nTiedoston paalokiTest1.txt avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Virhe, jos tiedostot eivät ole samanlaiset */
	if (vertaaTDO(tdo1, tdo2) == 0)
	{
		CU_PASS("1. check");
	}
	else
	{
		CU_FAIL("1. check");
	}

	/* Muistinvapautus */
	fclose(tdo1);
	fclose(tdo2);

	/* Ajetaan ohjelma ja verrataan syntynyttä tiedostoa oikeanlaiseen tiedostoon */
	Paaloki(23, 12.126);
	FILE *tdo3;
	if ((tdo3 = fopen("lokitiedosto.txt", "r")) == NULL)
	{
		perror("Tiedoston avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Oikeanlainen tiedosto, "paalokiTest2.txt" */
	FILE *tdo4;
	if ((tdo4 = fopen("paalokiTest2.txt", "r")) == NULL)
	{
		perror("\nTiedoston paalokiTest2.txt avaaminen epäonnistui.\n");
		exit(1);
	}

	/* Virhe, jos tiedostot eivät ole samanlaiset */
	if (vertaaTDO(tdo3, tdo4) == 0)
	{
		CU_PASS("2. check");
	}
	else
	{
		CU_FAIL("2. check");
	}

	/* Muistinvapautus */
	fclose(tdo3);
	fclose(tdo4);
}

/* cunit testien ajo */
int main(void)
{
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("Basic_test_suite", init_suite, clean_suite);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "test_lisays", test_lisays)) ||
		(NULL == CU_add_test(pSuite, "test_tietty", test_tietty)) ||
		(NULL == CU_add_test(pSuite, "test_palautus", test_palautus)) ||
		(NULL == CU_add_test(pSuite, "test_kpl", test_kpl)) ||
		(NULL == CU_add_test(pSuite, "test_maara", test_maara)) ||
		(NULL == CU_add_test(pSuite, "test_loki", test_loki)) ||
		(NULL == CU_add_test(pSuite, "test_temploki", test_temploki)) ||
		(NULL == CU_add_test(pSuite, "test_paaloki", test_paaloki)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
	CU_set_output_filename("Test");
	CU_automated_run_tests();
	/*CU_console_run_tests(); */

	CU_cleanup_registry();
	return CU_get_error();
}
