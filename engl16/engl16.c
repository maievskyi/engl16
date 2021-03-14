// engl16 дополнение 15.02.2021 - и идёт передача в GIT
//первый коммит пока нет .sln
//первый коммит есть .sln
//коммит перед изм имени структ inidat
// комм после изм имени стр-т ininame на inidat
// ком после изм им указ на стр-ру pdat1name на pmeminidat

//24/09/20 после RRRengl09 развиваем работу с fini.dat
// 31/07/20 дробление на мелкие ф-ции sepmini()
// extensmem()
// Начало работать  
// Надо добавлять первую сортировку ( по алфавиту)
//
#define _CRT_SECURE_NO_WARNINGS  //   ?? подробнее об предупреждениях ??
//#define VARTOKEN nodebug
//#define RENAME ok
//#define ALPHABET ok
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
#include"engl16.h"  //


FILE *pfiletxt; //---> текст который читать - argv[1] первый аргумент ком строки "txt2.txt"
FILE *pmyfile;	//---> указатель на структ. файл в котором сохранять базу слов - argv[2].dat"
FILE *pfini;	//---> указатель на структ. файл в котором сохранять файлов fini.dat
FILE *pnosortfile;	//---> указатель на структ. ф в котор сохр несорт базу слов - argv[1]_nosort.dat"
FILE *psortfile;	//---> указатель на структ. ф в котором сохр сорт базу слов - argv[1]_sort.dat"

char *pnamenosort;		//-->указат на имя ф-ла с запис несорт масс стр 
struct word *pmemword;		//-->глоб указат в main()на первичное выделеие ДИН памяти 
							//под МАССИВ СТРУКТУР (word) для отсепарирования token()
							//далее память будет перерасширятся по этому указателю
struct word *pmemsortword;  //--> указ на д пам стрктур с отсортированными словами
struct word *palphabetword;  //--> указ на д пам стр-р с отсорт-ми и сокращенными словами
long amountmem = 0;		//---> РАЗМЕР в байтах дин пам выде-мых под структуры word
long *pamountmem;		//--->укз РАЗМ в б-тах ДИН пам выде-мых под несорт структ word
int countnumword = 0;	//---счётчик инкремента слов а значит и стр-р при сепар-и
int *pcountnumword;		//--->указатель на счетч слов
struct inidat *pmeminidat;	//--->указ на ДИН пам с стр-й базы ini имён прог-мы
int flagtext = NEWTEXT;	//переменная -ФЛАГ режима работы со стар или нов текстом
						//т е будет ли сепарироваться по новой и писаться в нофую базу слов 

						//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%       main     %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%//
