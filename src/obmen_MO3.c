  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/kernel.h>

  #include <netinet/in.h>
  #include <stdio.h>
  #include <unistd.h>
  #include <stdlib.h>
  #include <netdb.h>
  #include <math.h>
  #include "../include/shared_mem.h"
  #include "../include/gloriya.h"
  #include "../include/IO_DT_SOI.h"
  #include "../include/func_IP.h"

  #define PKDMV 0x0001
  #define PKVH  0x0002
  #define PKPRD 0x0004
  #define PKPRM 0x0008
  #define PKVIH 0x0010
  #define PKZA  0x0020
  #define RES90 0x0200
  #define SVC   0x0400
  #define SVCFC 0x0800

  #define SRC_PORT41 8208
  #define DST_PORT41 8208

  # define max_len_OUT    4096*8
  # define max_len_IP     4096*8


	float Mc=64.*1852./32384./3600., Dbl, Flt=0;
	int sock, length, i , count_mes=0;
	static Udp_Client_t Uc41,Uc42;
	char bufi[1024];
	char bufo[1024];
	char gloria_start=0;	
	char gloria_count=0;	
	unsigned int pr1_c_old=0;
	unsigned int AK_c=0; //���稪 ������ ��᫥ ����㯫���� ������� ��
	short bM4; //���� ��� M4
	short cr_com41=0,cr_com42=0,cr_comAK=0;
	char out_buf[1024];
	//obmen_41_31_t from41;	
	//obmen_31_41_t to41;	
	paramAKcom=0;
	simfonia41_t simfonia;	
	int r,bytes,byta4;
	pid_t pid_CEP;
	short MK2[15];
	//unsigned short buf;
	short byta2,T,len_OUT,sen,j;
    div_t   vol;    // vol.quot - ������⢮ ������ ⮬��
    char          pack_buf[1500];  // ���� ����� obm_41_31. ��室�� ����� � Socket
    char                 numb_pack,     // ⥪�騩 ����� �����
                         numb_vol;      // ⥪�騩 ����� ⮬� � �����

struct
   { 
     char      out_buf[max_len_OUT];  // ����� ��� Socket'a
   } ip_out; 

	  
