#include "CEnemyFighter.h"
#include"LessonX.h"
#include<stdio.h>
#include<iostream>
using namespace std;

float CEnemyFighter::m_fCreateTime = 0.f;
int CEnemyFighter::m_iCreatedSpriteCount = 0;

CEnemyFighter::CEnemyFighter(const char* szName):CGameSprite(szName)
{
    //ctor
    m_fCanFireAfterCreated = 1.f;//1s �󱻿�����֮����Կ���
    m_fBulletCreateTime = 1.f;//ÿ��1S����һö�ӵ�
    m_fFloatTime = 1.f;
    m_bFloatUp = false;
    m_iHp = 200;
    m_iDamage = 100;//��������л�hp-100
    m_iScore = 2;
    m_iSize = 0;
}

void CEnemyFighter::ClassTick( float fDeltaTime ) //�����з�ս��
{
	// �Ƿ�ʱ�䴴��
	m_fCreateTime -= fDeltaTime;
	if( m_fCreateTime <= 0.f )
	{
		// ���һ��ʱ�䣬��Ϊ�´γ�����ʱ��
		m_fCreateTime	=	(float)CSystem::RandomRange( 3, 8 );
        //��������Ӵ���һ�ܵз�ս���Ĵ���
        int iPosBase = CSystem::RandomRange((int)CSystem::GetScreenTop()+10,
                                         (int)CSystem::GetScreenBottom() - 10);
        char	szName[MAX_NAME_LEN];
        sprintf(szName,"HorizontalSprite_%d", m_iCreatedSpriteCount); //���½��ĵз�ս������
        m_iCreatedSpriteCount++;
        //���������С��ս��
        CEnemyFighter *pSprite	=	new CEnemyFighter( szName );
        //ս���ͺŴ�Сm_iSize: 3,2,1,0�ֱ��Ӧ enemyTemplate[4-m_iSize];
        const char* enemyTemplate[4] = {"BigBoss_Template","VerticalSprite_Template",
                                    "HorizontalSprite_Template" ,"RotateSprite_Template"};
        int randomNum = CSystem::RandomRange(0,10);
        const char* tmpName;
        if(randomNum>=0&&randomNum<4)
            {
                pSprite->SetSize(0);
                tmpName = enemyTemplate[3];
                pSprite->SetHp(400);
                pSprite->SetDamage(200);//��������л�hp-200
                pSprite->SetScore(5);

            }
        else if(randomNum>=4&&randomNum<7)
            {

                pSprite->SetSize(1);
                tmpName = enemyTemplate[2];
                pSprite->SetHp(350);
                pSprite->SetDamage(150);//��������л�hp-150
                pSprite->SetScore(4);

            }
        else if(randomNum>=7&&randomNum<9)
            {
                pSprite->SetSize(2);
                tmpName = enemyTemplate[1];
                pSprite->SetHp(300);
                pSprite->SetDamage(100);//��������л�hp-100
                pSprite->SetScore(3);
            }
        else if(randomNum>=9&&randomNum<=10)
            {
                pSprite->SetSize(3);
                tmpName = enemyTemplate[0];
                pSprite->SetHp(250);
                pSprite->SetDamage(50);//��������л�hp-50
                pSprite->SetScore(2);

            }

        pSprite->CloneSprite( tmpName );  //��¡ģ��
        int	iRandom	=	CSystem::RandomRange( iPosBase - 10, iPosBase + 10 );
        float	fPosX	=	(int)CSystem::GetScreenRight() + 20.f;
        pSprite->SetSpritePosition( fPosX, (float)iRandom );
        pSprite->SetSpriteLinearVelocityX( -10.f );
        pSprite->SetSpriteWorldLimit(WORLD_LIMIT_KILL,
                             CSystem::GetScreenLeft()-10.f,CSystem::GetScreenTop(),
                             CSystem::GetScreenRight() + 200.f,CSystem::GetScreenBottom() );
        //��ӵз�ս��������������
        g_GameMain.AddSprite( pSprite );
	}
}

void CEnemyFighter::LoopTick( float fDeltaTime )//ʵ����������δ���ô˷��������Բ������¸���
{
   // cout<<"up and down"<<endl;
        float	fPosY	=	GetSpritePositionY();
		if( m_bFloatUp )
		{
			m_fFloatTime += fDeltaTime;
			if( m_fFloatTime >= 2.f )
			{
				m_bFloatUp = false;
			}

			fPosY			+=	6.f * fDeltaTime;
			SetSpritePositionY( fPosY );

           // cout<<fPosY<<endl;
		}
		else
		{
			m_fFloatTime -= fDeltaTime;
			if( m_fFloatTime <= 0.f )
			{
				m_bFloatUp = true;
			}
			//float	fPosY	=	GetSpritePositionY();
			fPosY			-=	6.f * fDeltaTime;
			SetSpritePositionY( fPosY );
			//cout<<"fudonghou:"<<fPosY<<endl;
		}
		m_fCanFireAfterCreated -= fDeltaTime;
		if( m_fCanFireAfterCreated <= 0.f )//������
		{
			m_fBulletCreateTime -= fDeltaTime;
			if( m_fBulletCreateTime <= 0.f )
			{
				m_fBulletCreateTime = 1.f;
				if(GetSpritePositionX()==0&&GetSpritePositionY()==0)
                    {
                        cout<<GetName()<<endl;
                        g_GameMain.DeleteSprite(this,true);
                    }
                else
                {
                    //cout<<"�ӵ��ͺţ�"<<GetHp()%10+1<<endl;

                    g_GameMain.CreateBullet(1,(GetSize()==3)?2:1,GetSpritePositionX(),fPosY
                                              //GetSpritePositionY()
                                            );
               // cout<<g_GameMain.GetM_SpriteList()->GetListSize()<<endl;
              //  cout<<"zidan: "<<GetSpritePositionY()<<endl;
                }
			}
		}
}

void CEnemyFighter::PlayEffect(int iSize,const float fPosX, const float fPosY, const float fRotation)
{
    const char* tmpName;//boss-iSize:3 ,���μ�С
    switch(iSize)
    {
    case 3: tmpName = "bigExplode";
        break;
    case 1:case 2: tmpName = "enemyExplode";
        break;
    case 0: tmpName = "smallExplode";
        break;
    default:
        break;
    }
    //cout<<tmpName<<endl;
    CEffect*    boom = new CEffect(tmpName,"",3.f);
    boom->PlayEffect(fPosX,fPosY,fRotation);

}

void CEnemyFighter::OnColOtherSprite( CGameSprite *pOther )
{
   // cout<<"enemy"<<endl;
    if( NULL == pOther )
		return;
	if( pOther-> IsMyFighter () || pOther-> IsMyBullet () )//��ҵ��ӵ������ս��
	{
		SetHp( GetHp() - pOther->GetDamage() );
		if(IsDead())
            {
                g_GameMain.GetMyFighter()->SetScore( g_GameMain.GetMyFighter()->GetScore() + GetScore() );

                //ɾ��ս����������Ч
                    int iSize = GetSize();
                    float x = GetSpritePositionX();
                    float y = GetSpritePositionY();
                    g_GameMain.GetM_SpriteList()->DeleteSprite(this,true);
                    PlayEffect(iSize,x,y,0.f);

                //SetScore(0);
            }
	}
}


CEnemyFighter::~CEnemyFighter()
{
    //dtor
}
