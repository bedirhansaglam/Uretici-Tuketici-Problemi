#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* Raftaki göz sayısı */
#define N 14
/* Dislama, bos ve dolu goz semaforlari */
sem_t sem_disla, sem_dolu, sem_bos; 
unsigned int raf[N];
/* Veri, uretilen ve cikan */
unsigned int sayac = 0, gelen = 0, cikan = 0;
unsigned int devamli=1; /*üretilen veri sayisi*/

/*3 üretici */
void *uretici_thread();
void *uretici_thread1();
void *uretici_thread2();

/*9 tüketici*/
void *tuketici_thread();/*1. tüketici*/
void *tuketici_thread1();/*2. tüketici*/
void *tuketici_thread2();/*3. tüketici*/
void *tuketici_thread3();/*4. tüketici*/
void *tuketici_thread4();/*5. tüketici*/
void *tuketici_thread5();/*6. tüketici*/
void *tuketici_thread6();/*7. tüketici*/
void *tuketici_thread7();/*8. tüketici*/
void *tuketici_thread8();/*9. tüketici*/


main()
{
	/* Iplikler ve semaforlar tanimlaniyor*/
	pthread_t uretici,uretici1,uretici2 ,tuketici,tuketici1,tuketici2,tuketici3,tuketici4,tuketici5,tuketici6,tuketici7,tuketici8;
	int th1, th2,th3,th4,th5,th6,th7,th8,th9,th10,th11,th12;
	
	if (sem_init(&sem_disla, 0, 1) == -1)
		printf("Dislama semaforu basarisiz\n");
	if (sem_init(&sem_dolu, 0, 0) == -1)
	{
		printf("Dolu sayma semaforu basarisiz\n");
		sem_destroy(&sem_disla);
	}
	if (sem_init(&sem_bos, 0, N) == -1)
	{
		printf("Bos sayma semaforu basarisiz\n");
		sem_destroy(&sem_dolu);
		sem_destroy(&sem_disla);
	}
	
        /* 3 Üretici  */
	th1 = pthread_create(&uretici, NULL, uretici_thread, NULL);
	th3 = pthread_create(&uretici1,NULL, uretici_thread1,NULL);
	th4 = pthread_create(&uretici2,NULL, uretici_thread2,NULL);
         
        /* 9 Tüketici */
	th2 = pthread_create(&tuketici, NULL, tuketici_thread, NULL);
	th5 = pthread_create(&tuketici1, NULL, tuketici_thread1, NULL);
	th6 = pthread_create(&tuketici2, NULL, tuketici_thread2, NULL);
	th7 = pthread_create(&tuketici3, NULL, tuketici_thread3, NULL);
	th8 = pthread_create(&tuketici4, NULL, tuketici_thread4, NULL);
	th9 = pthread_create(&tuketici5, NULL, tuketici_thread5, NULL);
	th10 = pthread_create(&tuketici6, NULL, tuketici_thread6, NULL);
	th11 = pthread_create(&tuketici7, NULL, tuketici_thread7, NULL);
	th12 = pthread_create(&tuketici8, NULL, tuketici_thread8, NULL);

	pthread_join(uretici, NULL);
	pthread_join(uretici1,NULL);
	pthread_join(uretici2,NULL);

	pthread_join(tuketici, NULL);		
	pthread_join(tuketici1, NULL);
	pthread_join(tuketici2, NULL);
	pthread_join(tuketici3, NULL);
	pthread_join(tuketici4, NULL);
	pthread_join(tuketici5, NULL);
	pthread_join(tuketici6, NULL);
	pthread_join(tuketici7, NULL);
	pthread_join(tuketici8, NULL);

	sem_destroy(&sem_disla);
	sem_destroy(&sem_bos);
	sem_destroy(&sem_dolu);		
}

void *uretici_thread()
{

	while (1)
	{
		printf("Üretici  %d verisini üretti.",devamli); 
		sem_wait(&sem_bos);		/* Bos goz var mı? */
		sem_wait(&sem_disla);   /* Bos goze erisim icin digerlerini disla */
		raf[gelen] = devamli;	/* Rafa veriyi yerlestir*/
		gelen = (gelen + 1) % N;/* Rafta yerlestirilen gozu goster */
		printf("Bu veri rafta %d .göze yerleştirildi\n",gelen); 
		sem_post(&sem_disla); /* Digerlerinin rafa erisimini sagla */
		sem_post(&sem_dolu); /* Tuketiciye dolu goz oldugunu haber ver */
		devamli++; /*Sonsuz döngüde üretilen veri*/

		
		sleep(1); /* Ipliklerin calismasini gostermek icin uyutuluyor */
	}
}

void *uretici_thread1()
{

	while (1)
	{
		printf("Üretici  %d verisini üretti.",devamli); 
		sem_wait(&sem_bos);		/* Bos goz var mı? */
		sem_wait(&sem_disla);   /* Bos goze erisim icin digerlerini disla */
		raf[gelen] = devamli;	/* Rafa veriyi yerlestir*/
		gelen = (gelen + 1) % N;/* Rafta yerlestirilen gozu goster */
		printf("Bu veri rafta %d .göze yerleştirildi\n",gelen); 
		sem_post(&sem_disla); /* Digerlerinin rafa erisimini sagla */
		sem_post(&sem_dolu); /* Tuketiciye dolu goz oldugunu haber ver */
		devamli++; /*Sonsuz döngüde üretilen veri*/

		
		sleep(1); /* Ipliklerin calismasini gostermek icin uyutuluyor */
	}
}

void *uretici_thread2()
{

	while (1)
	{
		printf("Üretici  %d verisini üretti.",devamli); 
		sem_wait(&sem_bos);		/* Bos goz var mı? */
		sem_wait(&sem_disla);   /* Bos goze erisim icin digerlerini disla */
		raf[gelen] = devamli;	/* Rafa veriyi yerlestir*/
		gelen = (gelen + 1) % N;/* Rafta yerlestirilen gozu goster */
		printf("Bu veri rafta %d .göze yerleştirildi\n",gelen); 
		sem_post(&sem_disla); /* Digerlerinin rafa erisimini sagla */
		sem_post(&sem_dolu); /* Tuketiciye dolu goz oldugunu haber ver */
		devamli++; /*Sonsuz döngüde üretilen veri*/

		
		sleep(1); /* Ipliklerin calismasini gostermek icin uyutuluyor */
	}
}


void *tuketici_thread()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread1()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread2()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread3()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread4()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread5()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread6()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread7()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
void *tuketici_thread8()
{
	/* Tuketici ipligi dolu gozden veriyi alir */
	while (1)
	{
		sem_wait(&sem_dolu); 	/* Dolu goz var mı? */
		sem_wait(&sem_disla);	/* Veriyi raftan alacak disladi */
		printf("Tüketici %d verisini tüketti.", raf[cikan]);
		cikan = (cikan + 1) % N; /* Veriyi aldigi goze isaret koy */
	        printf("Bu veri %d.gözden alındı\n",cikan);
		sem_post(&sem_disla); /* Digerlerinin rafa erisimine izin ver */
		sem_post(&sem_bos); /* Ureticiye bos goz oldugunu haber ver */
		/* Ipliklerin calismasini gostermek icin uyutuluyor */
		sleep(1);
	}	
}
