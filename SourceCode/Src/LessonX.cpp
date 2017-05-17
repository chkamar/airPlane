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
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。

//==============================================================================
//
// 构造函数
CGameMain::CGameMain()
{
	m_iGameState			=	0;

    g_BeginSprite = new CSprite("GameBegin");  //GameBegin就是我们“空格开始”精灵。
    g_CurScoreText=new CTextSprite("CurScoreText");		//显示当前积分
    g_MaxScoreText=new CTextSprite("MaxScoreText");// 显示最高分

    m_pMyFighter = NULL;

    m_iCreatedSpriteCount = 0;

    m_SpriteList = NULL;

    m_iMaxScore = 0;

}
//==============================================================================
//
// 析构函数
CGameMain::~CGameMain()
{
    if(m_pMyFighter!=NULL)
        delete m_pMyFighter;
}

//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态.
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			SetGameState(2); // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( !IsGameLost())
			{
				GameRun( fDeltaTime );
			}
			else // 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
			{
				SetGameState(0);
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}
//=============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void CGameMain::GameInit()
{
    g_BeginSprite->SetSpriteVisible( false );

    	// 创建玩家控制的Sprite
	if( NULL == m_pMyFighter )
	{
		m_pMyFighter	=	new CMyFighter("ControlSprite");
		//cout<<WORLD_LIMIT_STICKY<<endl;cout :5
        m_pMyFighter->SetSpriteWorldLimit(WORLD_LIMIT_STICKY,CSystem::GetScreenLeft()-10.f,
                                          CSystem::GetScreenTop(),CSystem::GetScreenRight() + 200.f,
                                          CSystem::GetScreenBottom());
        m_pMyFighter->m_iScore = 0;
	}

	// 更新当前等级/HP显示
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
		//更新最大积分
		//cout<<"update MaxScore:"<<m_iMaxScore<<endl;
		g_MaxScoreText->SetTextValue( m_iMaxScore );
    }

	//if(m_SpriteList == NULL)
    m_SpriteList = new CSpriteList();
}
//=============================================================================
//
// 每局游戏进行中
void CGameMain::GameRun( float fDeltaTime )
{
    // 执行我方战机的循环Tick函数
    if( m_pMyFighter )
        m_pMyFighter->LoopTick( fDeltaTime );

    //执行敌方战机的ClassTick函数，创建敌机
    CEnemyFighter::ClassTick( fDeltaTime );

    //遍历链表中的每个节点(存有敌方战机和所有子弹），获得所有敌方战机的节点，让战机执行LoopTick方法，实现战机发射子弹和上下浮动。
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
        // 写文件
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
// 本局游戏结束
void CGameMain::GameEnd()
{
    //m_SpriteList->DeleteAllSprite(true);//删除所有子弹和地方战机
    cout<<"gameover"<<endl;
}

void CGameMain::OnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
    // 按下空格，游戏开始
    if( KEY_SPACE == iKey && 0 == GetGameState() )
        {
            SetGameState( 1 );
        }

    if( 2 == GetGameState() ) //当游戏状态为2时
        {
            m_pMyFighter->OnMove(true,iKey);
           // cout<<"press"<<endl;
        }

        // 游戏进行中，按下空格发射子弹
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

	char	szName[MAX_NAME_LEN];// MAX_NAME_LE为CommonClass.h中宏定义 值为128
	sprintf( szName, "Bullet_%d", m_iCreatedSpriteCount );//按照 Bullet_%d 的格式将字符串写入 szName
	m_iCreatedSpriteCount++;
	CBullet *pBullet = new CBullet(iType,iEnemySize,szName);
	if(iEnemySize==1)
        pBullet->CloneSprite( "Bullet1_Template" );
    else
        pBullet->CloneSprite( "Bullet2_Template" );

	pBullet->SetSpritePosition( fPosX, fPosY );
	pBullet->SetSpriteLinearVelocityX( 60 );
    pBullet->SetSpriteWorldLimit(WORLD_LIMIT_NULL,//左，上，右，下
                                 CSystem::GetScreenLeft()-10.f,CSystem::GetScreenTop(),
                                 CSystem::GetScreenRight() + 200.f, CSystem::GetScreenBottom());
    AddSprite( pBullet );//加入精灵链表
    //pBullet->SetDamage(100);
    //pBullet->SetHp(100);
    if( 1 == iType ) //如果iType值为1，则说明子弹为敌方战机反射。
	{
		pBullet->SetSpriteLinearVelocityX( -30 );

	}
	else    //其他情况说明为我方战机反射
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
    //我方战机和子弹（1）碰撞
    if(szSrcName[0]=='B'&&szTarName[0]=='C'||szSrcName[0]=='C'&&szTarName[0]=='B')
    {
        ;
    }
    //我方战机与敌方战机

    //子弹（0）与敌方战机
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
    if((szName[0]=='H'||szName[0]=='B')&&iColSide==0)//左边
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
        cout<<"玩家战机被删除"<<endl;
	return ( m_pMyFighter ? m_pMyFighter->IsDead() : false );
}


