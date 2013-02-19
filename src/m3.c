#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/pci.h>
#include <sys/osinfo.h>
#include <process.h>
#include <conio.h>
#pragma off (check_stack)
#include <math.h>
#include <sys/psinfo.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include "../include/tx_drv.h"
#include "../include/Mod_B.h"
//-----------//
#define PI 3.1415926
#define NAVtoRAD PI/(65356)
#define Kmema 12.27
#define Maxncu 0x4AA
#define Minncu 0xF55
#define Maxmema 0x7A2
#define Minmema 0x85D
#define GRADtoRAD  0.00153398
#define RADtoGRAD 651.898648
#define pi 	3.14159265
#define Kncu 	12.27
#define msec 1000000
#define Kq 	0.5
#define P 1 //  pa3peweHue 1/3anpem 0 ne4amu
#define tow 50 // napaMemp owugaHuR uMeH=5c

		 //----- onucaHue nepeMeHHblx np.1.0 -----//
short K2Init=0;//������ ����ன�� �2 �� ������� "��砫� ��"
float oldKK,deltaKK;
float grad=180.0/PI;
short oldKOD,deltaKOD; 
short byta2;
float Flt=0;
     //-----------//
int Seans=0; //�ਧ��� ��砫� ᥠ�� �� �2
unsigned short toPR1[8]=
//{0x07C7,0x0000,0x0000,0x0000,0x7000,0x0000,0x0841,0};
{0x07C7,0x0000,0x0000,0x0000,0x000e,0x0000,0x8210,0};

struct DefCMD acmd[2]=
{{0x1028,toPR1},{0x1428,NULL}}; // KC+D[] MK npu6opa 1
      //----- nyck -----//

