#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <stdlib.h>
#include "../include/k1.h"
#include <math.h>
#define MS 1000000

void main( int argc, char *argv[] )
{
	unsigned short cr_com42=0,cr_com=0,num_com=0,data_count=0;
	unsigned int TCount=0,DTTM=0; 													//��騩 ⠩���, ��᫥���� ��室 ������
	int TC10=0; 																	//⠩��� �� 100 ��
	int N=0;																		//���-�� �⥭�� ����
	int N1=0;																		//���-�� �⥭�� ���� �� ��諮� ⠪�	
	int Mes, TstGl= -1;
    pid_t proxy,pid;
    timer_t id;
	unsigned int i,i2=0;
    struct itimerspec timer;
    struct sigevent event;
	short i_p=0;
	float Dopler1,m_porog[2],test_dpl;
	
	while( (i=getopt(argc, argv, "mis:") )!=-1)	
	{
		switch(i)
		{
			case 'p' :  break;
			case 's' :	break;//sscanf(optarg,"%f",&porog_sf); printf("Yaa Zdes!!\n"); break;
			case 'i' :	break;//sscanf(optarg,"%f",&porog_df); break;
		}																			//switch
	}																				//while
	
	porog_sf = atof(argv[2]);
	porog_df = atof(argv[3]);

	//---------------------------------------- Get a proxy for the timer to kick ------------------------------------------
    proxy = qnx_proxy_attach( 0, 0, 0, -1 );
    if( proxy == -1 ) 
	{
		printf( "Unable to attach proxy." );
		return;
    }

    //-------------------------------------------- Attach to the timer ----------------------------------------------------
    event.sigev_signo = -proxy;
    id = timer_create( CLOCK_REALTIME, &event );
    if( id == -1 ) 
	{
		printf( "Unable to attach timer." );
		return;
    }

	//create_shmem();
	delay(500);
	open_shmem();
	delay(500);
	
	ispr = (struct ispr_mo3k *) & p->to_MO3.to42.Mispr;

	//------------------------------------------------------------------------------------------------------------------------
	//while((p->from_MO3.from41.num_com==0)&&(p->from_MO3.from42.num_com==0)) delay(500);
	cr_com=p->from_MO3.from41.cr_com; 												//��������� ����� �������

	if ((p->from_MO3.from41.num_com==1)||(p->from_MO3.from41.num_com==2)||(p->from_MO3.from41.num_com==3)) 	
	{
		Init_K1(p->from_MO3.from41.num_KS-1);
	} 																				//�᫨ ���� ������� �� 4.1
	else Init_K1(0); 																//�᫨ ���� ������� �� 4.2 � �2

	/*
	Dopler1=60000;
	writeDopler(-Dopler1);
	
	printf("\n��⠭���� �㫥��� ��ண��\n");
	writePorogs(porog_sf, porog_df);

	printf("����� �।���� ���祭�� �஢�� �㬬�୮�� ������ ... \n");
	while(f <= 8) 
	{
		Write_K1(SUM4);
		//Write_K1(RAZN0);
		delay(400);
		pid=Receive( 0 , 0, 0 );				
		if (pid==proxy_DRV1) DDRead_K1();
		pid=Receive( 0 , 0, 0 );				
		if (pid==proxy_DRV1) DDRead_K1();
		Dopler1-=15000;
		writeDopler(-Dopler1);
	}
	SREDN = floatSUM_4/f;
	printf("����७ �஢��� �㬠 %3.3e \n",SREDN);			
	*/
	//writePorogs(SREDN*2, SREDN*2);
	//writePorogs(1e2, SREDN*2);
	writePorogs(1e8, 5e8);
	//writePorogs(SREDN*10, SREDN*2);
	//writePorogs( SREDN*10, 1e2);

	Dopler1=(float)p->from_MO3.from41.Fd*1000;
	//printf("d_from_MO3.from41=%e\n",p->from_MO3.from41.Fd);
	//writeDopler(-Dopler1);
	writeDopler(0);
	//test_dpl=Dopler1;
	//	Ubran test Glorii do uto4neni9 algoritma
	//TestGloriya(1);
    
	timer.it_value.tv_sec     = 2L; 												//start after X sec
    timer.it_value.tv_nsec    = 0L;
    timer.it_interval.tv_sec  = 0;
    timer.it_interval.tv_nsec = 75*MS;  											//100
    timer_settime( id, 0, &timer, NULL );

    while(1) 
	{
    	pid=Receive( 0 , 0, 0 );
		if (pid==proxy) 															//��ࠡ��稪 ⠩���
		{
			if ( ( (p->num_com==11) || ( (p->num_com==12) && (ispr->gl==0) ) ) &&
			 (cr_com42!=p->from_MO3.from42.cr_com) )
			{
				printf("\n 					Command for TestGL (%d) [%04h]\n", 
				p->from_MO3.from42.num_com, p->to_MO3.to42.Mispr);
				cr_com42 = p->from_MO3.from42.cr_com;
				nastr_upos(0);
				writePorogs(1e9, 1e9);
				delay(500);
				TstGl = TestGloriya(p->num_com-11); 								// 0 - test bez Gloria
				printf("\n TestGloriya = %d \n", TstGl);
				if (TstGl) p->to_MO3.to42.status_test=2; 							//�ன���
				else 	   p->to_MO3.to42.status_test=3; 							//�訡��
				p->to_MO3.to42.count_test++;
				writePorogs(1e2, 2e9);
			}
			if (  (p->num_com==14)  && (ispr->gl==0) && (cr_com42!=p->from_MO3.from42.cr_com) )
			{
				nastr_upos(1); 														//����ன�� ���� �� �2
				cr_com42 = p->from_MO3.from42.cr_com;
			}
			TCount++;
			TC10++;
			if ((TCount-N)>10) ispr->k1 = 1; 										//��� �����
			if (TC10==10) TC10=0;
			if (p->U.c_OI!=data_count)												//��諨 �����
			{	
				DTTM=TCount;														//��������� �६� ��室�
				data_count=p->U.c_OI;   											//�������� ���-��
			}

			//if (((TCount-DTTM>40)||(data_count>1249))&&(data_count>0)) 			//⠩�-��� ������ �� �� ����稨
			if ((TCount-DTTM>40)&&(data_count>0)) 									//⠩�-��� ������ �� �� ����稨
			{
				if ((p->from_MO3.from41.num_com==2)&&(p->from_MO3.from41.num_KS==1))		//�᫨ �� ᥠ�� �1
				{
					if(data_count>1250) data_count=1250;
					for(i=0;i<data_count;i++) p->to_MO3.to41.DCP_K1[i]=p->U.OI[i];			//�����㥬 � ��� ����
					p->to_MO3.to41.sum_DCP=data_count;								//��।��� ���-�� ������
					p->to_MO3.to41.cr_SEANCE++; 									//㢥��稫� ���浪��� ����� ���ᨢ�
					printf("��ନ஢�� ���ᨢ �1 N%d. ���-�� ������ %d ᫮�\n",p->to_MO3.to41.cr_SEANCE,p->to_MO3.to41.sum_DCP);
				}
				data_count=p->U.c_OI=0;  											//���㫥��� ���� ����
			}

			switch (TC10)
			{
				case 0 : Write_K1(SUM4); break;
				//case 1 : Write_K1(RAZN0); break;
				case 2 : Write_K1(SUM20); break;
				case 3 : Write_K1(YP); break;
				case 4 : Write_K1(DPL1); break;						
				//case 5 : Write_K1(RAZN0); break;						
				//case 6 : Write_K1(RAZN1); break;						
				case 9 : 															//ࠧ � ��� ᥪ �믮��塞 �ࢨ�� ����樨
						
						if (p->U.SUM_4>1e+8) p->to_MO3.to41.UR_sign_K1=(short)((log10(p->U.SUM_4)-8)*16);	else p->to_MO3.to41.UR_sign_K1=0;
						//	if ((abs(p->from_MO3.from41.Fd<4.5))&&(abs(p->from_MO3.from41.Fd)>5.5))
						if ((p->from_MO3.from41.num_com==1)||(p->from_MO3.from41.num_com==2))
						{
							test_dpl=(p->from_MO3.from41.Fd-2)*1000; 				//���४�஢�� �訡�� ��।������ ������ � �����
							if (abs(test_dpl-Dopler1) > 2000) 
							//if ((abs(test_dpl*1000<4500))||(abs(test_dpl*1000)>5500)) 		//���� �� ����ᠭ�� ������
							//if ((test_dpl<-5500)||(test_dpl>5500)||((test_dpl>-4500)&&(test_dpl<4500))) 		//���� �� ����ᠭ�� ������
							{
								//Dopler1=(float)p->from_MO3.from41.Fd*1000;
								Dopler1=test_dpl;
								//printf("-- %5.0f -- ",test_dpl);
								writeDopler(-Dopler1);
							}
						}
						//printf("lvl = %f data=%d\n",p->U.SUM_20,data_count);
						//printf("n_com_from_k1 = %x \n",p->from_MO3.from41.num_com);
						//printf("SUM_4=%3.3e LVL20=%1.1e DPL=%d hz\n",p->U.SUM_4,p->U.SUM_20,p->U.DPL_1*244);
						//printf("OI=%x c_OI=%x\n",p->U.OI,p->U.c_OI);				
						//printf("ZI_DATA=%x	 ZI_DOST=%x\n",p->U.ZI_DATA,p->U.ZI_DOST);
				break;
			}
			
			if ((cr_com!=p->from_MO3.from41.cr_com)&&(num_com!=p->from_MO3.from41.num_com))
			{
				if ((p->from_MO3.from41.num_com==1)||(p->from_MO3.from41.num_com==2)) Init_K1(p->from_MO3.from41.num_KS-1);
				cr_com=p->from_MO3.from41.cr_com;
				num_com=p->from_MO3.from41.num_com;
			}
			
			//if ((cr_com!=p->from_MO3.from41.cr_com)&&(p->from_MO3.from41.num_com==1))	Init_K1(p->from_MO3.from41.num_KS-1);
			//if ((cr_com!=p->from_MO3.from41.cr_com)&&(p->from_MO3.from41.num_com==2))	Init_K1(p->from_MO3.from41.num_KS-1);
			
			//if ((cr_com!=p->from_MO3.from41.cr_com)&&(p->from_MO3.from41.num_com==77))	writePorogs(SREDN,SREDN);
			if ((cr_com42!=p->from_MO3.from42.cr_com)&&(p->from_MO3.from42.num_com==6))	
			{
				Dopler1=-p->from_MO3.from42.Fd*1000;
				writeDopler(Dopler1);
				cr_com42 = p->from_MO3.from42.cr_com;
			}
			
			cr_com=p->from_MO3.from41.cr_com;
			//num_com=p->from_MO3.from41.num_com;
		}
		//------------------------------------------- �⥭�� �1 ---------------------------------------------
		if (pid==proxy_DRV1) 
		{
			Read_K1();
			ispr->k1 = 0; 															//���� ����
			N=TCount;
		}

	}	//------------------------------------------- END WHILE ---------------------------------------------

    timer_delete( id );
}	//----------------------------------------------- END MAIN() --------------------------------------------