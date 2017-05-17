/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonClass.h"
#include "LessonX.h"
#include "CMyFighter.h"
#include "CBullet.h"
#include "CEnemyFighter.h"
#include<iostream>
#include<stdio.h>
#include "fstream"
using namespace std;
////////////////////////////////////////////////////////////////////////////////
//
//
CGameMain		g_GameMain;



//==============================================================================
//
// ����ĳ�������Ϊ��GameMainLoop����Ϊ��ѭ��������������ÿ֡ˢ����Ļͼ��֮�󣬶��ᱻ����һ�Ρ�

//==============================================================================
//
// ���캯��
CGameMain::CGameMain()
{
	m_iGameState			=	0;

    g_BeginSprite = new CSprite("GameBegin");  //GameBegin�������ǡ��ո�ʼ�����顣
    g_CurScoreText=new CTextSprite("CurScoreText");		//��ʾ��ǰ����
    g_MaxScoreText=new CTextSprite("MaxScoreText");// ��ʾ��߷�

    m_pMyFighter = NULL;

    m_iCreatedSpriteCount = 0;

    m_SpriteList = NULL;

    m_iMaxScore = 0;

}
//==============================================================================
//
// ��������
CGameMain::~CGameMain()
{
    if(m_pMyFighter!=NULL)
        delete m_pMyFighter;
}

//==============================================================================
//
// ��Ϸ��ѭ�����˺���������ͣ�ĵ��ã�����ÿˢ��һ����Ļ���˺�����������һ��
// ���Դ�����Ϸ�Ŀ�ʼ�������С������ȸ���״̬.
// ��������fDeltaTime : �ϴε��ñ��������˴ε��ñ�������ʱ��������λ����
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// ��ʼ����Ϸ�������һ���������
	case 1:
		{
			GameInit();
			SetGameState(2); // ��ʼ��֮�󣬽���Ϸ״̬����Ϊ������
		}
		break;

		// ��Ϸ�����У����������Ϸ�߼�
	case 2:
		{
			// TODO �޸Ĵ˴���Ϸѭ�������������ȷ��Ϸ�߼�
			if( !IsGameLost())
			{
				GameRun( fDeltaTime );
			}
			else // ��Ϸ������������Ϸ���㺯����������Ϸ״̬�޸�Ϊ����״̬
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// ��Ϸ����/�ȴ����ո����ʼ
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// ÿ�ֿ�ʼǰ���г�ʼ���������һ���������
void CGameMain::GameInit()
{
    g_BeginSprite->SetSpriteVisible( false );

    	// ������ҿ��Ƶ�Sprite
	if( NULL == m_pMyFighter )
	{
		m_pMyFighter	=	new CMyFighter("ControlSprite");
		//cout<<WORLD_LIMIT_STICKY<<endl;cout :5
        m_pMyFighter->SetSpriteWorldLimit(WORLD_LIMIT_STICKY,CSystem::GetScreenLeft()-10.f,
                                          CSystem::GetScreenTop(),CSystem::GetScreenRight() + 200.f,
                                          CSystem::GetScreenBottom());
        m_pMyFighter->m_iScore = 0;
	}

	// ���µ�ǰ�ȼ�/HP��ʾ
	g_CurScoreText->SetTextValue(0);
	g_MaxScoreText->SetTextValue(0);

	static bool bReadData = false;
    if( !bReadData )
    {
        bReadData = true;
        fstream ScoreFile("Score.dat",fstream::in | fstream::binary);
	if( ScoreFile.is_open() )
        {
            ScoreFile >> m_iMaxScore;
			ScoreFile.close();
		}
		//����������
		//cout<<"update MaxScore:"<<m_iMaxScore<<endl;
		g_MaxScoreText->SetTextValue( m_iMaxScore );
    }

	//if(m_SpriteList == NULL)
    m_SpriteList = new CSpriteList();
}
//=============================================================================
//
// ÿ����Ϸ������
void CGameMain::GameRun( float fDeltaTime )
{
    // ִ���ҷ�ս����ѭ��Tick����
    if( m_pMyFighter )
        m_pMyFighter->LoopTick( fDeltaTime );

    //ִ�ез�ս����ClassTick�����������л�
    CEnemyFighter::ClassTick( fDeltaTime );

    //���������е�ÿ���ڵ�(���ез�ս���������ӵ�����������ез�ս���Ľڵ㣬��ս��ִ��LoopTick������ʵ��ս�������ӵ������¸�����
    int	iListSize	=	m_SpriteList->GetListSize();
	for( int iLoop = 0; iLoop < iListSize; iLoop++ )
	{
	    const char* SpriteName = (m_SpriteList ->GetSprite( iLoop ))->GetName();
	    //cout<<(m_SpriteList ->GetSprite( iLoop ))->GetName()<<endl;
	    if(SpriteName[0]=='B')
            continue;
		CEnemyFighter *pSprite	=( CEnemyFighter *)m_SpriteList ->GetSprite( iLoop );
		if( NULL != pSprite )
		{

		   // cout<<pSprite->GetHp()<<endl;

			pSprite->LoopTick( fDeltaTime );

			//cout<<iLoop<<endl;
		}
	}

	if(IsGameLost())
    {
         if( m_iMaxScore < m_pMyFighter->GetScore() )
        {
        m_iMaxScore	=	m_pMyFighter->GetScore();
        // д�ļ�
        fstream ScoreFile("Score.dat",fstream::out | fstream::binary);
        if( ScoreFile.is_open() )
            {
            ScoreFile << m_iMaxScore;
            ScoreFile.close();
            }
        }

        GameEnd();
    }

}
//=============================================================================
//
// ������Ϸ����
void CGameMain::GameEnd()
{
    //m_SpriteList->DeleteAllSprite(true);//ɾ�������ӵ��͵ط�ս��
    cout<<"gameover"<<endl;
}

void CGameMain::OnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
    // ���¿ո���Ϸ��ʼ
    if( KEY_SPACE == iKey && 0 == GetGameState() )
        {
            SetGameState( 1 );
        }

    if( 2 == GetGameState() ) //����Ϸ״̬Ϊ2ʱ
        {
            m_pMyFighter->OnMove(true,iKey);
           // cout<<"press"<<endl;
        }

        // ��Ϸ�����У����¿ո����ӵ�
    if( KEY_SPACE == iKey && NULL != m_pMyFighter )
			m_pMyFighter->SetCanFire( true );
}