main ()
{
float 	C1,C2,C3,C4,C5,C6,C7,C8;
unsigned short cr_com; //���浪��� ����� �।��饩 �������
		short		V,dV;
int cnt=0;
int i1=0,i2;
int rez;
unsigned short buf[4];
float Angle0;
 C1=2048./pi;C2=4096.0/360.0;C3=180./pi;C4=C1*Kncu;
 C5=C2*Kncu;C6=C1*Kq;C7=C3;C8=C2*Kq;
//���� �ࢥ�
//qnx_name_attach(0,"4.1");
//���樠������ ������ UDP
	i = Udp_Client_Ini(&Uc41,"194.1.1.6",SRC_PORT41,DST_PORT41);
	printf(" Udp_Init=%d	\n", i);
			
	//gloriya(1,1,31);//test K2 �� 㬮�砭��
	//gloriya(1,1,1);//work K2
	//gloriya(1,0,2);//work K1
	gloriya(1,0,31);//test K2 �� 㬮�砭��

	delay(2000);
	open_shmem();
	delay(1000);

	//Angle0=4;
	//p->jump=-1;

while(1)
  {
	//for(i=0;i<sizeof(obmen_41_31_t);i++) bufi[i]=0;

	bytes = Udp_Client_Read(&Uc41,bufi,4096);
//	printf(" read=%d size1=%d size2=%d size3=%d sizeALL=%d\n",
//	bytes,sizeof(obmen_42_31_2t),sizeof(obmen_41_31_2t),sizeof(obmen_AK_MN3_MO3K_t),sizeof(obmen_MO3_MO3K_t));

    memcpy(&p->from_MO3,&bufi[4],sizeof(obmen_MO3_MO3K_t)); 
	//�롮� �ࠢ����1 �������
	if (p->from_MO3.from42.cr_com!=cr_com42) 
	{
		printf(" New Command 4.2 = %d  cr_com = %d\n",
			p->from_MO3.from42.num_com,p->from_MO3.from42.cr_com);

		p->num_com=p->from_MO3.from42.num_com;
		cr_com42=p->from_MO3.from42.cr_com;
		if (p->num_com==5)
		{
			p->M[0]=p->from_MO3.from42.M1;
			p->M[1]=p->from_MO3.from42.M2;
			p->M[2]=p->from_MO3.from42.M3;
			p->M[3]=p->from_MO3.from42.M4;
			buf[0]=0;	//��ॢ��稢��� �ࠢ���騥 ᫮�� ��. 1
			for(i1=0;i1<16;i1++) {buf[0]+=((p->M[0]>>i1)&1)<<(15-i1);} p->M[0]=buf[0];buf[0]=0;
			for(i1=0;i1<16;i1++) {buf[0]+=((p->M[1]>>i1)&1)<<(15-i1);} p->M[1]=buf[0];buf[0]=0;
			for(i1=0;i1<16;i1++) {buf[0]+=((p->M[2]>>i1)&1)<<(15-i1);} p->M[2]=buf[0];buf[0]=0;
			for(i1=0;i1<16;i1++) {buf[0]+=((p->M[3]>>i1)&1)<<(15-i1);} p->M[3]=buf[0];buf[0]=0;
		}
	}
	if ((p->from_MO3.fromAK.cr_com!=cr_comAK)&&(p->from_MO3.fromAK.num_com!=0)) 
	{
		p->num_com=p->from_MO3.fromAK.num_com;
		cr_comAK=p->from_MO3.fromAK.cr_com;
		pr1_c_old=p->pr1_c;	//��࠭�� ���稪 ������ � ��.1
		AK_c=1;
		p->to_MO3.toAK.kzv=0;
		printf(" New Command AK = %d , p[0]=%d , cr_com = %d\n",
				p->from_MO3.fromAK.num_com,p->from_MO3.fromAK.a_params[0],p->from_MO3.fromAK.cr_com);
		p->M[2]=0x0001; //���� ��
		bM4=0;
		paramAKcom=0;
		switch(p->num_com)
		{
			case 260 : case 290 :	paramAKcom=1;break;//8410
			case 264 :				paramAKcom=2;break;
			case 265 : 	switch(p->from_MO3.fromAK.a_params[0])
						{
							case 2:	case 3: paramAKcom=3;break; 
							case 4: case 5: 
							case 6:	case 7: 
							case 8: case 9: paramAKcom=4;break;
						}
						break;
			case 292 : 	switch(p->from_MO3.fromAK.a_params[0])
						{
							case 1: paramAKcom=1;break;
							case 3:	paramAKcom=2;break;//C430
							case 5: paramAKcom=3;break;//9450
						}
						break;
			case 300 : 	switch(p->from_MO3.fromAK.a_params[0])
						{
							case 0: paramAKcom=1;break;
							case 1:	paramAKcom=3;break;
						}
						break;
		}
		switch(paramAKcom)
		{
			case 1 : p->M[3]=0x8410;printf("M=1\n");break;
			case 3 : p->M[3]=0xC430;printf("M=3\n");break;
			case 2 : p->M[3]=0x9450;printf("M=2\n");break;
			case 4 : p->M[3]=0xC410;printf("M=4\n");break;
		}
	}

	if (p->from_MO3.from41.cr_com!=cr_com41) 
	{
		p->num_com=p->from_MO3.from41.num_com;
		cr_com41=p->from_MO3.from41.cr_com;
		p->M[0]=0x0000;
		p->M[1]=0x000e;
		p->M[2]=0x0000;
		p->M[3]=0x8410;		
		printf(" New Command 4.1 = %d\n",p->num_com);
	}
	
	//printf("V=%d\n",V);
	//printf("V=%f\n",p->from41.Vr);
	//for(i=4;i<20;i++) printf("%x ",bufi[i]);printf("\n");
	//printf("crcom=%x n_com=%x NKS=%x NSHKR=%x Nd_FR4=%x N_FR4=%x ZUNf=%x N_psp=%x Vr=%f Ar=%f\n",
	//p->from41.cr_com,p->from41.num_com,p->from41.num_KS,
	//p->from41.Nkey_SHAKR,p->from41.Nd_FRCH,p->from41.N_FRCH,
	//p->from41.ZUNf,p->from41.Nans_PSP,p->from41.Vr,p->from41.Ar);

	//SIMFONIA
	buf[0]=p->Dout41[7]; 
	buf[1]=p->Dout41[6];
 	buf[2]=p->Dout41[9];
	buf[3]=p->Dout41[8];		
 
	p->simfonia41.status1=p->Dout41[24];
    //memcpy(&byta2,&p->Dout41[0],2);	 Flt=byta2*pi/(1<<14); p->simfonia41.Kg=Flt;// printf("Kypc=%8.4f \n",Flt);
    memcpy(&byta2,&p->Dout41[4],2);	 Flt=byta2*Mc;p->simfonia41.V=Flt;	
    memcpy(&byta4,&buf[0],4);	 Flt=byta4*pi/(1<<31);p->simfonia41.fi=-Flt;// printf("Fi=%f \n",Flt*180/pi);
    memcpy(&byta4,&buf[2],4);	 p->simfonia41.la=-(byta4*pi/(1<<31));	

    memcpy(&byta2,&p->Dout41[10],2); p->simfonia41.a=byta2*32000./(1<<15);	
    memcpy(&byta2,&p->Dout41[11],2); p->simfonia41.b=byta2*32000./(1<<15);	
    memcpy(&byta2,&p->Dout41[12],2); p->simfonia41.tau=byta2*pi/(1<<15);	
    memcpy(&byta2,&p->Dout41[13],2); p->simfonia41.status2=byta2;	


//	printf("%02x%02x	",p->Dout41[6],p->Dout41[7]);
//  printf("Kg=%4.3f V=%4.3f fi=%4.3f ",p->to41.simfonia41.Kg, p->to41.simfonia41.V,p->to41.simfonia41.fi);
//	printf("la=%4.3f a=%4.3f b=%4.3f ",p->to41.simfonia41.la,p->to41.simfonia41.a,p->to41.simfonia41.b);
//	printf("tau=%4.3f st=%d \n",p->to41.simfonia41.tau,p->to41.simfonia41.status2);
// 	printf("st1=%x st2=%x\n",p->to41.simfonia41.status1,p->to41.simfonia41.status2);

	if (p->U.SUM_20==0) p->to_MO3.to41.Fd_FACT=0;
		else p->to_MO3.to41.Fd_FACT=-(float)0.24414*p->U.DPL_1;
	//printf("d=%d\n",p->U.DPL_1);

	//p->to_MO3.to41.UR_sign_K1=(short)p->U.SUM_20;	
	if (p->to_MO3.to41.UR_sign_K1>17) p->to_MO3.to41.PrM_K1=1;else p->to_MO3.to41.PrM_K1=0;

//	printf("                                Angle_Pr1 b=%4.3f q=%4.3f   \n",p->to_MO3.to41.beta_FACT*57.3,p->to_MO3.to41.P_FACT*57.3);
//	printf(" Angle_PR4 = %4.3f %4.3f\n",p->from_MO3.from41.beta*57.3,p->from_MO3.from41.P_ANT*57.3);
//	printf("					 P_ANT = %4.3f", p->from_MO3.from41.P_ANT*57.3);
//	printf(" P_FACT = %4.3f  com42=%d \n",p->to_MO3.to41.P_FACT*57.3,p->from42.num_com);

	//printf("n_com1=%d cr_com=%d\n",p->from_MO3.from41.num_com,p->from_MO3.from41.cr_com);
	//printf("Angl 2=%02f r=%f NK%d  \n",from41.P_ANT,p->to_MO3.to41.P_FACT,from41.num_com);

	//��⮢����� � ᥠ��� �裡
	if (p->num_com==1) i2++; //��⠥� �६� �� ��ࢮ� ��� ��� ᥠ��
	if ((gloria_start==0)&&((p->num_com==1)||(p->num_com==2)))
	{
		if ((p->from_MO3.from41.Nkey_SHAKR<=31)&&(p->from_MO3.from41.Nkey_SHAKR>=0)) 
			{rez=gloriya(1,p->from_MO3.from41.num_KS-1,p->from_MO3.from41.Nkey_SHAKR);gloria_start=1;}
		else printf("Error Gloriya Key %d \n",p->from_MO3.from41.Nkey_SHAKR);
		if (rez) p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr&0xFEFF;else p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr|0x0100;
	}

	if (p->num_com==2) 
	{
		gloria_count++;
		if (gloria_count>50)
		{
			rez=gloriya_read();
			if (rez) p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr&0xFEFF;else p->to_MO3.to42.Mispr=p->to_MO3.to42.Mispr|0x0100;
			gloria_count=0;
		}
	}
	if (i2>30) 	{p->to_MO3.to41.pr_GSS=1;i2=0;}
	if (p->num_com==3) gloria_start=0;
	///printf("GSS=%d ",p->to_MO3.to41.pr_GSS);

	cr_com=p->from_MO3.from41.cr_com;
	//�ਧ��� ���ᮯ஢������� �� �1
	//p->to_MO3.to41.pr_AS=1;
	//�ਧ��� �ਥ�� ������ �� �2
	//p->to_MO3.to41.pr_PD=1;

/////////////////////////////////////////////////////////////////////	
	buf[0]=0;
	for(i1=0;i1<16;i1++) {buf[0]+=((p->from_MO3.from42.M1>>i1)&1)<<(15-i1);} p->from_MO3.from42.M1=buf[0];buf[0]=0;
	for(i1=0;i1<16;i1++) {buf[0]+=((p->from_MO3.from42.M2>>i1)&1)<<(15-i1);} p->from_MO3.from42.M2=buf[0];buf[0]=0;
	for(i1=0;i1<16;i1++) {buf[0]+=((p->from_MO3.from42.M3>>i1)&1)<<(15-i1);} p->from_MO3.from42.M3=buf[0];buf[0]=0;
	for(i1=0;i1<16;i1++) {buf[0]+=((p->from_MO3.from42.M4>>i1)&1)<<(15-i1);} p->from_MO3.from42.M4=buf[0];buf[0]=0;

//	printf("M1=%x\n",p->from_MO3.from42.M1);
//	printf("M2=%x\n",p->from_MO3.from42.M2);
//	printf("M3=%x\n",p->from_MO3.from42.M3);
//	printf("M4=%x\n",p->from_MO3.from42.M4);

	//��� ������
	if (p->num_com==9) p->toPR1[6]=0xFA30;

	if (p->num_com==12) p->no_navi=1;	
	if (p->num_com==13) p->no_navi=0;	

	//printf("cr_com=%x n_com=%x NKS=%d NSHKR=%x Nd_FR4=%d N_FR4=%x ZUNf=%x N_psp=%x Vr=%f Ar=%f\n",
	//p->from41.cr_com,p->from41.num_com,p->from41.num_KS,
	//p->from41.Nkey_SHAKR,p->from41.Nd_FRCH,p->from41.N_FRCH,
	//p->from41.ZUNf,p->from41.Nans_PSP,p->from41.Vr,p->from41.Ar);
	
		
//	printf(" %04x   %04x   %04x   %04x ",p->from_MO3.from42.M1,p->from_MO3.from42.M2,p->from_MO3.from42.M3,p->from_MO3.from42.M4);
//	printf(" CR=%d NC=%d \n",p->from_MO3.from42.cr_com,p->from_MO3.from42.num_com);
//  printf("\n");  
  
//	p->to_MO3.to42.Ms1=p->PR1[3];   //���ﭨ� �ਡ�� 1.0
//	p->to_MO3.to42.Ms2=p->PR1[4];
//	p->to_MO3.to42.Ms3=p->PR1[5];
	p->to_MO3.to42.USign=p->PR1[6]; //�஢��� ᨣ���� ��� �� ��� ��1.0

	
//	p->to_MO3.to42.sum_K1=p->U.SUM_4;
//	p->to_MO3.to42.sum_K1=p->U.SUM_20; //�뢮���� ��᫥ �����䬠
	

	p->to_MO3.to42.D_K1=(float)p->U.DPL_1*244.14;

	//printf("DPL=%x\n",p->U.DPL_1);
    //����
	p->to_MO3.to42.q=(p->PR1[0]-1991)*2/RADtoGRAD; //������
	if (p->PR1[2]&0x800) p->to_MO3.to42.beta=(360-p->PR1[2]/C2)/C3; //���� �����
	else p->to_MO3.to42.beta=-p->PR1[2]/C1;
	if (p->PR1[1]&0x800) p->to_MO3.to42.alfa=(p->PR1[1]-0xFFF)/12.27/RADtoGRAD;//����
	else p->to_MO3.to42.alfa=p->PR1[1]/C4; 

	for(i1=0;i1<16;i1++) {buf[0]+=((p->to_MO3.to42.Ms1>>i1)&1)<<(15-i1);} p->to_MO3.to42.Ms1=buf[0];buf[0]=0;
	for(i1=0;i1<16;i1++) {buf[0]+=((p->to_MO3.to42.Ms2>>i1)&1)<<(15-i1);} p->to_MO3.to42.Ms2=buf[0];buf[0]=0;
	for(i1=0;i1<16;i1++) {buf[0]+=((p->to_MO3.to42.Ms3>>i1)&1)<<(15-i1);} p->to_MO3.to42.Ms3=buf[0];buf[0]=0;

//	printf("1=%04x 2=%04x 3=%04x\n",Priem[1],Priem[2],Priem[3]);
//	for(i1=0;i1<16;i1++) {buf+=((Priem[7]>>i1)&1)<<(15-i1);} Priem[8]=buf;buf=0;

//	p->to_MO3.to42.Ms1=p->to_MO3.to42.Ms1|0x5;   //���ﭨ� �ਡ�� 1.0
//    printf("%04x ",p->to_MO3.to42.Ms1);
// printf("%04x ",p->to_MO3.to42.Ms2);
// printf("%04x ",p->to_MO3.to42.Ms3);printf("\n");

//	printf(" q=%8.4f a=%8.4f b=%8.4f \n",p->to_MO3.to42.q,p->to_MO3.to42.alfa,p->to_MO3.to42.beta);
//	p->to_MO3.to42.q=p->to_MO3.to42.alfa=p->to_MO3.to42.beta=1;
//	if ((p->PR1[3]&0x0008)&&(p->PR1[5]&0x0004)) printf("!!!\n");    
//	for(i=0;i<3;i++) printf("%04x ",p->PR1[3+i]);printf("\n");
////////////////////////////UPR AK//////////////////////////////////////
	if (AK_c>0) //����� � ����� �������� ��
	{
		if (p->pr1_c - pr1_c_old>10) //����� 2 �⢥⮢ �� ��.1
		{
			p->to_MO3.toAK.cr_com=p->from_MO3.fromAK.cr_com;
			p->to_MO3.toAK.num_com=p->from_MO3.fromAK.num_com;
			p->to_MO3.toAK.lp2_param=p->from_MO3.fromAK.a_params[0];
			p->to_MO3.toAK.kzv=1;
			AK_c=0;
			printf("paramAKcom=%d\n",paramAKcom);
			switch(paramAKcom)
			{
				case 1 : case 3: case 4: 
//					if ((p->PR1[3]&0x0004)&&(p->PR1[5]&0x0004)) p->to_MO3.toAK.kzv=0;	break;
					if (p->PR1[3]&0x0004) p->to_MO3.toAK.kzv=0;	break;
				case 2 : 		  
					if ((p->PR1[3]&0x0004)&&(p->PR1[5]&0x0006)) p->to_MO3.toAK.kzv=0;	break;
//					if (p->PR1[3]&0x0004) p->to_MO3.toAK.kzv=0;	break;

			}
			//p->M[3]=p->M[3]&0xFFFE; //�⪫�祭�� �� ��� ��
			printf("����砭�� ������� %d. kzv=%d pr1.3=%x pr1.5=%x\n",p->to_MO3.toAK.num_com,p->to_MO3.toAK.kzv,p->PR1[3],p->PR1[5]);

			}
		else 	if (AK_c>10)  //2
				{
					p->to_MO3.toAK.cr_com=p->from_MO3.fromAK.cr_com;
					p->to_MO3.toAK.num_com=p->from_MO3.fromAK.num_com;
					p->to_MO3.toAK.lp2_param=p->from_MO3.fromAK.a_params[0];
					p->to_MO3.toAK.kzv=1;
					AK_c=0;
					printf("����砭�� ������� %d. ��� �⢥� �� ��. 1. kzv=1\n",p->to_MO3.toAK.num_com);
				}
				else AK_c++; 
	}

	//printf("pr1_c=%d pr1_c_old=%d AK_c=%d\n",p->pr1_c,pr1_c_old,AK_c);
	//printf("num_com=%d kzv=%x\n",
	//    p->from_MO3.fromAK.num_com,p->to_MO3.toAK.kzv);


//////////////////////////////////////////////////////////////////////
  	len_OUT = sizeof(obmen_MO3K_MO3_t); //!!!!
    memcpy(ip_out.out_buf,&p->to_MO3,sizeof(obmen_MO3K_MO3_t)); ///!!!!!!
    if (len_OUT <= 1400) 
    {
         pack_buf[0] = 80 ;               
         pack_buf[1] = numb_pack;
         pack_buf[2] = 1;
         pack_buf[3] = 1;
         for (j = 0; j<1400; j++) pack_buf[j+4] = ip_out.out_buf[j];
         sen = Udp_Client_Send(&Uc41,pack_buf,(len_OUT+4));
    }
    else
    {
         pack_buf[0] = 81 ;               
         vol = div(len_OUT,1400);
         pack_buf[1] = numb_pack;
         pack_buf[2] = 1;
         pack_buf[3] = vol.quot + 1;
         for (numb_vol = 1;numb_vol <=vol.quot; numb_vol++)
         {
           for (j = 0; j<1400; j++) {pack_buf[j+4] = ip_out.out_buf[(1400*(numb_vol-1))+j]; }
           Udp_Client_Send(&Uc41,pack_buf,1404);
		   if (numb_vol==3) delay(2);//5 10
		   if (numb_vol==6) delay(2);
		   if (numb_vol==9) delay(2);
		   if (numb_vol==12) delay(2);

           pack_buf[2] ++ ;
         }
                
         for (j = 0; j<vol.rem; j++) pack_buf[j+4] = ip_out.out_buf[(1400*(vol.quot))+j]; 
          Udp_Client_Send(&Uc41,pack_buf,(vol.rem + 4));
    }
          numb_pack ++;
  }   
}