void main(int argc, char *argv[])
{int i,j,k,res;
	int cnt_K2=0;
	struct ispr_mo3k *ispr;
    pid_t pid_timer;
    timer_t id_timer;
	struct itimerspec timer;
    struct sigevent event;
//	obmen_41_31_t from41;
	short b2,num_KS=0;	//����� ������ �裡 1 - ��-�1, 2 - ��-�2 	
	unsigned int N_TIMER=0;//���-�� �ࠡ��뢠��� ⠩���
	short TIMER10=0;//����� � ��1.0	
	short TIMER41=0;	
//----- onucaHue gaHHblx npu pa6ome c MK -----//
int short owu6ka,i1;
pid_t pid,pid_K1,pid_41,pid_42;
dev_tx_t *dev;
unsigned short Kypc,Ckopocmb,KpeH,DuHT;
unsigned short q=1,ncu=2,mema=3;
int StateK1=1,StateK2=0;//0 - stop, 1-start
int TestK2=0;//��� ����ன�� �2
float 	C1,C2,C3,C4,C5,C6,C7,C8;
int TIMESEV,setANT=0,minus_x;
	double PSI=0,TETA=0,oldPSI,oldTETA;
	double x,y,x1,y1,C,S,ri,r1,r2,r3,
	x2=0,y2=0;//������ �� ��窠�
	double prim,primq,primcos;
float KK=0;  //���� ��ࠡ��
const AgpecHK=28,AgpecCEB=31,nogAgpecHK=0,nogAgpecCEB=0;// agpeca OY
const Ynp_np1=1,HK=2,CEB=0;// No KAH MK
const Cnp1=1,CK1=Cnp1+8,CK2=CK1+20;//cMeweHue gaHHblx B Dout
const Cq=16,C42np1=10;//cMeweHue gaHHblx B Dout
unsigned pci_index=0;
unsigned char s,pewuM_K1;
int		 SIMF[4]={0,0,0,0}; //����稥 ᨬ䮭�� 0,1 - ModA :  2,3 - ModB
int		 MODB[2]={0,0};
//----- onucaHue daHHblx npu pa6ome c np.4-1,4-2 -----//
#define V 1400
unsigned short DCEB[6];//Dout42[V];

 C1=2048./pi;C2=4096.0/360.0;C3=180./pi;C4=C1*Kncu;
 C5=C2*Kncu;C6=C1*Kq;C7=C3;C8=C2*Kq;

    pid_timer = qnx_proxy_attach( 0, 0, 0, -1 );
    if( pid_timer == -1 ) {printf( "Unable to attach proxy." );return;}
    /* Attach to the timer */
    event.sigev_signo = -pid_timer;
    id_timer = timer_create( CLOCK_REALTIME, &event );
    if( id_timer == -1 ) {printf( "Unable to attach timer." );return;}
    timer.it_value.tv_sec     = 1L; //start after X sec
    timer.it_value.tv_nsec    = 0L;
    timer.it_interval.tv_sec  = 0;
    timer.it_interval.tv_nsec = 100*msec;
    timer_settime( id_timer, 0, &timer, NULL );


	printf("\nCTAPT M3\n");

	create_shmem();
	delay(1000);
	open_shmem();
	
	ispr = (struct ispr_mo3k *) p->to_MO3.to42.Mispr;
	p->pr1_c=0;
	//----- Hacmpouka MaH4ecm.KaH. -----//
	owu6ka=0;dev=OpenTx(pci_index);

	if(regim_kk(dev,Ynp_np1,true)==-1){owu6ka|=0x4000;}//Heucnp-Mble.owu6ku
	if(regim_ou(dev,HK,AgpecHK,true)==-1){owu6ka|=0x2000;}
	///if(regim_ou(dev,CEB,AgpecCEB,true)==-1){owu6ka|=0x1000;} //!!!
	Init_ModB();
	p->to_MO3.to42.Mispr=0;
	p->toPR1[0]=0x07C7;
	p->toPR1[1]=p->toPR1[2]=p->toPR1[3]=0x0000;
	p->toPR1[4]=0x000e;
	p->toPR1[5]=0x0000;
	p->toPR1[6]=0x8210;
	p->toPR1[7]=0;

for(;;)//----- CEPBEP -----//
{
 pid=Receive(0,dev->tx_B,N_B*2);s=0;owu6ka&=0xF000;//ucnp-Mble.owu6ku
 if(pid==dev->proxyR[Ynp_np1])s=1;
 if(pid==dev->proxyERR[Ynp_np1])s=2;
 if(pid==dev->proxyR[HK])s=3;
 if(pid==dev->proxyOUT[HK])s=4;
 if(pid==dev->proxyMODE[HK])s=5;
 if(pid==dev->proxyR[CEB])s=6;
 if(pid==dev->proxyOUT[CEB])s=7;
 if(pid==dev->proxyMODE[CEB])s=8;
 if(pid==proxy_RS)s=9;
 if(pid==pid_timer)s=12;
 

 switch(s)
 {	case 0:owu6ka|=1;break; // HEBEPEH proxy

	case 1://--- ������ ������ �� ��1
		if(KK_end(dev,Ynp_np1,2)==-1){owu6ka|=2;break;}
		p->pr1_c++;
		for(i=0;i<8;i++) p->PR1[i]=dev->tx_B[10+i];
		//for(i=0;i<3;i++) printf(" in[%d]=%04x",i,dev->tx_B[10+i]);printf("\n");
		//for(i=0;i<3;i++) printf("  to[%d]=%x",i,toPR1[i]);printf("\n");
		//for(i=0;i<1;i++) printf("from   %d",p->PR1[i]);

		p->Dout41[Cq]=p->PR1[0];  // q
		p->Dout41[Cq+1]=p->PR1[1];// ncu
		p->Dout41[Cq+2]=p->PR1[2];// mema

		//ANGLE
	    memcpy(&byta2,&p->Dout41[0],2);	 Flt=byta2*pi/(1<<14); p->simfonia41.Kg=Flt;// printf("Kypc=%8.4f \n",Flt);
		p->to_MO3.to41.P_FACT=(p->Dout41[16]-1991)*2/RADtoGRAD+p->simfonia41.Kg+x2;//������+����

		if (p->to_MO3.to41.P_FACT<0) p->to_MO3.to41.P_FACT+=2*pi;//������+����
		if (p->to_MO3.to41.P_FACT>2*PI) p->to_MO3.to41.P_FACT-=2*pi;//������+����

		if (p->Dout41[18]&0x800) p->to_MO3.to41.beta_FACT=(360-p->Dout41[18]/C2)/C3; //���� �����
			else p->to_MO3.to41.beta_FACT=-p->Dout41[18]/C1;
		p->to_MO3.to41.beta_FACT+=y2;
		//printf("x2=%3.3e y2=%3.3e\n",x2,y2);
		TIMER10=0;//�� ����� � ��1.0
		break;
	case 2://--- ������ ������ � ��1
		if(KK_end(dev,Ynp_np1,2)==-1)owu6ka|=1024;else owu6ka|=4;
		break;
	case 3://--- HK
		SIMF[0]++; //���� ᨬ䮭��
		if (SIMF[0]==60000) SIMF[0]=0;
		if(ou_read(dev,HK,nogAgpecHK)){owu6ka|=8;break;}
   		if((dev->tx_B[3])!=15){owu6ka|=512;break;}
    	for(j=0;j<15;j++) p->Dout41[j]=dev->tx_B[4+j]; //--- npueM HK
		//printf("N=%d",SIMF[0]);
		//printf("ModA simf- "); 	for(j=0;j<15;j++) printf("%x ",p->Dout41[j]);printf("\n");

		//�����
		if (dev->tx_B[6]&0x8000) PSI=-(0xFFFF-dev->tx_B[6])*NAVtoRAD;
		    else PSI=(float)dev->tx_B[6]*NAVtoRAD;
		if (dev->tx_B[7]&0x8000) TETA=-(0xFFFF-dev->tx_B[7])*NAVtoRAD;
		    else TETA=(float)dev->tx_B[7]*NAVtoRAD;
//			if (dev->tx_B[6]==0x8000) PSI=0;
//			if (dev->tx_B[7]==0x8000) TETA=0;
		if (abs(PSI)>1/4)  PSI=oldPSI;
		if (abs(TETA)>1/4) TETA=oldTETA;

  		break;
	case 4:owu6ka|=32;break; // HEBEPEH proxy HK
	case 5://--- npueM KY cuHxp HK ---//
		ou_mode_read(dev,HK,0x8000);
		break;
	case 6://--- npueMHuk CEB ---//
		if(ou_read(dev,CEB,nogAgpecCEB)){owu6ka|=64;break;}
		if((dev->tx_B[3])!=6){owu6ka|=128;break;}
		for(j=0;j<6;j++)DCEB[j]=dev->tx_B[4+j]; //--- npueM CEB
		break;//--- end npueMHuk CEB ---//
	case 7:case 8:owu6ka|=256;break; // HEBEPEH proxy CEB
	case 9:   //����� � ���� 
		SIMF[2]++; //���� ᨬ䮭�� ModB
		if (SIMF[2]==60000) SIMF[2]=0;		
		i=Read_ModB(); //�⠥� ����� �� ��� �
		if (i!=48) break; //�᫨ �� 楫� ����� - ��室
		if (Din_ModB[1]==0) p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr|0x0020; //�ਧ��� ������ ������樨 � ��� �
		else {
				p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr&0xffdf; //������� ��� � ��ࠢ��
			    if (p->to_MO3.to42.Mispr & 0x0010) //�᫨ ��� ������樨 � ��� �
					for(j=0;j<15;j++) p->Dout41[j]=Din_ModB[j+2]; //�ᯮ��㥬 �� �
			 }				
		//printf("ModB - ");	for(j=0;j<15;j++) printf("%x ",Din_ModB[j+2]);printf("\n");
		break;
	case 12://��ࠡ��稪 ⠩��� (10 ��) 
		N_TIMER++;//���稪 ⨪�� 

		TIMER41++;
		if (TIMER41>1) //  3/10 Hz
		{
			TIMER10++;
			//printf("TIMER10=%d\n",TIMER10);
			if (TIMER10<10) {p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr&0xff7f;} //���� ��1.0
			else {p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr|0x0080;} //��� ��1.0 

			p->Dout41[30]=(Din_ModB[20]>>8)&0x000F;
			p->Dout41[30]+=(Din_ModB[20]>>12)*10;     //hours
			p->Dout41[31]=(Din_ModB[21]>>8)&0x000F;
			p->Dout41[31]+=(Din_ModB[21]>>12)*10;	//minutes
			p->Dout41[32]=Din_ModB[21]&0x000F;
			p->Dout41[32]+=((Din_ModB[21]>>4)&0x000f)*10; //seconds
			//printf("H=%d M=%d S=%d T41=%d T31=%d \n",p->Dout41[30],p->Dout41[31],p->Dout41[32],p->from_MO3.from41.T_SS,p->Dout41[30]*3600+p->Dout41[31]*60+p->Dout41[32]);			
			//printf("navi=%d jump=%d \n",p->no_navi,p->jump);
			
			//�����
			oldPSI=PSI;
			oldTETA=TETA;		
	
			if (p->num_com==1) //�����⮢�� � ᥠ��� �裡
			{
			    memcpy(&b2,&p->Dout41[0],2);	 KK=b2*pi/(1<<14);
				if (p->no_navi==1) KK=1.218; //printf("navi=%d\n",p->no_navi);
				KK=p->from_MO3.from41.P_ANT_1-KK;

				if ((KK>pi/2)&&(p->from_MO3.from41.P_ANT_2>p->from_MO3.from41.P_ANT_1)) p->jump=-1;
					else if ((KK<-pi/2)&&(p->from_MO3.from41.P_ANT_2<p->from_MO3.from41.P_ANT_1)) p->jump=1;

				if (KK>4.71225)  p->jump=-1;	
				if (KK<-4.71225) p->jump=1;

				KK=KK+2*p->jump*pi;
				oldKK=KK; //��࠭�� ��⠭������� ������

	    		if (p->from_MO3.from41.beta_1>=0)	p->toPR1[2]=-p->from_MO3.from41.beta_1*C1;//���� ����
			    else p->toPR1[2]=(360+(-p->from_MO3.from41.beta_1*C3))*C2;//
				p->toPR1[0]=KK*RADtoGRAD/2+1991;//������
				oldKOD=p->toPR1[0];//��࠭���� ���� 㣫�	
				setANT=1;//�뫠 ����ன�� 㣫�� ��। ᥠ�ᮬ
			}
			else
			if (p->num_com==2) //ᥠ�� �裡 ��砫��
			{
			    memcpy(&b2,&p->Dout41[0],2);	 KK=b2*pi/(1<<14);	
				if (p->no_navi==1) KK=1.218; //printf("navi=%d\n",p->no_navi);
				KK=p->from_MO3.from41.P_ANT-KK;
				KK=KK+2*p->jump*pi;
				
				if (KK>2*PI) KK=KK-2*PI;
				if (KK<-2*PI) KK=KK+2*PI;
//!!!
				x=(double)KK;	
				if (x<0) {x+=2*PI;minus_x=1;} else minus_x=0;
				y=(double)p->from_MO3.from41.beta;
		//		PSI=(double)i*rad;		
		//		TETA=(double)i*rad;		// �ࠤ
				r1=cos(y);			r3=sin(y);
				r2=r1*cos(x);		r1=r1*sin(x);
				C=cos(-PSI);S=sin(-PSI);
				x1=C*r2+S*r3;		r3=C*r3-S*r2;
				S=sin(-TETA)*r1+cos(-TETA)*r3;
				y1=asin(S);
				prim=x1/cos(y1);	if (prim>1) prim=1;
				x1=acos(prim);
				if (abs(x1-x)>abs(2*PI-x1-x)) x1=2*PI-x1;
				if (minus_x==1) x1=x1-2*PI;
				x2=x-x1; //����� �� x
				y2=y-y1; //����� �� y
				//printf(" x0=%3.1f y0=%3.1f PSI=%3.1f TETA=%3.1f x1=%3.1f y1=%3.1f\n",
				//KK*grad,y*grad,PSI*grad,TETA*grad,x1*grad,y1*grad);
				
				KK=x1;

				oldKOD=p->PR1[0];
				oldKK=(oldKOD-1991)/325.94915;//������ ��⠭�������	

				if (KK!=oldKK)
				{
					deltaKK=KK-oldKK;

					//if (deltaKK>0) deltaKK-=0.01;else deltaKK+=0.01;  
					
					if (deltaKK>5) {deltaKK-=2*pi;printf("-\n");}  
					if (deltaKK<-5) {deltaKK+=2*pi;printf("+\n");}

					//deltaKK=deltaKK*RADtoGRAD/2;
					deltaKOD=(short)(deltaKK*RADtoGRAD/2);
					//deltaKOD=(short)deltaKK;
					//printf("P_ANT=%3.2f  KK=%3.2f  oldKK=%3.2f dKK=%3.2f dKOD=%d\n",
					//p->from_MO3.from41.P_ANT*57.32,KK*57.32,oldKK*57.32,deltaKK,deltaKOD);
						
					if (deltaKOD!=0)
					{
						p->toPR1[0]=oldKOD+deltaKOD;
					//	oldKOD=p->toPR1[0];
					//	oldKK=(oldKOD-1991)/325.94915;//������ ��⠭�������	
					//	printf("	toPR1=%d  deltaKOD=%d realKK=%f\n",p->toPR1[0],deltaKOD,oldKK);
					}
				}

				if (y1>=0)	p->toPR1[2]=-y1*C1;//���� ����
		    		else p->toPR1[2]=(360+(-y1*C3))*C2;//
			}
			else 
	    	//if ((p->num_com==4)||(p->num_com==5)) //4-� ��� 5-� ������� �� 4.2
	    	if (p->num_com==4) //4-� ��� 5-� ������� �� 4.2
			{	//�ࠢ����� ��. 1.0 �� 4.2
				//����
				//printf("Az%f Um=%f\n",p->from_MO3.from42.q,p->from_MO3.from42.beta);
    			if (p->from_MO3.from42.beta>=0)	p->toPR1[2]=-p->from_MO3.from42.beta*C1;//���� ����
		    	else p->toPR1[2]=(360+(-p->from_MO3.from42.beta*C3))*C2;//
			    if (p->from_MO3.from42.alfa>=0)	p->toPR1[1]=p->from_MO3.from42.alfa*C4;//KPEH
			    else p->toPR1[1]=0xFFF+(p->from_MO3.from42.alfa*RADtoGRAD)*12.27;
				p->toPR1[0]=p->from_MO3.from42.q*RADtoGRAD/2+1991;//������				
			
			}
			if (p->num_com==301) //4-� ��� 5-� ������� �� 4.2
			{	//�ࠢ����� ��. 1.0 �� 4.2 //����
    			if (p->from_MO3.fromAK.beta>=0)	p->toPR1[2]=-p->from_MO3.fromAK.beta*C1;//���� ����
		    	else p->toPR1[2]=(360+(-p->from_MO3.fromAK.beta*C3))*C2;//
				p->toPR1[0]=p->from_MO3.fromAK.Peleng*RADtoGRAD/2+1991;//������			
			}
			//-------------------------------------------------------------
			TIMER41=0;
			if (SIMF[1]<SIMF[0]) {p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr&0xffef;} //���� ᨬ�
			else {p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr|0x0010;} //��� ᨬ� 
			SIMF[1]=SIMF[0];
 			if (SIMF[3]<SIMF[2]) {p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr&0xfffd;} //���� ����
			else {p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr|0x0022;} //��� ᨬ� 
			SIMF[3]=SIMF[2];

			if ((p->to_MO3.to42.Mispr&0x0020)&&(p->to_MO3.to42.Mispr&0x0010)) p->Dout41[24]=0;
			else p->Dout41[24]=1;
  			//printf("ispr=%x simf=%x \n",p->to_MO3.to42.Mispr,p->Dout41[24]);
			//printf("n_k=%d \n",p->num_com);
			//printf("jmp=%d \n",p->jump);
		} //����� 3-� ����
		//-------------------------- 10 Hz -------------------------
		p->toPR1[3]=p->M[0];		p->toPR1[4]=p->M[1];
		p->toPR1[5]=p->M[2];		p->toPR1[6]=p->M[3];	

		for(i=0;i<3;i++) p->toPR1[i]=p->toPR1[i]&0x0fff;
		//-------------------------- 1 Pr -------------------------
		for(i=0;i<8;i++) toPR1[i]=p->toPR1[i];
		for(i=0;i<8;i++) printf("  %x",toPR1[i]);printf("\n");
		//printf("toPR1=%x from42=%f\n",toPR1[2],p->from_MO3.from41.beta);
	 	if((KK_frame(dev,Ynp_np1,2,acmd))==-1){owu6ka|=16;break;}

		if (p->to_MO3.to42.Mispr&0x0010) Write_ModB(); //�᫨ ��� ������樨 ����� � ����� �
		else if (N_TIMER&1) Write_ModB();//���� ���� 5 �� 
		break; 
 }// ----- end switch
} // ----- end CEPBEP for(;;)
}//----- end main()