void CGameMain::OnKeyUp( const int iKey )
{
    if( 2 == GetGameState() )
    {
        m_pMyFighter->OnMove(false,iKey);
    }

    if( KEY_SPACE == iKey && NULL != m_pMyFighter )
        m_pMyFighter->SetCanFire( false );
}

void CGameMain::SetCurScore(int score)
{
    //
    //cout<<"update curScore:"<<score<<endl;
    g_CurScoreText->SetTextValue(score);
}

void CGameMain::CreateBullet( int iType,int iEnemySize, const float fPosX, const float fPosY )
{

	char	szName[MAX_NAME_LEN];// MAX_NAME_LEΪCommonClass.h�к궨�� ֵΪ128
	sprintf( szName, "Bullet_%d", m_iCreatedSpriteCount );//���� Bullet_%d �ĸ�ʽ���ַ���д�� szName
	m_iCreatedSpriteCount++;
	CBullet *pBullet = new CBullet(iType,iEnemySize,szName);
	if(iEnemySize==1)
        pBullet->CloneSprite( "Bullet1_Template" );
    else
        pBullet->CloneSprite( "Bullet2_Template" );

	pBullet->SetSpritePosition( fPosX, fPosY );
	pBullet->SetSpriteLinearVelocityX( 60 );
    pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,//���ϣ��ң���
                                 CSystem::GetScreenLeft()-10.f,CSystem::GetScreenTop(),
                                 CSystem::GetScreenRight() + 200.f, CSystem::GetScreenBottom());
    AddSprite( pBullet );//���뾫������
    //pBullet->SetDamage(100);
    //pBullet->SetHp(100);
    if( 1 == iType ) //���iTypeֵΪ1����˵���ӵ�Ϊ�з�ս�����䡣
	{
		pBullet->SetSpriteLinearVelocityX( -30 );

	}
	else    //�������˵��Ϊ�ҷ�ս������
	{
		pBullet->SetSpriteFlipX( true );
		pBullet->SetSpriteLinearVelocityX( 60 );

	}

}

void CGameMain::AddSprite( CSprite *pSprite )
{
			m_SpriteList->AddSprite( pSprite );
}

void  CGameMain::DeleteSprite( CSprite *pSprite ,bool bDeleteImage)
{
    m_SpriteList->DeleteSprite( pSprite , bDeleteImage );
}


CGameSprite *CGameMain::GetSprite( const int iIndex )
{

	CSprite	*pSprite	=	m_SpriteList->GetSprite( iIndex );
	return dynamic_cast<CGameSprite*>( pSprite );
}

CGameSprite *CGameMain::GetSprite( const char *szName )
{
	CSprite	*pSprite	=	m_SpriteList->GetSprite( szName );
	return dynamic_cast<CGameSprite*>( pSprite );
}


bool CGameMain::IsMyFighter( const char *szName )
{
	  return (strcmp( m_pMyFighter ->GetName(), szName ) == 0);
}

void CGameMain::OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
    /*
    //�ҷ�ս�����ӵ���1����ײ
    if(szSrcName[0]=='B'&&szTarName[0]=='C'||szSrcName[0]=='C'&&szTarName[0]=='B')
    {
        ;
    }
    //�ҷ�ս����з�ս��

    //�ӵ���0����з�ս��
    */
    //if(szSrcName[0]==szTarName[0])
    //    cout<<szSrcName<<szTarName<<endl;

    if( 2 != GetGameState() )
		return;
	CGameSprite	*pSrcSprite	=	IsMyFighter (szSrcName ) ? m_pMyFighter :	GetSprite( szSrcName );
	CGameSprite *pTarSprite	=	IsMyFighter (szTarName ) ? m_pMyFighter :	GetSprite( szTarName );

	if( NULL == pSrcSprite || NULL == pTarSprite )
		return;
	pSrcSprite->OnColOtherSprite( pTarSprite );
	pTarSprite->OnColOtherSprite( pSrcSprite );
/*
	if( !pSrcSprite-> IsMyFighter () )
	{
		if( pSrcSprite->IsDead() )
			g_GameMain.DeleteSprite( pSrcSprite, true );
	}
    if( !pTarSprite-> IsMyFighter () )
	{
		if( pTarSprite->IsDead() )
			g_GameMain.DeleteSprite( pTarSprite, true );
	}
	*/
}

void CGameMain::OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
    //CGameSprite	*pSprite = GetSprite(szName);
    if((szName[0]=='H'||szName[0]=='B')&&iColSide==0)//���
    {
        m_SpriteList->DeleteSprite(szName,true);
    }
    if(szName[0]=='B'&&iColSide==1)
    {
        m_SpriteList->DeleteSprite(szName,true);

    }
}

bool CGameMain::IsGameLost()
{
    if(m_pMyFighter==NULL)
        cout<<"���ս����ɾ��"<<endl;
	return ( m_pMyFighter ? m_pMyFighter->IsDead() : false );
}