int main(int argc, const char ** argv, const char** env)
{

	system("chcp 1251 > nul");
	errno_t err;			//  переменная (int?) для вывода ошибок ? внутр переменная (int?)

							//проверка наличия аргументов ком строки  ==================================================
	if (argc == 1)	//если нет аргументов ком строки
	{
		// проверка на уже сущ-вание файла в котор сохр-ть имена ф-лов "fini.dat"=======		
		err = fopen_s(&pfini, "fini.dat", "r+b");// открывается на чтение с дозаписью

		// не существует файла имён - выходим или раб с ранее созданным,===================
		if (err)	// выходим								
		{
			perror("fini.dat");
			puts("\n !!! на выход - не существовал файл пользователя \n с именами баз текстов \n");
			system("pause");
			exit(1);
			// _________________________________________________________________________________
			/*
			puts("\n Будет создан Новый файл пользователя \n с новыми именами баз текстов \n");
			err = fopen_s(&pfini, "fini.dat", "w+b");// ф-л в котор сохр  имена ф-лов "niname.dat"
			if (err)
			{
			puts("\n Ошибка! \n Неудачная попытка создания Нового файла пользователя \n\
			с новыми именами баз \n");
			free(pmeminidat);		//освобождение памяти под базу имён программы
			system("pause");
			exit(1);
			}

			//записываем в него содержимое дин память pmeminidat, (предполож = 0)
			size_t result = fwrite(pmeminidat, QUANTITYCHARNAME, QUANTITYNAME, pfini);

			puts("\n Создан Новый файл пользователя \"fini.dat\"\n\
			с новыми именами баз текстов \n");
			system("pause");
			//exit(1);
			*/
		} // end ... не существует файла имён
		  // end ... не существует файла имён

		  //... уже существовал файл имён fini.dat - работаем с ранее созд-м ф-лом--------
		else     //... уже существовал файл имён fini.dat - работаем с ранее созд-м ф-лом
		{
			// тут потом можно вставить инстр выбора "хотите ли созд fini.dat для другого txt"
			// etc..............................................................................

			// работаем с уже открытым ранее созданным ф-лом
			// создание дин памяти с базой имён программы ???? переделать QUANTITYCHARNAME=========
			//pmeminidat = (char*)malloc(QUANTITYNAME * sizeof(struct inidat));
			pmeminidat = (struct inidat*)malloc(QUANTITYNAME * QUANTITYCHARNAME);
			if (pmeminidat == NULL)printf("Не выделена память под базу имён программы \n");
			else printf("  Выделена дин пам din1name = %d Bytes \n\
 под %d записей базы имён программы \n",
				QUANTITYNAME * QUANTITYCHARNAME, QUANTITYNAME);			//  ??  отладка

																		//считываем в дин память ->pmeminidat содержимое файлового потока pfini->
			size_t result = fwrite(pmeminidat, QUANTITYCHARNAME, QUANTITYNAME, pfini);

			puts("\n Считан \"fini.dat\" с новыми именами баз текстов в ->pmeminidat \n");
			system("pause");		// отладка

									// etc......................................................................




		}  // end ifelse... уже с-вал файл имён fini.dat - работали с ранее созд-м ф-лом
		   //end проверка на уже сущ-вание файла в котор сохр-ть имена ф-лов "fini.dat"	

		{//  отладка temp->
			fclose(pfini);	// закрыть файловый ввод из которого читаются имена файлов
								//err = fopen_s(&pfini, "fini.dat", "r+b");// открывается на чтение с дозаписью
		}	// отладка <-temp
	}	// end if...нет аргументов ком строки
		// ...end if нет аргументов ком строки

		//...else...есть аргументы ком строки----------------------------------------
	else	//!!!!!!!!!!!...есть аргументы ком строки-------------------------------
	{
		// надо ли выбрать нов текст для сепарирования================================ 
		puts(" !!! Выбирается новый текстовый файл для сепарирования \n\
		если согласны нажмите \"Y\", если нет -\"N\" \n");

		//выбор нового текста для сепарирования ==================================
		//int tempchar = getchar(); //выходной рабочий вариант
		//если выбран нов текст для сепар =========================
		//if (('Y' == tempchar)||('y' == tempchar)) // выбран нов текст для сепар ====
		if (1) // выбран нов текст для сепар ====  вар TEMP DEBUG
		{
			//проверка существования именно двух аргументов ком строки
			if (argc == 2) // проверка существования именно двух аргументов ком строки
			{
				flagtext = NEWTEXT;		// флаг - согласие что есть файл с новым текстом ?
			}							// флаг зачем?? = в ф writebase2
			else
			{
				puts("Нет второго арг ком строки \n повторите ввод! \n");
				system("pause");
				exit(0);
			}
			// end ifelse проверка существования именно двух аргументов ком строки

			//создание и заполнение ???? "0" Нов файла настроек "fini.dat" пользователя 
			// тут надо писать

			//созд указ pfini на нов ini файл имён польз-ля "fini.dat" с нов именами баз текстов
			{  // простой блок
				puts("\n Будет создан Новый fini.dat файл настроек пользователя \n с новыми именами баз текстов \n");
				err = fopen_s(&pfini, "fini.dat", "w+b");// ф-л в котор сохр  имена ф-лов "niname.dat"
				if (err)
				{
					puts("\n Ошибка! \n Неудачная попытка создания Нового ini файла пользователя \n\
 с новыми именами баз \n");
					system("pause");
					exit(1);
				}

				// созд-е по укз pmeminidat дн пам с ini базой пользователя программы  ================
				pmeminidat = (struct inidat*)malloc(QUANTITYNAME * sizeof(struct inidat));
				if (pmeminidat == NULL)printf("Не выделена память под базу имён программы \n");
				else printf("  Выделена дин пам din1name = %d Bytes \n под %d записей базы имён программы \n",
					QUANTITYNAME * sizeof(struct inidat), QUANTITYNAME);

				//запись в ф fini.dat содержимое дин память pmeminidat, (?надоли обн  = 0) ============
				size_t result = fwrite(pmeminidat, sizeof(struct inidat), QUANTITYNAME, pfini);
				puts("\n Создан Новый файл пользователя \"fini.dat\"\n\
 с новыми обнулёнными именами баз текстов \n");
				fclose(pfini);	// закрыть файловый поток из которого читаются имена файлов
				system("pause");
			}// простой блок
			 // простой блок

			//// здесь все операции по сепарированию нового текста простой блок ================
			{
			// открытие входного .txt файла ==============================================
				err = fopen_s(&pfiletxt, argv[1], "rb");// инициализируется указатель FILE *pfiletxt 
										//на вх-ой txt ф-л (argv[1])
										//  и открывается в режиме (rb)-  "txt2.txt" 
				if (err) {
					puts("нет требуемого ком строкой ф-ла \n");
					perror(argv[1]); exit(1);
				};  // puts("нет требуемого ком строкой ф-ла \n"); 

			// перенос ф-ла текста в оперативную динам память, для цього ---> ================

					//~~~~~~~  определяем РАЗМЕР файла в байтах  ------------------------------------------
				long txtSize = 0;	//--- размер в байтах файла котор будет считан в дин память
				// устанавливаем текущ позицию в конец файла, т е (смещ на 0 относ конца ф-ла)	 
				fseek(pfiletxt, 0, SEEK_END);
				txtSize = ftell(pfiletxt); //в txtSize = ПОЛУЧАЕМ РАЗМЕР В БАЙТАХ

				//rewind(pfiletxt);  //+ очистка буфера      														
				fseek(pfiletxt, 0, SEEK_SET);	// перевести текущую поз на начало файла
												//
				printf("Размер памяти входного текста = %d Bytes \n", txtSize);

				//~~~~~~  выделение дин памяти буфеp *pmemtxtbuf---------------------------------
				char * pmemtxtbuf;			//--->  локальн указатель на дин пам. pmemtxtbuf 
										//		для хранения содерж-го из вх-го файла...........
				pmemtxtbuf = (char*)malloc(sizeof(char) * txtSize); // выделить дин память pmemtxtbuf для хран-я содерж-го из ф-л а
																 // далее подлежащего разбиению токенами
				if (pmemtxtbuf == NULL)
				{
					fputs("Ошибка памяти", stderr);
					exit(2);
				}
				printf("~~ выделена дин пам. pmemtxtbuf для хранения текста из файла ~~\n");
				// ------из pfiletxt считываем файл в буфер	pmemtxtbuf!!!------------------------------------
				size_t result = fread(pmemtxtbuf, sizeof(char), txtSize, pfiletxt);  // СЧИТЫВАЕМ файл в буфер!!!
				if (result != txtSize)  //если не совпало число считанных байт
				{
					if (feof(pfiletxt)) printf("Преждевременное достижение конца файла.\n");
					else printf("Ошибка при чтении файла.\n");
					exit(3);
				}
				fclose(pfiletxt);	//поработал и закрыл )) файловый ввод из которого читается входной текст

#ifdef TEXT	//~~~~~ текст выв-ся в станд. поток вывода консоли НА ЭКРАН (для  отладки)============ =======
				if (puts(pmemtxtbuf) == EOF) {
					printf("Ошибка при записи из текстов файла \n");
				}  // -> -> -> 
				else {
					printf("Файл текста  считан-записан в ф-ции main нормально\n");
					printf("		~~~ !!!!!Текст выше - это содержащийся в файле %s ~~~       \n \
	!!!!!!!!на который указывала ком строка, далее сепарирование \n", argv[1]);	//  ???*
				}
#endif//~~~~~~~~~~~~~~~~~~~~~ после отл можнои убрать  ~~~~~~~~~~~~~~~
				//~~~~~  самое первое выдел пам *pmemword под сеп и поехали! прост блок =======================
				{
					printf("  Размер памяти под одну структуру %d байт\n", sizeof(struct word));
					amountmem = MAX_WORD * sizeof(struct word);  //размер (байт) начально выд-мой памяти 
					pmemword = (struct word *) malloc(amountmem);   //самое первое выделение памяти 
																	//  под сепарацию и занесения строк в структуры 
																	//временно - начальное количество MAX_WORD 
					if (pmemword == NULL)printf("Не выделенна память под punsort \n");
					else printf("  Выделенна память punsort = %d Bytes \n  под %d неотсортированных структур \
  и ПОЕХАЛИ! сепарировать\n",
						MAX_WORD * sizeof(struct word), MAX_WORD);				//    отладка
				}

				//~~~~~~~~~    далее (подготовка аргументов?) вызов ф-ции сепаррования - sepmini() ------   
				pamountmem = &amountmem;  // указ на РАЗМ дин пам БАЙТ для сепарир стр-р(пока= 8 стр)
				pcountnumword = &countnumword; //указ на счётч инкр-та СЛОВ = СТРУКТ при сепар-и 
				// pmemword - указ на МАССИВ СТРУКТУР (word) для отсепарирования token()
				//pmemtxtbuf - указ на дин массив неразбитого текста - копии входн файла
				//argv[1] - из ком строки имя для отладки printf

				// ВЫЗОВ СЕПАРИРОВАНИЯ  long amountword = *pcountnumword / sizeof(struct word); 
				pmemword = sepmini(pmemword, pamountmem, pmemtxtbuf, pcountnumword, argv[1]);


				//~~~~~~~~~~   далее запись в файл базу WORDnosort сепарированных но несортированных структур ===========				
				char *pnamewordnosort;  //указ д строки для преобраз.rename имя ф "argv[1]_nosort.dat"
				// ~~~~~~~преобразов имени - арг[1] для несортир-го масс *_nosort.dat вызовом ф - и rename2()
				//~~~~~~~  преобразов имени - арг [1] ком стр в нов стр *_nosort.dat вызовом ф-и rename2()
				{	pnamewordnosort = rename2(argv[1], "_nosort.dat", 4);
				}
			//~~~~~~~~~~~~ запись в WORD hdd файл(заранее переим) базу несортир структур ---///////////////  
				writebase2(pnosortfile, pnamewordnosort, pmemword, countnumword);//
							//pnosortfile - указ на откр внутр ф-ции hdd файл в котором сохранять базу слов 
							//pnamewordnosort - уже сформированное ранее имя ф-ла для hdd ("argv[1]_nosort.dat")
							// pmemword - указ на дин массив несорт структур, 
							// countnumword - число несорт структур
							//,?? возврат указ имя файла с  структурами ( ----- )????
				puts(pnamewordnosort);		//debug вывод имени .hdd несортированных слов

			//~~~~~~~~~~  запись в дин пам pmeminidat <- ИМЕНИ  XXX_nosort.dat    ~~~~~~~~~
				{pmeminidat->idname = 0;
				strncpy(pmeminidat->name, pnamewordnosort, EN1);
				}

			//~~~~~~~~~~  запись в ф ini "fini.dat" <- ИМЕНИ XXX_nosort.dat из дин памяти  ~~~~~~~~   	
				err = fopen_s(&pfini, "fini.dat", "r+b");//XXX_nosrt.dat сохр в ф-л "fini.dat"
				if (err)
				{
					puts("\n Ошибка! \n Неудача отытия ранее созданного ф-ла имён пользователя \n");
					system("pause");
					exit(1);
				}
				fwrite(pmeminidat, sizeof(struct inidat), QUANTITYNAME, pfini);//fini.dat
																			   
			//~~~~~~~~~~   преобразование имени для сортировнного массива  XXX_sort.dat
				char *pnamesortword;  // указат на дин строка-имя читаемого файла "argv[1]_sort.dat"
				pnamesortword = rename2(argv[1], "_sort.dat", 4);  // д п выдел ф rename2()
				puts(pnamesortword); 		//debug

			//~~~~~~~~~~    начало алфавитной сортировки    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
 				
				pmemsortword = (struct word *) malloc((*pcountnumword) * sizeof(struct word));
				// глоб указ = выделение д пам стрктур с отсортированными словами

				//  под сепарацию и занесения строк в структуры 
				//временно - начальное количество MAX_WORD 
				if (pmemsortword == NULL)printf("Не выделенна память под pmemsortword \n");
				else printf("  Выделенна память psort = %d Bytes \n  под %d сортированных структур \
  и поехали! сортировать\n",
					(*pcountnumword) * sizeof(struct word), (*pcountnumword));		//    отладка
																					//-----------   цикл копирования в новую дин память несортиров слов для сортировки 
				int temp = 0;
				for (temp = 0; temp < *pcountnumword; temp++)
				{
					*(pmemsortword + temp) = *(pmemword + temp); //копирование
#ifdef M_SORT 
					printf("Структуры скопированы в нов массb для алфавитной сортировки --> \n"
						printf("m_sort %d - %s \n", temp, pmemsortword[temp].en);  // отладка
#endif
				}
				// ~~~~~~~~~~ вызов  алфавитной сортировки  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
				{
					//int disloc = 0;  //расположение поля в структуре word
					int disloc = &pmemword[0].id - &pmemword[0].id;
					pmemsortword = alphabet4(pmemsortword, pcountnumword, measurealph, disloc);//сортировка
					palphabetword = reduct3(pmemsortword, pcountnumword);			//сокращение повторений
																					//по указ palphabetword находится  алфавитно сортирован массив с заполн полем repeat
				}

				//
				//printf(" \ntemp  Далее in engl12.C  Отсорт-й мас- стр pret[0].id = %d\n", palphabetword[0].id);
				int disloc = 0;
				pmemsortword = idsort(palphabetword, pcountnumword, measurerepeat, disloc);//сортировка

				pmemsortword = alphabet4(pmemsortword, pcountnumword, measurealph, disloc);//сортировка

				printf("This \"Print\" inside to engl12_c - \n");
				int m;
				for (m = 0; m < *pcountnumword; m++)
				{
					printf(" _ %3d.  id=%3d  repeat_id=%3d _( %s )___[ %d ]   \n", m, pmemsortword[m].id, pmemsortword[m].repeat_id, pmemsortword[m].en, pmemsortword[m].repeat);    // temp
				}

				//~~~~~~~~~~  запись в дин пам pmeminidat имени файла отсорт-ных структ word    ~~~~~~~~~
				(pmeminidat + 1)->idname = 1;
				strncpy((pmeminidat + 1)->name, pnamesortword, EN1);

				//~~~~~~~~~~   вывод с второй записью в hdd файл имён fini.dat   имени  XXX_sort.dat	---////////
				fseek(pfini, 0, SEEK_SET);
				fwrite(pmeminidat, sizeof(struct inidat), QUANTITYNAME, pfini);//fini.dat

																					//	//~~~  temp????  ~~~~ открытие нового hdd файла для отсортированного масс структ слов
																					//			puts("\n будет создан новый файл пользователя \n с отсортированными словами \n");
																					//			err = fopen_s(&psortfile, pnamesortword, "w+b");// ф-л в котор сохр  имена ф-лов "niname.dat"
																					//			if (err)
																					//			{
																					//				puts("\n ошибка! \n неудачная попытка создания нового файла пользователя \n\ 
																					//с отсортированными словами\n");
																					//				system("pause");
																					//				exit(1);
																					//			}

																					//~~~~~~~~~~~~ запись в hdd файл(заранее переименов) базу отсортир структур  ---////////  
				writebase2(psortfile, pnamesortword, palphabetword, countnumword);//  countnumword  ??????????????????:?
																				  //pnamesortword-  уже сформированное ранее имя ф-ла для hdd
																				  // palphabetword - указ на дин мас отсорт структур, pcountnumword - число отсорт структ
																				  //, возврат указ имя файла с  структурами ( ----- )

			} // конец всех операций по сепарированию и сортировке нового текста простой блок
			  // конец всех операций по сепарированию и сортировке нового текста простой блок

			  //			fclose(psortfile);	//поработал всё записал и закрыл )) файл отсортированных слов ...dat
			fclose(pfini);	//поработал всё записал и закрыл )) файл имён fini.dat

#ifdef RENAME
			{
				char * ptempstr1 = (char*)malloc(32 * sizeof(char)); // выделить дин память
				char * ptempstr2 = (char*)malloc(32 * sizeof(char)); // выделить дин память
																	 //char * pnewname0 = (char*)malloc(64 * sizeof(char)); // выделить дин память
				char * pnewname0;
				//strncpy(pnamewordnosort, argv[1], lenargv1 - 4);	// копир аргум к с без расшир-.txt
				int temp3 = 6;
				//printf(" ~~~ sizeof(temp1) = ( %d )   ~~~\n", sizeof(temp1));
				//*temp1= "abcdefgh.dat";
				char str1[16] = "abcdefgh.dat";
				char str2[16] = "_yz.dat";
				char str3[] = "123456.dat";
				printf(" ~~~ strlen(str1) = ( %d )   ~~~\n", strlen(str1));
				printf(" ~~~ sizeof(str1) = ( %d )   ~~~\n", sizeof(str1));
				printf(" ~~~ strlen(str2) = ( %d )   ~~~\n", strlen(str2));
				printf(" ~~~ sizeof(str2) = ( %d )   ~~~\n", sizeof(str2));
				printf(" ~~~ strlen(str3) = ( %d )   ~~~\n", strlen(str3));
				printf(" ~~~ sizeof(str3) = ( %d )   ~~~\n", sizeof(str3));
				//strncpy(temp1, str1, 16);
				strncpy(ptempstr1, str1, 16);
				printf(" ~~~ strlen(ptempstr1) after copy = ( %d )   ~~~\n", strlen(ptempstr1));
				printf(" ~~~ sizeof(ptempstr1) after copy = ( %d )   ~~~\n", sizeof(ptempstr1));
				strncpy(ptempstr2, str2, 16);
				printf(" ~~~ strlen(temp2) after copy = ( %d )   ~~~\n", strlen(ptempstr2));
				printf(" ~~~ sizeof(temp2) after copy = ( %d )   ~~~\n", sizeof(ptempstr2));
				pnewname0 = rename2(ptempstr1, "_aaa.sos");
				printf(" ########  outside of rename1(); #########\n ");    // temp
				printf(" ~~~ pnewname0 = ( %s )   ~~~\n", pnewname0);    // temp
				free(ptempstr1);		//
				free(ptempstr2);		//
				free(pnewname0);		//
			}
#endif // RENAME
		}	//... end  выбрть нов текст для сепарирования

			// отказ от нового текста для сепарирования и выход--------------------
		else	// отказ от нового текста для сепарирования и выход
		{
			flagtext = OLDTEXT;;		// флаг - согласие что УЖЕ есть файл с сепар текстом
			puts("Новый файл не будет обработан \n работа с предыдущей базой слов! \n");
			system("pause");
			exit(0);
		};		// end else ... отказ от нового текста для сепарирования и выход---
				// ... конец надо ли выбрать нов текст для сепарирования ----- 

				////////////>>>>>>>>>>>>>>>>>>>   Движок   <<<<<<<</////////////////////////
		int go = 1;
		if (go == 1)
		{
			//system("cls");
			printf("\n\n  Press key \" \" for study or any key for exit \n");
			int lett;
			lett = getch(stdin);
			int m = 0;
			while (lett == ' ')
			{

				//printf("This \"Print\" inside GO \n");


				system("cls");
				printf("                 Press key \" \" for study or any key for exit \n");
				printf("\n\n   %3d. id=%3d  repeat = %3d _  (    %s     ) _ [ %d ]   \n", m, pmemsortword[m].id, pmemsortword[m].repeat_id, pmemsortword[m].en, pmemsortword[m].repeat);
				m++;

				lett = getch(stdin);

				if ((lett == 'z') || (m == *pcountnumword)) //конец урока
				{
					break;
				}
			}





		}; //%%%%%%%%%%%%%%%%%%%%%%%% end if (go)  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%





	};	//... end else есть аргументы ком строки---
		//... end else есть аргументы ком строки---

		//конец проверки наличия аргументов ком строки  -----------------------

		// конец всех операций по сепарированию и сортировке нового текста 

		//free(pnamewordnosort);//
		//free(pmemword);		//освобождение памяти массива отсепарированных неотсортированных структур
		//free(pmeminidat);		//освобождение памяти под базу имён программы

	printf("\n\n             The END!   -     конец урока! \n\n\n");
	system("pause");
}  //end main