/////////////////////////////////////////////////////////////////////////
///// �������� ������ ��.��3 � �⠭樨 ��3� 						/////
/////  � ࠬ��� ����樮����� ������ �� ࠡ�� � ०��� ��1�		/////
/////////////////////////////////////////////////////////////////////////
//pdn [���.17.12.2012]
typedef struct	{
	unsigned short	cr_com;	//���浪��� ����� ��᫥���� �믮������� �������  
							//0-USHRT_MAX
	short	num_com;		//����� ��᫥����� ������� �� �����
	int		lp2_param;	//���祭�� ��ࠬ��� ��᫥���� �������

	short	kzv;			//��� �����襭�� ��᫥���� ������� (0 - ��ଠ, 1 - �� ��ଠ(�訡��), 2 - ������� �⬥����)

} obmen_AK_MO3K_MN3_t;


typedef struct	{
	unsigned short	cr_com;	//���浪��� ����� ��᫥���� �������, �뤠���� �� ��.��3 � ��.��3� 
							//0-USHRT_MAX

	short num_com;		//����� ��᫥����� ������� �� �����
	int	 a_params[5];	//���ᨢ ��ࠬ��஢ ������� �ࠢ�����

	short	Pr_bearing; //�ਧ��� ��।�� ������� (0-�⪫,1-���)
	float	Peleng;		//������ ������. �१ 1 ᥪ., ࠤ
	float	beta;	//㣮� ���� ��⥭�� �१ 1 ᥪ., ࠤ

} obmen_AK_MN3_MO3K_t;
/////////////////////////////////////////////////////////////////////////

